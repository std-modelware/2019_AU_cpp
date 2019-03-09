#include "pch.h"
#include <iostream> //стандартная библиотека для потоков вывода
#include <vector>
#include <string>

using namespace std;

class Guest {

private:
	int size;

public:
	Guest(int size = 1){
		this->size = size;
	}

	int getSize() const{ //const - функция не меняет состояние объекта. Такие функции называются getter'ы. Остальные - setter'ы.
		return this->size;
	}
};

class Table {

private:				//не видно вне класса
	bool isFree;		//занят или нет
	int capability;		//количество мест
	int notFreeSeats;	//кол-во занятых мест
	int freeSeats;		//кол-во свободных мест
	std::string name;
	
public:					//видно вне класса
	Table(int capability, std::string name):isFree(true), name(name) {
		//this->isFree = true; //сам сразу заполняет 
		this->capability = capability;
		this->notFreeSeats = 0;
		this->freeSeats = this->capability;
		cout << "Create table with capacity " << this->capability << endl;
	}

	int FreeSeats() {
		return this->freeSeats;
	}
	
	bool IsFree() const{
		return this->isFree;
	}

	void sitDown(Guest g) {
		this->isFree = false;
		this->notFreeSeats = g.getSize();
		this->freeSeats = this->capability - this->notFreeSeats;
		cout << "Table was occupired with size " << this->notFreeSeats << endl;
	}

	void printInfo() {
		cout << "name table = " << this->name << ", capability = " << capability << ", freeSeats = " << this->freeSeats << endl;
	}
};

class RestourantManager {		//RM
private:
	vector<Table> tables;
	vector<Guest> questQueue;
public:
	RestourantManager(vector<Table> tables) {
		this->tables = tables;
	}

	bool onArrive(Guest g) {
		Table* minsize;
		bool t = false;
		vector<Table>::iterator it_tbl = this->tables.begin();
		
		for (; it_tbl != this->tables.end(); it_tbl++) {
			if ( it_tbl->FreeSeats() >= g.getSize() )
			{
				return false;
			}
		}

		//1) проверить что сущ. столик, за который может сесть гость. Если такого столика нет - отказ.
		//2) есть ли свободный столик, куда влезет гость?
			//2.1) если есть, усадить туда гостя
			//2.2) если столик не найден, добавляем гостя в очередь 
		this->questQueue.push_back(g);
		return false;
	}

	void printInfo() {
		cout << ">TABLES" << endl;

		vector<Table>::iterator it_tbl = this->tables.begin();
		for (; it_tbl != this->tables.end(); it_tbl++) {
			it_tbl->printInfo();
		}
	}

};

int main()
{
	Table t1(2, "First");
	Table t2(3, "Second");
	Table t3(4, "Third");

	vector<Table> tables = { t1, t2, t3 };
	RestourantManager *rest = new RestourantManager(tables);
	rest->printInfo();

	Guest g1;
	Guest g2(2);

	t1.sitDown(g1);
	cout << "t1 isFree()=" << t1.IsFree() << endl;
}