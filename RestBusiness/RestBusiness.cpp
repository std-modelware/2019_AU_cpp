// Rest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class ClientsGroup
{
private:

	int size; // number of clients
	std::string name; // just for identification

public:

	ClientsGroup(int size, std::string name) {
		this->size = size;
		this->name = name;
		std::cout << "Create clients group with name = " << this->name << ", size = " << this->size << std::endl;
	}

	int getSize() {
		return this->size;
	}

	void printInfo() {
		std::cout << "group name = " << this->name << ", size = " << this->size << std::endl;
	}

	//bool operator==(const ClientsGroup& other) const {
	//	return this->name.compare(other.name);
	//}

	friend bool operator==(const ClientsGroup& lhs, const ClientsGroup& rhs);

};


inline bool operator==(const ClientsGroup& lhs, const ClientsGroup& rhs) {
	return lhs.name.compare(rhs.name) == 0;
}

class Table
{

private:
	int size; // number of chairs
	int freeSeats; // number of free chairs
	std::string name; // just for identification

	std::vector<ClientsGroup> groups; // clients groups on the table

public:
	Table(int size, std::string name) {
		this->size = size;
		this->freeSeats = size;
		this->name = name;
		std::cout << "Create table with name = " << this->name << ", size = " << this->size << std::endl;
	}

	// try sit down group in the table
	bool sitDown(ClientsGroup& group) {

		int gSize = group.getSize();

		if (this->freeSeats < gSize) {
			return false;
		}

		this->freeSeats -= gSize;
		this->groups.push_back(group);

		return true;
	}

	// group stands up (if it is possible)
	bool standUp(ClientsGroup& group) {
		std::vector<ClientsGroup>::iterator res = std::find(this->groups.begin(), this->groups.end(), group);

		if (res == this->groups.end()) {
			return false;
		}

		this->freeSeats += res->getSize();
		this->groups.erase(res);
		return true;
	}

	bool lookup(ClientsGroup& group) {
		std::vector<ClientsGroup>::iterator res = std::find(this->groups.begin(), this->groups.end(), group);
		return res != this->groups.end();
	}

	int getFreeSeats() {
		return this->freeSeats;
	}

	void printInfo() {
		std::cout << "==================" << std::endl;
		std::cout << "name = " << this->name << ", size = " << this->size << ", freeSeats = " << this->freeSeats << std::endl;

		std::vector<ClientsGroup>::iterator it = this->groups.begin();
		for (; it != this->groups.end(); it++)
		{
			it->printInfo();
		}
	}

	friend bool table_comp(const Table &a, const Table &b);

};

bool table_comp(const Table &t1, const Table &t2) {
	
	bool isT1Free = (t1.size == t1.freeSeats);
	bool isT2Free = (t2.size == t2.freeSeats);

	// both tables are free => compare size
	if (isT1Free && isT2Free) {
		return t1.size > t2.size;
	}

	// both tables are NOT free => compare freeSeats
	if (!isT1Free && !isT2Free) {

		// table with zero free seats - "down"
		//if (t2.freeSeats == 0) return false;
		//if (t1.freeSeats == 0) return true;

		return t1.freeSeats > t2.freeSeats;
	}

	// the only free table - "up"
	return isT2Free;
}

class RestaurantManager
{
private:
	std::vector<Table> tables;
	std::vector<ClientsGroup> clientsGroupQueue;

public:
	RestaurantManager(std::vector<Table> tables)
	{
		std::cout << "initialized RestManager with tables" << std::endl;
		this->tables = tables;
		std::sort(this->tables.begin(), this->tables.end(), table_comp);
	}

	// new client(s) show up
	void onArrive(ClientsGroup& group)
	{
		// search a fit table
		std::vector<Table>::iterator it = this->tables.begin();
		for (; it != this->tables.end(); it++) {
			if (it->getFreeSeats() >= group.getSize()) {
				it->sitDown(group);
				std::sort(this->tables.begin(), this->tables.end(), table_comp);
				return;
			}
		}

		// add to the queue
		this->clientsGroupQueue.push_back(group);
	}

