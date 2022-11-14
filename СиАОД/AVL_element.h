#pragma once
#ifndef __AVL_ELEMENT_H__
#define __AVL_ELEMENT_H__
#include <iostream>
using namespace std;

class AVL_element
{
private:
	unsigned int height;
public:
	string license; //key

	AVL_element* left;
	AVL_element* right;

	AVL_element(string license)
	{
		left = nullptr;
		right = nullptr;
		this->license = license;
		this->height = 1;
	};

	int get_height()
	{
		return height;
	}

	int bal_factor()
	{
		unsigned int h1, h2;
		if (right)
			h2 = right->get_height();
		else h2 = 0;
		if (left)
			h1 = left->get_height();
		else h1 = 0;
		return h2 - h1;
	}

	void fix_height()
	{
		unsigned int h1, h2;
		if (left)
			h1 = left->get_height();
		else h1 = 0;
		if (right)
			h2 = right->get_height();
		else h2 = 0;
		if (h1 > h2)
			height = h1 + 1;
		else height = h2 + 1;
	}
};
#endif