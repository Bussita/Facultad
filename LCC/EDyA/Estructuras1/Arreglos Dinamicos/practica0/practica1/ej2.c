#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define READSIZE 100


char *getnewline() {
  char buffer[READSIZE + 1], *linea = NULL;
  printf("Ingrese la frase: ");
  scanf("%[^\n]", buffer);
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

int string_len(char* str){
    int contador = 0, bandera = 1;
    while (bandera){
        if(str[contador] == '\0'){
            return contador;
        }
        contador++;
    }
    return -1;
}

void string_reverse(char* str){
    int n = strlen(str);
    int j = n-1;
    char aux;
    for(int i = 0; i<n/2;i++){
        aux = str[i];
        str[i] = str[j];
        str[j] = aux;
        printf("%s\n",str);
        j--;
    }
    return;
}

int string_concat(char** str1, char* str2, int max){
    if(*str1 == NULL || str2 == NULL){
        return 0;
    }
    int j = strlen(*str1);
    int n = strlen(str2);
    int i;
    *str1 = realloc(*str1,sizeof(char)*(n+j+1));
    if(*str1 == NULL){
        printf("No hay memoria disponible.");
        exit(1);
    }
    for(i=0; i<max && i<n;i++){
        (*str1)[j] = str2[i];
        j++;
    }
    (*str1)[j] = '\0';
    return i;
}

int string_compare(char* str1, char* str2){
    
}

int string_prefijo(char* grande, char* chico){
    int i;
    for(i=0; grande[i]==chico[i] && chico[i]!='\0';i++);
    if(chico[i]=='\0'){
        return 1;
    }else{
        return 0;
    }
}
int string_subcadena(char* grande, char* chico){
    int inicio = -1;
    for(int i=0; grande[i]!='\0' && inicio == -1; i++){
        if(string_prefijo(grande+i, chico)){
            inicio = i;
        }
    }
    return inicio;
}
int main(){
    char frase[]= 'batatas';
    char subcadena[] = 'atas';
    int pos = string_subcadena(frase, subcadena);
    printf("La posicion encontrada es %d \n", pos);
    /*int longitud;
    longitud = string_len(frase);
    printf("La longitud de %s es %d \n",frase,longitud); */

    //string_reverse(frase);
    // int cant = string_concat(&frase,f2,20);
    // printf("La frase es %s y se copiaron %d caracteres\n",frase,cant);
    
    //free(frase);
    //free(f2);
    return 0;
}