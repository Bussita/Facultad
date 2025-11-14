#include <stdio.h>

int main() {
    unsigned char al = 0xFE; // 0xFE es 254 en decimal
    signed char bl = -1;     // -1 es representado como 0xFF en binario de 8 bits
    
    al = al + bl;  // Suma el valor de bl a al
    bl++;          // Incrementa bl en 1
    return al;
}
