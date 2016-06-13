/* CLASS LIST DECLARATIONS ARE HERE */

#pragma once
#ifndef HybridList_h
#define HybridList_h
#include "Libraries.h"

// Typedefs
typedef double ComponentType;

// Struct forward declaration
struct NodeType;

class HybridList
{
public:
	HybridList (); 
	HybridList (const HybridList &copyList); // Used so the list isn't lost when passing class objects through functions. Not really needed for this lab, but added it for practice
	~HybridList (); 
	bool IsEmpty () const;
	void Print () const;
	
	void Insert (ComponentType item);
	void DeleteList (ComponentType item);
	void Delete (ComponentType item);

	void search_data1 (); // Search how many times the head node's data repeats
	void search_last_data (); // Search how many times the tail node's data repeats
	void copy_tail (); // Copies tail node and places it at the beginning of the list

	float get_data(); 

private:
	NodeType* head;
	int node_number = 1;
	int number_rerun = 0;


};
#endif