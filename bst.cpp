/************************************************************************************************************************
Name: Eric Hinds                             Z#: Z23134823
Course: Data Structures (COP3530)
Professor: Dr. Lofton Bullard
Due Date:  4/24/2016                    Due Time: 11:59 p.m.
Total Points: 25
Assignment 9: bst.cpp

Description: Contains a default constructor that opens a file county_data.txt and adds these values into two separate binary search trees,
one sorted by county name and the other sorted by population size, using insert functions. Contains a search function to search the county sorted
bst by county name, insert functions for inserting into both binary search trees, delete function for deleting individual entries from both search trees,
a delete all function for both trees for use in the destructor, a population_range function that prints all of the information with population sizes
between a specified min and max value in the parameter section, sorted only by county name, a print_tree function that prints both search trees 
to the screen (county and population size sorting), and a sorted_info function that creates a file called county_info.txt and prints 
the county sorted bst information to this file.

*************************************************************************************************************************/


#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "bst.h"

using namespace std;

/**************************************************************************************************************************
Name: bst
Precondition: binary search trees have not been created from file
Postcondition: Tbinary search trees have been created from file
Description: default constructor reads county and population size from a file called county_data.txt
separates the two into an integer and string value and uses the insert function to create binary search trees
/************************************************************************************************************************/
bst::bst()
{
	ifstream in;
	string string_line, county;
	int population;
	root = 0;
	root1 = 0;

	in.open("county_data.txt");
	if (in.fail())
	{
		cout << "Input file did not open correctly.\n";
		exit(1);
	}

	while (getline(in, string_line))
	{
		if (string_line.empty()) continue;
		istringstream iss(string_line);
		string word;
		while (iss >> word)
		{
			if (!isdigit(word[0]))
			{
				county = word;
				while (iss >> word && !isdigit(word[0]))
				{
					county = county + " " + word;
				}
				stringstream(word) >> population;
			}
		}
		insert(county, population);
	}

	in.close();
}

/**************************************************************************************************************************
Name: empty
Precondition: binary search tree has not been evaluated to see if empty
Postcondition: binary search tree has been evaluated to see if empty
Description: Returns true if the binary search tree is empty
/************************************************************************************************************************/
bool bst::empty()
{
   return (root == 0);
}

/**************************************************************************************************************************
Name: insert
Precondition: Entries have not been inserted into the binary search trees
Postcondition: Entries have been inserted into the binary search trees
Description: First it uppercases the first letter of the county name and then it runs to insert functions, one to create
a binary search tree sorted by county name and another to create a binary search tree sorted by population size
/************************************************************************************************************************/
void bst::insert(string item, const int & population)
{
	item[0] = toupper(item[0]);
	insert(root, item, population);
	insert_numeric(root1, item, population);
}

/**************************************************************************************************************************
Name: insert
Precondition: Entries have not been inserted into the binary search trees by order of county
Postcondition: Entries have been inserted into the binary search trees by order of county
Description: Inserts entries into a binary search tree ordered by county name
/************************************************************************************************************************/
void bst::insert(treenode * & loc_ptr, string item, const int & population)
{
    if (loc_ptr == 0)
    {
       loc_ptr = new treenode;
       loc_ptr->lchild = loc_ptr->rchild = 0;
	   loc_ptr->info = item + " " + to_string(population);
    }
    else if (loc_ptr->info > item)
       insert(loc_ptr->lchild, item, population);
    else if (loc_ptr->info < item)
       insert(loc_ptr->rchild, item, population);
    else
       cout<<"the item is already in the tree\n\n";
}

/**************************************************************************************************************************
Name: insert_numeric
Precondition: Entries have not been inserted into the binary search trees by order of population size
Postcondition: Entries have been inserted into the binary search trees by order of population size
Description: Inserts entries into a binary search tree ordered by population size
/************************************************************************************************************************/
void bst::insert_numeric(treenode * & loc_ptr, string item, const int & population)
{
	if (loc_ptr == 0)
	{
		loc_ptr = new treenode;
		loc_ptr->lchild = loc_ptr->rchild = 0;
		loc_ptr->info = to_string(population) + " " + item;
	}
	stringstream is(loc_ptr->info);
	string word;
	int loc_population;
	//filter population from county
	while (is >> word)
	{
		if (isdigit(word[0]))
		{
			stringstream(word) >> loc_population;
		}
	}
	if (loc_population > population)
		insert_numeric(loc_ptr->lchild, item, population);
	else if (loc_population < population)
		insert_numeric(loc_ptr->rchild, item, population);
	else
		;// cout << "the item is already in the tree\n\n";
}

