/* ALL CLASS LIST IMPLEMENTATION GOES HERE */

#include "Libraries.h"
#include "List.h"

// Typedefs
typedef NodeType* NodePtr; // The computer will read NodePtr as NodeType*

// Structs
struct NodeType
{
	ComponentType data;
	NodePtr link;
};

// Class Implementations
HybridList::HybridList ()
{
	head = NULL;
}
HybridList::HybridList(const HybridList &copyList)
{
	// Define pointers
	NodePtr fromPtr;
	NodePtr toPtr;

	// If nothing is in the list, exit function
	if (head == NULL)
	{
		head = NULL;
		return;
	}

	// Copy first node
	fromPtr = copyList.head;
	head = new NodeType;
	head->data = fromPtr->data;

	// Copy the rest of the list
	toPtr = head;
	fromPtr = fromPtr->link;
	while (fromPtr != NULL)
	{
		toPtr->link = new NodeType;
		toPtr = toPtr->link;
		toPtr->data = fromPtr->data;
		fromPtr = fromPtr->link;
	}
	toPtr->link = NULL; // Since the loop doesn't place NULL in toPtr->link
}
bool HybridList::IsEmpty () const
{
	// If head points to nothing and the list is empty
	if (head == NULL)
		return true;
	else
		return false;		
}
void HybridList::Print () const
{
	// Variables
	NodePtr currPtr = head;

	// If user decided to print out the contents of a node, but no node was added
	if (currPtr == NULL)
		cout << "You have no nodes in the list." << endl;

	// Event controlled loop to print out the component of each node
	while (currPtr != NULL) // While currPtr does not point to the last node
	{
		cout << "Data in node is " << currPtr->data << endl;
		currPtr = currPtr->link;
	}
}
void HybridList::Insert (ComponentType item)
{
	// Check list is empty
	if (head == NULL)
	{
		// Create a new node
		NodePtr newNodePtr = new NodeType;

		// Place a value in the component type of the new node
		newNodePtr->data = item;

		// Use the external pointer head and copy the address it points to (1st node) into the link member of the new node
		newNodePtr->link = head;

		// Copy the address of newNodePtr points to (1st node) and place it in the head pointer so head points to the new node that is the 1st one
		head = newNodePtr;
		return;
	}
		
	// Declare local pointer variables
	NodePtr newNodePtr; // Points to the new node when a node is created
	NodePtr prevPtr; // Points to the previous node currPtr points to
	NodePtr currPtr; // Points to the current node

	// Set up node to be inserted
	newNodePtr = new NodeType; // Creates a new node
	newNodePtr->data = item; // Places item into the data portion of the new node

	// Initialize pointers for the linked list
	prevPtr = NULL; 
	currPtr = head; // Head and currPtr both point to the 1st node

	// While loop to search for the proper insertion point so the data members are all in order
	while ((currPtr != NULL) && (item > currPtr->data))
	{
		prevPtr = currPtr; // Copies the address currPtr points to and places it into prevPtr
		currPtr = currPtr->link; // Copies the node the link member currPtr points to (next node) and places it into currPtr
	}

	// Once insertion point is located, insert node
	newNodePtr->link = currPtr; // CurrPtr points to the first node. This puts the address it points to and places it in the link member of newNodePtr
	if (prevPtr == NULL)
	{
		head = newNodePtr; // If the while loop above was not entered, then head points to the new node newNodePtr points to and ultimately placing the new node at the beginning of the list 
	}
	else
	{
		prevPtr->link = newNodePtr; // The node newNodePtr points to is placed in the link member prevPtr points to, which is basically inserting the new node at the proper insertion point the while loop above detected
	}
}
void HybridList::DeleteList (ComponentType item)
{
	// If list is empty
	if (head == NULL)
	{
		cout << "Your list is empty. Enter a node to remove the list." << endl;
		return;
	}

	// Pointers
	NodePtr currPtr = head; // Create a temporary pointer and have it point to the first node (the node head is pointing to)
	NodePtr tempPtr;

	// Delete each node separately
	while (currPtr != NULL)
	{
		tempPtr = currPtr;
		currPtr = currPtr->link;
		delete[] tempPtr;
	}
	head = NULL;
	if (head == NULL)
		cout << "Your list was deleted." << endl;
	number_rerun++;
}
void HybridList::Delete (ComponentType item) 
{
	// If the list is empty, print a message and return out of the program
	if (head == NULL)
	{
		cout << "You have no nodes to delete. Insert a node to delete one." << endl;
		return;
	}

	// Define pointers
	NodePtr delPtr = new NodeType; // Pointer to the node to be deleted
	NodePtr currPtr; // Loop control pointer that will help us pin the node to be deleted

	// Variables
	int incorrect_input_e = 0;
	int node_input_e = 0;
	
	// Display data in each node
	do
	{
		do
		{
			// Reset error variables
			if (incorrect_input_e == 5)
				incorrect_input_e = 0;
			if (node_input_e == 5)
				node_input_e = 0;

			// Print list of nodes
			cout << "Print of nodes" << endl;
			HybridList::Print();

			// Ask which node they want to delete
			cout << "Type in the node's data to be deleted:" << endl;
			cin >> item;
			cin.get();

			// If user set off cin flag
			if (!cin)
			{
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "You did not enter in an integer. Please enter in only an integer" << endl;
				node_input_e = 5;
			}
		} while (node_input_e == 5);

		currPtr = head;

		// Check if node to be deleted is the 1st node
		if (item == head->data)
		{
			// Assign head pointer to del pointer because head is the node you want to delete
			delPtr = head; // Assigning addresses
			head = head->link; // Assign the address link points to (next node) and assign it to head pointer so the list isn't lost
		}
		else if (currPtr->data != item) // Checks if user actually typed in a number in the node
		{
			if (currPtr->link != NULL)
			{
				while (currPtr->link != NULL && currPtr->data != item)
				{
					currPtr = currPtr->link;
				} 
			}
			if (currPtr->data != item)
			{
				// Let the user know they didn't enter in a correct input
				cout << "You did not enter in a correct input. Please type in a node's data that you see listed." << endl;
				incorrect_input_e = 5;
			}
			if (incorrect_input_e != 5)
			{
				// Initialize currPtr to point to the same node head is pointing to
				currPtr = head;

				// Search for the node in the rest of the list
				while (currPtr->link->data != item) // Check if currPtr->link's component does not equal item
					currPtr = currPtr->link; // Update the currPtr so it points to next node in the list
			}
		}
	} while (incorrect_input_e == 5);

	// If user deleted the first node
	if (item == delPtr->data)
	{	
		delete delPtr;
		return;
	}

	// Delete delPtr
	delPtr = currPtr->link; // delPtr is assigned currPtr->link's address
	currPtr->link = currPtr->link->link; // Update currPtr by assigning the link member of currPtr to the next node after the one that is going to be deleted
	delete delPtr; // Delete the node delPtr points to
}
void HybridList::search_data1 ()
{
	if (head == NULL)
	{
		cout << "Your list is empty." << endl;
		return;
	}

	// Initialize currPtr
	NodePtr currPtr = head; // Points to the current node in the list
	int n_head_repeat = 0;

	// Check how many times the head node is repeated in the list
	while (currPtr != NULL)
	{
		if (currPtr->data == head->data)
		{
			n_head_repeat++;
		}
		currPtr = currPtr->link;
	}
	
	// Print how many times head->data repeated
	cout << "The head node's data repeated " << n_head_repeat << " in the list" << endl;
}
void HybridList::search_last_data()
{
	if (head == NULL)
	{
		cout << "Your list is empty." << endl;
		return;
	}

	// Initialize currPtr
	NodePtr currPtr = head;
	double tail_value;
	int n_tail_repeat = 0;

	// Get tail node's data
	while (currPtr->link != NULL)
	{
		currPtr = currPtr->link;
	}
	tail_value = currPtr->data;

	// Check for the tail node's value by starting at the beginning of the list
	currPtr = head;
	while (currPtr != NULL)
	{
		if (currPtr->data == tail_value)
		{
			n_tail_repeat++;
		}
		currPtr = currPtr->link;
	}
	
	// Print how many times the tail node's value repeated
	cout << "The tail node's value repeated " << n_tail_repeat << " in the list" << endl;
}
void HybridList::copy_tail()
{
	// If head equals null, exit function
	if (head == NULL)
	{
		cout << "You have no nodes in the list. Insert one to copy its contents." << endl;
		return;
	}

	// Pointers
	NodePtr currPtr;
	NodePtr tempPtr;
	NodePtr newNodePtr;

	// Initialize pointers
	currPtr = head;

	// Loop to get currPtr to point to the tail node
	while (currPtr->link != NULL)
		currPtr = currPtr->link;
	tempPtr = currPtr;

	// Once currPtr is pointing to the tail node, copy it's value into a new node and put it at the beginning of the list
	newNodePtr = new NodeType;
	newNodePtr->link = head;
	head = newNodePtr;
	newNodePtr->data = tempPtr->data;

	// Let the user know a new node was made and its contents are the same as the tail node
	if (newNodePtr->data == tempPtr->data)
	{
		cout << "Tail node's value copied into a new head node" << endl;
		node_number++;
	}
	return;
}
float HybridList::get_data()
{
	// Variables
	int get_data_error = 0;
	float item = 0;
	bool list_empty = true;

	// Check if user deleted the whole list so the node number resets back to 0
	list_empty = IsEmpty();
	if (list_empty == true)
		node_number = 1;

	// Ask user
	do
	{
		// Reset error variable if error was reached
		if (get_data_error == 5)
			get_data_error = 0;

		// Get number
		cout << "What number do you want to put in node" << node_number << "?" << endl;
		cin >> item;
		cin.get();

		// Round the user's answer
		item = item * 100;
		item = round(item);
		item = item / 100;

		// If user did not enter in a number
		if (!cin)
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "You did not enter in an integer. Please enter in an integer." << endl;
			get_data_error = 5;
		}
	} while (get_data_error == 5);
	node_number++;
	return item;
}
HybridList::~HybridList()
{
	delete head;
}