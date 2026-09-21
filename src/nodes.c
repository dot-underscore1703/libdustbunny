// =====================
// NODES.C - NO D'E TREE
// =====================

#include <stdlib.h>
#include <stdio.h>
#include "libdustbunny/debug.h"

// This should be the maximum amount of children one node can have (excluding the root node), as I am not aware of any shell operation that exceeds that limit
#define MAX_CHILDREN 2

/// Types for nodes. Each node has a type, which tells the interpreter how to use it and its children.
typedef enum NodeType {
	Root,				// The root of the AST
	
	// Text nodes carry strings of data.
	// This data is usually commands.
	// It should have no children, and should instead use the Nodes value string to store its text.
	Text,				// Any text. Commands, filepaths etc
	Command,			// e.g 'gcc -c mylib.c'
	File,				// e.g 'cat ~/.bashrc'

	// Pipe nodes indicate that the output of the command(s) on the left side of the pipe should be sent to the input of the command(s) of the left side of the pipe.
	// They s 
	Pipe,				// e.g 'ls | grep "o.txt"'
	RedirectTo,			// e.g 'ls > my_files.txt'
	RedirectFrom,		// e.g 'cat < my_files.txt'
	SendToBackground,	// e.g 'firefox &'
	ExecuteOnSuccess,	// e.g 'gcc main.c -o a.out && ./a.out'
	ExecuteOnFailure	// e.g 'gcc main.c -o a.out || echo "compilation failed"'
} NodeType;

/// The node type. The AST node tree is comprised of these types. Every node should have a parent except for the Root node, and every node should have a child except for the Text node.
typedef struct Node {
	NodeType type;
	
	struct Node *parent;
	size_t parent_idx;

	struct Node **children;
	size_t children_amt;
	
	char *value;
} Node;

/// Create a new node with the node type and its value, if applicable.
Node *node_new(NodeType type, char *value) {
	// Get node size and allocate memory for a new node.
	size_t node_size	= sizeof(Node);
	DUSTBUNNY_DEBUG("creating new node with size of %zu",node_size);
	Node *node			= malloc(node_size);

	// Make sure malloc() was succesfull.
	if(!node){
		// malloc() returned NULL.
		DUSTBUNNY_DEBUG("failed to allocate space for node");
		return NULL;
	}

	// Set the nodes fields to the appropriate values provided by the function params
	node->type 	= type;
	node->value = value;
	
	// Create a temporary variable for the nodes children pointers
	Node **tmp_children = malloc(sizeof(Node*) * MAX_CHILDREN);

	// Make sure malloc() was successful.
	if(!tmp_children){
		// Temporary variable allocation failed
		DUSTBUNNY_DEBUG("failed to allocate space for node children");
		return NULL;
	}

	// Temporary variable was created correctly, assign it to the node.
	node->children = tmp_children;

	// Then free the temporary variable
	free(tmp_children);
	
	// And nullify the pointer.
	tmp_children = NULL;

	// Return the node we created.
	return node;
}

/// Destroy the node at the provided pointer and free its fields.
void node_destroy(Node *node) {
	DUSTBUNNY_DEBUG("destroying node");

	// Check that the node we are trying to destroy actually exists.
	if(!node){
		// It doesn't exist, exit.
		DUSTBUNNY_DEBUG("...but nobody came");
		return;
	}

	// === I haven't checked that this works yet, its a bit confusing ;-; but it'll be fixed ===
	
	// Free the nodes fields before freeing the node itself.
	free(&node->type);
	free(node->value);

	// Loop over each child and destroy the children.
	for(size_t i = 0; i < node->children_amt; ++i) {
		node_destroy(node->children[i]);
	}

	// The root node shouldn't be destroyed so hopefully this works.

	// Destroy the parent nodes pointer to this node
	node->
		parent->
			children[node->parent_idx] = NULL;

	// Decrement the parents amount of children.
	--node->
		parent->
			children_amt;

	// Nullify the parent pointer.
	node->
		parent = NULL;

	// Free the node
	free(node);
}

/// Add the child node provided to the parent nodes children.
void node_adopt(Node *parent, Node *child) {
	DUSTBUNNY_DEBUG("adopting node");

	// We want to know both the child and parent actually exist.
	if(!parent) {
		// The parent does not exist, exit.
		DUSTBUNNY_DEBUG("the parent is null");
		return;
	}
	if(!child) {
		// The child does not exist, exit.
		DUSTBUNNY_DEBUG("the child is null");
		return;
	}

	// This code is really funny, and probably not that good.

	// Add the child to the parents children field
	parent->
		children[parent->children_amt] = child;
		
	// Set the childs parent field to the parent pointer
	child->
		parent = parent;
	
	// Set the childs parent_idx field to the position it was placed at in the parents children.
	child->
		parent_idx = parent->children_amt++;

	return;  
}

/// Disown the child provided from the parent node. The parent node will be found automatically, so no need to provide a pointer to one.
void node_disown(Node *child) {
	// Nullify the parents pointer to the child 
	child->
		parent->
			children[child->
						parent->
							children_amt] = NULL;

	// Decrement the parents children_amt counter
	--child->	
		parent->
			children_amt;

	// Nullify the pointer to the parent.
	child->parent = NULL;
	return;
}

