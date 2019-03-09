#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Guest {
private:
	int size;
public:
	Guest(int size = 1) {
		this->size = size;//в скобках указание значения по умолчанию
	}
	int getSize() const { //тк не меняем состояние
		return this->size;
	}
};

class Table {

private:
	Guest g;
	bool isFree;
	int capability;
	int freeSeats;
	int notFreeSeats;
	string name;

public:
	Table(int capability,string name): isFree(true), freeSeats(capability), notFreeSeats(0), name(name){
		this->capability = capability;
		cout << "create table with capacity = " << this->capability << endl;
	}
	
	bool IsFree() {
		return this->isFree;
	}
	int getSizeT() {
		return capability;
	}
	void sitDown(Guest g) {
		this->g = g;
		this->isFree = false;
		this->notFreeSeats = g.getSize();
		this->freeSeats = this->capability - g.getSize();
		cout << "table "<<name<< " occupied with number of guests = " << g.getSize() << endl;
	}
	void leaveOut(Guest g) {
		this->g = NULL;
		this->isFree = true;
		this->notFreeSeats = 0;
		this->freeSeats = capability;
	}
	void printInfo() {
		cout << "Table name:" << this->name << " capability:" << this->capability
			<< " freeSeats:" << this->freeSeats << " occupied:" << !this->isFree<< endl;
	};
	int guestSize() {
		return g.getSize();
	}
};

class Manager {
private:
	int maxsizeT;
	std::vector<Table> tables;
	std::vector<Guest> guestQueue;
	std::vector<int> tableSizes;
public:
	Manager(std::vector<Table> tables): maxsizeT(0) {
		this->tables = tables;
		std::vector<Table>::iterator it_tbl1 = this->tables.begin();
		for (;it_tbl1 != this->tables.end();it_tbl1++) {
			if (it_tbl1->getSizeT() >= maxsizeT) {
				maxsizeT = it_tbl1->getSizeT();
				tableSizes.push_back(it_tbl1->getSizeT());
			}
		}
	}
	void printInfo() {
		cout << "Tables:" << endl;
		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (;it_tbl != this->tables.end();it_tbl++) {
			it_tbl->printInfo();// or (*it_tbl).printInfo();
		}
		if (!(guestQueue.empty())) {
			cout << "Current queue:";
			std::vector<Guest>::iterator it_gq = this->guestQueue.begin();
			for (;it_gq != this->guestQueue.end();it_gq++) {
				cout<< " " << it_gq->getSize();
			}
		}
	}
	bool onArrive(Guest g) {
		bool timeToBreak = false;
		bool guestToQueue = true;
		int minSize = g.getSize();
		if (g.getSize() > maxsizeT) {
			return false;
		}
		for (int i = g.getSize();i <= maxsizeT;i++) {
			if (timeToBreak) {
				break;
			}
			std::vector<Table>::iterator it_tbl = this->tables.begin();
			for (;it_tbl != this->tables.end();it_tbl++) {
				if (it_tbl->getSizeT() == i && it_tbl->IsFree()) {
					it_tbl->sitDown(g);
					guestToQueue = false;
					timeToBreak = true;
				}
				if (timeToBreak) {
					break;
				}
			}
		}
		if (guestToQueue) {
			guestQueue.push_back(g);
		}
		//check if there is free one
		//place a guest
		//if no free - move it to a queue 
	}
};

int main()
{
	Table t1(5,"1st");
	Table t2(3,"2nd"); 
	Table t3(7,"3rd");

	std::vector<Table> tables = { t1,t2,t3 };
	Manager *rest = new Manager(tables);
	rest->printInfo();

	const Guest g1(4);
	const Guest g2(4);
	const Guest g3(1);
	const Guest g4(3);
	const Guest g5(2);
	const Guest g6(6);

	rest->onArrive(g1);
	rest->onArrive(g2);
	rest->onArrive(g3);
	rest->onArrive(g4);
	rest->onArrive(g5);
	rest->onArrive(g6);
	rest->printInfo();
}
