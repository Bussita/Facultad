#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *);
typedef void *(*FuncionCopia)(void *);
typedef void (*FuncionVisitante)(void *);
typedef int (*Predicado) (void *);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode* GList;

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


/*
  Eliminar el primer elemento de una lista
*/
GList glist_eliminar_inicio(GList lista, FuncionDestructora d);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);


/*
  Dada una lista general, retorna una nueva lista con los elementos
  que cumplen el predicado p.
*/
GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);


GList glist_invertir(GList lista, FuncionCopia c);


#endif /* __GLIST_H__ */
