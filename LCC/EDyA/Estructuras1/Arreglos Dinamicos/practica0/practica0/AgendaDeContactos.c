#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define READSIZE 50

typedef struct Contacto_{
    char* nombre;
    char telefono[20];
    unsigned int edad;

} Contacto;

typedef struct Agenda_{
    Contacto arreglo[100];
    unsigned int n;
} Agenda;


char *getnewline(){
  char buffer[READSIZE + 1], *linea = NULL;
  printf("Ingrese el nombre del contacto: ");
  scanf("%[^\n]", buffer);
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

Contacto crear_contacto(){
    
    Contacto nuevoContacto;
    nuevoContacto.nombre=getnewline();
    getchar();
    printf("\n Ingrese el telefono: ");
    scanf("%s",nuevoContacto.telefono);
    getchar();
    printf("\n Ingrese la edad: ");
    scanf("%u",&nuevoContacto.edad);
    getchar();
    return nuevoContacto;
}

void actualizar_edad(Contacto* contact){
    printf("\nIngrese la nueva edad del contacto: ");
    scanf("%d",&contact->edad);
    return;
}

void alta_contactos(Agenda *agendita){
    Contacto nuevoContacto = crear_contacto();
    agendita->arreglo[agendita->n] = nuevoContacto;
    agendita->n++;
    return;
}

void modificar_edad(Agenda* miAgenda){
    printf("\n Ingrese el nombre del contacto a buscar: ");
    char* contactoBusqueda = getnewline();
    for(int i=0; i<miAgenda->n;i++){
        if((strcmp(miAgenda->arreglo[i].nombre,contactoBusqueda)==0)){
            actualizar_edad(&(miAgenda->arreglo[i]));
            printf("\nAhora la edad del contacto es: %d\n",miAgenda->arreglo[i].edad);
        }
    }
}

void imprimir_contactos(Agenda *miAgenda){
    printf("Lista de contactos: \n ");
    for(int i=0; i<miAgenda->n;i++){
        printf("Contacto: %s Telefono: %s Edad: %u\n",miAgenda->arreglo[i].nombre, miAgenda->arreglo[i].telefono,miAgenda->arreglo[i].edad);
    }
    return;
}

double prom(Agenda *miAgenda){
    int suma = 0;
    double promedio = 0;
    for(int i = 0; i<miAgenda->n;i++){
        suma = suma + miAgenda->arreglo[i].edad;
    }
    promedio = (double) suma / miAgenda->n;
    return promedio;
}
int main(){
    /*Contacto nuevoContacto;
    nuevoContacto = crear_contacto();
    printf("Contacto creado:\n Nombre: %s\n Telefono: %s \n Edad %u\n",nuevoContacto.nombre,nuevoContacto.telefono,nuevoContacto.edad);
    actualizar_edad(&nuevoContacto);
    printf("\n La edad actualizada es: %d",nuevoContacto.edad);
    free(nuevoContacto.nombre); */
    Agenda miAgenda;
    miAgenda.n = 0;
    for(int j=0; j<2;j++){
    alta_contactos(&miAgenda);
    }
    // modificar_edad(&miAgenda);
    imprimir_contactos(&miAgenda);
    double promedio = prom(&miAgenda);
    printf("El promedio de edades de la agenda es: %.2f \n", promedio);
    for(int i=0; i<miAgenda.n;i++){
        free(miAgenda.arreglo[i].nombre);
    }
    return 0;
}