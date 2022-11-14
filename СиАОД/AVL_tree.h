#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
using namespace std;
#include <iostream>
#include "AVL_element.h"
#include "business.h"
#include <fstream>
#include <stdio.h>

#include <time.h>
#include <stdio.h>
#include <random>
#include <chrono>

double turn = 0;

class AVL_tree
{
private:
	string file_name;
	AVL_element* root;

public:

	AVL_tree()
	{
		root = nullptr;
	}

	AVL_tree(string license)
	{
		AVL_element* el = new AVL_element(license);
		root = el;
	}

	void delete_tree(AVL_element* el)
	{
		if (el)
		{
			delete_tree(el->left);
			delete_tree(el->right);
			delete el;
		}
	}

	~AVL_tree()
	{
		delete_tree(root);
	}


	void rec_print_tree(AVL_element* el, int space)
	{
		if (el)
		{
			rec_print_tree(el->right, space + 1);
			for (int i = 0; i < space; i++)
				cout << "    ";
			cout << el->license << endl;
			rec_print_tree(el->left, space + 1);
		}
	}

	void print_tree()
	{
		rec_print_tree(root, 0);
		cout << endl;
	}

	AVL_element* rotate_right(AVL_element* el)
	{
		AVL_element* left_el = el->left;
		el->left = left_el->right;
		left_el->right = el;
		el->fix_height();
		left_el->fix_height();
		turn++;
		return left_el;
	}

	AVL_element* rotate_left(AVL_element* el)
	{
		AVL_element* right_el = el->right;
		el->right = right_el->left;
		right_el->left = el;
		el->fix_height();
		right_el->fix_height();
		turn++;
		return right_el;
	}

	AVL_element* balance(AVL_element* el)
	{
		//cout << el->license << " " << el->get_height() << " ";
		el->fix_height();
		//cout << el->get_height() << endl;
		if (el->bal_factor() == 2)
		{
			if (el->right->bal_factor() < 0)
				el->right = rotate_right(el->right);
			return rotate_left(el);
		}
		if (el->bal_factor() == -2)
		{
			if (el->left->bal_factor() > 0)
				el->left = rotate_left(el->left);
			return rotate_right(el);
		}
		el->fix_height();
		return el;
	}

	AVL_element* insert_rec(AVL_element* el, string license)
	{
		if (!el)
			return new AVL_element(license);
		if (stoi(el->license) > stoi(license))
			el->left = insert_rec(el->left, license);
		else
			el->right = insert_rec(el->right, license);
		return balance(el);
	}

	void insert(string license)
	{
		root = insert_rec(root, license);
		//cout << "Количество поворотов:\t" << turn << endl;
		//turn = 0;
	}

	bool build_tree(string file_name)
	{
		ifstream fb;
		fb.open(file_name + ".dat", ios::in | ios::binary);
		if (!fb.good())
		{
			return false;
		}
		business st;
		double count = 0;
		fb.read((char*)&st, sizeof(business));

		root = new AVL_element(st.license);
		count++;
		AVL_element* el = root;
		fb.read((char*)&st, sizeof(business));
		while (fb.good())
		{
			insert(st.license);
			count += 1;
			fb.read((char*)&st, sizeof(business));
		}
		print_tree();
		cout << "Количество поворотов:\t" << turn << endl;
		cout << "Отношение числа добавленных элементов к числу поворотов:\t" << setprecision(3) << count / turn << endl;
		turn = 0;
		return true;
	}

	AVL_element* find_min(AVL_element* el)
	{
		if (el->left)
			return find_min(el->left);
		else return el;
	}

	AVL_element* remove_min(AVL_element* el)
	{
		if (el->left == nullptr)
			return el->right;
		el->left = remove_min(el->left);
		return balance(el);
	}

	AVL_element* erase_rec(AVL_element* el, string key)
	{
		if (!el) return nullptr;
		if (stoi(el->license) > stoi(key))
			el->left = erase_rec(el->left, key);
		else if (stoi(el->license) < stoi(key))
			el->right = erase_rec(el->right, key);
		else if (stoi(el->license) == stoi(key))
		{
			AVL_element* left = el->left;
			AVL_element* right = el->right;
			delete el;
			if (!right)
				return left;
			AVL_element* min = find_min(right);
			min->right = remove_min(right);
			min->left = left;
			return balance(min);
		}
		return balance(el);
	}

	bool erase(string key)
	{
		if (!erase_rec(root, key))
		{
			return false;
		}
		else {
			return true;
		}
	}

	AVL_element* find_by_key_rec(AVL_element* el, string key) {
		if (!el) return nullptr;
		auto start_time = chrono::high_resolution_clock::now();
		if (stoi(el->license) > stoi(key))
			el->left = find_by_key_rec(el->left, key);
		else if (stoi(el->license) < stoi(key))
			el->right = find_by_key_rec(el->right, key);
		else if (stoi(el->license) == stoi(key))
		{
			auto end_time = chrono::high_resolution_clock::now();
			chrono::duration<double>search_time = end_time - start_time;
			cout << "Время поиска по дереву:" << fixed << setprecision(9) << search_time.count() << endl;
			return el;
		}
	}

	bool find_by_key(string key) {
		if (!find_by_key_rec(root, key))
			return false;
		else return true;
	}
};
#endif