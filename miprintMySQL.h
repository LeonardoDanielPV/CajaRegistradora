int MaxInt(int x, int y)
{
    if(x > y)
        return x;
    return y;
}

int Coincidencias(char *arreglo, char c)
{
    int coincidencias = 0;
    for(int i = 0; arreglo[i]; i++)
        coincidencias += (arreglo[i] == c);
    return coincidencias;
}

void ImpSepHorizontal(int *CLMax, int columnas_longitud)
{
    for(int i = 0; i < columnas_longitud; i++)
    {
        putchar('+');
        for(int j = 0; j < CLMax[i] + 2; j++)
            putchar('-');
    }
    putchar('+');
    putchar('\n');
}

void ImpFila(int *CLMax, char *elementosSC, int columnas_longitud)
{
    putchar('|');

    for(int i = 0, j = 0; i < columnas_longitud; i++)
    {
        putchar(' ');
        int impresos = 0;
        while(elementosSC[j++] != ',' && elementosSC[j - 1])
        {
            putchar(elementosSC[j - 1]);
            impresos++;
        }
        while(impresos++ < CLMax[i])
            putchar(' ');
        putchar(' ');
        putchar('|');
    }
    putchar('\n');
}

void ImpTablasSC(char **columnas, int columnas_longitud)
{
    int CLMax[columnas_longitud]; // Columna Longitud Maxima
    for(int i = 0; i < columnas_longitud; i++)
        CLMax[i] = 0;
    char *columnaActual;
    char c;

    for(int i = 0; i < columnas_longitud; i++)
    {
        columnaActual = *(columnas + i);

        int j = 0;
        int CLActual = 0;
        do
        {
            c = columnaActual[j];
            if(c == ',' || !c)
                CLMax[i] = MaxInt(CLMax[i], CLActual);
            CLActual = (CLActual + 1) * !!(c - 44);
            j++;
        } while(c);
    }

    ImpSepHorizontal(CLMax, columnas_longitud);

    int apRenglon[columnas_longitud]; // Desplazamiento para llegar al apRenglon[i]-ésimo renglon de cada i-ésima columna
    for(int i = 0; i < columnas_longitud; i++)
        apRenglon[i] = 0;

    int caracteres = columnas_longitud;
    for(int i = 0; i < columnas_longitud; i++)
        caracteres += CLMax[i];
    char elementosSC[caracteres];
    int renglones = Coincidencias(*(columnas), ',') + 1; // Se asume cada renglo NO termina con ','

    int desplazamiento = 0;
    for(int i = 0; i < columnas_longitud; i++)
    {
        columnaActual = *(columnas + i);
        int j = apRenglon[i];
        do
        {
            c = columnaActual[j++];
            elementosSC[desplazamiento++] = c + ',' * !c;
        } while(c != ',' && c);
        apRenglon[i] = j;
    }
    ImpFila(CLMax, elementosSC, columnas_longitud);
    ImpSepHorizontal(CLMax, columnas_longitud);
    for(int r = 1; r < renglones; r++)
    {
        desplazamiento = 0;
        for(int i = 0; i < columnas_longitud; i++)
        {
            columnaActual = *(columnas + i);
            int j = apRenglon[i];
            do
            {
                c = columnaActual[j++];
                elementosSC[desplazamiento++] = c + ',' * !c;
            } while(c != ',' && c);
            apRenglon[i] = j;
        }
        ImpFila(CLMax, elementosSC, columnas_longitud);
    }
    ImpSepHorizontal(CLMax, columnas_longitud);
}

