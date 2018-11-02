template <typename T>
string_map<T>::string_map(){
   _raiz = new Nodo;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    reErase(_raiz);
    _raiz = nullptr;
    _size = d.size();
    _raiz = reCopia(d._raiz);


}

template <typename T>
string_map<T>::~string_map(){
    for (int i = 0; i < 255 ; ++i) {
        if(_raiz->siguientes[i] != nullptr){
            reErase(_raiz->siguientes[i]);
        }
    }
    if( _raiz->definicion != nullptr){
        delete(_raiz->definicion);
    }
    delete(_raiz);
    _size = 0;
}

template <typename T>
T& string_map<T>::operator[](const string& key){
    string clave = key;
    Nodo* res = reBusq(_raiz, clave);
    bool not_def = false;
    if(res == nullptr || res->definicion == nullptr) {
        _size++;
        not_def = true;
    }
    unsigned long int tam = clave.size();
  /*  if(_raiz == nullptr){
        _raiz = new Nodo;
    }
  */Nodo* nod = _raiz;

    for (int i = 0; i < tam; ++i) {
        char ind = clave.front();
        Nodo* aux = nod->siguientes[(int)ind];
        if(aux == nullptr){
            not_def = true;
            Nodo* nuevo = new Nodo;
            nod->siguientes[(int)clave.front()] = nuevo;
        }
        nod = nod->siguientes[(int)clave.front()];
        clave.erase(0,1);
    }
    if(not_def){
        nod->definicion = new T;
    }
    return *nod->definicion;

}


template <typename T>
int string_map<T>::count(const string& clave) const{
    int res = 0;
    Nodo * aux = reBusq(_raiz,clave);
    if( aux != nullptr && aux->definicion != nullptr){
        res = 1;
    }
    return res;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    return reBusq(_raiz, clave)->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    return reBusq(_raiz, clave)->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* padre = _raiz;
    Nodo* actual= nullptr;
    Nodo* sig= nullptr;
    actual = reBusq(_raiz, clave);
    if (numHijos(actual) >0){
        //caso: es prefijo, borro la def solamente
        delete( actual->definicion );
        actual->definicion = nullptr;
    }else{
        //caso: es hoja
        actual = _raiz;
        char letra = '\0';
        int tam = clave.size() -1;
        for (int i = 0; i < tam ; ++i) {
            sig = reBusq(_raiz, clave.substr(0,i));
            if(numHijos(sig) != 1 || sig->definicion != nullptr){
                letra = clave[i];
                actual = sig;
            }
        }
        if(letra != '\0'){
            reErase(actual->siguientes[letra]);
            actual->siguientes[letra] = nullptr;
        }else{
            reErase(_raiz->siguientes[clave.front()]);
            _raiz->siguientes[clave.front()] = nullptr;
        }
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}
template <typename T>
typename string_map<T>::Nodo *string_map<T>::reBusq(string_map<T>::Nodo *res, string key) {
    string clave = key;
    if(this->_size != 0) {
        if (!clave.empty()) {
            int idx = (int) clave.front();

            if (res->siguientes[idx] != nullptr) {
                return reBusq(res->siguientes[idx], clave.erase(0,1));
            } else {
                return nullptr;
            }

        }
    return res;
}
    return nullptr;
}
template <typename T>
typename string_map<T>::Nodo *string_map<T>::reBusq(string_map<T>::Nodo *res, string key) const{
    string clave = key;
    if(this->_size != 0) {
        if (!clave.empty()) {
            int idx = (int) clave.front();

            if (res->siguientes[idx] != nullptr) {
                return reBusq(res->siguientes[idx], clave.erase(0,1));
            } else {
                return nullptr;
            }

        }
    return res;
}
    return nullptr;
}

template <typename T>
void string_map<T>::reErase(string_map<T>::Nodo *desde) {
    for (int i = 0; i < 256 ; ++i) {
        if(desde->siguientes[i]!= nullptr){
            reErase(desde->siguientes[i]);
        }
    }
    if(desde->definicion != nullptr){
        delete desde->definicion;
    }
    delete desde;
}
template <typename T>
typename string_map<T>::Nodo *string_map<T>::reCopia(string_map<T>::Nodo *src) {
    Nodo* dst =new Nodo();
    if( src->definicion != nullptr ) {
        T* def = new T();
        *def = *src->definicion;
        dst->definicion = def;
    }

    for (int i = 0; i <255 ; ++i) {
        if( src->siguientes[i] != nullptr){
            dst->siguientes[i]= reCopia(src->siguientes[i]);
        }
    }
    return dst;
}
template <typename T>
int string_map<T>::numHijos(string_map<T>::Nodo *nod) {
    int res =0;
    for (int i = 0; i < 256; ++i) {
        if(nod->siguientes[i]!= nullptr){
            res++;
        }
    }
    return res;
}

