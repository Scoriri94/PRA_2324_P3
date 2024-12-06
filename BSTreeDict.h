#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

	private:
		BSTree<TableEntry<V>>* tree;

	public:
		BSTreeDict() {
			tree = new BSTree<TableEntry<V>>();
		}
		
		~BSTreeDict() {
		       delete tree;
		}

		friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &abs) {
		out << *abs.tree;
		return out;
		}

		V operator[](std::string key) {
			TableEntry<V>  entry(key);
			try {
				TableEntry<V> result = tree->search(key);
				return result.value;
			} catch (std::runtime_error&) {
				throw std::runtime_error("Clave no encontrada.");
			}		
		}


		void insert(const std::string& key, V value) override {
			TableEntry<V> entry(key, value);		
			tree->insert(entry);
		}

		V search(const std::string& key) override {
			TableEntry<V> entry(key);	
			try {
				TableEntry<V> result = tree->search(entry);
				return result.value;
			} catch (std::runtime_error&) {
				throw std::runtime_error("Clave no encontrada");
			}
		}

		V remove(const std::string& key) {
			TableEntry<V> entry(key);
			try {
				TableEntry<V> result = tree->remove(key);
				return result.value;
			} catch (std::runtime_error&) {
				throw std::runtime_error("La clave no esta en el árbol.");
			}
		}

		int entries() override {
			return tree->nelem;
		}
};

#endif 

