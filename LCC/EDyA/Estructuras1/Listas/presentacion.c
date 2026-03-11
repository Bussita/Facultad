#include "./glist/glist.h"
#include <stdlib.h>
#include <stdio.h>

GList slist_intersecar(GList list1, GList list2, FuncionComparadora f, FuncionCopia copy){
    GList result = glist_crear();
    for(GNode* temp = list1; temp != NULL; temp = temp->next){
        for(GNode* temp2 = list2; temp2 != NULL ; temp2 = temp2->next){
            if(f(temp->data, temp2->data) == 0)
                result = glist_agregar_inicio(result, temp->data, copy);
        }
    }
    return result;
}

int buscar_rec(void* dato, GList lista, FuncionComparadora f){
    if(lista == NULL) return 0;
    if(f(dato, lista->data) == 0){
        return 1;
    }else{
        return buscar_rec(dato, lista->next, f);
    }
}

GList slist_intersecar2(GList list1, GList list2, FuncionComparadora f, FuncionCopia copy){
    if(list1 == NULL || list2 == NULL){
        return glist_crear();
    }
    if(buscar_rec(list1->data, list2, f)){
        GNode* new = malloc(sizeof(GNode));
        new->data  = copy(list1->data);
        new->next  = slist_intersecar2(list1->next,list2,f,copy);
        return new;
    }
    return slist_intersecar2(list1->next,list2,f,copy);
}

void* copiar_int(void* dato) {
    int* copia = malloc(sizeof(int));
    *copia = *(int*)dato;
    return copia;
}

void destruir_int(void* dato) {
    free(dato);
}

