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
            BSNode<T>* resultNode = search(root, e);
            return resultNode->elem;
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

        T remove(T e) {
            root = remove(root, e);
            nelem--;  // Decrementar el número de elementos después de eliminar
            return e; // Devolver el valor eliminado
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
                return search(n->left, e);
            } else {
                return search(n->right, e);
            }
        }

        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                return new BSNode<T>(e);
            } else if (n->elem == e) {
                throw std::runtime_error("El elemento ya existe en el árbol");
            } else if (n->elem < e) {
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);        
            }
            return n;
        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n == nullptr) {
                return;
            }
            print_inorder(out, n->left);
            out << n->elem << " - ";
            print_inorder(out, n->right);
        }

        BSNode<T>* remove(BSNode<T>* n, const T e) {
            if (n == nullptr) {
                throw std::runtime_error("El elemento no existe");
            } else if (e < n->elem) {
                n->left = remove(n->left, e);
            } else if (e > n->elem) {
                n->right = remove(n->right, e);
            } else {
                // Caso 1: Nodo con solo un hijo o sin hijos
                if (n->left == nullptr) {
                    BSNode<T>* temp = n->right;
                    delete n;
                    return temp;
                } else if (n->right == nullptr) {
                    BSNode<T>* temp = n->left;
                    delete n;
                    return temp;
                }

                // Caso 2: Nodo con dos hijos
                n->elem = max(n->left);  // Reemplazar el valor con el máximo del subárbol izquierdo
                n->left = remove_max(n->left);  // Eliminar el nodo que tiene el máximo valor
            }
            return n;
        }

        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado");
            }
            while (n->right != nullptr) {
                n = n->right;
            }
            return n->elem;  // Devolver el valor máximo
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                BSNode<T>* temp = n->left;
                delete n;
                return temp;
            }
            n->right = remove_max(n->right);
            return n;
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

