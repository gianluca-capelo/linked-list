//Gianluca Capelo 83/19

#include "Lista.h"

Lista::Nodo::Nodo(const int &elem):valor(elem),sig(nullptr),ant(nullptr) {}

Lista::Lista(): len_(0), primero_(nullptr), ultimo_(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    while (primero_ != nullptr){
        this->eliminar(0);
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    Nodo* nodoActual = this->primero_;
    const Nodo* nodoActual_aCopiar = aCopiar.primero_;
    int longitudCopia = this->longitud();
    int longitudMasLarga = max(longitudCopia,aCopiar.longitud());
    for (int i = 0; i < longitudMasLarga ; ++i) {
        if (i >= longitudCopia) {
            this->agregarAtras(nodoActual_aCopiar->valor);
            nodoActual_aCopiar = nodoActual_aCopiar->sig;
        }
        else if (i >= aCopiar.longitud()) {
            this->eliminar(this->longitud() -1);
        }
        else {
            nodoActual->valor = nodoActual_aCopiar->valor;
            nodoActual = nodoActual->sig;
            nodoActual_aCopiar = nodoActual_aCopiar->sig;
        }
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    if (len_ == 0){
        Nodo* nuevo = new Nodo(elem);
        primero_ = nuevo;
        ultimo_ = nuevo;
    }
    else if (len_ == 1){
        Nodo* nuevo = new Nodo(elem);
        primero_ = nuevo;
        primero_->sig = ultimo_;
        ultimo_->ant = primero_;
    }
    else{
        Nodo* nuevo = new Nodo(elem);
        nuevo->sig = primero_;
        primero_->ant = nuevo;
        primero_ = nuevo;
    }
    len_++;
}

void Lista::agregarAtras(const int& elem) {
    if (len_ == 0){
        Nodo* nuevo = new Nodo(elem);
        primero_ = nuevo;
        ultimo_ = nuevo;
    }
    else if (len_ == 1){
        Nodo* nuevo = new Nodo(elem);
        ultimo_ = nuevo;
        ultimo_->ant = primero_;
        primero_->sig = ultimo_;
    }
    else{
        Nodo* c = new Nodo(elem);
        c->ant = ultimo_;
        ultimo_->sig = c;
        ultimo_ = c;
    }
    len_++;
}

void Lista::eliminar(Nat i) {
    if (len_ <= i){ //i fuera de rango , no elimina ningun elemento
        return;
    }
    else if (i == 0){
        if (len_ == 1){
            delete primero_;
            primero_ = nullptr;
            ultimo_ = nullptr;
        }
        else if(len_ == 2){
            delete primero_;
            ultimo_->ant = nullptr;
            primero_ = ultimo_;
        }
        else {
            primero_ = primero_->sig;
            delete primero_->ant;
            primero_->ant = nullptr;
        }
        len_ --;
    }
    else if (i == len_ -1){
        if(len_ == 2){
            delete ultimo_;
            primero_->sig = nullptr;
            ultimo_ = primero_ ;
        }
        else{
            ultimo_ = ultimo_->ant;
            delete ultimo_->sig;
            ultimo_->sig = nullptr;
        }
        len_ --;
    }
    else{
        Nodo* NodoAEliminar;
        if (i  <= len_ - 1 - i) {                      // caso: elemento a elimininar mas cerca del primero; recorre la lista desde el principio
            NodoAEliminar = primero_->sig;
            for (int j = 1; j < i; ++j) {
                NodoAEliminar = NodoAEliminar->sig;
            }
        }
        else {                                         // caso contrario; recorre la lista desde el final
            NodoAEliminar = ultimo_->ant;
            for (int j = 1; j < len_ -1 - i; ++j) {
                NodoAEliminar = NodoAEliminar->ant;
            }
        }
        (NodoAEliminar->ant)->sig = NodoAEliminar->sig;
        (NodoAEliminar->sig)->ant = NodoAEliminar->ant;
        delete NodoAEliminar;
        len_ --;
    }
}

int Lista::longitud() const {
    return len_;
}

const int& Lista::iesimo(Nat i) const {
    assert( i < len_ );
    Nodo* iesimoNodo;
    if (i  <= len_ - 1 - i) {
        iesimoNodo = primero_;
        for (int j = 0; j < i; ++j) {
            iesimoNodo = iesimoNodo->sig;
        }
    }
    else {
        iesimoNodo = ultimo_;
        for (int j = 0; j < len_ -1 - i; ++j) {
            iesimoNodo = iesimoNodo->ant;
        }
    }
    return iesimoNodo->valor ;
}

int& Lista::iesimo(Nat i) {
    assert( i < len_ );
    Nodo* iesimoNodo;
    if (i  <= len_ - 1 - i) {
        iesimoNodo = primero_;
        for (int j = 0; j < i; ++j) {
            iesimoNodo = iesimoNodo->sig;
        }
    }
    else{
        iesimoNodo = ultimo_;
        for (int j = 0; j < len_ -1 - i; ++j) {
            iesimoNodo = iesimoNodo->ant;
        }
    }
    return iesimoNodo->valor ;
}

void Lista::mostrar(ostream& o) {
    if(this->longitud() == 0){
        o << "[]" << endl;
    }
    else{
        o << "[";
        Nodo *nodoActual = this->primero_;
        while (nodoActual->sig != nullptr) {
            o << nodoActual->valor << ", ";
            nodoActual = nodoActual->sig;
        }
        o << this->ultimo_->valor << "]" << endl;
    }
}