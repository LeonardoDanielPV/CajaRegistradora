typedef struct n
{
    void *dato;
    struct n*siguiente;
} nodo;

typedef struct
{
    nodo *ultimo;
    int cantidad;
} Pila;

void IniciarPila(Pila *pila)
{
    pila->ultimo = NULL;
    pila->cantidad = 0;
}

nodo *NuevoNodo(void *dato, nodo *siguiente)
{
    nodo *actual = (nodo *)malloc(sizeof(nodo));
    actual->dato = dato;
    actual->siguiente = siguiente;
}

void Push(Pila *pila, void *dato)
{
    nodo *actual = NuevoNodo(dato, pila->ultimo);
    pila->ultimo = actual;
    pila->cantidad += 1;
}

void *Pop(Pila *pila)
{
    if(!pila->ultimo)
        return NULL;
    
    nodo *ultimo = pila->ultimo;
    void *actual = ultimo->dato;
    pila->ultimo = ultimo->siguiente;
    pila->cantidad -= 1;
    free(ultimo);
    return actual;
}

void Vaciar(Pila *pila)
{
    void *actual;
    for(int i = 0; i < pila->cantidad; i++)
    {
        actual = Pop(pila);
        free(actual);
    }
}
