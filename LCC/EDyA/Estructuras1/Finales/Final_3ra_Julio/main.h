typedef enum color{Rojo, Azul, Neutro} Color;

typedef struct Nodo_{
    char* cdato;
    Color colorNodo;
    struct Nodo_ *der, *izq;
} Nodo;

typedef Nodo* ArbolBinarioColoreado;

ArbolBinarioColoreado arbol_coloreado_crear();

