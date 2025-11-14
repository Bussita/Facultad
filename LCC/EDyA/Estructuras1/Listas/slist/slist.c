#include "slist.h"
#include <stdlib.h>
#include <stdio.h>


SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista){
  int longitud=0;
  for(SNodo* temp = lista; temp!=NULL; temp=temp->sig){
    longitud++;
  }
  return longitud;
}

SList slist_concatenar(SList lista, SList lista2){
  SNodo* node=lista;
  for(;node->sig!=NULL;node=node->sig);
  node->sig = lista2;
  return lista;
}

SList slist_insertar(SList lista, int dato, int pos){
  if(pos<=0){
    slist_agregar_inicio(lista, dato);
  }

  SNodo* nuevoNodo = malloc(sizeof(SNodo)), *temp = lista;
  nuevoNodo->dato = dato;
  int contador = 0;

  for(;contador<pos-1 && temp->sig != NULL;temp = temp->sig){
    contador++;
  }
  nuevoNodo->sig = temp->sig;
  temp->sig = nuevoNodo;
  return lista;
}

SList slist_eliminar(SList lista, int pos){
  if(pos<0){
    return lista;
  }
  int contador=0;
  SNodo* node=lista, *nodeToDelete;
  if(pos == 0){
    nodeToDelete = lista;
    lista = lista->sig;
    free(nodeToDelete);
    return lista;
  }
  for(;contador<pos-1 && node->sig!=NULL;node=node->sig){
    contador++;
  }
   if(node->sig!=NULL){
    nodeToDelete = node->sig;
    node->sig = node->sig->sig;
    free(nodeToDelete);
  }
  return lista;
}

int slist_contiene(SList lista, int dato){
  if(lista==NULL){
    printf("Lista vacia retorno 0\n");
    return 0;
    }
  int booleano=0;
  for(SNodo* node=lista;node!=NULL; node=node->sig){
    if(node->dato == dato){
      booleano=1;
    }
  }
  return booleano;
}

int slist_indice(SList lista, int dato){
  int contador=0, status=0;
  for(SNodo* node=lista; node!=NULL && status==0; node=node->sig){
    if(node->dato == dato){
      status = 1;
    }
    contador++;
  }
  if(status==0){
    return -1;
  }else{
    return contador;
  }
}


SList slist_intersecar(SList lista, SList lista2){
  SList listaNueva = slist_crear();
  int status=0, datoProvisorio;
  for(SNodo* node=lista; node!=NULL; node=node->sig){
    for(SNodo* node2=lista2;node2!=NULL && status==0; node2=node2->sig){
      if(node->dato == node2->dato){
        datoProvisorio = node->dato;
        status = 1;
      }
    }
    if (status == 1 && slist_contiene(listaNueva, datoProvisorio)==0){
        listaNueva = slist_agregar_final(listaNueva, datoProvisorio);
      }
    status = 0;
  }
  return listaNueva;
}

SList slist_intersecar_custom(SList lista, SList lista2, FuncionComparadora funcion){
  SList listaNueva = slist_crear();
  int status=0;
  void* datoProvisorio;
  for(SNodo* node=lista; node!=NULL; node=node->sig){
    for(SNodo* node2=lista2;node2!=NULL && status==0; node2=node2->sig){
      if(funcion(&node->dato, &node2->dato)==0){
        datoProvisorio = &node->dato;
        status = 1;
      }
    }
    if (status == 1 && slist_contiene(listaNueva, *((int*)datoProvisorio))==0){
        listaNueva = slist_agregar_final(listaNueva, *((int*)datoProvisorio));
      }
    status = 0;
  }
  return listaNueva;
}

SList slist_ordenar(SList lista, FuncionComparadora funcion){
  int aux;
  if(lista == NULL){
    return lista;
  }
  for(SNodo* node=lista; node->sig!=NULL; node=node->sig){
    for(SNodo* node2=node->sig; node2!=NULL; node2 = node2->sig){
      if(funcion(&node->dato,&node2->dato)==1){
        aux = node->dato;
        node->dato = node2->dato;
        node2->dato = aux;
      }
    }
  }
  return lista;
}

SList slist_reverso(SList lista){
  SList listaNueva = slist_crear();
  for(SNodo* node=lista; node!=NULL; node=node->sig){
    listaNueva = slist_agregar_inicio(listaNueva, node->dato);
  }
  return listaNueva;
}

SList slist_intercalar(SList lista, SList lista2){
  if(lista == NULL && lista2==NULL) return NULL;
  if(lista==NULL){
    return lista2;
  }
  if(lista2 == NULL){
    return lista;
  }
  SList listaNueva = slist_crear();
  SNodo* nodo1=lista, *nodo2=lista2;
  while(nodo1!=NULL && nodo2!=NULL){
    slist_agregar_final(listaNueva,nodo1->dato);
    slist_agregar_final(listaNueva,nodo2->dato);
    nodo1 = nodo1->sig;
    nodo2 = nodo2->sig;
  }
  if(nodo1 !=NULL){
    for(;nodo1!=NULL; nodo1=nodo1->sig){
      slist_agregar_final(listaNueva, nodo1->dato);
    }
  }
  if(nodo2 !=NULL){
    for(;nodo2!=NULL; nodo2=nodo2->sig){
      slist_agregar_final(listaNueva, nodo2->dato);
    }
  }
  return listaNueva;
}

SList slist_partir(SList lista){
  int longitud = slist_longitud(lista), contador=0;
  SList listaNueva = slist_crear();
  if(longitud%2 == 0){
    SNodo* nodo=lista;
    while(contador<longitud/2){
      nodo = nodo->sig;
      contador++;
    }
    listaNueva = nodo->sig;
    nodo->sig = NULL;
  }else{
    SNodo* nodo=lista;
    while(contador<(longitud/2)+1){
      nodo = nodo->sig;
      contador++;
    }
    listaNueva = nodo->sig;
    nodo->sig = NULL;
  }
  return listaNueva;
}