#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
	BSNode<T> *root;
    public:
        BSTree() : nelem(0), root(nullptr) {}
	
	int size() const {
		return nelem;
	}

	T search(T e) const {
		BSNode result = search(root, e);
	}
	
	T operator[](T e) const {
		BSNode<T>* n = search(e);
			return n->elem; 

	}

	void insert(T e) {
		 root = insert(root, e);
		 nelem++; 
	}

	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
		bst.print_inorder(out, bst.root);
		return out;
	}

	void remove(T e) {
		root = remove(root, e);
	}

	~BSTree() {
	       delete_cascade(root);
	}	       

    private:
	BSNode<T>* search(BSNode<T>* n, T e) const {
		if (n == nullptr) {
			throw std::runtime_error("No se encuentra el elemento.");
		} else if (e == n->elem) {
			return n;
		} else if (e < n->elem) {
			return search(n->le {
			return search(n->right, e);
		}
	}

	BSNode<T>* insert(BSNode<T>* n, T e) {
		if (n == nullptr) {
			return new BSNode(e);
		} else if (n->elem == e) {
			throw std::runtime_error("El elemento ya existe en el árbol");
		
		} else if (n->elem < e) {
		  	return insert(n->right, e);
	        
		} else if (n->elem > e) {
	 		return insert(n->left, n);		
		}
	}

	void print_inorder(std::ostream &out, BSNode<T>* n) const {
		if (n == nullptr) {
			return;
		}
		print_inorder(out, n->left);

	      	out << n->data << " - ";
		
		print_inorder(out, n->right);
	
	}    

	BSNode<T>* remove(BSNode<T>* n, T e) {
		if (n == nullptr) {
			throw std::runtime_error("El elemento no existe");
		} else if (e < n->data) {
			n->left = remove(n->left, e);
		} else if (e > n->data) {
			n->right = remove(n->right, e);
		} else {//porque sabemos que e == e->elem?
		       if (n->left != nullptr && n->right != nullptr) {
				n->data =  max(e->left);
			        n->left = remove_max(n->left);
			} else {
				BSNode<T>* temp = (n->left != nullptr) ? n->left : n->right;
				delete n;
				nelem--;
				return temp;
			}
		}
		return n;
 	}

	T max(BSNode<T>* n) const {
		if (n == nullptr) {
			throw std::runtime_error("Elemento no encontrado");

		} 
		if (n->right != nullptr) {
			return max(n->right);
		} else {
			return n->data;
		}
	}

	BSNode<T>* remove_max(BSNode<T>* n) {
		if (n->right == nullptr) {
			BSNode<T>* temp =  n->left;
			delete n;
			nelem--;
			return temp;
		} else {
			n->right = remove_max(n->right);
			return n;
		}
	}
				
	void delete_cascade(BSNode<T>* n) {
		if (n == nullptr) {
			return;
		}

		delete_cascade(n->left);
		delete_cascade(n->right);

		delete n;
	}
				
					
};

#endif
