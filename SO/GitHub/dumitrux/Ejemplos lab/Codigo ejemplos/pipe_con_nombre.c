/* Pipe(FIFO) con nombre*/


// pipewrite.c:

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
  FILE *mipipe; 
  char buffer[128];
  int i=0;

  if (mkfifo("pipetest", S_IWUSR |  /* El usuario puede escribir */
                 S_IRUSR |  /* El usuario puede leer */
                 S_IRGRP |  /* El grupo puede leer */
                     S_IROTH    /* Otros pueden leer */
         )!=0)
    printf ("Hubo un problema al crear la pipe\n");

  mipipe=fopen("pipetest", "w"); /* Lo abrimos como un fichero normal y corriente */

  /* Con esta línea leemos hasta que se cierre la tubería por el otro */

  while (i<10)
    {
      sprintf(buffer, "CADENA ENVIADA Número: %i\n", i+1);
      fputs(buffer, mipipe);
      i++;
    }

  fclose(mipipe);       /* Cerramos la tubería por aquí también */




//piperead.c:

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
  FILE *mipipe; 
  char buffer[128];
  if (mkfifo("pipetest", S_IWUSR |  /* El usuario puede escribir */
                 S_IRUSR |  /* El usuario puede leer */
                 S_IRGRP |  /* El grupo puede leer */
                     S_IROTH    /* Otros pueden leer */
         )!=0)
    printf ("Hubo un problema al crear la pipe\n");

  mipipe=fopen("pipetest", "r"); /* Lo abrimos como un fichero normal y corriente */

  /* Con esta línea leemos hasta que se cierre la tubería por el otro */
  while (!feof(mipipe))      
    {
      if (fgets(buffer, 128, mipipe))
      printf ("RECIBIDO: %s", buffer);
    }

  fclose(mipipe);       /* Cerramos la tubería por aquí también */
}
