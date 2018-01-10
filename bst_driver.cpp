/************************************************************************************************************************
Name: Eric Hinds                             Z#: Z23134823
Course: Data Structures (COP3530)
Professor: Dr. Lofton Bullard
Due Date:  4/24/2016                    Due Time: 11:59 p.m.
Total Points: 25
Assignment 9: bst_driver.cpp

Description: Contains a default constructor that opens a file county_data.txt and adds these values into two separate binary search trees,
one sorted by county name and the other sorted by population size, using insert functions. Contains a search function to search the county sorted
bst by county name, insert functions for inserting into both binary search trees, delete function for deleting individual entries from both search trees,
a delete all function for both trees for use in the destructor, a population_range function that prints all of the information with population sizes
between a specified min and max value in the parameter section, sorted only by county name, a print_tree function that prints both search trees 
to the screen (county and population size sorting), and a sorted_info function that creates a file called county_info.txt and prints 
the county sorted bst information to this file.

*************************************************************************************************************************/

#include <iostream>
#include "bst.h"

using namespace std;

int main( )
{

	cout<<"Test 1: default constructor\n";
	bst  myTree;
	myTree.print_tree();
	cout<<"\nEnd Test 1\n\n";

	cout<<"Test 2:insert\n";
	myTree.insert("new-county", 234658);
	myTree.print_tree();
	cout<<"\nEnd Test 2\n\n";

	cout << "Test 3: Search\n\n";
	myTree.search_tree("indian river");
	cout << "\nEnd Test 3\n\n";

	cout<<"Test 4: population_ranges\n";
	myTree.population_ranges(0,50000);
	cout<<"\nEnd Test 4\n\n";

	cout<<"Test 5: del_name\n\n";
	myTree.del_name("miami-dade");
	myTree.print_tree();
	cout<<"\nEnd Test 5\n\n";

	cout<<"Test 6: sorted_info\n\n";
	myTree.sorted_info();
	cout<<"\nEnd Test 6\n\n";

	return 0;
}


