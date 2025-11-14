#include <math.h>

#define YES 1
#define NO 0

#line 3000

#if defined(TRUE)
  #undef TRUE
  #define TRUE 1
#endif

#ifdef TRUE
  #undef TRUE
  #define TRUE
#endif


#if (TRUE != 0)
  #define FALSE 0

#else
  #define FALSE 1

#endif

#define SQUARE_VOLUME(side_size) pow(side_size,3);
