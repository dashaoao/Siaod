#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string> 
#include <algorithm>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <random>

#include <chrono>
#include <iomanip>


using namespace std;

struct comp_reg
{
	int lic_num;
	int position = -1;
};

class HashTable {
public:
	int size = 10;
	int n = 0;
	vector<list<comp_reg>> table;

	HashTable() {
		table.resize(size);
	}

	~HashTable() {
		size = 0;
		n = 0;
		for (auto it = table.begin(); it != table.end(); it++) {
			(*it).clear();
		}
		table.clear();
	}

	void push(comp_reg new_node) {
		int hash = this->hash(new_node);
		table[hash].push_front(new_node);
		n++;
		if (isOverflow()) {
			rehash();
		}
	}

	void pop(int lic_num) {
		int hash = this->hash(lic_num);
		for (auto it = table[hash].begin(); it != table[hash].end(); it++) {
			if ((*it).lic_num == lic_num) {
				pos((*it).position);
				table[hash].erase(it);
				break;
			}
		}
		n--;
	}

	void pos(int key) {
		for (int i = 0; i < size; i++)
		{
			if (!table[i].empty()) {
				for (auto it = table[i].begin(); it != table[i].end(); it++) {
					if ((*it).position > key) {
						(*it).position--;
					}
				}
			}
		}
	}

	int find(int lic_num) {
		int hash = this->hash(lic_num);
		auto start_time = chrono::high_resolution_clock::now();
		for (auto it = table[hash].begin(); it != table[hash].end(); it++) {
			if ((*it).lic_num == lic_num) {
				auto end_time = chrono::high_resolution_clock::now();
				chrono::duration<double>search_time = end_time - start_time;
				cout << "Время поиска по таблице:" << fixed << setprecision(9) << search_time.count() << endl;
				return (*it).position;
				break;
			}
		}
	}

	void output() {
		cout << "\n\t\tТАБЛИЦА" << endl;
		for (int i = 0; i < this->table.size(); i++) {
			cout << i << " - ";
			if (!table[i].empty()) {
				for (auto it = table[i].begin(); it != table[i].end(); it++) {
					cout << (*it).lic_num << " " << (*it).position << ";\t";
				}
			}
			cout << endl;
		}
	}

private:

	bool isOverflow() {
		return ((double)n / size) > 0.75 ? true : false;
	}

	int hash(comp_reg node) {
		return node.lic_num % this->size;
	}
	int hash(int lic_num) {
		return lic_num % this->size;
	}

	void rehash() {
		cout << "\n\t\tРЕХЕШИРОВАНИЕ ТАБЛИЦЫ" << endl;
		this->n = 0;
		vector<list<comp_reg>> temp(table);
		this->size *= 2;
		table.clear();
		table.resize(this->size);
		for (int i = 0; i < this->size / 2; i++) {
			while (!(temp[i].empty())) {
				this->push(temp[i].front());
				temp[i].pop_front();
			}
		}
		temp.clear();
	}
};




class File {
	ifstream IFile;
	ofstream OFile;
	HashTable* hashTable;
	int position = 0;

public:
	File(string path) {
		OFile.open(path, ios::app);
		hashTable = new HashTable();
		fillTable();
	}
	~File() {
		delete hashTable;
		IFile.close();
		OFile.close();
		position = 0;
	}

	void find(int pos) {
		string str;
		int count = -1;
		IFile.open("test_pw4_1000.txt");
		auto start_time = chrono::high_resolution_clock::now();
		cin.ignore();
		while (count != pos) {
			getline(IFile, str);
			count++;
		}
		auto end_time = chrono::high_resolution_clock::now();
		chrono::duration<double>search_time = end_time - start_time;
		cout << "Время поиска по файлу:" << fixed << setprecision(9) << search_time.count() << endl;
		cout << "Запись:\t" << str << endl << endl;
		IFile.close();
	}

	int find_2(int key) {
		return this->hashTable->find(key);
	}

	void push(comp_reg new_node, string name, string founder) {
		new_node.position = position;
		this->position++;
		this->hashTable->push(new_node);
		OFile << new_node.lic_num << " " << name << " " << founder << endl;
	}

	void output() {
		this->hashTable->output();
	}

	void pop(int key) {
		string str;
		vector<string> coll;
		IFile.open("test_pw4_1000.txt");
		cin.ignore();
		if (IFile.is_open())
		{
			while (getline(IFile, str)) {
				coll.push_back(str);
			}
		}

		for (int i = 0; i < coll.size(); i++)
		{
			if (coll[i].substr(0, 6) == to_string(key))
				coll.erase(coll.begin() + i);
		}

		IFile.close();
		OFile.close();
		remove("test_pw4_1000.txt");

		IFile.open("test_pw4_1000_1.txt");
		OFile.open("test_pw4_1000_1.txt", ios::app);

		for (int j = 0; j < coll.size(); j++) {
			OFile << coll[j] << endl;
		}
		coll.clear();

		IFile.close();
		OFile.close();

		rename("test_pw4_1000_1.txt", "test_pw4_1000.txt");

		OFile.open("test_pw4_1000.txt", ios::app);

		hashTable->pop(key);
		position--;
	}

	int random() {
		return rand() % 900000 + 100000;
	}

	void fill_file(comp_reg node) {
		string name = "something", founder = "someone";
		int key;
		srand(time(0));
		for (int i = 0; i < 1000; i++)
		{
			key = random();
			node = { key };
			node.position = position;
			this->position++;
			this->hashTable->push(node);
			OFile << node.lic_num << " " << name << " " << founder << endl;
		}
	}

private:
	void fillTable() {
		int buff;
		string name, founder;
		IFile.open("test_pw4_1000.txt");
		while (IFile >> buff) {
			comp_reg* node = new comp_reg();
			IFile >> name;
			IFile >> founder;
			node->lic_num = buff;
			node->position = position;
			position++;
			this->hashTable->push(*node);
		}
		IFile.close();
	}
};
void choice() {
	cout << endl << "Выберете действие: " << endl
		<< "1 - вставить запись в таблицу" << endl
		<< "2 - удалить запись из таблицы" << endl
		<< "3 - найти запись по ключу" << endl
		<< "4 - вывести таблицу (номера лицензии + список индексов)" << endl
		<< "5 - добавить в файл и таблицу 1000 записей" << endl
		<< "6 - завершить работу" << endl
		<< "Действие\t-\t";
}
void main1() {
	setlocale(LC_ALL, "RUS");
	cout << "Начало работы" << endl;
	File* file = new File("test_pw4_1000.txt");
	int key;
	string n, f;
	int action = 0;
	while (action != 6) {
		choice();
		cin >> action;
		switch (action) {
		case 1:
		{
			cout << "Введите номер лицензии:\t";
			cin >> key;
			cout << "Введите название:\t";
			cin >> n;
			cout << "Введите учредителя:\t";
			cin >> f;
			comp_reg node = { key };
			file->push(node, n, f);
			cout << "Запись добавлена." << endl;
			break;
		}
		case 2:
		{
			cout << "Введите номер лицензии для удаления:\t";
			cin >> key;
			file->pop(key);
			cout << "Запись удалена." << endl;
			break;
		}
		case 3:
		{
			cout << "Введите номер лицензии для поиска:\t";
			cin >> key;
			file->find(file->find_2(key));
			break;
		}
		case 4:
		{
			file->output();
			break;
		}
		case 5:
		{
			comp_reg node;
			file->fill_file(node);
			break;
		}
		case 6:
			break;
		}
	}
}
