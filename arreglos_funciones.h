void InvCadena(char *);
void IntACadena(int, char *);
int PonArregloInt(int *);

void InvCadena(char *cadena)
{
    int longitud = 0;
    while(*(cadena + longitud))
        longitud++;

    char aux;
    for(int i = 0; i < longitud / 2; i++)
    {
        aux = *(cadena + i);
        *(cadena + i) = *(cadena + longitud - 1 - i);
        *(cadena + longitud - 1 - i) = aux;
    }
}

void IntACadena(int numero, char *cadena)
{
    int numero_copia = numero;
    if(numero < 0)
        numero_copia *= -1;
    int i = 0;
    do
        *(cadena + i++) = numero_copia % 10 + 48;
    while(numero_copia /= 10);
    if(numero < 0)
        *(cadena + i++) = 45;
    *(cadena + i) = 0;
    InvCadena(cadena);
}

int PonArregloInt(int *arreglo)
{
    int valida;
    int arreglo_longitud = 0;
    do
    {
        valida = scanf("%d", arreglo + arreglo_longitud);
        if(valida == 1)
            arreglo_longitud++;
    }while(valida == 1);
    return arreglo_longitud;
}

int PonArregloIntDin(int **arreglo)
{
    int valida;
    int arreglo_longitud = 0;
    int *x = (int *)malloc((arreglo_longitud + 1) * sizeof(int));
    int *y;
    while((valida = scanf("%d", x + arreglo_longitud)) == 1)
    {
        arreglo_longitud++;
        y = realloc(x, (arreglo_longitud + 1) * sizeof(int));
        if(y == NULL)
        {
            free(y);
            return 0;
        }
        x = y;
    }
    *arreglo = x;
    return arreglo_longitud;
}

void CopiaCadena(char *destino, char *origen)
{
    int i = 0;
    while((destino[i] = origen[i]))
        i++;
}

void Concatena(char *agregando, char *agregado)
{
    int i;
    for(i = 0; agregando[i]; i++);
    for(int j = 0; agregado[j]; j++, i++)
        agregando[i] = agregado[j];
    agregando[i] = 0;
}
