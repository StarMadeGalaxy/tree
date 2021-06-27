#include "stdafx.h"


void Tree::print_binary_tree(const std::string& prefix, const Node* node, bool is_right)
{
	if (node != nullptr)
	{
		std::cout << prefix << "|\n" << prefix << "|___";
		std::cout << node->key << std::endl;

		// enter the next tree level - left and right branch
		print_binary_tree(prefix + (is_right ? "|   " : "    "), node->right_node, true);
		print_binary_tree(prefix + (is_right ? "|   " : "    "), node->left_node, false);
	}
}


Node* Tree::node_insert(Node*& root_pointer, int key, char* temp_array)
{
	if (root_pointer == nullptr) {
		root_pointer = node_create(key, temp_array);
		return root_pointer;
	} else if (key < root_pointer->key) {
		root_pointer->left_node = node_insert(root_pointer->left_node, key, temp_array);
	} else {
		root_pointer->right_node = node_insert(root_pointer->right_node, key, temp_array);
	}
	return root_pointer;
}


void Tree::two_children_nodes(Node*& root_pointer, int& amount_variable)
{
	if (root_pointer == nullptr)
		return;

	two_children_nodes(root_pointer->left_node, amount_variable);

	if (root_pointer->left_node != nullptr && root_pointer->right_node != nullptr)
		amount_variable++;

	two_children_nodes(root_pointer->right_node, amount_variable);
}


void Tree::balanced_build(Node*& root_pointer, Node*& balanced_nodes, int start, int end)
{
	if (start > end) 
		return;

	int mid = (start + end) / 2;
	node_insert(root_pointer, balanced_nodes[mid].key, balanced_nodes[mid].data);
	balanced_build(root_pointer, balanced_nodes, start, mid - 1);
	balanced_build(root_pointer, balanced_nodes, mid + 1, end);
}


Node* Tree::node_delete(Node*& root_pointer, int key)
{
	if (root_pointer == nullptr) {
		return nullptr;
	} else if (key > root_pointer->key) {
		root_pointer->right_node = node_delete(root_pointer->right_node, key);
	} else if (key < root_pointer->key) {
		root_pointer->left_node = node_delete(root_pointer->left_node, key);
	} else {	// Consider tree cases
		if (root_pointer->right_node == nullptr && root_pointer->left_node == nullptr) {	// 1. Node is a leaf
			delete root_pointer;
			root_pointer = nullptr;
			return nullptr;
		} else if (root_pointer->right_node == nullptr) {	// 2. Node has one child
			Node* temp_node = root_pointer->left_node;
			delete root_pointer;
			root_pointer = temp_node;
			return root_pointer;
		} else if (root_pointer->left_node == nullptr) {
			Node* temp_node = root_pointer->right_node;
			delete root_pointer;
			root_pointer = temp_node;
			return root_pointer;
		} else {	// 3. Node has two children
			Node* temp_node = node_find_min(root_pointer->right_node);
			root_pointer->key = temp_node->key;
			root_pointer->right_node = node_delete(root_pointer->right_node, temp_node->key);
		}
	}
	return root_pointer;	// saw in guide, imho its unreachable, but in other case function does not cotrol all of the return pathes
}


Node* Tree::node_find(Node*& root_pointer, int key)
{
	// I finally found a bug! If i reverse a tree
	// and trying to found an element, find algorithm will
	// go to the left if an element less then root and 
	// go to the right if an element greater than root.
	// BUT TREE IS REVERSED, AND ALGORITHM REMAIN THE SAME
	// Algorithm cannot find small element for example in right part
	// There are two solution i came up with.
	// Create a flag that shows if tree is reverse or not,
	// or check left and right node of the root, and choose
	// between two algorithms.

	if (root_pointer->key == key || root_pointer == nullptr) {
		return root_pointer;
	} else if (key < root_pointer->key) {
		return node_find(root_pointer->left_node, key);
	} else {
		return node_find(root_pointer->right_node, key);
	}
}


void Tree::get_nodes_amount(Node* root_pointer)
{
	if (root_pointer == nullptr) return;
	get_nodes_amount(root_pointer->left_node);
	nodes_amount++;
	get_nodes_amount(root_pointer->right_node);
}


void Tree::get_sorted_nodes(Node* root_pointer, Node*& nodes_array, int& index)
{
	if (root_pointer == nullptr) return;
	get_sorted_nodes(root_pointer->left_node, nodes_array, index);
	nodes_array[index++] = *root_pointer;
	get_sorted_nodes(root_pointer->right_node, nodes_array, index);
}


void Tree::get_sorted_keys(Node* root_pointer, int* keys_array, int& index)
{
	if (root_pointer == nullptr) return;
	get_sorted_keys(root_pointer->left_node, keys_array, index);
	keys_array[index++] = root_pointer->key;
	get_sorted_keys(root_pointer->right_node, keys_array, index);
}


Node* Tree::node_find_min(Node* root_pointer)
{
	while (root_pointer->left_node != nullptr)
		root_pointer = root_pointer->left_node;
	return root_pointer;
}


void Tree::deletion(Node*& root_pointer)
{
	if (root_pointer == nullptr) return;
	deletion(root_pointer->left_node);
	deletion(root_pointer->right_node);
	delete root_pointer;
	root_pointer = nullptr;
}


Node* Tree::reverse(Node*& root_pointer)
{
	if (root_pointer == nullptr) {
		return root_pointer;
	} else {
		reverse(root_pointer->left_node);
		reverse(root_pointer->right_node);

		Node* temp_node = root_pointer->right_node;
		root_pointer->right_node = root_pointer->left_node;
		root_pointer->left_node = temp_node;
	}
	return root_pointer;
}


Node* Tree::node_create(int key, char* temp_array)
{
	Node* new_node = new Node;
	new_node->key = key;

	int i;
	for (i = 0; temp_array[i] != '\0'; i++) {
		new_node->data[i] = temp_array[i];
	} new_node->data[i] = temp_array[i]; // For Null-terminator

	new_node->left_node = nullptr;
	new_node->right_node = nullptr;

	return new_node;
}


void Tree::printing(const Node* node)
{
	print_binary_tree("", node, false);
}


void Tree::node_info_input(char* array)
{
	int size = 0;		    // index and the size to be returned at the same time

	while (size < NODE_INFO_SIZE - 1)
	{
		char c = _getch();
		if (c == 13) {
			break;
		} else if (c == '\b') {
			if (size > 0) {
				size--;
				std::cout << "\b \b";
			}
		} else {
			array[size++] = c;
			std::cout << (char)c;
		}
	}
	array[size++] = '\0';
}


