#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void* dato1, void* dato2);
typedef int (*Predicado)(void* dato);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode* GList;
typedef GList SGList;


/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

GList glist_filtrar(GList lista, FuncionCopia copy, Predicado p);


SGList sglist_crear();

void sglist_eliminar(SGList lista, FuncionDestructora destroy);

int sglist_vacia(SGList lista);

void sglist_recorrer(SGList lista, FuncionVisitante visit);

SGList sglist_insertar(SGList lista, FuncionCopia copy, FuncionComparadora compare, void* dato);

int sglist_buscar(SGList lista, void* data, FuncionComparadora function);

SGList sglist_arr(void** arrdata, int longitud, FuncionCopia copy, FuncionComparadora compare);
#endif /* __GLIST_H__ */
