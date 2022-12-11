/* Programa para almacenar, consultar y borrar información sobre articulos del stock de una tienda departamental
   con ayuda de un menú de usuario. Permite a su vez realizar ventas. */

/* En este programa se asume que las asignaciones de memoria dinamica son siempre satisfactorias. */

// ----------- Funciones de uso general -----------

#include <stdio.h>
#include <stdlib.h>
#include "C:\Programas\ESCOM_NS_ISC_S2_AED_(C)\Herramientas\matematicas_funciones.h"
#include "C:\Programas\ESCOM_NS_ISC_S2_AED_(C)\Herramientas\arreglos_funciones.h"

// ----------- Funciones para pila -----------

#include "C:\Programas\ESCOM_NS_ISC_S2_AED_(C)\Practicas\Caja registradora\Pila.h"

// ----------- Funciones para tabla hash -----------

int Funcion(int, void *);
int CompDatos(void *, void *);
void LiberarDatos(void **, int);
#include "C:\Programas\ESCOM_NS_ISC_S2_AED_(C)\Practicas\Caja registradora\TablaHash.h"

// ----------- Funciones para interfaz -----------

void ImpMenuUsuario(char *);
char Seleccion();

// ----------- Funciones y datos para manejar el stock -----------

char encReal[64] = "id,caducidad,precio,unidades,nombre";
typedef struct
{
    int id;
    char caducidad[64];
    int precio;
    int unidades;
    char nombre[64];
} producto;
int ValidaEncabezado(char *);
TablaHash *Cargar(char *);
TablaHash *AgregarProducto(char *);
producto *ConsultarProducto(TablaHash, int);
void ImprimirProductos(producto **, int);
void CopiarProducto(producto *, producto);

// ----------- Funciones para vender articulos -----------

void AgregarALista(TablaHash, Pila *, int);
producto *EliminarALista(TablaHash, Pila *);
void VenderLista(TablaHash, Pila *);

int main(int argc, char **argv)
{
    TablaHash *productos = Cargar("BaseDatos.txt");

    Pila lista;
    IniciarPila(&lista);

    producto *pActual;
    int idActual;

    ImpMenuUsuario("MenuUsuario.txt");
    printf("Por favor elegir (1-8/x)");
    int salir = 0;
    int s;
    while(!salir)
    {
        s = Seleccion();
        if(s == '1')
        {
            printf("Id: ");
            scanf("%d", &idActual);
            AgregarALista(*productos, &lista, AbsInt(idActual));
        }
        else if(s > '1' && s < '5')
        {
            if(!lista.cantidad)
                printf("No hay articulos en la lista");
            else if(s == '2')
            {
                pActual = EliminarALista(*productos, &lista);
                printf("Se quito %s", pActual->nombre);
            }
            else if(s == '3')
            {
                while(lista.cantidad > 0)
                     EliminarALista(*productos, &lista);
                printf("Hecho");
            }
            else if(s == '4')
            {
                VenderLista(*productos, &lista);
            }
        }
        else if(s > '4' && s < '9')
        {
            if(s == '5')
            {
                Vaciar(&lista);
                LiberarTablaHash(productos);
                free(productos);
                productos = AgregarProducto("BaseDatos.txt");
            }
            else if(s == '6')
            {
                printf("Id: ");
                scanf("%d", &idActual);
                if((pActual = ConsultarProducto(*productos, idActual)))
                    ImprimirProductos(&pActual, 1);
                else
                    printf("No existe el producto");
            }
            else if(s == '7')
            {
                ImprimirProductos((producto **)(productos->datos), productos->datos_long);
            }
            else if(s == '8')
            {
                printf("Proximamente");
            }
        }
        else if(s == 'x')
        {
            Vaciar(&lista);
            LiberarTablaHash(productos);
            free(productos);
            salir = 1;
        }
        else
            printf("Nada seleccionado");
    }
}

//////////////////////////////////////////////////////////////////

int Funcion(int longitud, void *dato)
{
    producto *actual = (producto *)dato;
    int clave = actual->id % longitud;
    return clave;
}

int CompDatos(void *dato1, void *dato2)
{
    producto *p1 = (producto *)dato1;
    producto *p2 = (producto *)dato2;
    if(p1->id == p2->id)
        return 1;
    return 0;
}

void LiberarDatos(void **datos, int datos_longitud)
{
    for(int i = 0; i < datos_longitud; i++)
        free(datos[i]);
}

//////////////////////////////////////////////////////////////////

void ImpMenuUsuario(char *menu)
{
    FILE *arch = fopen(menu, "rt");
    char c;
    while(fscanf(arch, "%c", &c) != EOF)
        putchar(c);
}

char Seleccion()
{
    fflush(stdin);
    char c;
    printf("\n>>> ");
    scanf("%c", &c);
    while(getchar() != '\n');
    return c;
}

//////////////////////////////////////////////////////////////////

int ValidaEncabezado(char *encabezado)
{
    int i;
    for(i = 0; encReal[i] && encabezado[i]; i++)
        if(encReal[i] != encabezado[i])
            return 0;
    if(!encReal[i])
        return 1;
    return 0;
}

