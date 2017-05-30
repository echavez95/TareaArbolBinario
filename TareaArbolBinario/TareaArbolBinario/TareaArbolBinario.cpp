// TareaArbolBinario.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip> 
#define MARKER -1
using namespace std;

struct node
{
	int key_value;
	node *left;
	node *right;
};

class btree
{
public:
	node *root;

	btree()
	{
		root = NULL;
	}

	void destroy_tree(node *leaf)
	{
		if (leaf != NULL)
		{
			destroy_tree(leaf->left);
			destroy_tree(leaf->right);
			delete leaf;
		}
	}

	void insert(int key, node *leaf)
	{
		if (key< leaf->key_value)
		{
			if (leaf->left != NULL)
				insert(key, leaf->left);
			else
			{
				leaf->left = new node;
				leaf->left->key_value = key;
				leaf->left->left = NULL;    //Sets the left child of the child node to null
				leaf->left->right = NULL;   //Sets the right child of the child node to null
			}
		}
		else if (key >= leaf->key_value)
		{
			if (leaf->right != NULL)
				insert(key, leaf->right);
			else
			{
				leaf->right = new node;
				leaf->right->key_value = key;
				leaf->right->left = NULL;  //Sets the left child of the child node to null
				leaf->right->right = NULL; //Sets the right child of the child node to null
			}
		}
	}

	node* search(int key, node *leaf)
	{
		if (leaf != NULL)
		{
			if (key == leaf->key_value)
				return leaf;
			if (key<leaf->key_value)
				return search(key, leaf->left);
			else
				return search(key, leaf->right);
		}
		else return NULL;
	}

	void insert(int key)
	{
		if (root != NULL)
			insert(key, root);
		else
		{
			root = new node;
			root->key_value = key;
			root->left = NULL;
			root->right = NULL;
		}
	}

	node* search(int key)
	{
		return search(key, root);
	}

	void destroy_tree()
	{
		destroy_tree(root);
	}

	// This function stores a tree in a file pointed by fp
	void serialize(node *root, FILE *fp)
	{
		// If current node is NULL, store marker
		if (root == NULL)
		{
			fprintf(fp, "%d ", MARKER);
			return;
		}
		// Else, store current node and recur for its children
		fprintf(fp, "%d ", root->key_value);
		serialize(root->left, fp);
		serialize(root->right, fp);
	}

	// This function constructs a tree from a file pointed by 'fp'
	void deSerialize(node *&root, FILE *fp)
	{
		// Read next item from file. If theere are no more items or next
		// item is marker, then return
		int val;
		if (!fscanf(fp, "%d ", &val) || val == MARKER)
			return;

		// Else create node with this item and recur for children
		insert(val);
		deSerialize(root->left, fp);
		deSerialize(root->right, fp);
	}

	// A simple inorder traversal used for testing the constructed tree
	void inorder(node *root)
	{
		if (root)
		{
			inorder(root->left);
			cout << root->key_value << ' ';
			//printf("%d ", root->key_value);
			inorder(root->right);
		}
	}

	void postorder(node* p, int indent = 0)
	{
		if (p != NULL) {
			if (p->left) postorder(p->left, indent + 4);
			if (p->right) postorder(p->right, indent + 4);
			if (indent) {
				std::cout << std::setw(indent) << ' ';
			}
			cout << p->key_value << "\n ";
		}
	}

};


int main()
{
	btree arbol;
	arbol.insert(3);
	arbol.insert(2);
	arbol.insert(10);
	arbol.insert(13);
	arbol.insert(20);
	arbol.insert(15);
	arbol.insert(8);
	arbol.insert(18);
	arbol.insert(16);
	arbol.insert(9);

	arbol.inorder(arbol.root);

	system("pause");
    return 0;
}

