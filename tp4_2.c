#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Defincion de cabeza

struct Tarea{
    int TareaID;   //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion   //Entre 10-100
};
typedef struct Tarea **Lista;

//Defincion de funciones

void BusquedaPorPalabra(Lista tareasRealizadas, Lista listas, char*palabra,int cantidad,int desc);

//Funcion principal
int main(){

//Defincion de variables

srand(time(NULL));
Lista listas, tareasRealizadas;
int cant, resp,desicion,desicion2;
char *buff;
char aux[100];

//Cantidad de tareas a realizar
printf("Ingrese la cantidad de tareas a realizar: ");
scanf("%d", &cant);

//Asignacion de memoria dinamica
listas= (struct Tarea**)malloc(cant*sizeof(struct Tarea*));
buff=(char*)malloc(100*sizeof(char));

//Cargado de tareas
for (int i = 0; i < cant; i++)
{
    fflush(stdin);
    listas[i]=(struct Tarea*)malloc(sizeof(struct Tarea));
    listas[i]->TareaID=i+1;
    listas[i]->Duracion=rand()%91+10;
    
    printf("\nIngrese descripcion de la tarea: ");
    gets(buff);

    listas[i]->Descripcion=(char*)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(listas[i]->Descripcion, buff);
}

//Mostrar tareas y mover los arreglos
tareasRealizadas=(struct Tarea**)malloc(cant*sizeof(struct Tarea));

for (int i = 0; i < cant; i++)
{
    printf("\nRealizo la tarea N %d?(1 para Si, 0 para No): ", listas[i]->TareaID);
    scanf("%d", &resp);

    if (resp==1)
    {
        tareasRealizadas[i]=listas[i];
        listas[i]=NULL;
    }
}
printf("\n\n");
puts("-----------Tareas pendientes: -------------");
    for (int i = 0; i < cant; i++)
    {
        if (listas[i]!=NULL)
        {
            printf("\nID de la tarea: %d", listas[i]->TareaID);
            printf("\n Duracion de la tarea: %d", listas[i]->Duracion);
            printf("\nDescripcion de la tarea: ");
            puts(listas[i]->Descripcion);
        }
    }
    
puts("--------------Tareas realizadas: ---------");   
for (int i = 0; i < cant; i++)
{
    if (tareasRealizadas[i]==NULL)continue;
    {
        printf("\nID de la tarea: %d", tareasRealizadas[i]->TareaID);
        printf("\n Duracion de la tarea: %d", tareasRealizadas[i]->Duracion);
        printf("\nDescripcion de la tarea: ");
        puts(tareasRealizadas[i]->Descripcion);
    }
}

printf("\n\n");
//Implementar funcion Busca por palabra
puts("Desea buscar alguna tarea?(Ingrese 1 para si, 0 para no): ");
scanf("%d",&desicion );
if (desicion==1)
{
    puts("Su tarea fue realizada(1) o esta pendiente(0)?: ");
    scanf("%d", &desicion2);
    fflush(stdin);
    printf("Ingresar palabra clave: ");
    gets(aux);
    fflush(stdin);
    BusquedaPorPalabra(tareasRealizadas, listas,aux,cant,desicion2);
}else{
    puts("------Fin del programa------");
}

    return 0;
}


//Definicion de funciones
void BusquedaPorPalabra(Lista tareasRealizadas, Lista listas, char*palabra,int cantidad, int desc){
      if (desc==1)
    {
        for (int i = 0; i < cantidad; i++)
        {
                if(strstr(tareasRealizadas[i]->Descripcion, palabra)){
                    printf("\nID de la tarea: %d", tareasRealizadas[i]->TareaID);
                    printf("\n Duracion de la tarea: %d", tareasRealizadas[i]->Duracion);
                    printf("\nDescripcion de la tarea: ");
                    puts(tareasRealizadas[i]->Descripcion);
                    
                }
        }
    }else{
        
            for (int i = 0; i < cantidad; i++){
                    if (strstr(listas[i]->Descripcion, palabra)){
                        printf("\nID de la tarea: %d", listas[i]->TareaID);
                        printf("\n Duracion de la tarea: %d", listas[i]->Duracion);
                        printf("\nDescripcion de la tarea: ");
                        puts(listas[i]->Descripcion);
                      
                    }
            }
       }
}

