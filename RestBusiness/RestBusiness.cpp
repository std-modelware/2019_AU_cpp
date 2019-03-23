// RestBusiness.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Guest {

private:
	int size;
	string name;
public:
	Guest(int size = 1, string name = "Alice") {
		this->size = size;
		this->name = name;
	}

	int getSize() const {
		return this->size;
	}
	string getName() const {
		return this->name;
	}

	bool operator == (const Guest &other) const {
		return this->name == other.getName();
	}
};

class Table {

private:
	std::vector<Guest> guestsOn;
	int capability;
	int freeSeats;
	std::string name;

public:
	Table(int capability, std::string name): name(name){
		this->capability = capability;
		this->freeSeats = this->capability;
		cout << "create table with capacity = " << this->capability << endl;
	}

	void sitDown(Guest g) {
		this->freeSeats = this->freeSeats - g.getSize();
		guestsOn.push_back(g);
	}

	void printInfo() {
		std::cout << "name table = " << this->name << ", capability = " << capability <<
			", freeSeats = " << this->freeSeats << std::endl;
	}
	int getSizeT() {
		return this->freeSeats;
	}
	int getCapability() {
		return this->capability;
	}
	int guestSize() { 
		int size = 0;
		std::vector<Guest>::iterator it_g = this->guestsOn.begin();
		for (;it_g != this->guestsOn.end();it_g++) {
			size += it_g->getSize();
		}
		return size;
	}
	bool tableLeave(Guest g) {
		std::vector<Guest>::iterator it_g = find(this->guestsOn.begin(), this->guestsOn.end(), g);
		if (it_g == this->guestsOn.end()) return false;
		this->freeSeats += g.getSize();
		this->guestsOn.erase(it_g);
		return true;
	}
};

class RestourantManager {
private:
	int maxsizeT;
	std::vector<Table> tables;
	std::vector<Guest> guestQueue;
public:
	RestourantManager(std::vector<Table> tables) : maxsizeT(0) {
		this->tables = tables;
		std::vector<Table>::iterator it_tbl1 = this->tables.begin();
		for (;it_tbl1 != this->tables.end();it_tbl1++) {
			if (it_tbl1->getSizeT() >= this->maxsizeT) {
				this->maxsizeT = it_tbl1->getSizeT();
			}
		}
	}

	bool onArrive(Guest g) {
		if (g.getSize() > this->maxsizeT) {
			return false;
		}
		std::vector<Table>::iterator it_tbl2 = this->tables.begin();
		for (int i = g.getSize();i <= this->maxsizeT;i++) {
			for (it_tbl2 = this->tables.begin();it_tbl2 != this->tables.end();it_tbl2++) {
				if (it_tbl2->getSizeT() == it_tbl2->getCapability() && i == it_tbl2->getSizeT()) {
					it_tbl2->sitDown(g);
					return true;
				}
			}
		}
		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (int i = g.getSize();i <= this->maxsizeT;i++) {
			for (it_tbl = this->tables.begin();it_tbl != this->tables.end();it_tbl++) {
				if (it_tbl->getSizeT() == i) {
					it_tbl->sitDown(g);
					return true;
				}
			}
		}
		guestQueue.push_back(g);
		return false;
	}
	bool onLeave(Guest g) {
		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (;it_tbl != this->tables.end();it_tbl++) {
				if (it_tbl->tableLeave(g)) {
					std::vector<Table>::iterator it_tbl1 = this->tables.begin();
					for (;it_tbl1 != this->tables.end();it_tbl1++) {
						if (it_tbl1->getSizeT() >= this->maxsizeT) {
							this->maxsizeT = it_tbl1->getSizeT();
						}
					}
					for (int j = it_tbl->getSizeT();j >= 0;j--) {
						std::vector<Guest>::iterator g1 = this->guestQueue.begin();
						for (;g1 != this->guestQueue.end();g1++) {
							if (g1->getSize() == j) {
								if (onArrive((*g1))) {
									guestQueue.erase(g1);
									return true;
								}
							}
						}
					}
					return true;
				}
			}
			return false;
		}

	void getInfo() {
		std::cout << ">TABLES" << std::endl;

		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			it_tbl->printInfo();
//			(*it_tbl).printInfo();
		}
		if (!(guestQueue.empty())) {
			cout << "Current queue: ";
			std::vector<Guest>::iterator it_gq = this->guestQueue.begin();
			for (;it_gq != this->guestQueue.end();it_gq++) {
				cout <<it_gq->getSize()<<" ";
			}
			cout << endl;
		}
	}
};

int main()
{
	Table t1(5, "1st");
	Table t2(3, "2nd");
	Table t3(7, "3rd");

	std::vector<Table> tables = { t1,t2,t3 };
	RestourantManager *rest = new RestourantManager(tables);

	Guest g1(4,"a");
	Guest g2(4,"b");
	Guest g3(1,"c");
	Guest g4(3,"d");
	Guest g5(2,"e");
	Guest g6(6,"f");
	Guest g7(3,"g");

	rest->onArrive(g1);
	rest->onArrive(g2);
	rest->onArrive(g3);
	rest->onArrive(g4);
	rest->onArrive(g5);
	rest->onArrive(g6);
	rest->onArrive(g7);
	rest->getInfo();
	rest->onLeave(g1);
	rest->getInfo();
}
