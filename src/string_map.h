#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    operator[]
    * Acceso o definición de pares clave/valor
    **/

    T &operator[](const string &key);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &clave) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string&clave) const;
    T& at(const string& clave);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& clave);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

private:

    struct Nodo {
        Nodo() : siguientes(256, nullptr), definicion(nullptr) {}
        vector<Nodo*> siguientes;
        T* definicion;
    };

    Nodo* _raiz;
    int _size;
     //busca recursivamente la clave "key" en "r"
    Nodo* reBusq(Nodo*res, string key);
    //busca recursivamente la clave "key" en "r"
    Nodo* reBusq(Nodo* r, string key)const;
    //borra recursivamente todos los nodos siguientes de desde
    void reErase(Nodo* desde);
    //reCopia: copia recursivamente todos los nodos de raiz a nuevos nodos,
    // devuelve un puntero a la nueva raiz
    Nodo* reCopia(Nodo* raiz);
    //devuelve un int con el numero de nodos siguientes a nod
    int numHijos(Nodo* nod);
    };

#include "string_map.hpp"

#endif // STRING_MAP_H_
