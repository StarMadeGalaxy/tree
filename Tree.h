#pragma once

#ifndef _NODE_H_
#define _NODE_H_

#include "stdafx.h"


struct Node {
	int key;
	Node* right_node, * left_node;
	char data[NODE_INFO_SIZE];
};


class Tree
{
public:
	int nodes_amount = 0;		// amount of nodes in the whole tree

	bool is_reversed = false;	// flag for changing rules while find and deletion
	int* keys = nullptr;

	void get_sorted_nodes(Node* root_pointer, Node*& nodes_array, int& index);
	void balanced_build(Node*& root_pointer, Node*& balanced_nodes, int start, int end);
	void two_children_nodes(Node*& root_pointer, int& amount_variable);
	void get_nodes_amount(Node* root_pointer);
	void get_sorted_keys(Node* root_pointer, int* keys_array, int& index);
	void deletion(Node*& root_pointer);
	void printing(const Node* node);
	void node_info_input(char* array);
	Node* node_delete(Node*& root_pointer, int key);
	Node* node_insert(Node*& root_pointer, int key, char* temp_array);
	Node* node_find(Node*& root_pointer, int key);
	Node* reverse(Node*& root_pointer);
private:
	void print_binary_tree(const std::string& prefix, const Node* node, bool is_left);
	Node* node_find_min(Node* root_pointer);
	Node* node_create(int key, char* temp_array);
};


#endif	// _NODE_H_