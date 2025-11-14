#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 10


typedef struct {

    char* name;
    char* phone;
    unsigned int age; 

} Contact;


typedef struct {

    Contact* contacts;
    unsigned int size;    

} Agenda;


Contact create_contact();

char* get_new_line(void);

void update_age(Contact* contact);

void add_contact(Agenda* agenda);

void change_age(Agenda* agenda);

void print_contacts(Agenda* agenda);

double prom(Agenda* agenda);

void free_agenda(Agenda* agenda);



int main(){

    // Inicializamos agenda
    Agenda new_agenda;
    new_agenda.size = 0;
    new_agenda.contacts = NULL;


    print_contacts(&new_agenda);

    add_contact(&new_agenda);

    add_contact(&new_agenda); 
    
    print_contacts(&new_agenda);

    change_age(&new_agenda);

    print_contacts(&new_agenda);

    free_agenda(&new_agenda);

    return 0;
}






Contact create_contact(){

    printf("CREANDO NUEVO CONTACTO...\n");

    Contact new_contact; // Creo nuevo contacto en el scope de la funcion

    // Ingresamos el nombre del contacto
    printf("Ingrese nombre del contacto: ");
    new_contact.name = get_new_line();

    // Ingresamos el numero del contacto
    printf("Ingrese numero del contacto: ");
    new_contact.phone = get_new_line();

    // Ingresamos la edad del contacto
    printf("Ingrese edad del contacto: ");
    scanf("%u",&(new_contact.age));

    // Consumimos el '\n' que nos queda pendiente con otro scanf
    char buffer;
    scanf("%c",&buffer);

    return new_contact;
}


void update_age(Contact* contact){

    printf("Ingrese la nueva edad: ");
    scanf("%u",&(contact->age));

}


void add_contact(Agenda* agenda) {

    Contact new_contact = create_contact();

    Contact* buffer = realloc(agenda->contacts, sizeof(Contact) * (agenda->size + 1));

    agenda->contacts = buffer;

    agenda->contacts[agenda->size] = new_contact;
        
    agenda->size ++;

    return;
}


void change_age(Agenda* agenda){

    printf("Ingrese el nombre a buscar:");
    char* name = get_new_line();

    for (unsigned int i = 0 ; i < agenda->size ; i++) {

        if (strcmp(name,agenda->contacts[i].name) == 0)
            update_age(&(agenda->contacts[i]));
    }

    free(name);
}



void print_contacts(Agenda* agenda){

    if (agenda->size == 0){
        printf("La agenda no contiene contactos...\n");
        return;
    }

    printf("\nMOSTRANDO CONTACTOS DE LA AGENDA:\n");

    for (unsigned int i = 0 ; i < agenda->size ; i++){

        printf("\n%s\n",agenda->contacts[i].name);
        printf("%s\n",agenda->contacts[i].phone);
        printf("%d\n",agenda->contacts[i].age);

    }
}


double prom(Agenda* agenda){

    if (agenda->size == 0) { // NO TIENE CONTACTOS
        return 0;
    }

    double sum = 0;

    for (unsigned int i = 0 ; i < agenda->size ; i++)

        sum += agenda->contacts[i].age;

    return sum / agenda->size;
}




char* get_new_line(){

    char buffer[MAX_BUFFER + 1];
    char* new_line = NULL;
    char* buscador;

    size_t largoTotal = 0, largoActual = 0;

    int continuar = 1;

    while (continuar) {
        
        fflush(stdin);

        fgets(buffer, MAX_BUFFER + 1, stdin);

        buscador = strchr(buffer,'\n'); // Esto te devuelve el puntero al '\n'

        if (buscador != NULL) {

            *buscador = '\0'; // Colocamos donde esta el '\n' en el terminador
            continuar = 0;
        }

        largoActual = strlen(buffer);

        new_line = realloc(new_line, sizeof(char) * (largoTotal + largoActual + 1)); // Pido mas memoria

        strcpy(new_line + largoTotal, buffer); // Copio desde donde termine antes

        largoTotal += largoActual;
    }

    return new_line;
}



void free_agenda(Agenda* agenda) {

    for (unsigned int i = 0 ; i < agenda->size ; i++){

        free(agenda->contacts[i].name);
        free(agenda->contacts[i].phone);

    }
    
    free(agenda->contacts);
}
