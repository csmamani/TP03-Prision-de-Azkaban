#include "comandos.h"
#include <string.h>
#include <stdio.h>

#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIBERADOS "mostrar_liberados"
#define COMANDO_AYUDA "ayuda"
#define COMANDO 1
#define PARAMETRO_2 2
#define PARAMETRO_3 3
#define PARAMETRO_4 4
#define PRIMERA_LETRA 0
#define ARGUMENTOS_PERDONABLES 3
#define ARGUMENTOS_LIBERAR 5
#define ARGUMENTOS_ACTUALIZAR 3
#define ARGUMENTOS_MOSTRAR_LIBERADOS 3

/*PRE: el usuario debe ingresar la linea de ejecucion con el comando y parametros que desee*/
/*POST: el programa efectua el comando deseado si la linea de ejecucion fue ingresada correctamente, de lo contrario se muestra una ayuda*/
void efectuar_comandos (int argc, char* argv[]) {
    if (strcmp (argv[COMANDO], COMANDO_PERDONABLES)==0) {
        if (argc!=ARGUMENTOS_PERDONABLES) 
            mostrar_ayuda ();
        else
            presos_perdonables (argv[PARAMETRO_2]);
    }
    else if (strcmp (argv[COMANDO], COMANDO_LIBERAR)==0) {
        if (argc!=ARGUMENTOS_LIBERAR)
            mostrar_ayuda ();
        else 
            presos_liberados (argv[PARAMETRO_2], argv[PARAMETRO_3], argv[PARAMETRO_4][PRIMERA_LETRA]);
    }
    else if (strcmp (argv[COMANDO], COMANDO_ACTUALIZAR)==0) {
        if (argc!=ARGUMENTOS_ACTUALIZAR)
            mostrar_ayuda ();
        else
            archivos_actualizados (argv[PARAMETRO_2]);
    }
    else if (strcmp (argv[COMANDO], COMANDO_MOSTRAR_LIBERADOS)==0) {      
        if (argc!=ARGUMENTOS_MOSTRAR_LIBERADOS)
            mostrar_ayuda ();
        else
            liberados_por_pantalla (argv[PARAMETRO_2]);
    }
    else if (strcmp (argv[COMANDO], COMANDO_AYUDA)==0) {
        mostrar_ayuda ();
    }
    else 
        mostrar_ayuda ();

}

/*Llama al procedimiento que se encarga de efectuar los distintos comandos*/
int main (int argc, char *argv[]) {
    
    efectuar_comandos (argc, argv);
    
    return 0;
}