TablaHash *Cargar(char *baseDatos)
{
    TablaHash *tablaHash = (TablaHash *)malloc(sizeof(TablaHash));
    tablaHash->datos = NULL;
    tablaHash->datos_long = 0;

    FILE *arch = fopen(baseDatos, "rt");
    if(!arch)
    {
        arch = fopen(baseDatos, "wt");
        fprintf(arch, "%s\n", encReal);
        fclose(arch);
        return tablaHash;
    }

    char encabezado[64];
    fscanf(arch, "%s", encabezado);
    if(!ValidaEncabezado(encabezado))
    {
        printf("error: base de datos corrupta, corrigiendo...\n");
        fclose(arch);
        arch = fopen(baseDatos, "wt");
        fprintf(arch, "%s\n", encReal);
        fclose(arch);
        return tablaHash;
    }

    producto *productos;
    productos = NULL;
    int productos_long = 0;

    int id;
    char caducidad[64];
    int precio;
    int unidades;
    char nombre[64];

    int valida;
    do
    {
        fscanf(arch, "%d,%[^,],%d,%d,", &id, caducidad, &precio, &unidades);
        valida = fscanf(arch, "%[^\n]", nombre);
        if(valida == 1)
        {
            productos = (producto *)realloc(productos, sizeof(producto) * (productos_long + 1));
            productos_long += 1;
            productos[productos_long - 1].id = id;
            CopiaCadena(productos[productos_long - 1].caducidad, caducidad);
            productos[productos_long - 1].precio = precio;
            productos[productos_long - 1].unidades = unidades;
            CopiaCadena(productos[productos_long - 1].nombre, nombre);
        }
    } while(valida == 1);
    fclose(arch);

    producto *pActual;
    InciarTablaHash(tablaHash, productos_long);
    for(int i = 0; i < productos_long; i++)
    {
        pActual = (producto *)malloc(sizeof(producto));
        CopiarProducto(pActual, productos[i]);
        InsertarDato(*tablaHash, pActual);
    }
    free(productos);
    return tablaHash;
}

TablaHash *AgregarProducto(char *baseDatos)
{
    producto actual;

    printf("Id: ");
    scanf("%d", &actual.id);
    while(getchar() != '\n');
    printf("Nombre: ");
    scanf("%[^\n]", actual.nombre);
    while(getchar() != '\n');
    printf("Fecha de caducidad (dd-mm-aaaa): ");
    scanf("%s", actual.caducidad);
    while(getchar() != '\n');
    printf("Precio: ");
    scanf("%d", &actual.precio);
    while(getchar() != '\n');
    printf("Unidades: ");
    scanf("%d", &actual.unidades);
    while(getchar() != '\n');

    FILE *arch = fopen(baseDatos, "at");
    fprintf(arch, "%d,%s,%d,%d,%s\n", actual.id, actual.caducidad, actual.precio, actual.unidades, actual.nombre);
    fclose(arch);

    printf("Agregado");
    return Cargar(baseDatos);
}

producto *ConsultarProducto(TablaHash tablaHash, int id)
{
    producto actual;
    actual.id = id;
    return ObtenerDato(tablaHash, &actual);
}

void ImprimirProductos(producto **p, int cantidad)
{
    puts("Id\tNombre\tPrecio\tCaducidad\tUnidades");
    for(int i = 0; i < cantidad; i++)
        printf("%d\t%s\t%d\t%s\t%d\n", p[i]->id, p[i]->nombre, p[i]->precio, p[i]->caducidad, p[i]->unidades);
}

void CopiarProducto(producto *destino, producto origen)
{
    CopiaCadena(destino->caducidad, origen.caducidad);
    destino->id = origen.id;
    CopiaCadena(destino->nombre, origen.nombre);
    destino->precio = origen.precio;
    destino->unidades = origen.unidades;
}

//////////////////////////////////////////////////////////////////

void AgregarALista(TablaHash productos, Pila *lista, int id)
{
    int *idAp = (int *)malloc(sizeof(int));
    *idAp = id;

    producto actual;
    actual.id = id;
    producto *agregar = (producto *)ObtenerDato(productos, &actual);
    if(!agregar)
        printf("El articulo no existe");
    else if(agregar->unidades > 0)
    {
        Push(lista, idAp);
        agregar->unidades -= 1;
        printf("Se agrego %s", agregar->nombre);
    }
    else
        printf("No hay unidades disponibles");
}

producto *EliminarALista(TablaHash productos, Pila *lista)
{
    int *id;
    producto actual;
    producto *quitar;
    
    id = (int *)Pop(lista);
    actual.id = *id;
    quitar =(producto *)ObtenerDato(productos, &actual);
    quitar->unidades += 1;
    free(id);
    return quitar;
}

void VenderLista(TablaHash productos, Pila *lista)
{
    int *id;
    producto actual;
    producto *vender;
    if(lista->cantidad == 0)
    {
        printf("La lista de venta esta vacia");
        return;
    }
    while(lista->cantidad > 0)
    {
        id = (int *)Pop(lista);
        actual.id = *id;
        vender = (producto *)ObtenerDato(productos, &actual);
        ImprimirProductos(&vender, 1);
        putchar('\n');
        free(id);
    }
}