/**************************************************************************************************************************
Name: search
Precondition: Entries have not been searched and/or found
Postcondition: Entries have been searched and have either been found or not found
Description: runs the search auxilary function to search BST ordered by county name only
/************************************************************************************************************************/
treenode * bst::search_tree(string item)
{
	return search_tree(root, item);
}

/**************************************************************************************************************************
Name: search
Precondition: Entries have not been searched and/or found
Postcondition: Entries have been searched and have either been found or not found
Description: Searches through the BST that is ordered by county name. It lowercases the search value and compares it to a lowercase
version of the string entry. Filters out the population using stringstream so only accepts county name as a search parameter.
/************************************************************************************************************************/
treenode * bst::search_tree(treenode * loc_ptr, string item)
{
	if (loc_ptr != 0)
	{
		//search for entries regardless of capitalization
		treenode * temp = loc_ptr;
		for (unsigned int i = 0; i < item.length(); i++)
		{
			item[i] = tolower(item[i]);
		}
		for (unsigned int j = 0; j < temp->info.length(); j++)
		{
			temp->info[j] = tolower(temp->info[j]);
		}
		stringstream is(temp->info);
		string county, word;
		int population;
		//filter population from county
		while (is >> word)
		{
			if (!isdigit(word[0]))
			{
				county = word;
				while (is >> word && !isdigit(word[0]))
				{
					county = county + " " + word;
				}
				stringstream(word) >> population;
			}
		}
		//begin searching, if found return
		if (county == item)
		{
			cout << "Item found.\n\n";
			return temp;
		}
		//continue moving through rest of BST
		else if (county > item)
			return search_tree(temp->lchild, item);
		else
			return search_tree(temp->rchild, item);
	}
	else
	{
		cout << "item not found.\n\n";
		return loc_ptr;
	}
}
	
/**************************************************************************************************************************
Name: del_name
Precondition: Entries have not been deleted from both binary search trees
Postcondition: Entries have been deleted from both binary search trees
Description: Runs the del_name auxsilary fumction to delete entries
/************************************************************************************************************************/
void bst::del_name(string item)
{
	del_name(root,item);
	del_name(root1, item);
}

/**************************************************************************************************************************
Name: del_name
Precondition: Entries have not been deleted from the binary search trees
Postcondition: Entries have been deleted from the binary search trees
Description: Deletes an entry from either the county or population size BST. Uses stringstream to separate the population from county.
Only deletes a single entry.
/************************************************************************************************************************/
void bst::del_name(treenode * & loc_ptr, string item)
{
	treenode * temp = loc_ptr;
	for (unsigned int i = 0; i < item.length(); i++)
	{
		item[i] = tolower(item[i]);
	}
	for (unsigned int j = 0; j < temp->info.length(); j++)
	{
		temp->info[j] = tolower(temp->info[j]);
	}
	stringstream is(temp->info);
	string county, word;
	int population;
	//filter population from county
	while (is >> word)
	{
		if (!isdigit(word[0]))
		{
			county = word;
			while (is >> word && !isdigit(word[0]))
			{
				county = county + " " + word;
			}
			stringstream(word) >> population;
		}
	}
   if (temp == 0)
       cout<<"item not in tree\n\n";

   else if (county > item)
       del_name(temp->lchild, item);

   else if (county < item)
       del_name(temp->rchild, item);
   else
   {
       treenode * ptr;

       if (loc_ptr->lchild == 0)
       {
          ptr = loc_ptr->rchild;
          delete loc_ptr;
          loc_ptr = ptr;
       }
       else if (loc_ptr->rchild == 0)
       {
          ptr = loc_ptr->lchild;
          delete loc_ptr;
          loc_ptr = ptr;
       }
       else
       {
          ptr = inorder_succ(loc_ptr);
          loc_ptr->info = ptr->info;
          del_name(loc_ptr->rchild, ptr->info);
       }
	   cout << "Item deleted successfully.\n";
    }

}

/**************************************************************************************************************************
Name: del_all
Precondition: Entries have not been deleted from county sorted BST
Postcondition: Entries have been deleted from county sorted BST
Description: Runs the del_all auxsilary fumction to delete all county sorted entries
/************************************************************************************************************************/
void bst::del_all(string item)
{
	del_all(root, item);
}

