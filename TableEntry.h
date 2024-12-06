#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <iostream>

template <typename V>
class TableEntry {
	public:
		std::string key;
		V value;
	public:
		TableEntry(const std::string& key, V value) : key(key), value(value) {}
		
	       	TableEntry(const std::string key) : key(key), value(V()) {}
		
		TableEntry(): key("") {}

		friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
		return (te1.key == te2.key);
		}

		friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
		return !(te1 == te2);
		}

		friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te) {
		out << "Clave: " << te.key << std::endl << "Valor: " << te.value;
		return out;
		}

		friend bool operator<(const TableEntry<V>& te1, const TableEntry<V>& te2) {
		       return te1.key < te2.key;
		}

		friend bool operator>(const TableEntry<V>& te1, const TableEntry<V>& te2) {
		       return te1.key > te2.key;
		}	       

};

#endif