int comparar_int(void* a, void* b) {
    int va = *(int*)a;
    int vb = *(int*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;  // 0 = iguales
}

void imprimir_int(void* dato) {
    printf("%d ", *(int*)dato);
}

GList crear_lista_desde_array(int* arr, int n) {
    GList lista = glist_crear();
    for (int i = 0; i < n; i++) {
        lista = glist_agregar_inicio(lista, &arr[i], copiar_int);
    }
    return lista;
}

void imprimir_lista(const char* nombre, GList lista) {
    printf("%s: [ ", nombre);
    glist_recorrer(lista, imprimir_int);
    printf("]\n");
}

int main(){
    printf("=== Test 1: Elementos en comun ===\n");
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {3, 4, 5, 6, 7};
    GList l1 = crear_lista_desde_array(arr1, 5);
    GList l2 = crear_lista_desde_array(arr2, 5);
    imprimir_lista("L1", l1);
    imprimir_lista("L2", l2);
    GList inter1 = slist_intersecar(l1, l2, comparar_int, copiar_int);
    imprimir_lista("Interseccion (esperado: 3 4 5)", inter1);
    printf("\n");

    printf("=== Test 2: Sin elementos en comun ===\n");
    int arr3[] = {1, 2, 3};
    int arr4[] = {4, 5, 6};
    GList l3 = crear_lista_desde_array(arr3, 3);
    GList l4 = crear_lista_desde_array(arr4, 3);
    imprimir_lista("L3", l3);
    imprimir_lista("L4", l4);
    GList inter2 = slist_intersecar(l3, l4, comparar_int, copiar_int);
    imprimir_lista("Interseccion (esperado: vacia)", inter2);
    printf("\n");

    printf("=== Test 3: Listas identicas ===\n");
    int arr5[] = {10, 20, 30};
    GList l5 = crear_lista_desde_array(arr5, 3);
    GList l6 = crear_lista_desde_array(arr5, 3);
    imprimir_lista("L5", l5);
    imprimir_lista("L6", l6);
    GList inter3 = slist_intersecar(l5, l6, comparar_int, copiar_int);
    imprimir_lista("Interseccion (esperado: 10 20 30)", inter3);
    printf("\n");

    printf("=== Test 4: Una lista vacia ===\n");
    int arr6[] = {1, 2, 3};
    GList l7 = crear_lista_desde_array(arr6, 3);
    GList l8 = glist_crear();
    imprimir_lista("L7", l7);
    imprimir_lista("L8 (vacia)", l8);
    GList inter4 = slist_intersecar(l7, l8, comparar_int, copiar_int);
    imprimir_lista("Interseccion (esperado: vacia)", inter4);
    printf("\n");

    printf("=== Test 5: Ambas vacias ===\n");
    GList l9 = glist_crear();
    GList l10 = glist_crear();
    GList inter5 = slist_intersecar(l9, l10, comparar_int, copiar_int);
    imprimir_lista("Interseccion (esperado: vacia)", inter5);
    printf("\n");

    printf("========================================\n");
    printf("   Tests de slist_intersecar2 (recursiva)\n");
    printf("========================================\n\n");

    printf("=== Test 6: Elementos en comun (recursiva) ===\n");
    GList l11 = crear_lista_desde_array(arr1, 5);
    GList l12 = crear_lista_desde_array(arr2, 5);
    imprimir_lista("L11", l11);
    imprimir_lista("L12", l12);
    GList inter6 = slist_intersecar2(l11, l12, comparar_int, copiar_int);
    imprimir_lista("Interseccion2 (esperado: 3 4 5)", inter6);
    printf("\n");

    printf("=== Test 7: Sin elementos en comun (recursiva) ===\n");
    GList l13 = crear_lista_desde_array(arr3, 3);
    GList l14 = crear_lista_desde_array(arr4, 3);
    imprimir_lista("L13", l13);
    imprimir_lista("L14", l14);
    GList inter7 = slist_intersecar2(l13, l14, comparar_int, copiar_int);
    imprimir_lista("Interseccion2 (esperado: vacia)", inter7);
    printf("\n");

    printf("=== Test 8: Listas identicas (recursiva) ===\n");
    GList l15 = crear_lista_desde_array(arr5, 3);
    GList l16 = crear_lista_desde_array(arr5, 3);
    imprimir_lista("L15", l15);
    imprimir_lista("L16", l16);
    GList inter8 = slist_intersecar2(l15, l16, comparar_int, copiar_int);
    imprimir_lista("Interseccion2 (esperado: 10 20 30)", inter8);
    printf("\n");

    printf("=== Test 9: Una lista vacia (recursiva) ===\n");
    GList l17 = crear_lista_desde_array(arr6, 3);
    GList l18 = glist_crear();
    imprimir_lista("L17", l17);
    imprimir_lista("L18 (vacia)", l18);
    GList inter9 = slist_intersecar2(l17, l18, comparar_int, copiar_int);
    imprimir_lista("Interseccion2 (esperado: vacia)", inter9);
    printf("\n");

    printf("=== Test 10: Ambas vacias (recursiva) ===\n");
    GList l19 = glist_crear();
    GList l20 = glist_crear();
    GList inter10 = slist_intersecar2(l19, l20, comparar_int, copiar_int);
    imprimir_lista("Interseccion2 (esperado: vacia)", inter10);
    printf("\n");

    glist_destruir(l1, destruir_int);
    glist_destruir(l2, destruir_int);
    glist_destruir(inter1, destruir_int);
    glist_destruir(l3, destruir_int);
    glist_destruir(l4, destruir_int);
    glist_destruir(inter2, destruir_int);
    glist_destruir(l5, destruir_int);
    glist_destruir(l6, destruir_int);
    glist_destruir(inter3, destruir_int);
    glist_destruir(l7, destruir_int);
    glist_destruir(inter4, destruir_int);
    glist_destruir(inter5, destruir_int);
    glist_destruir(l11, destruir_int);
    glist_destruir(l12, destruir_int);
    glist_destruir(inter6, destruir_int);
    glist_destruir(l13, destruir_int);
    glist_destruir(l14, destruir_int);
    glist_destruir(inter7, destruir_int);
    glist_destruir(l15, destruir_int);
    glist_destruir(l16, destruir_int);
    glist_destruir(inter8, destruir_int);
    glist_destruir(l17, destruir_int);
    glist_destruir(inter9, destruir_int);
    glist_destruir(inter10, destruir_int);

    return 0;
}