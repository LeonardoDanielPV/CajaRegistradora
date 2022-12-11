typedef struct
{
    void **datos;
    int datos_long;
} TablaHash;

void InciarTablaHash(TablaHash *tablaHash, int cantidad)
{
    tablaHash->datos = (void **)malloc(sizeof(void *) * cantidad);
    tablaHash->datos_long = cantidad;
    for(int i = 0; i < cantidad; i++)
        tablaHash->datos[i] = NULL;
}

void InsertarDato(TablaHash tablaHash, void *dato)
{
    int clave = Funcion(tablaHash.datos_long, dato);

    int i = 0;
    while(tablaHash.datos[clave + i] != NULL)
    {
        if(clave + i == tablaHash.datos_long - 1)
            i = -clave;
        else
            i++;
    }
    tablaHash.datos[clave + i] = dato;
}

void *ObtenerDato(TablaHash tablaHash, void *dato)
{
    if(tablaHash.datos_long == 0)
        return NULL;
    
    int clave = Funcion(tablaHash.datos_long, dato);

    int i = 0;
    int contador = 0;
    while(!CompDatos(tablaHash.datos[clave + i], dato))
    {
        if(clave + i == tablaHash.datos_long - 1)
            i = -clave;
        else
            i++;
        
        contador++;
        if(contador == tablaHash.datos_long)
            return NULL;
    }

    return tablaHash.datos[clave + i];
}

void LiberarTablaHash(TablaHash *tablaHash)
{
    LiberarDatos(tablaHash->datos, tablaHash->datos_long);
    free(tablaHash->datos);
    tablaHash->datos = NULL;
    tablaHash->datos_long = 0;
}
