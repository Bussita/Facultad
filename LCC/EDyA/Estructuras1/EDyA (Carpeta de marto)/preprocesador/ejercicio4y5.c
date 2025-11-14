#define MINIMUN2(x,y) (x < y) ? x : y

#define MINIMUN3(x,y,z) (MINIMUN2(x,y) < MINIMUN2(y,z)) ? MINIMUN2(x,y) : MINIMUN2(y,z)

