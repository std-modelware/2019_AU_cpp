// RestBuis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <map>

using namespace std;
int quanity = 0; //number of guests

class Guest {

private:
	int size;
	int name;

public:
	Guest(int size = 1) {
		this->size = size;
	};

	void call(int num) {
		name = num;
	}

	int getSize() const {
		return this->size;
	}

	int getName() const {
		return name;
	}
};


class Table {
private:
	bool isFree;
	int capability;
	int freeSeats;
	int notFreeSeats;
	string name;
	int guestName = 0; //имя гостя, который занимает этот столик.

public:
	Table(int capability, string name) : isFree(true), name(name), capability(capability) {
		this->notFreeSeats = 0;
		this->freeSeats = this->capability;
		cout << "create table with capability = " << this->capability << endl;
	};

	bool IsFree() const {
		return this->isFree;
	}

	void sitDown(Guest g) {
		this->isFree = false;
		this->notFreeSeats = g.getSize();
		this->freeSeats = capability - g.getSize();
		this->guestName = g.getName();
		cout << "table " << this->name << " was occupied by group " << g.getName() << " with size " << g.getSize() << endl;
	}

	void standUp(Guest g) {
		this->isFree = true;
		this->notFreeSeats -= g.getSize();
		this->freeSeats += g.getSize();
		this->guestName = 0;
		cout << "group " << guestName << " left table " << name << endl;
	}

	int getSize() const {
		return this->capability;
	}

	void printInfo() {
		cout << "name table = " << this->name;
		if (isFree == false) {
			cout << "; this table is occupied by group " << guestName;
		}
		cout << "; capability = " << capability <<
			", freeSeats = " << this->freeSeats << endl;

	}
};


class RestaurantManager {
private:
	vector<Table*> tables; //*
	vector<Guest> guestQueue;
	int maxSize = 1;
	map<Guest*, Table*> plan;

public:
	RestaurantManager(vector<Table*> tables) { //*
		this->tables = tables;
		vector<Table*>::iterator it_tbl = this->tables.begin(); //*
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if (maxSize < (*it_tbl)->getSize()) {
				maxSize = (*it_tbl)->getSize();
			}
		};

	}


	void Bye(Guest g) {
		plan[&g]->standUp(g);
		for (vector<Guest>::iterator group = guestQueue.begin(); group != guestQueue.end(); group++) {
			if (group->getSize() <= plan[&g]->getSize()) {
				plan[&g]->sitDown(*group) ; //первый гость в очереди с размером не больше стола может сесть
				plan.erase(&g);
			};
		};
	}


	bool onArrive(Guest g) {

		if (maxSize < g.getSize()) {
			cout << "We haven't got such big tables" << endl;
			return false;
		};

		g.call(++quanity);
		int p = 0;
		vector<Table*>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if ((*it_tbl)->getSize() >= g.getSize()) {
				if ((*it_tbl)->IsFree() == true) {
					(*it_tbl)->sitDown(g);
					plan[&g] = (*it_tbl);
					p = 1;
					break;
				};
			};
		};
		if (p == 0) { guestQueue.push_back(g); return false; };

		return true;
	}

	void printInfo() {
		cout <<endl << ">TABLES"<< endl << "maximum Size = " << maxSize << endl;

		vector<Table*>::iterator it_tbl = this->tables.begin(); //*
		for (; it_tbl != this->tables.end(); it_tbl++) {
			(*it_tbl)->printInfo();
		}

		int i = 1;
		cout << '<' << endl;
		cout <<endl << ">Guest queue" << endl;
		for (vector<Guest>::iterator group = guestQueue.begin(); group != guestQueue.end(); group++) {
			cout <<'№'<< i << ' ' << "group " << group->getName() << " with " << group->getSize() << " people" << endl;
			i++;
		};
		cout << '<' << endl;

		cout << "There were " << quanity << " guests today yet." << endl;
	}

};

int main()
{
	Table t1(2, "first");
	Table t2(3, "second");
	Table t3(4, "third");

	vector<Table*> tables = { &t1, &t2, &t3 }; //* , &
	RestaurantManager *rest = new RestaurantManager(tables);
	rest->printInfo();

	Guest g1;
	Guest g2(2), g3(5), g4(4), g5(2), g6(2);

	rest->onArrive(g1);
	rest->onArrive(g2);
	rest->onArrive(g3);
	rest->onArrive(g4);
	rest->Bye(g2);
	rest->onArrive(g5);
	rest->onArrive(g6);
	rest->printInfo();
}
