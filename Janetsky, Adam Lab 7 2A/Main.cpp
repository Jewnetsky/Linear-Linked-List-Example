/* MAIN FILE */

/* RESERVED ERROR NOTES
- None currently
*/

#include "Libraries.h"
#include "List.h"

/*
Adam Janetsky
4/29/16
This is a linked list super example that asks the user whether they want to add, delete, or print the contents of a linked list. I did NOT use
any of the functions provided because I find that it's harder for me to figure out their purpose and I end up learning more if
I just make my own functions. I still strive to accomplish the overall goal of the program, but I'm just doing it my own way.
*/

// Function prototypes
bool ask_to_add_node (); // Asks the user whether they want to add another node
float print_menu (); // Prints the options the user can do with the linked list
void intro (); // Intro to the program and explicitly tells that the nodes are ordered by their component's value from least to greatest
void carry_out_choice (); // Walks through the different option the user chose from the menu function
bool rerun_menu (); // Asks the user if they want to rerun the menu
void end_program (); // Ends program
int main (void)
{
	// Intro
	intro();
	
	// Carry out the user's choice from the option they chose
	carry_out_choice();

	// End program
	end_program();
}
bool ask_to_add_node ()
{
	/* Variables */

	// Arrays
	char user_response [10];
	char no [10] = "No";
	char yes [10] = "Yes";

	// Ints
	int adding_error = 0;

	// Ask user if they want to add another node
	do
	{
		// Reset error variable if error was reached
		if (adding_error == 5)
			adding_error = 0;

		// Ask
		cout << "Do you want to add another node to the list?" << endl;
		cin.getline (user_response, 10);

		// If user said yes, return true
		if ((strcmp (yes, user_response) == 0) || (user_response[0] == 'Y') || (user_response[0] == 'y'))
			return true;
		else if ((strcmp (no, user_response) == 0) || (user_response[0] == 'N') || (user_response[0] == 'n'))
			return false;
		else /* ERROR NOTE: COMPILER SENDS A WARNING THAT NOT ALL PATHS RETURN A VALUE. THIS IS OKAY BECAUSE THE USER NEEDS TO ENTER A CORRECT INPUT BEFORE PROCEEDING */
		{
			cout << "You entered an incorrect input. Please type in either Yes/No" << endl;
			adding_error = 5;
		}
	} while (adding_error == 5);
}
float print_menu ()
{
	// Variables
	float menu_answer = 0;
	int menu_error = 0;

	// Menu stuff
	do
	{
		// Reset error variable if user didn't enter a number 1-7
		if (menu_error == 5)
			menu_error = 0;

		// Da menu
		cout << "Please type the number option you wish to activate." << endl << endl;
		cout << "1. Check if list is empty." << endl;
		cout << "2. Print the contents of all the nodes in the linked list." << endl;
		cout << "3. Insert a node." << endl;
		cout << "4. Delete the whole list." << endl;
		cout << "5. Delete a node by searching for it's component." << endl;
		cout << "6. See how many times the component of the HEAD node repeats itself in the list." << endl;
		cout << "7. See how many times the component of the TAIL node repeats itself in the list." << endl;
		cout << "8. Copy the tail node's value into a new head node (NOTE: THIS WILL RUIN THE ORDER OF NODES FROM BEING LEAST TO GREATEST)." << endl;
		cin >> menu_answer;
		cin.get();

		// If user set off the cin flag
		if (!cin)
		{
			cin.clear();
			cin.ignore(10000, '\n');
			menu_error = 5;
		}
		// Round answer in case they entered in a decimal
		menu_answer = round(menu_answer);

		// If user didn't enter in a number between 1-8
		if ((menu_answer < 1) || (menu_answer > 8))
		{
			cout << "You did not enter in one of the options listed. Please list a number 1-8." << endl;
			menu_error = 5;
		}
	} while (menu_error == 5);
	return menu_answer;
}
void intro ()
{
	cout << "Hello. This program creates a linear linked list and will display options on what you want to do with the list." << endl;
	cout << "Things to note:" << endl;
	cout << "The nodes in the list are placed in order with least being the head node and the greatest being the tail node." << endl;
	
}
void carry_out_choice()
{
	/* Variables */

	// Arrays
	char yes[10] = "Yes";

	// Bool
	bool rerun_response = true; // Holds the response if the user wants to add another node or not and true is there for initialization
	bool list_empty_response = true; // Holds the answer if the list is empty or not and true is there for initialization
	bool rerun_menu_answer = true; // Holds the answer if the user wants to rerun the program or not
	
	// Class objects
	HybridList user_list;
	
	// Ints
	int node_number = 1;

	// Floats
	float menu_choice = 0;
	float node_item = 0;
	
	/* ******************************************************************************** */

	/* ******* Flow control for each of the responses from the menu ******* */

	do
	{
		// Print menu
		menu_choice = print_menu();

		// If user chose to see if the list is empty
		if (menu_choice == 1.0)
		{
			list_empty_response = user_list.IsEmpty();
			if (list_empty_response == true)
				cout << "Your list is empty." << endl;
			else if (list_empty_response == false)
				cout << "Your list is NOT empty." << endl;
			else
				cout << "IsEmpty() function from the class HybridList did not return either true or false. Sounds like some wack to me" << endl;
		}

		// If user chose to print the contents of the list
		else if (menu_choice == 2.0)
			user_list.Print();
			
		// If user wants to insert a node
		else if (menu_choice == 3.0)
		{
			// Reset rerun_response so loop is entered
			if (rerun_response == false)
				rerun_response = true;

			while (rerun_response == true)
			{
				// Ask user what they want to enter in the node
				node_item = user_list.get_data();

				// Add value user entered into node
				user_list.Insert(node_item);

				// Ask the user if they want to enter another node
				rerun_response = ask_to_add_node(); 
				node_number++;
			}
		}

		// If user wants to delete the list
		else if (menu_choice == 4.0)
		{
			// Delete list
			user_list.DeleteList(node_item);
		}

		// If user wants to delete a single node
		else if (menu_choice == 5.0)
		{
			// Delete a node by searching for its component
			user_list.Delete(node_item);
		}

		// If user wants to see how many times the head node's value repeats throughout the list
		else if (menu_choice == 6.0)
		{
			// Check if the 1st node's component is repeated in the list
			user_list.search_data1();
		}

		// If user wants to see how many times the tail node's value repeats throughout the list
		else if (menu_choice == 7.0)
		{
			// Check if the last node's component is repeated in the list
			user_list.search_last_data();
		} 
		else if (menu_choice == 8.0)
		{
			// Copy tail node
			user_list.copy_tail();
		}
		
		// Ask user if they want to rerun the menu
		rerun_menu_answer = rerun_menu();
		system("CLS");
	} while (rerun_menu_answer == true);
}
bool rerun_menu()
{
	// Variables
	char yes [10];
	char no [10];
	char answer [10];
	int input_error = 0;

	do
	{
		// Reset error code
		if (input_error == 5)
			input_error = 0;

		// Ask user
		cout << "Back to menu? Yes/No" << endl;
		cin.getline(answer, 10);

		// Check their answer
		if ((strcmp(yes, answer) == 0) || (answer[0] == 'y') || (answer[0] == 'Y'))
			return true;
		else if ((strcmp(no, answer) == 0) || (answer[0] == 'n') || (answer[0] == 'N'))
			return false;
		else /* ERROR NOTE: COMPILER SENDS A WARNING THAT NOT ALL PATHS RETURN A VALUE. THIS IS OKAY BECAUSE THE USER NEEDS TO ENTER A CORRECT INPUT BEFORE PROCEEDING */
		{
			cout << "You didn't enter in the correct input. Please type in either Yes or No" << endl;
			input_error = 5;
		}
	}  while (input_error == 5);
}
void end_program()
{
	cout << "Press ENTER to end the program" << endl;
	cin.get();
}
