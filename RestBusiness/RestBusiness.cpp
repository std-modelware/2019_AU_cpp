// RestBusiness.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <random>
#include <limits>  
#include <set> 

using namespace std;

void printSep(int n){
	for (int i = 0; i<n; i++){
		cout << '=';
	}
	cout << endl;
}

class Guest {

private:
    int size;
    uint64_t uid;

public:
    Guest(int size = 1) {
        this->size = size;
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> dist(
        	numeric_limits<uint64_t>::min(), numeric_limits<uint64_t>::max());
        uid = dist(rng);
    }

    int getSize() const {
        return this->size;
    }

    uint64_t getUID() const {
    	return uid;
    }

    void printInfo(){
    	cout << "A group of " << size << " guests." << endl;
    }

    bool operator==(const Guest& g) const{
    	return uid == g.getUID();
    }
};

class Table {

private:
    bool isFree; // занят столик или нет
    int capacity;
    int notFreeSeats;
    string name;
    vector<Guest> guests;
    uint64_t uid;

public:
    Table(int capacity, string name) : name(name), isFree(true) {
        this->isFree = true;
        this->capacity = capacity;
        this->notFreeSeats = 0;
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> dist(
            numeric_limits<uint64_t>::min(), numeric_limits<uint64_t>::max());
        uid = dist(rng);
        cout << "create table with capacity = " << this->capacity << endl;
    }

    bool operator<(const Table& rhs) const {
        int lhs_cap = capacity - notFreeSeats;
        int rhs_cap = rhs.capacity - rhs.notFreeSeats;
        if (lhs_cap == rhs_cap){
            return uid < rhs.uid;
        }
        else{
            return lhs_cap > rhs_cap;
        }
    }

    bool IsFree() const{
        return this->isFree;
    }

    int getCapacity() const{
    	return capacity;
    }

    int getFreeCap() const{
    	return capacity - notFreeSeats;
    }

    bool sitDown(Guest g) {
    	if (g.getSize() > capacity - notFreeSeats){
    		return false;
    	}
        this->isFree = false;
        this->notFreeSeats += g.getSize();
        this->guests.push_back(g);
        cout << "Table \"" << name << "\" was occupied by group of size = " << g.getSize() << endl;
        return true;
    }

    bool sitDownCheck(const Guest g) const {
        if (g.getSize() > capacity - notFreeSeats){
            return false;
        }
        return true;
    }

    bool standUp(Guest g) {
    	vector<Guest>::iterator res = find(guests.begin(), guests.end(), g);
    	if (res == this->guests.end()){
    		return false;
    	}
    	notFreeSeats -= res->getSize();
    	guests.erase(res);
    	cout << "Table \"" << name << "\" was left by group of size = " << g.getSize() << endl;
    	return true;
    }

    bool standUpCheck(Guest g) const {
        vector<Guest>::const_iterator res = find(guests.begin(), guests.end(), g);
        if (res == this->guests.end()){
            return false;
        }
        return true;
    }

    void printInfo() const {
        cout << "Table \"" << name << "\", capacity = " << capacity << ", free seats = " << capacity - notFreeSeats << endl;
    }
};


class RestaurantManager {
private:
    deque<Guest> guestQueue;
    int maxCap;
    set<Table> tables;

public:
    RestaurantManager(set<Table> tables){
        this->tables = tables;
        updateCap();
        guestQueue = deque<Guest> ();
    }

    void updateCap(){
    	maxCap = tables.begin()->getFreeCap();
    }

    void printInfo() {
    	printSep(20);
        cout << "Tables:" << endl;
        for (set<Table>::iterator it = tables.begin(); it != tables.end(); it++){
            it->printInfo();
        }
        printSep(20);
        if (guestQueue.size() > 0){
        	cout << "The queue has " << guestQueue.size() << " groups of guests:" << endl;
        	for (deque<Guest>::iterator it = guestQueue.begin(); it != guestQueue.end(); it++){
        		it->printInfo();
        	}
        }
        else{
        	cout << "The queue is empty." << endl;
        }
        printSep(20);
    }
    bool onArrive(Guest g){

        // 1) проверить, что существует столик за который может сесть гость. Если столик не найден - отказ

		// 2) есть ли свободный столик, куда "влезет" гость
			// 2.1) если такой столик найден - сажаем туда гостя
		if (maxCap >= g.getSize()){		
			for (set<Table>::iterator it = tables.begin(); it != tables.end(); it++) {
				if (it->sitDownCheck(g)) {
                    Table tbl = *it;
                    tables.erase(it);
                    tbl.sitDown(g);
                    tables.insert(tbl);
					updateCap();
					return true;
				}
			}
		}
		else{
			// 2.2) если столик не найде - добавляем гостя в очередь
			this->guestQueue.push_back(g);
		}
	return false;
    }

    bool onLeave(Guest g){
    	for (set<Table>::iterator it = tables.begin(); it != tables.end(); it++) {
			if (it->standUpCheck(g)) {
                Table tbl = *it;
                tables.erase(it);
                tbl.standUp(g);
                tables.insert(tbl);
				updateCap();
				return true;
			}
		}
		return false;
    }
};


int main()
{
    Table t1(2, "Table 1");
    Table t2(3, "Table 2");
    Table t3(4, "Table 3");

    set<Table> tables = { t1, t2, t3 };
    RestaurantManager *rest = new RestaurantManager(tables);
    rest->printInfo();

    const Guest g1;
    const Guest g2(2);
    const Guest g3(2);
    const Guest g4(2);
    const Guest g5(2);

    rest->onArrive(g1);
    rest->onArrive(g2);
    rest->onArrive(g3);
    rest->onArrive(g4);
    rest->onArrive(g5);
    rest->printInfo();

    rest->onLeave(g4);
    rest->onLeave(g1);
    rest->onLeave(g2);
    rest->printInfo();


    cout << "t1 isFree()=" << t1.IsFree() << endl;
}
