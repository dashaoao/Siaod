#pragma once
#ifndef __BINAR_FILE_H__
#define __BINAR_FILE_H__
#include "business.h"
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class binar_file
{
public:

    void print_file(string name)
    {
        ifstream fb(name + ".dat", ios::binary);
        if (!fb.good())
        {
            cout << "Не получается открыть файл\n";
            return;
        }
        cout << "\t\t\t\t\tСОДЕРЖАНИЕ ФАЙЛА\n";
        business st;
        fb.read((char*)&st, sizeof(business));
        cout << setw(20) << "Название" << setw(20) << "Учредитель" << setw(20) << "Лицензия\n";
        while (fb.good())
        {
            cout << setw(20) << st.name << setw(20) << st.founder << setw(20) << st.license << endl;
            fb.read((char*)&st, sizeof(business));
        }
        cout << endl;
        fb.close();
    }

    bool text_to_binar(string textName, string name)
    {
        ofstream fb;
        fb.open(name + ".dat", ios::out | ios::binary);
        ifstream in(textName + ".txt", ios::in);
        if (!fb.good())
        {
            cout << "Не получается открыть бинарный файл\n";
            return false;
        }
        if (!in.good())
        {
            cout << "Не получается открыть текстовый файл\n";
            return false;
        }
        while (in.good())
        {
            business st;
            in >> st.license;
            in >> st.name;
            in >> st.founder;
            in.get();
            fb.write((char*)&st, sizeof(business));
        }
        fb.close();
        in.close();
        return true;
    }

    bool binar_to_text(string textName, string name)
    {
        ifstream fb;
        fb.open(name + ".dat", ios::binary);
        ofstream txt(textName + ".txt", ios::out);
        if (!fb.good())
        {
            cout << "Не получается открыть бинарный файл\n";
            return false;
        }
        if (!txt.good())
        {
            cout << "Не получается открыть текстовый файл\n";
            return false;
        }
        business st;
        fb.read((char*)&st, sizeof(business));
        txt << st.license << "\n" << st.name << "\n" << st.founder << "\n";
        fb.read((char*)&st, sizeof(business));
        while (fb.good())
        {
            txt << st.license << "\n" << st.name << "\n" << st.founder << "\n";
            fb.read((char*)&st, sizeof(business));
        }
        return true;
    }

    business get_by_index(string name, int index)
    {
        ifstream fb;
        business result;
        fb.open(name + ".dat", ios::binary);
        if (!fb.good())
        {
            cout << "Не получается открыть бинарный файл\n";
            result.name[0] = '0';
            return result;
        }
        if (fb.is_open())
        {
            while (fb.read((char*)&result, sizeof(business))) {
                if (stoi(result.license) == index) {
                    break;
                }
            }
        }
        fb.close();
        return result;
    }

    bool delete_by_index(string name, int index)
    {
        fstream fb;
        fb.open(name + ".dat", ios::out | ios::in | ios::binary);
        if (!fb.good())
        {
            cout << "Не получается открыть бинарный файл\n";
            return false;
        }
        business lastELement;
        fb.read((char*)&lastELement, sizeof(business));
        while (fb.good())
            fb.read((char*)&lastELement, sizeof(business));
        fb.close();
        fb.open(name + ".dat", ios::out | ios::in | ios::binary);
        fb.seekg(index * sizeof(business));
        fb.write((char*)&lastELement, sizeof(business));
        fb.close();
        return true;
    }

    bool delete_by_key(string name, string key)
    {
        fstream fb;
        fb.open(name + ".dat", ios::out | ios::in | ios::binary);
        if (!fb.good())
        {
            cout << "Не получается открыть бинарный файл\n";
            return false;
        }
        
		vector<business> coll;
        business result;
		if (fb.is_open())
		{
			while (fb.read((char*)&result, sizeof(business))) {
                coll.push_back(result);
                /*if (coll.size() > 1) {
                    if (stoi(coll[coll.size() - 1].license) == stoi(coll[coll.size() - 2].license)) {
                        coll.pop_back();
                        break;
                    }
                }*/
			}
		}
        fb.close();
        //string n = name + ".dat";
        //const char* n1 = name.c_str();
        //remove(n1);

        text_to_binar("test_empty", "test_pw41");
        print_file(name);
        fb.open(name + ".dat", ios::out | ios::in | ios::binary);
        for (int i = 0; i < coll.size(); i++)
        {
            if (stoi(coll[i].license) != stoi(key))
                fb.write((char*)&coll[i], sizeof(business));
        }
		fb.close();
        return true;
	}

    bool insert_element(string name, business st)
    {
        ofstream fb(name + ".dat", ios::app | ios::binary);
        if (!fb.good())
        {
            cout << "Не получается открыть бинарный файл\n";
            return false;
        }
        fb.write((char*)&st, sizeof(business));
        fb.close();
        return true;
    }
};
#endif