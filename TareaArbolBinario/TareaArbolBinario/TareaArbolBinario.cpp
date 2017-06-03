// TareaArbolBinario.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip> 
#include <cstdlib>
using namespace std;
//Binary Search Tree Program

class BinarySearchTree
{
private:
	struct tree_node
	{
		tree_node* left;
		tree_node* right;
		int data;
	};

public:
	tree_node* root;

	BinarySearchTree()
	{
		root = NULL;
	}

	bool isEmpty() const { return root == NULL; }

	void print_inorder()
	{
		inorder(root);
	}

	void inorder(tree_node* p)
	{
		if (p != NULL)
		{
			if (p->left) inorder(p->left);
			cout << " " << p->data << " ";
			if (p->right) inorder(p->right);
		}
		else return;
	}

	void print_preorder()
	{
		preorder(root);
	}

	void preorder(tree_node* p)
	{
		if (p != NULL)
		{
			cout << " " << p->data << " ";
			if (p->left) preorder(p->left);
			if (p->right) preorder(p->right);
		}
		else return;
	}

	void print_postorder()
	{
		postorder(root);
	}

	void postorder(tree_node* p)
	{
		if (p != NULL)
		{
			if (p->left) postorder(p->left);
			if (p->right) postorder(p->right);
			cout << " " << p->data << " ";
		}
		else return;
	}

	tree_node* search(int key, tree_node *node)
	{
		if (node != NULL)
		{
			if (key == node->data)
				return node;
			if (key<node->data)
				return search(key, node->left);
			else
				return search(key, node->right);
		}
		else return NULL;
	}

	void insert(int d)
	{
		tree_node* t = new tree_node;
		tree_node* parent;
		t->data = d;
		t->left = NULL;
		t->right = NULL;
		parent = NULL;


		if (isEmpty()) root = t;
		else
		{

			tree_node* curr;
			curr = root;

			while (curr)
			{
				parent = curr;
				if (t->data > curr->data) curr = curr->right;
				else curr = curr->left;
			}

			if (t->data < parent->data)
				parent->left = t;
			else
				parent->right = t;
		}
	}

	void remove(int d)
	{
		//Locate the element
		bool found = false;
		if (isEmpty())
		{
			cout << " El arbol esta vacio! " << endl;
			return;
		}

		tree_node* curr;
		tree_node* parent;
		curr = root;
		parent = NULL;

		while (curr != NULL)
		{
			if (curr->data == d)
			{
				found = true;
				break;
			}
			else
			{
				parent = curr;
				if (d>curr->data) curr = curr->right;
				else curr = curr->left;
			}
		}
		if (!found)
		{
			cout << " no se encontro el nodo! " << endl;
			return;
		}

		//si es un nodo con un hijo
		if ((curr->left == NULL && curr->right != NULL) || (curr->left != NULL
			&& curr->right == NULL))
		{
			if (curr->left == NULL && curr->right != NULL)
			{
				if (parent->left == curr)
				{
					parent->left = curr->right;
					delete curr;
				}
				else
				{
					parent->right = curr->right;
					delete curr;
				}
			}
			else
			{
				if (parent->left == curr)
				{
					parent->left = curr->left;
					delete curr;
				}
				else
				{
					parent->right = curr->left;
					delete curr;
				}
			}
			return;
		}

		//si es un nodo sin hijos
		if (curr->left == NULL && curr->right == NULL)
		{
			if (parent->left == curr) parent->left = NULL;
			else parent->right = NULL;
			delete curr;
			return;
		}


		//si es un nodo con 2 hijos
		if (curr->left != NULL && curr->right != NULL)
		{
			tree_node* chkr;
			chkr = curr->right;
			if ((chkr->left == NULL) && (chkr->right == NULL))
			{
				curr = chkr;
				delete chkr;
				curr->right = NULL;
			}
			else
			{
				if ((curr->right)->left != NULL)
				{
					tree_node* lcurr;
					tree_node* lcurrp;
					lcurrp = curr->right;
					lcurr = (curr->right)->left;
					while (lcurr->left != NULL)
					{
						lcurrp = lcurr;
						lcurr = lcurr->left;
					}
					curr->data = lcurr->data;
					delete lcurr;
					lcurrp->left = NULL;
				}
				else
				{
					tree_node* tmp;
					tmp = curr->right;
					curr->data = tmp->data;
					curr->right = tmp->right;
					delete tmp;
				}

			}
			return;
		}

	}


	void serialize(tree_node *root, FILE *fp)
	{
		if (root == NULL)
		{
			fprintf(fp, "%d ", -1);
			return;
		}
		fprintf(fp, "%d ", root->data);
		serialize(root->left, fp);
		serialize(root->right, fp);
	}


	void deSerialize(tree_node *&root, FILE *fp)
	{
		int val;
		if (!fscanf(fp, "%d ", &val) || val == -1)
			return;
		insert(val);
		deSerialize(root->left, fp);
		deSerialize(root->right, fp);
	}

};

int main()
{
	BinarySearchTree b;
	FILE *fp;
	int ch, tmp, tmp1;
	while (1)
	{
		system("cls");
		cout << " ARBOL BINARIO DE BUSQUEDA " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. INSERTAR NODO " << endl;
		cout << " 2. IMPRIMIR IN ORDER " << endl;
		cout << " 3. IMPRIMIR PRE ORDER " << endl;
		cout << " 4. IMPRIMIR POST ORDER " << endl;
		cout << " 5. BORRAR ELEMENTO " << endl;
		cout << " 6. GUARDAR EN ARCHIVO " << endl;
		cout << " 7. LEER DE ARCHIVO " << endl;
		cout << " 8. SALIR " << endl;
		cout << " ESCRIBA LA OPCION: ";
		cin >> ch;
		switch (ch)
		{
		case 1: cout << " Ingrese numero : ";
			cin >> tmp;
			b.insert(tmp);
			break;
		case 2: cout << endl;
			cout << " In-Order " << endl;
			cout << " -------------------" << endl;
			b.print_inorder();
			cout <<endl<< " -------------------" << endl;
			break;
		case 3: cout << endl;
			cout << " Pre-Order " << endl;
			cout << " -------------------" << endl;
			b.print_preorder();
			cout << endl << " -------------------" << endl;
			break;
		case 4: cout << endl;
			cout << " Post-Order " << endl;
			cout << " --------------------" << endl;
			b.print_postorder();
			cout << endl << " -------------------" << endl;
			break;
		case 5: cout << " Numero a Borrar : ";
			cin >> tmp1;
			b.remove(tmp1);
			break;
		case 6: cout << " Se guardara el arbol en el archivo arbol.bin "<<endl;
			fp = fopen("arbol.bin", "w");
			if (fp == NULL)
			{
				puts("No se puede abrir el archivo");
				return 0;
			}
			b.serialize(b.root, fp);
			fclose(fp);
			break;
		case 7: cout << " Se leera el archivo arbol.bin y se perdera el arbol actual " << endl;
			fp = fopen("arbol.bin", "r");
			b.deSerialize(b.root, fp);
			break;
		case 8:
			return 0;

		}
		system("pause");
	}
}