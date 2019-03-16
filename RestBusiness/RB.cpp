// RB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <sstream>
#include <map>

using namespace std;

class Guest {

private:
	int size;
	int name;

public:
	Guest(int size = 1) {
		static int s_quanity = 0; //number of guests
		this->size = size;
		this->name = ++s_quanity;
	};

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
	vector<Guest*> guests; //имена гостей, которые занимают этот столик.

public:
	Table(int capability, string name) : isFree(true), name(name), capability(capability) {
		this->notFreeSeats = 0;
		this->freeSeats = this->capability;
		cout << "create table with capability = " << this->capability << endl;
	};

	bool IsFree() const {
		return this->isFree;
	}

	bool sitDown(Guest g) {
		if (g.getSize() > this->freeSeats) return false;
		this->isFree = false;
		this->notFreeSeats += g.getSize();
		this->freeSeats -= g.getSize();
		(this->guests).push_back(&g);
		cout << "table " << this->name << " was occupied by group " << g.getName() <<
			" with size " << g.getSize() << endl;
		return true;
	}

	bool standUp(Guest g) {
		vector<Guest*>::iterator res = find(this->guests.begin(), this->guests.end(), &g);
		if (res == this->guests.end()) return false;
		this->notFreeSeats -= g.getSize();
		this->freeSeats += g.getSize();
		if (this->freeSeats == this->capability) this->isFree = true;
		this->guests.erase(res);
		cout << "group " << g.getName() << " left table " << name << endl;
		return true;
	}

	int getSize() const {
		return this->capability;
	}

	int getSeats() const {
		return this->freeSeats;
	}

	void printInfo() {
		cout << "name table = " << this->name;
		if (isFree == false) {
			cout << "; this table is occupied by groups:";
			for (Guest* k : this->guests) {
				cout << " " << k->getName(); ///////////////////????????????
			}
		}
		cout << "; capability = " << capability <<
			", freeSeats = " << this->freeSeats << endl;

	}
};


class RestaurantManager {
private:
	vector<Table*> tables;
	vector<Guest> guestQueue;
	int maxSize = 1;
	map<Guest*, Table*> plan;
	int quanity = 0; //numer of guests by this time
public:
	RestaurantManager(vector<Table*> tables) {
		this->tables = tables;
		vector<Table*>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if (maxSize < (*it_tbl)->getSize()) {
				maxSize = (*it_tbl)->getSize();
			}
			++quanity;
		};

	}


	bool Bye(Guest g) {
		Table* tt;
		for (vector<Table*>::iterator t = this->tables.begin(); t != this->tables.end(); t++) {
			if ((*t)->standUp(g) == true) {
				tt = *t;
				for (vector<Guest>::iterator g_fromQ = guestQueue.begin(); g_fromQ != guestQueue.end(); g_fromQ++) {
					if (g_fromQ->getSize() <= tt->getSize()) {
						tt->sitDown(*g_fromQ); //первый гость в очереди с размером не больше стола может сесть
					};
					return true;
				};
			};
			return false;
		};
	}


	bool onArrive(Guest g) {

		if (maxSize < g.getSize()) {
			cout << "We haven't got such big tables" << endl;
			return false;
		};

		bool p = false;
		bool p2 = false;
		static Table* nf_table;
		vector<Table*>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if ((*it_tbl)->getSeats() >= g.getSize()) {
				p = true;
				if ((*it_tbl)->IsFree() == true) {
					(*it_tbl)->sitDown(g);
					break;
					};
				if (p2 != true) {
					nf_table = *it_tbl;/* первый достаточно пустой столик запоминается на случай 
									   отсутствия полностью свободного столика*/
					p2 = true;
				};
			};
		};
		if (p2 == true) {
			nf_table->sitDown(g);
			
		};
		if (p == false) { guestQueue.push_back(g); return false; };

		return true;
	}

	void printInfo() {
		cout << endl << ">TABLES" << endl << "maximum Size = " << maxSize << endl;

		vector<Table*>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			(*it_tbl)->printInfo();
		}

		int i = 1;
		cout << '<' << endl;
		cout << endl << ">Guest queue" << endl;
		for (vector<Guest>::iterator group = guestQueue.begin(); group != guestQueue.end(); group++) {
			cout << '№' << i << ' ' << "group " << group->getName() << " with " << group->getSize() << " people" << endl;
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
	Guest g2(2);
	Guest g3(5), g4(4), g5(2), g6(2);
	t3.sitDown(g2);
	rest->onArrive(g1);
	rest->onArrive(g2);
	rest->onArrive(g3);
	rest->onArrive(g4);
	rest->Bye(g2);
	rest->onArrive(g5);
	rest->onArrive(g6);
	rest->printInfo();
	
}
