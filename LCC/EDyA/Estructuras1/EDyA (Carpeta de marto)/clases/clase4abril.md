## ARRAYS
- Indexables.
- Longitud fija - Redimensionables con malloc / realloc
- Datos contiguos en la memoria.
- De tipo unico.


## LISTAS
Las listas casi no comparten nada con arrays
- De tipo unico.

```C

struct Nodo {

  int dato;
  struct Nodo *sig;
}

void SList_agregar_final(struct Nodo **lista, int dato); // Funcion que agrega al final

struct Nodo SList_agregar_final_recursiva(struct Nodo *lista, int dato); // Funcion que agrega al final

int main(void) {
  struct Nodo *lista; // La lista en si, donde inicia
  lista = malloc(sizeof(struct Nodo)); // Asignamos espacio para el primero

  lista->dato = 3; // Le damos un valor
  lista->sig = malloc(sizeof(struct Nodo)); // Asignamos memoria para el siguiente 

  lista->sig->dato = 4; // Le damos valor de 4
  lista->sig->sig = malloc(sizeof(struct Nodo))


  // Seguimos repitiendo el proceso
  lista->sig->sig->dato = 5;
  lista->sig->sig->sig = malloc(sizeof(struct Nodo));

  lista->sig->sig->sig->dato = 6;
  lista->sig->sig->sig->sig = NULL; // Finalmente llegamos al nodo final

}


// Trabajamos con la direccion de la lista 
void SList_agregar_final(struct Nodo **lista, int dato) {

  if (*lista == NULL) {

    *lista = malloc(sizeof(struct Nodo);
    (*lista)->dato = dato;
    (*lista)->sig = NULL;

    return;
  }

  struct Nodo *temp;

  for(temp = *lista ; temp->sig != NULL ; temp = temp->sig);

  temp->sig = malloc(sizeof(struct Nodo));
  temp->sig->dato = dato;
  temp->sig->sig = NULL;

  return;
}





struct Nodo SList_agregar_final_variante(struct Nodo **lista, int dato) {

  struct Nodo *nuevo_nodo = malloc(sizeof(Struct Nodo));
  nuevo_nodo->dato;
  nuevo_nodo->sig = NULL;

  if (lista == NULL) 
    lista = nuevo_nodo;

  else {

    struct Nodo *temp = lista;
    for (temp = lista ; temp->sig != NULL ; temp = temp->sig);
    temp->sig = nuevo_nodo;
  }

  return lista
}



// Trabajamos con la lista y devolvemos un nuevo valor
// El problema con esto, es que estamos pisando las direcciones 
// que ya teniamos previamente.
struct Nodo SList_agregar_final_recursiva(struct Nodo *lista, int dato) {

  if (list == NULL) {

    lista = malloc(sizeof(structNodo));
    lista->dato = dato;
    list->sig = NULL;
    return lista;
  }

  lista->sig = SList_agregar_final_recursiva(lista->sig, dato);
  return lista;
}
```