int FloorFloat(float);
int CeilFloat(float);
int AbsInt(int);

int FloorFloat(float valor)
{
    int redondeo = valor;
    return redondeo;
}

int CeilFloat(float valor)
{
    int redondeo = valor;
    redondeo++;
    return redondeo;
}

int AbsInt(int valor)
{
    int abs;
    if(valor < 0)
        abs = -valor;
    else
        abs = valor;
    return abs;
}
