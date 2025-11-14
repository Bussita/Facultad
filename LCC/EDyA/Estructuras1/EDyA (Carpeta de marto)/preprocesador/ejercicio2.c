#include <stdio.h>
// #include <math.h>

#define PI 3.14159

#define SPHERE_VOLUME(radius) (4 / 3 * PI * (radius) * (radius) * (radius))

#define MAX_RADIUS 10


int main(void) {

  for (int i = 1 ; i <= MAX_RADIUS ; i++)
    printf("Radius: %d  --  Volume: %.2f\n",i, SPHERE_VOLUME(i));

  return 0;
}