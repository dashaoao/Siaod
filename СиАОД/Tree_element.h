#pragma once
#ifndef __TREE_ELEMENT_H__
#define __TREE_ELEMENT_H__
#include <iostream>
using namespace std;


struct Tree_element
{
	string license; //key
	Tree_element* left;
	Tree_element* right;
	Tree_element(string license) {
		left = nullptr;
		right = nullptr;
		this->license = license;
	};
};
#endif