/**************************************************************************************************************************
Name: del_all
Precondition: Entries have not been deleted from county sorted BST
Postcondition: Entries have been deleted from county sorted BST
Description: deletes all county sorted entries from the BST
/************************************************************************************************************************/
void bst::del_all(treenode * & loc_ptr, string item)
{
	if (loc_ptr == 0)
		cout << "item not in tree\n\n";

	else if (loc_ptr->info > item)
		del_all(loc_ptr->lchild, item);

	else if (loc_ptr->info < item)
		del_all(loc_ptr->rchild, item);
	else
	{
		treenode * ptr;

		if (loc_ptr->lchild == 0)
		{
			ptr = loc_ptr->rchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else if (loc_ptr->rchild == 0)
		{
			ptr = loc_ptr->lchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else
		{
			ptr = inorder_succ(loc_ptr);
			loc_ptr->info = ptr->info;
			del_all(loc_ptr->rchild, ptr->info);
		}
		cout << "Item deleted successfully.\n";
	}
}

/**************************************************************************************************************************
Name: del_all_numeric
Precondition: Entries have not been deleted from population size sorted BST
Postcondition: Entries have been deleted from population size sorted BST
Description: Runs the del_all auxsilary fumction to delete all population size sorted entries
/************************************************************************************************************************/
void bst::del_all_numeric(string item)
{
	del_all_numeric(root1, item);
}

/**************************************************************************************************************************
Name: del_all_numeric
Precondition: Entries have not been deleted from population size sorted BST
Postcondition: Entries have been deleted from population size sorted BST
Description: Deletes all population size sorted entries from the BST
/************************************************************************************************************************/
void bst::del_all_numeric(treenode * & loc_ptr, string item)
{
	if (loc_ptr == 0)
		cout << "item not in tree\n\n";

	stringstream is(loc_ptr->info);
	string word;
	int loc_population;
	//filter population from county
	while (is >> word)
	{
		if (isdigit(word[0]))
		{
			stringstream(word) >> loc_population;
		}
	}
	stringstream iss(item);
	string word1;
	int population;
	//filter population from county
	while (iss >> word1)
	{
		if (isdigit(word1[0]))
		{
			stringstream(word1) >> population;
		}
	}

	if (loc_population > population)
		del_all_numeric(loc_ptr->lchild, item);

	else if (loc_population < population)
		del_all_numeric(loc_ptr->rchild, item);
	else
	{
		treenode * ptr;

		if (loc_ptr->lchild == 0)
		{
			ptr = loc_ptr->rchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else if (loc_ptr->rchild == 0)
		{
			ptr = loc_ptr->lchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else
		{
			ptr = inorder_succ(loc_ptr);
			loc_ptr->info = ptr->info;
			del_all_numeric(loc_ptr->rchild, ptr->info);
		}
		cout << "Item deleted successfully.\n";
	}
}

/**************************************************************************************************************************
Name: inorder_succ
Precondition: The inorder successor has not been pointed to
Postcondition: The inorder successor has been pointed to
Description: Finds and points to the inorder successor of any BST
/************************************************************************************************************************/
treenode * bst::inorder_succ(treenode * loc_ptr)
{

  treenode *ptr = loc_ptr->rchild;

  while(ptr->lchild != 0)
  {
     ptr = ptr->lchild;
  }
  return ptr;
}
 
/**************************************************************************************************************************
Name: print_tree
Precondition: Entries have not been printed to the screen
Postcondition: Entries have been printed to the screen
Description: Runs the print_tree auxilary to print to the screen
/************************************************************************************************************************/
void bst::print_tree()
{
	cout << endl;
	print_tree(root);
	cout << endl;
	print_tree(root1);
}

/**************************************************************************************************************************
Name: print_tree
Precondition: Entries have not been printed to the screen
Postcondition: Entries have been printed to the screen
Description: Prints all of the entries to the screen for both BSTs, county and population size sorted.
/************************************************************************************************************************/
void bst::print_tree(treenode * loc_ptr)
{
  if (loc_ptr!=0)
  {
	  if (!isdigit(loc_ptr->info[0]))
	  {
		  loc_ptr->info[0] = toupper(loc_ptr->info[0]);
	  }
	 print_tree(loc_ptr->lchild);
	 cout<<loc_ptr->info<<endl; 
	 print_tree(loc_ptr->rchild);
  }
}

/**************************************************************************************************************************
Name: population_ranges
Precondition: Entries have not been printed to the screen
Postcondition: Entries have been printed to the screen
Description: Runs the population_ranges auxillary function to print all population ranges to screen
/************************************************************************************************************************/
void bst::population_ranges(const double & min_size, const double & max_size)
{
	cout << endl;
	population_ranges(root, min_size, max_size);
}

/**************************************************************************************************************************
Name: population_ranges
Precondition: Entries have not been printed to the screen
Postcondition: Entries have been printed to the screen
Description: Prints all of the entries to the screen for county sorted entries only with a min and max range specified in
function parameter
/************************************************************************************************************************/
void bst::population_ranges(treenode * loc_ptr, const double & min_size, const double & max_size)
{
	if (loc_ptr != 0)
	{
		loc_ptr->info[0] = toupper(loc_ptr->info[0]);
		stringstream is(loc_ptr->info);
		string county, word;
		int population;
		//filter population from county
		while (is >> word)
		{
			if (!isdigit(word[0]))
			{
				county = word;
				while (is >> word && !isdigit(word[0]))
				{
					county = county + " " + word;
				}
				stringstream(word) >> population;
			}
			population_ranges(loc_ptr->lchild, min_size, max_size);
			if (population >= min_size && population <= max_size)
			{
				cout << loc_ptr->info << endl;
			}
			population_ranges(loc_ptr->rchild, min_size, max_size);
		}
	}
}

/**************************************************************************************************************************
Name: sorted_info
Precondition: Entries have not been added to file
Postcondition: Entries have been added to file county_info.txt
Description: Opens county_info.txt for output and runs sorted_info auxillary function to begin printing to file. Closes the file
when finished
/************************************************************************************************************************/
void bst::sorted_info()
{
	ofstream out;

	out.open("county_info.txt");

	if (out.fail())
	{
		cout << "Output file failed to open properly.";
		exit(1);
	}
	sorted_info(root, out);
	
	out.close();

	cout << "File created Successfully\n";
}

/**************************************************************************************************************************
Name: sorted_info
Precondition: Entries have not been added to file
Postcondition: Entries have been added to file county_info.txt
Description: sets the first character to uppercase and prints the county sorted only data to file county_info.txt
/************************************************************************************************************************/
void bst::sorted_info(treenode * loc_ptr, ofstream & out)
{
	if (loc_ptr != 0)
	{
		loc_ptr->info[0] = toupper(loc_ptr->info[0]);
		sorted_info(loc_ptr->lchild, out);
		out << loc_ptr->info << endl;
		sorted_info(loc_ptr->rchild, out);
	}
}

/**************************************************************************************************************************
Name: ~bst
Precondition: Entries have not been cleared from memory
Postcondition: Entries have been cleared from memory
Description: Destructor, deletes all entries from both BSTs to clear it from memory
/************************************************************************************************************************/
bst::~bst()
{
   while (!empty())
   {
	   del_all(root->info);
	   del_all_numeric(root1->info);
   }
}



/*int main()
{
    bst B;
	//treenode *root1=0, *root2=0;
    string s;
    char ch;
    string key3; 
    string key4;
	string response;
	string r1, r2;
    cout<<"enter command, c=count, i=insert item,s=search tree,d=delete item,p=print tree, r = range, e=exit: ";
    cin>>ch;
    cout<<endl;

    while (ch!='e')
    {
       switch (ch)
       {
	   case 'i'  :cout<<"enter string: ";
             cin>>s;
             B.insert(s);
             break;
 
       case 's'  :cout<<"enter word to search for: ";
             cin>>s;
             if (!B.search_tree(s))
                cout<<s<<"not in tree\n";
             else
                cout<<s<<" was found in the tree\n";
             break;
       case 'd'  :cout<<"enter word to delete: ";
                  cin>>s;
                  B.del(s);
                  break;
       case 'p'  :cout<<"...printing tree...\n";
             B.print_tree();
			 break;
		   
				default:break;
      }
      cout<<"enter command, i=insert item,s=search tree,d=delete item,p=print tree, e=exit: ";
      cin>>ch;
      cout<<endl;
    }
 
    cout<<endl<<"no more binary tree.....\n";
    return 0;
} */
     
