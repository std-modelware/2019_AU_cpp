// RestBusiness.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class Table;

class Guest {

private:
	int size;
	string name;

public:
	Guest(int size = 1, string name = "unnamed") {
		this->size = size;
		this->name = name;
	}

	int getSize() const {
		return this->size;
	}

	string Name() const {
		return this->name;
	}
};

class Table {

private:
	bool isFree;
	int capability;
	int notFreeSeats;
	int freeSeats;
	std::string name;
	std::vector<Guest> guests;

public:
	Table(int capability, std::string name) : name(name), isFree(true) {
		this->capability = capability;
		this->notFreeSeats = 0;
		this->freeSeats = this->capability;
		cout << "create table with capacity = " << this->capability << endl;
	}

	bool IsFree() const {
		return this->isFree;
	}

	int Size() const {
		return this->capability;
	}

	bool sitDown(Guest g) {

		int gSize = g.getSize();

		if (this->freeSeats < gSize) return false;
		this->freeSeats -= gSize;
		this->guests.push_back(g);
		cout << "table was occupied by group " << g.Name() << " with size " << g.getSize() << endl;
		return true;
	}

	bool standUp(Guest g) {
		std::vector<Guest>::iterator res = std::find(this->guests.begin(), this->guests.end(), g);

		if (res == this->guests.end()) return false;
		this->freeSeats += res->getSize();
		this->guests.erase(res);
		return true;
	}

	int getFreeSeats() const {
		return this->freeSeats;
	}

	string Name() const {
		return this->name;
	}

	void printInfo() {
		std::cout << "name table = " << this->name << ", capability = " << capability <<
			", freeSeats = " << this->freeSeats << std::endl;
	}
};

class RestourantManager {
private:
	std::vector<Table> tables;
	std::vector<Guest> guestQueue;
	int maxSize;
public:
	RestourantManager(std::vector<Table> tables) {
		this->tables = tables;
		this->maxSize = 0;
	}
	
	void checkMaxSize() {
		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if (it_tbl->Size() > this->maxSize) this->maxSize = it_tbl->Size();
		}
	}

	bool onArrive(Guest g) {
		if (g.getSize() > this->maxSize) {
			std::cout << "Guest with size" << g.getSize() << "left" << std::endl;
			return false;
		}

		string free_tbl = "";
		string occup_tbl;
		int free_size = this->maxSize;
		int occup_size = this->maxSize;

		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if ((it_tbl->IsFree) && (it_tbl->Size < g.getSize)) {
				if (free_tbl == "") {
					free_tbl = it_tbl->Name;
					free_size = it_tbl->Size;
				}
				else {
					if (free_size > it_tbl->Size) {
						free_tbl = it_tbl->Name;
						free_size = it_tbl->Size;
					}
				}
			}
			else if (it_tbl->getFreeSeats >= g.getSize) {
				if (occup_tbl == "") {
					occup_tbl = it_tbl->Name;
					occup_size = it_tbl->getFreeSeats;
				}
				else {
					if (occup_size > it_tbl->getFreeSeats) {
						occup_tbl = it_tbl->Name;
						occup_size = it_tbl->getFreeSeats;
					}
				}
			}
		}

		if (free_tbl == "") {
			std::vector<Table>::iterator it_tbl = this->tables.begin();
			for (; it_tbl != this->tables.end(); it_tbl++) {
				if (it_tbl->Name == occup_tbl) {
					it_tbl->sitDown(g);
					return true;
				}
			}

		}
		else {
			std::vector<Table>::iterator it_tbl = this->tables.begin();
			for (; it_tbl != this->tables.end(); it_tbl++) {
				if (it_tbl->Name == free_tbl) {
					it_tbl->sitDown(g);
					return true;
					break;
				}
			}
		}

		this->guestQueue.push_back(g);
		this->checkMaxSize();
		return false;
	}

	void onLeave(Guest g) {
		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			it_tbl->standUp(g);
		}
	}

	void printInfo() {
		std::cout << ">TABLES" << std::endl;

		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			it_tbl->printInfo();
		}

		std::cout << ">QUEUE" << std::endl;
		std::vector<Guest>::iterator it_guest = this->guestQueue.begin();
		for (; it_guest != this->guestQueue.end(); it_guest++) {
			std::cout << "Guest with size " << it_guest->getSize() << std::endl;
		}
	}
};

int main()
{
	Table t1(2, "first");
	Table t2(3, "second");
	Table t3(4, "third");

	std::vector<Table> tables = { t1, t2, t3 };
	RestourantManager *rest = new RestourantManager(tables);
	rest->printInfo();

	Guest g1;
	Guest g2(2);

	rest->onArrive(g1);
	//	t1.sitDown(g1);
	rest->onLeave(g1);

	std::cout << "t1 isFree()=" << t1.IsFree() << std::endl;
}