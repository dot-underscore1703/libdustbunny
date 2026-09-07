// =====================
// NODES.C - NO D'E TREE
// =====================

#include <stdlib.h>
#include <stdio.h>
#include "libdustbunny/debug.h"

// This should be the maximum amount of children one node can have (excluding the root node), as I am not aware of any shell operation that exceeds that limit
#define MAX_CHILDREN 2

typedef enum NodeType {
	Text,
	Pipe,
	RedirectTo,
	RedirectFrom,
	SendToBackground,
	ExecuteOnSucces,
	ExecuteOnFailure
} NodeType;

typedef struct Node {
	NodeType type;
	
	struct Node *parent;
	size_t parent_idx;

	struct Node **children;
	size_t children_amt;
	
	char *value;
} Node;

Node *node_new(NodeType type, char *value) {
	size_t node_size = sizeof(Node);
	DUSTBUNNY_DEBUG("creating new node with size of %zu",node_size);
	Node *node = malloc(node_size);

	if(!node){
		DUSTBUNNY_DEBUG("failed to allocate space for node");
		return NULL;
	}
	node->type = type;
	node->value = value;

	Node **tmp_children = malloc(sizeof(Node*) * MAX_CHILDREN);
	if(tmp_children == NULL){
		DUSTBUNNY_DEBUG("failed to allocate space for node children");
		return NULL;
	}

	node->children = tmp_children;
	free(tmp_children);
	tmp_children = NULL;

	return node;
}

void node_destroy(Node *node) {
	DUSTBUNNY_DEBUG("destroying node");
	if(node == NULL){
		DUSTBUNNY_DEBUG("...but nobody came");
		return;
	}

	free(&node->type);
	free(node->value);
	for(size_t i = 0; i < node->children_amt; ++i) {
		free(node->children[i]);
	}
	node->parent->children[node->parent_idx] = NULL;
	--node->parent->children_amt;
	node->parent = NULL;
	free(node);
}

void node_adopt(Node *parent, Node *child) {
	DUSTBUNNY_DEBUG("adopting node");
	if(parent == NULL) {
		DUSTBUNNY_DEBUG("but the father is absent");
		return;
	}
	if(child == NULL) {
		DUSTBUNNY_DEBUG("but the child is dead");
		return;
	}

	parent->children[parent->children_amt] = child;
	child->parent_idx = parent->children_amt;
	++parent->children_amt;
	return;  
}

void node_disown(Node *child) {
	child->parent->children[child->parent->children_amt] = NULL;
	--child->parent->children_amt;
	child->parent = NULL;
	return;
}

