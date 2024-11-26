#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../PRA_2324_P1/ListLinked.h"  

#include "Dict.h"
#include "TableEntry.h"
#include <stdexcept>
#include <ostream>

template <typename V>
class HashTable : public Dict<V> {
	private:
		int n;//num elementos almacenados live
		int max;//tamaño tabla
		ListLinked<TableEntry<V>>* table;//tabla de cubetas, almacenan pares clave->valor de tipo TE<V>
	private:
		int h(std::string key) {
			int count = 0;
			for (int i = 0; i < key.length(); i++) {
			       count += int(key.at(i));
			}
			return count % max;	       
		}

		HashTable(int size) : n(0), max(size) {
			table = new ListLinked<TableEntry<V>>[max];
		}

		~HashTable() {
			delete[] table;
		}

		int capacity() {
			return max;
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
			for( int i = 0; i < th.max; i++) {
				out << "Bucket " << i << "=> ";
				if (th.table[i].n == 0) {
					out << "[]";
				} else {

					out << "[";
					for( int j = 0; j < th.table[i].n; j++) {
						const TableEntry<V>& entry = th.table[i][j];
						out << "(Clave: " << entry.key << ", Valor: "<< entry.value << ")";
						if (j != th.table[i].n - 1) {
							out << " -> ";
						}
					}
			        	out << "]";
				}
				out << std::endl;
			}
			return out;
		}	
		
		V operator[](std::string key) {
			int index = h(key);
			ListLinked<TableEntry<V>>* bucket = table[index];

			for ( int i = 0; i < bucket->n; i++) {
				TableEntry<V>& entry =(*bucket)[i];  
				if (entry.key == key) {
					return entry.value;
				}
			}
			throw std::runtime_error("No existe un valor para esta clave");
		}

		void insert(std::string key, V value) override {
			int index = h(key);

			if (table[index] == nullptr) {//si es bucket no esta inicializado crea una nueva lista para esta clave
				table[index] = new ListLinked<TableEntry<V>>();
			}

			ListLinked<TableEntry<V>>* bucket = table[index];
			//verfica si la clave ya existe
			for (int i = 0; i < bucket->size(); i++) {
				TableEntry<V>& entry = (*bucket)[i];
				if (entry.key == key) {
				throw std::runtime_error("Esta clave ya existe");
				}
			}
			bucket->insert(bucket->size(), TableEntry<V>{key, value});
			n++;
		}

		V search(std::string key) {
			int index = h(key);
   			ListLinked<TableEntry<V>>& bucket = table[index]; // Accede al bucket correspondiente.

    			for (int i = 0; i < bucket->n; i++) { // Recorre los elementos en el bucket.
        			TableEntry<V>& entry = bucket[i];
       				if (entry.key == key) {
            			return entry.value; // Retorna el valor asociado a la clave.
        			}
   			}	

   			 throw std::runtime_error("No existe un valor para esta clave");
		}

		V remove(std::string key) override {
   			 int index = h(key);
    			 ListLinked<TableEntry<V>>& bucket = table[index]; // Accede al bucket correspondiente.

    			for (int i = 0; i < bucket->n; i++) { // Recorre los elementos en el bucket.
        			TableEntry<V>& entry = bucket[i];
        			if (entry.key == key) {
            			V value = entry.value; // Guarda el valor antes de eliminarlo.

            			bucket.remove(i); // Elimina el elemento en la posición i.
            			n--;
            			return value; // Retorna el valor eliminado.
        			}
    			}

    			throw std::runtime_error("No se pudo eliminar la clave porque no existe.");
		}

		int entries() override {
			int total_entries = 0;


    			for (int i = 0; i < max; i++) { // Recorre todos los buckets.
        			ListLinked<TableEntry<V>>& bucket = table[i];
				if (bucket != nullptr) {
      	  			total_entries += bucket->n; // Suma el número de entradas en cada bucket.
   				}
			}
   			return total_entries; // Devuelve el número total de entradas en la tabla.
		}

};
		
#endif
