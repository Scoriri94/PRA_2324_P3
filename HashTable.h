#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int count = 0;
        for (int i = 0; i < key.length(); i++) {
            count += int(key.at(i));
        }
        return count % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];  // Inicializa el array de cubetas
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() {
        return max;
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << std::endl;
        out << "===============" << std::endl;

        for (int i = 0; i < th.max; i++) {
            out << "== Cubeta " << i << " ==" << std::endl;
            out << "List => ";
            if (th.table[i].size() == 0) {
                out << "[]";
            } else {
                out << "[";
                for (int j = 0; j < th.table[i].size(); j++) {
                    const TableEntry<V>& entry = th.table[i][j];
                    out << "(" << entry.key << " => " << entry.value << ")";
                    if (j != th.table[i].size() - 1) {
                        out << " ";
                    }
                }
                out << "]";
            }
            out << std::endl;
        }
        out << "===============" << std::endl;
        return out;
    }

    V operator[](std::string key) {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); i++) {
            TableEntry<V>& entry = bucket[i];
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("No existe un valor para esta clave");
    }

    void insert(const std::string& key, V value) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); i++) {
            TableEntry<V>& entry = bucket[i];
            if (entry.key == key) {
                throw std::runtime_error("Esta clave ya existe");
            }
        }

        bucket.append(TableEntry<V>{key, value});
        n++;
    }

    V search(const std::string& key) {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); i++) {
            TableEntry<V>& entry = bucket[i];
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("No existe un valor para esta clave");
    }

    V remove(const std::string& key) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];

        for (int i = 0; i < bucket.size(); i++) {
            TableEntry<V>& entry = bucket[i];
            if (entry.key == key) {
                V value = entry.value;
                bucket.remove(i);
                n--;
                return value;
            }
        }
        throw std::runtime_error("No se pudo eliminar la clave porque no existe.");
    }

    int entries() override {
        return n;
    }
};

#endif

