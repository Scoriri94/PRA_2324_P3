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

	BSNode<T>* search(BSNode<T>* n, T e) const {
		if (n == nullptr) {
			throw std::runtime_error("No se encuentra el elemento.");
		} if (e == n->elem) {
			return n;
		} if (e < n->elem) {
			return search(n->left, e);
		} else (e > n->elem) {
			return search(n->right, e);
		}
	}			
    
};

#endif
