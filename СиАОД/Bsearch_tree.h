#ifndef __BSEARCH_TREE_H__
#define __BSEARCH_TREE_H__

#include "Tree_element.h"
#include <iostream>
#include <fstream>
#include "business.h"
#include "binar_file.h"

#include <time.h>
#include <stdio.h>
#include <random>
#include <chrono>

using namespace std;

class Bsearch_tree
{
private:
	string file_name;
	int size;
	Tree_element* root;

public:

	Bsearch_tree(string license)
	{
		Tree_element* el = new Tree_element(license);
		root = el;
		size = 1;
	}

	Bsearch_tree()
	{
		root = nullptr;
		size = 0;
	}

	void set_file_name(string file_name)
	{
		this->file_name = file_name;
	}

	void delete_tree(Tree_element* el)
	{
		if (el)
		{
			delete_tree(el->left);
			delete_tree(el->right);
			delete el;
		}
	}

	~Bsearch_tree()
	{
		delete_tree(root);
	}


	void print_tree()
	{
		if (size == 1)
			cout << root->license;
		else
			rec_print_tree(root, 0);
		cout << endl;
	}

	void rec_print_tree(Tree_element* el, int space = 0)
	{
		if (el)
		{
			if (el->right != nullptr)
				rec_print_tree(el->right, space + 1);
			for (int i = 0; i < space; i++)
				cout << "    ";
			cout << el->license << endl;
			if (el->left != nullptr)
				rec_print_tree(el->left, space + 1);
		}
	}

	business find(string key)
	{
		Tree_element* el = root;
		auto start_time = chrono::high_resolution_clock::now();
		while (el && stoi(el->license) != stoi(key))
		{
			if (stoi(el->license) > stoi(key))
				el = el->left;
			else
				el = el->right;
		}
		if (stoi(el->license) == stoi(key))
		{
			auto end_time = chrono::high_resolution_clock::now();
			chrono::duration<double>search_time = end_time - start_time;
			cout << "Время поиска по дереву:" << fixed << setprecision(9) << search_time.count() << endl;
			binar_file bin = binar_file();
			return bin.get_by_index(file_name, stoi(el->license));
		}

		business st = business();
		st.license[0] = '-';
		st.license[1] = '1';
		return st;
	}

	void insert(string license)
	{
		Tree_element* el = root;
		while (el && (stoi(el->license) != stoi(license)))
		{
			if (stoi(el->license) > stoi(license) && el->left == nullptr)
			{
				el->left = new Tree_element(license);
				++size;
				return;
			}
			if (stoi(el->license) < stoi(license) && el->right == nullptr)
			{
				el->right = new Tree_element(license);
				++size;
				return;
			}
			if (stoi(el->license) > stoi(license))
				el = el->left;
			else
				el = el->right;
		}
	}

	bool erase(string key)
	{
		Tree_element* el = root;
		Tree_element* parent = nullptr;
		while (el && stoi(el->license) != stoi(key))
		{
			parent = el;
			if (stoi(el->license) > stoi(key))
			{
				el = el->left;
			}
			else
			{
				el = el->right;
			}
		}
		if (!el)
			return false;
		binar_file bin = binar_file();
		bin.delete_by_key(file_name, el->license);

		if (el->left == nullptr)
		{
			if (parent && parent->left == el)
				parent->left = el->right;
			if (parent && parent->right == el)
				parent->right = el->right;
			--size;
			delete el;
			return true;
		}
		if (el->right == nullptr)
		{
			if (parent && parent->left == el)
				parent->left = el->left;
			if (parent && parent->right == el)
				parent->right = el->left;
			--size;
			delete el;
			return true;
		}
		Tree_element* replace = el->right;
		while (replace->left)
			replace = replace->left;
		string replace_data = replace->license;
		erase(replace_data);
		el->license = replace_data;
		return true;
	}

	string get_file_name()
	{
		return file_name;
	}

	bool build_tree(string fileName)
	{
		set_file_name(fileName);
		ifstream fb;
		fb.open(fileName + ".dat", ios::in | ios::binary);
		if (!fb.good())
		{
			return false;
		}
		business st;
		fb.read((char*)&st, sizeof(business));
		root = new Tree_element(st.license);
		size++;
		fb.read((char*)&st, sizeof(business));
		while (fb.good())
		{
			insert(st.license);
			fb.read((char*)&st, sizeof(business));
		}
		return true;
	}
};
#endif