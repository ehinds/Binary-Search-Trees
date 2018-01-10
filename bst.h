/************************************************************************************************************************
Name: Eric Hinds                             Z#: Z23134823
Course: Data Structures (COP3530)
Professor: Dr. Lofton Bullard
Due Date:  4/24/2016                    Due Time: 11:59 p.m.
Total Points: 25
Assignment 9: bst.h

Description: Contains a default constructor that opens a file county_data.txt and adds these values into two separate binary search trees,
one sorted by county name and the other sorted by population size, using insert functions. Contains a search function to search the county sorted
bst by county name, insert functions for inserting into both binary search trees, delete function for deleting individual entries from both search trees,
a delete all function for both trees for use in the destructor, a population_range function that prints all of the information with population sizes
between a specified min and max value in the parameter section, sorted only by county name, a print_tree function that prints both search trees 
to the screen (county and population size sorting), and a sorted_info function that creates a file called county_info.txt and prints 
the county sorted bst information to this file.

*************************************************************************************************************************/

#include <string>

using namespace std;

#ifndef BST_H
#define BST_H

class treenode
{
public:
	string info;
	treenode *lchild, *rchild;
};

class bst
{
public:
	bst();	
	~bst();
	bool empty();
	void insert(string item, const int & population);
	void insert(treenode * &, string item, const int & population);
	void insert_numeric(treenode * &, string item, const int & population);
	void del_name(string item);
	void del_name(treenode * & loc_ptr, string item);
	void del_all(string item);
	void del_all(treenode * & loc_ptr, string item);
	void del_all_numeric(string item);
	void del_all_numeric(treenode * & loc_ptr, string item);
	treenode * search_tree(string item);
	treenode * search_tree(treenode *, string item);
	treenode * inorder_succ(treenode *);
	void print_tree();
	void print_tree(treenode *);
	void population_ranges(const double & min_size, const double & max_size);
	void population_ranges(treenode * loc_ptr, const double & min_size, const double & max_size);
	void sorted_info();
	void sorted_info(treenode * loc_ptr, ofstream & out);

private:
	treenode *root, * root1;

};
#endif
