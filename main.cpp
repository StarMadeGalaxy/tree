#include "stdafx.h"
 

int main()
{
	Tree tree;
	Node* tree_pointer = nullptr;
 

	while (true) {
		ClearScreen();

		std::cout << "Binary search tree\n\n"
			<< "1. Insert nodes\n"
			<< "2. Delete nodes\n"
			<< "3. Inverse tree\n"
			<< "4. Balance tree\n"
			<< "5. View tree\n"
			<< "6. Individual task\n"
			<< "7. Find information by key\n"
			<< "0, ELSE. Exit.\n\n"
			<< "Type here: ";


		switch (_getch() - 48) {
		case 1:		// Insertion
		{
			ClearScreen();

			bool was_reversed = false;
			if (tree.is_reversed) {
				tree.reverse(tree_pointer);
				was_reversed = true;
			}

			std::cout << "How many nodes you would like to insert ?\n\n"
				<< "Type here: ";

			int insert_amount = static_cast<int>(number_input(TEST_LIMIT));	// nodes to insert
			int key = 0;	// current key to insert

			if (tree_pointer == nullptr) {
				tree.keys = new int[insert_amount];
			} else {
				// If keys-array is not empty => resize keys-array with 
				// size equal to insert_amount+previous_size
				int* temp_keys = new int[tree.nodes_amount];				// create temp array
				int temp_index = 0;											// index to store elements in temp array through traverse

				tree.get_sorted_keys(tree_pointer, temp_keys, temp_index);	// get keys in temp_keys
				delete[] tree.keys;											// clear initial keys-array

				tree.keys = new int[tree.nodes_amount + insert_amount];			// create enlarged array

				for (int i = 0; i < tree.nodes_amount; i++) {				// move keys from temp array to new keys-array
					tree.keys[i] = temp_keys[i];
				}

				delete[] temp_keys;											// delete temp keys
			}


			for (int i = 0; i < insert_amount; i++)
			{
				ClearScreen();
				tree.printing(tree_pointer);

				while (true) {
					bool break_loop = true;
					std::cout << "\nEnter a number: ";
					key = static_cast<int>(number_input(TEST_LIMIT));

					for (int i = 0; i < tree.nodes_amount; i++) {
						if (tree.keys[i] == key) {		// check for duplicate
							ClearScreen();
							tree.printing(tree_pointer);
							std::cout << "\nElement '" << key << "' is already in tree.\n";
							break_loop = false;
							break;
						}
					} 
					
					if (break_loop) {
						ClearScreen();
						std::cout << "\nEnter the data for the node with key '" 
							<< key << "'. [Maximum " << NODE_INFO_SIZE - 1 << " symbols]." 
							<< "\nWARNING! ENTER IS NOT COUNTED AS A SYMBOL."
							<< "\n\nType here: ";


						char* temp_node_info = new char[NODE_INFO_SIZE];
						tree.node_info_input(temp_node_info);			// store info to the temp array and return size
						tree.node_insert(tree_pointer, key, temp_node_info);	// insert node in the tree
						delete[] temp_node_info;									// delete temp array
						tree.keys[tree.nodes_amount++] = key;								// append entered key in tree.keys and increment
						tree.printing(tree_pointer);	
						break;
					}
				}
			}
			ClearScreen();
			tree.printing(tree_pointer);

			if (was_reversed) {
				was_reversed = false;
				tree.reverse(tree_pointer);
			}

			std::cout << "\n\nInsertion is complete.\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 2:		// Deletion
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			bool was_reversed = false;
			if (tree.is_reversed) {
				tree.reverse(tree_pointer);
				was_reversed = true;
			}

			ClearScreen();

			tree.printing(tree_pointer);
			std::cout << "\nWhat you would like to delete ?\n\n"
				<< "1. The whole tree\n"
				<< "2. Some nodes from tree\n"
				<< "0, ELSE. Back\n\n"
				<< "Type here: ";


			switch (_getch() - 48)
			{
			case 1:		// Delete the whole tree
			{
				ClearScreen();

				if (tree_pointer == nullptr) {
					std::cout << "Tree is empty.\n"
						<< "\n\nPress any to button to continue...";
					_getch();
					break;
				}

				tree.deletion(tree_pointer);
				tree.nodes_amount = 0;	// Therefore amount of nodes is 0
				delete[] tree.keys;		// Clear keys array
				tree.keys = nullptr;	// prevent dangling pointer

				std::cout << "\nNow tree is empty"
						<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}
			case 2:		// Delete some nodes
			{
				ClearScreen();

				tree.printing(tree_pointer);
				std::cout << "\nHow many nodes you would to delete ?\n\n"
					<< "Type here: ";

				int nodes_to_delete = 0;

				while (true) {
					ClearScreen();

					tree.printing(tree_pointer);
					std::cout << "\nHow many node you would to delete ?\n\nType here: ";
					nodes_to_delete = static_cast<int>(number_input(TEST_LIMIT));

					if (nodes_to_delete > tree.nodes_amount) {
						ClearScreen();
						std::cout << "Number of elements is too high.\n\nPress any to button to continue...";
						_getch();
					} else if (nodes_to_delete < 0) {
						ClearScreen();
						std::cout << "Number of elements is too low.\n\nPress any to button to continue...";
						_getch();
					} else {
						break;
					}
				}

				for (int i = 0; i < nodes_to_delete; i++)
				{
					bool print_warning = false;
					bool break_loop = false;
					while (!break_loop) {
						ClearScreen();
						tree.printing(tree_pointer);

						if (print_warning)
							std::cout << "\nThere is no element like that. Try again.\n";

						std::cout << "\nEnter a number: ";
						int number = static_cast<int>(number_input(TEST_LIMIT));

						for (int i = 0; i < tree.nodes_amount; i++)
						{
							if (tree.keys[i] == number){
								ClearScreen();

								tree.node_delete(tree_pointer, number);		// delete node
								tree.nodes_amount--;						// update the counter

								delete[] tree.keys;							// delete previous keys
								tree.keys = new int[tree.nodes_amount];		// create keys-array with new size

								int index = 0;
								tree.get_sorted_keys(tree_pointer, tree.keys, index);	// then traverse the tree to get new keys w/o deleted one
								tree.printing(tree_pointer);

								print_warning = false;
								break_loop = true;
								break;
							}
						}
						print_warning = true;
					}
				}

				if (was_reversed) {
					was_reversed = false;
					tree.reverse(tree_pointer);
				}

				std::cout << "\n\nDeletion is complete.\n\nPress any to button to continue...";
				_getch();
				break;
			}
			default:
			{
				if (was_reversed) {
					was_reversed = false;
					tree.reverse(tree_pointer);
				}
				break;
			}
			}
			if (was_reversed) {
				was_reversed = false;
				tree.reverse(tree_pointer);
			}
			break;
		}
		case 3:		// Reverse tree
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			std::cout << "Not reversed:\n\n";
			tree.printing(tree_pointer);
			std::cout << "\nReversed:\n\n";
			tree.reverse(tree_pointer);

			if (tree.is_reversed == false) tree.is_reversed = true;
			else tree.is_reversed = false;

			tree.printing(tree_pointer);

			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 4:		// Balance tree
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			bool was_reversed = false;
			if (tree.is_reversed) {
				tree.reverse(tree_pointer);
				was_reversed = true;
			}

			std::cout << "Not balanced:\n\n";
			tree.printing(tree_pointer);

			Node* balanced_nodes = new Node[tree.nodes_amount];						// Allocate array
			int balanced_index = 0;													// Index for traverse	
			tree.get_sorted_nodes(tree_pointer, balanced_nodes, balanced_index);	// Do an in-order traverse to get sorted nodes
			tree.deletion(tree_pointer);											// Delete previous tree

			tree.balanced_build(tree_pointer, balanced_nodes , 0, tree.nodes_amount - 1);			// Build tree from balanced nodes
			L("STEP 4");

			delete[] balanced_nodes;												// Then clear balanced nodes

			if (was_reversed) {
				was_reversed = false;
				tree.reverse(tree_pointer);
			}

			std::cout << "\nBalanced:\n\n";
			tree.printing(tree_pointer);
			std::cout << "\n\nTree's balanced.\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 5:		// Print tree
		{
			ClearScreen();

			if (tree_pointer == nullptr)
				std::cout << "Tree is empty.\n";
			else
				tree.printing(tree_pointer);

			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 6:	// indidual task
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			bool was_reversed = false;
			if (tree.is_reversed) {
				tree.reverse(tree_pointer);
				was_reversed = true;
			}

			int two_children_nodes_amount = 0;
			tree.two_children_nodes(tree_pointer, two_children_nodes_amount);

			tree.printing(tree_pointer);
			std::cout << "\n\nIndividual task is: "
				<< "\n\n'Find amount of nodes with two children'\n"
				<< "\nAmount is equal to " << two_children_nodes_amount;

			if (was_reversed) {
				was_reversed = false;
				tree.reverse(tree_pointer);
			}

			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 7:		// find 
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			bool was_reversed = false;
			if (tree.is_reversed) {
				tree.reverse(tree_pointer);
				was_reversed = true;
			}
			
			int key_to_find = 0;
			bool key_found = false;
			bool warning_flag = false;

			while (!key_found)
			{
				ClearScreen();
				tree.printing(tree_pointer);
				if (warning_flag) { std::cout << "\n\nKey's not found. Try again"; }
				std::cout << "\n\nEnter the key of the data you would like to find.\n"
					<< "\nType here: ";
				key_to_find = static_cast<int>(number_input(TEST_LIMIT));

				for (int i = 0; i < tree.nodes_amount; i++)
				{
					if (tree.keys[i] == key_to_find)
					{
						ClearScreen();

						Node* found_node = tree.node_find(tree_pointer, key_to_find);

						std::cout << "Node with key '" << key_to_find << "' has been found."
							<< "\n\nData: ";
						
						for (int i = 0; i < NODE_INFO_SIZE - 1 && found_node->data[i] != '\0'; i++)
							std::cout << found_node->data[i];

						std::cout << "\nAddress: " << found_node;
						std::cout << "\nKey: " << found_node->key;

						key_found = true;
						warning_flag = true;
						break;
					}
				} if (!key_found) {
					warning_flag = true;
				}
			}

			if (was_reversed) {
				was_reversed = false;
				tree.reverse(tree_pointer);
			}

			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		default:
		{
			std::cout << "\n\n\n";	// just for beautiful output
			return 0;
		}
		}
	}
	if (tree.keys != nullptr)
		delete[] tree.keys;
	return 0;
}




