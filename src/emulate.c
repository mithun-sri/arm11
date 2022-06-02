#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *file = fopen(argv[1], "rb");

  /* Test for errors with file */

  /* Initialise memory and registers to 0 */

  /* Load instructions into memory */
  
  fclose(file);
  /* Begin execution */

  return EXIT_SUCCESS;
}
