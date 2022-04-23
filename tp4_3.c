#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Definicion de estructuras
typedef struct Tarea
{
    int TareaID;       // Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

struct Nodo
{
    struct Tarea T;
    struct Nodo *siguiente;
};
typedef struct Nodo *Lista;

// Defincion de funciones
Lista insertarNodo(Lista pendiente, Tarea tarea);
void mostrarTarea(Tarea tarea);
Lista borrarNodo(Lista cabeza, int ID);
Lista busquedaPorId(Lista cabeza, int ID);
Lista busquedaPorPalabra(Lista cabeza, char *palabra);

// Funcion principal
int main()
{
    Tarea nuevaTarea;
    Lista tareasRealizadas, tareasPendientes, auxiliar;

    srand(time(NULL));

    int cant, cont, ID;
    char aux[100];

    tareasPendientes = NULL;
    tareasRealizadas = NULL;

    // Cargar tareas
    puts("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cant);

    for (int i = 0; i < cant; i++)
    {
        nuevaTarea.TareaID = i + 1;

        printf("Tarea %d - Ingresar descripcion: ", i + 1);
        fflush(stdin);
        gets(aux);
        nuevaTarea.Descripcion = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(nuevaTarea.Descripcion, aux);

        nuevaTarea.Duracion = rand() % 91 + 10;
        tareasPendientes = insertarNodo(tareasPendientes, nuevaTarea);
    }

    // Cargar tareas pendientes en realizadas
    auxiliar = tareasPendientes;
    printf("\n");
    for (int i = 0; i < cant; i++)
    {

        mostrarTarea(auxiliar->T);

        printf("Se realizo la tarea? (1: Si / 0: No): ");
        fflush(stdin);
        scanf("%d", &cont);
        fflush(stdin);

        if (cont == 1)
        {
            tareasRealizadas = insertarNodo(tareasRealizadas, auxiliar->T);
            auxiliar = auxiliar->siguiente;
            tareasPendientes = borrarNodo(tareasPendientes, cant - i);
        }
        else
        {
            auxiliar = auxiliar->siguiente;
        }
    }

    // Mostrar tareas realizadas y tareas pendientes
    puts("---------Tareas pendientes:---------------");
    auxiliar = tareasPendientes;
    while (auxiliar != NULL)
    {
        mostrarTarea(auxiliar->T);
        printf("\n");
        auxiliar = auxiliar->siguiente;
    }

    puts("-----------Tareas realizadas:------------");
    auxiliar = tareasRealizadas;
    while (auxiliar != NULL)
    {
        mostrarTarea(auxiliar->T);
        printf("\n");
        auxiliar = auxiliar->siguiente;
    }

    // Busqueda por ID
    printf("Ingrese un ID para buscar la tarea: ");
    scanf("%d", &ID);

    printf("\nPor las tareas pendientes: \n");
    auxiliar = busquedaPorId(tareasPendientes, ID);
    if (auxiliar != NULL)
    {
        mostrarTarea(auxiliar->T);
    }
    else
    {
        printf("No se encontraron tareas con el ID %d\n", ID);
    }

    printf("\nPor las tareas realizadas: \n");
    auxiliar = busquedaPorId(tareasRealizadas, ID);
    if (auxiliar != NULL)
    {
        mostrarTarea(auxiliar->T);
    }
    else
    {
        printf("No se encontraron tareas con el ID %d\n\n", ID);
    }

    // Busqueda por palabra
    printf("\nIngrese una palabra para buscar la tarea: ");
    fflush(stdin);
    gets(aux);
    fflush(stdin);

    auxiliar = busquedaPorPalabra(tareasPendientes, aux);
    printf("\nEn tareas pendientes: \n");
    if (auxiliar != NULL)
    {
        mostrarTarea(auxiliar->T);
    }
    else
    {
        printf("No se encontraron tareas con la descripcion %s\n\n", aux);
    }

    auxiliar = busquedaPorPalabra(tareasRealizadas, aux);
    printf("\nEn tareas realizadas: \n");
    if (auxiliar != NULL)
    {
        mostrarTarea(auxiliar->T);
    }
    else
    {
        printf("No se encontraron tareas con la descripcion %s\n\n", aux);
    }

    // Liberar memoria
    while (tareasPendientes != NULL)
    {
        tareasPendientes = borrarPrimerNodo(tareasPendientes);
    }

    while (tareasRealizadas != NULL)
    {
        tareasRealizadas = borrarPrimerNodo(tareasRealizadas);
    }

    //FINAL DEL PROGRAMA

    return 0;
}

Lista insertarNodo(Lista pendiente, Tarea tarea)
{
    Lista nuevoNodo;

    nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevoNodo->T = tarea;
    nuevoNodo->siguiente = pendiente;

    return nuevoNodo;
}

void mostrarTarea(Tarea tarea)
{
    printf("ID: %d\n", tarea.TareaID);
    printf("Descripcion: %s\n", tarea.Descripcion);
    printf("Duracion: %d\n", tarea.Duracion);
}

Lista borrarNodo(Lista cabeza, int ID)
{
    Lista aux, auxBorrar;

    if (cabeza == NULL)
        return cabeza;

    aux = cabeza;

    if (cabeza->T.TareaID == ID)
    {
        cabeza = cabeza->siguiente;
        free(aux);
    }
    else
    {
        while (aux->siguiente != NULL)
        {
            if (aux->siguiente->T.TareaID == ID)
            {
                auxBorrar = aux->siguiente;
                aux->siguiente = aux->siguiente->siguiente;
                free(auxBorrar);
                break;
            }

            aux = aux->siguiente;
        }
    }

    return cabeza;
}

Lista busquedaPorId(Lista cabeza, int ID)
{
    while (cabeza != NULL)
    {
        if (cabeza->T.TareaID == ID)
            return cabeza;
        cabeza = cabeza->siguiente;
    }
}

Lista busquedaPorPalabra(Lista cabeza, char *palabra)
{
    while (cabeza != NULL)
    {
        if (strcmp(cabeza->T.Descripcion, palabra) == 0)
            return cabeza;
        cabeza = cabeza->siguiente;
    }
}
