typedef struct _DNodo {
  int dato;
  struct _DNodo* sig;
  struct _DNodo* ant;
} DNodo;


typedef struct {
    DNodo* primero;
} CDList;

CDList* cdlist_crear();

CDList* cdlist_agregar(CDList *lista,int dato);

void cdlist_eliminar(CDList* lista);

void cdlist_recorrer(CDList *lista);