	// client(s) leave, either served or simply abandoning the queue
	void onLeave(ClientsGroup& group)
	{
		// search a group on table
		std::vector<Table>::iterator it = this->tables.begin();
		for (; it != this->tables.end(); it++) {

			if (it->standUp(group)) { // if found => stand up
				std::sort(this->tables.begin(), this->tables.end(), table_comp);
				group.printInfo();
				std::cout << "Group stands up from table" << std::endl;
				this->manageQueue(); // try to free queue
				return;
			}
		}

		// group can be in the queue ...
		std::vector<ClientsGroup>::iterator res = std::find(this->clientsGroupQueue.begin(), this->clientsGroupQueue.end(), group);

		if (res == this->clientsGroupQueue.end()) {
			std::cout << "Group is not found" << std::endl;
			return;
		}

		this->clientsGroupQueue.erase(res);
		std::cout << "Group removed from queue" << std::endl;
	}


	// try to reduce queue (sit down groups)
	void manageQueue() {
		std::vector<ClientsGroup> processedGroups;

		std::vector<ClientsGroup>::iterator it = this->clientsGroupQueue.begin();
		for (; it != this->clientsGroupQueue.end(); it++) {

			std::vector<Table>::iterator it_tbl = this->tables.begin();
			for (; it_tbl != this->tables.end(); it_tbl++) {
				if (it_tbl->sitDown(*it)) { // if the group can sit down
					std::sort(this->tables.begin(), this->tables.end(), table_comp);
					processedGroups.push_back(*it);
					break;
				}
			}
		}

		// remove from the queue all sitting down groups
		it = processedGroups.begin();
		for (; it != processedGroups.end(); it++) {
			std::vector<ClientsGroup>::iterator res = std::find(this->clientsGroupQueue.begin(), this->clientsGroupQueue.end(), *it);

			if (res != this->clientsGroupQueue.end()) {
				this->clientsGroupQueue.erase(res);
			}
		}
	}

	void printInfo() {
		std::cout << "----------------" << std::endl;
		std::cout << ">Tables" << std::endl;

		std::vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			it_tbl->printInfo();
		}

		std::cout << ">Queue" << std::endl;
		std::cout << "==================" << std::endl;

		std::vector<ClientsGroup>::iterator it_queue = this->clientsGroupQueue.begin();
		for (; it_queue != this->clientsGroupQueue.end(); it_queue++) {
			it_queue->printInfo();
		}

		std::cout << "----------------" << std::endl;
	}

};

int main()
{

	Table t1(2, "t1");
	Table t2(2, "t2");
	Table t3(3, "t3");

	std::vector<Table> tables = { t1, t2, t3 };
	// std::sort(tables.begin(), tables.end(), table_comp);

	RestaurantManager *rest_mgr = new RestaurantManager(tables);
	rest_mgr->printInfo();

	std::cout << std::endl;
	ClientsGroup g1(2, "g1");
	rest_mgr->onArrive(g1);
	rest_mgr->printInfo();

	std::cout << std::endl;
	ClientsGroup g2(3, "g2");
	rest_mgr->onArrive(g2);
	rest_mgr->printInfo();

	std::cout << std::endl;
	ClientsGroup g3(3, "g3");
	rest_mgr->onArrive(g3);
	rest_mgr->printInfo();

	std::cout << std::endl;
	rest_mgr->onLeave(g2);
	rest_mgr->printInfo();

	std::cout << std::endl;
	rest_mgr->onLeave(g3);
	rest_mgr->printInfo();

	std::cout << std::endl;
	ClientsGroup g4(1, "g4");
	rest_mgr->onArrive(g4);
	rest_mgr->printInfo();

	std::cout << std::endl;
	ClientsGroup g5(1, "g5");
	rest_mgr->onArrive(g5);
	rest_mgr->printInfo();

	std::cout << std::endl;
	ClientsGroup g6(1, "g6");
	rest_mgr->onArrive(g6);
	rest_mgr->printInfo();

	std::cout << std::endl;
	rest_mgr->onLeave(g1);
	rest_mgr->printInfo();

	return 0;
}

