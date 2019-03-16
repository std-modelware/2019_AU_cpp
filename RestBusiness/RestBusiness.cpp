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
	//Table* place;

public:
	Guest(int size = 1) {
		this->size = size;
		//this->place = NULL;
	}

	int getSize() const {
		return this->size;
	}

/*	Table table() {
		return *this->place;
	} 

	void sitDown(Table tbl) {
		if (this->place == NULL) this->place = &tbl;
	}

	void standUp(Table tbl) {
		if (this->place == &tbl) this->place = NULL;
	} */
};

class Table {

private:
	bool isFree; // занят столик или нет
	int capability;
	int notFreeSeats;
	int freeSeats;
	std::string name;

	std::vector<Guest> guests;

public:
	Table(int capability, std::string name) : name(name), isFree(true) {
		//this->isFree = true;
		this->capability = capability;
		this->notFreeSeats = 0;
		this->freeSeats = this->capability;
		cout << "create table with capacity = " << this->capability << endl;
	}

	bool IsFree() const {
		return this->isFree;
	}

	bool sitDown(Guest g) {

		int gSize = g.getSize();

		if (this->freeSeats < gSize) return false;
		//g.sitDown(*this);
		this->freeSeats -= gSize;
		this->guests.push_back(g);
		cout << "table was occupied by group with size = " << g.getSize() << endl;
		return true;
	}

	bool standUp(Guest g) {
		std::vector<Guest>::iterator res = std::find(this->guests.begin(), this->guests.end(), g);

		if (res == this->guests.end()) return false;
		//g.standUp(*this);
		this->freeSeats += res->getSize();
		this->guests.erase(res);
		return true;
	}

	int getFreeSeats() const {
		return this->freeSeats;
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

	void checkMaxSize() {
		std::vector<Guest>::iterator it_guest = this->guestQueue.begin();
		for (; it_guest != this->guestQueue.end(); it_guest++) {
			if (it_guest->getSize() < this->maxSize) this->maxSize = it_guest->getSize();
		}
	}
public:
	RestourantManager(std::vector<Table> tables) {
		this->tables = tables;
		this->maxSize = 0;
		this->checkMaxSize();
	}

	bool onArrive(Guest g) {
		// 1) проверить, что существует столик за который может сесть гость. Если столик не найден - отказ

		// 2) есть ли свободный столик, куда "влезет" гость
			// 2.1) если такой столик найден - сажаем туда гостя		
		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if (it_tbl->sitDown(g)) {
				return true;
			}
		}
		// 2.2) если столик не найден - добавляем гостя в очередь
		this->guestQueue.push_back(g);
		this->checkMaxSize();
		return false;
	}

	void onLeave(Guest g) {
		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if (it_tbl->standUp(g)) {
				it_tbl->standUp(g);
				break;
			}
		}
	}

	void printInfo() {
		std::cout << ">TABLES" << std::endl;

		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			it_tbl->printInfo();
			//			(*it_tbl).printInfo();
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
