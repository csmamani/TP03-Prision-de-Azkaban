#include "comandos.h"
#include <stdio.h>
#include <string.h>


#define MAX_NOMBRE_COMANDO 50
#define ARCHIVO_CRUCIO "crucio.dat"
#define ARCHIVO_CRUCIO_NUEVO "crucio_nuevo.dat"
#define ARCHIVO_IMPERIUS "imperius.dat"
#define ARCHIVO_IMPERIUS_NUEVO "imperius_nuevo.dat"
#define FALLO_EN_APERTURA -1
#define YA_EXISTE_LIBERADOS -2
#define NO_LEYO 0
#define CONDUCTA_BUENA 'B'
#define CONDUCTA_REGULAR 'R'
#define CONDUCTA_MALA 'M'
#define COMIENZO_ARCHIVO_LIBERADOS "liberados_"
#define EXTENSION_ARCHIVO_TEXTO ".txt"
#define LARGO_FECHA 6
#define CANTIDAD_REGISTROS_A_LEER 1
#define CANTIDAD_REGISTROS_A_ESCRIBIR 1
#define FORMATO_LEER_NOMBRES "%[^\n]\n"
#define FORMATO_ESCRIBIR_NOMBRES "%s\n"
#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIBERADOS "mostrar_liberados"


/*PRE: el archivo debio haber sido abierto correctamente*/
/*POST: la funcion leera del archivo a los presos correspondientes*/
size_t presos_leidos_binario (FILE* archivo, preso_t* preso);

/*PRE: el archivo debio haber sido abierto correctamente*/
/*POST: la funcion leera del archivo los nombres de los presos correspondientes*/
int presos_leidos_texto (FILE* archivo, char nombre[MAX_NOMBRE]);

/*PRE: el archivo debio haber sido abierto correctamente*/
/*POST: el procedimiento escribira en el archivo a los presos correspondientes*/
void escribir_preso (FILE* archivo, preso_t preso);

/*PRE: el archivo debio haber sido abierto correctamente*/
/*POST: el procedimiento escribira en el archivo los nombres de los presos correspondientes*/
void escribir_nombre_preso (FILE* archivo, char nombre [MAX_NOMBRE]);

/*PRE: la fecha debe haber sido ingresada correctamente*/
/*POST: el procedimiento formara el nombre del archivo de presos liberados*/
void formar_nombre_archivo_liberados (char fecha [MAX_FECHA], char nombre_archivo_liberados [MAX_NOMBRE_ARCHIVO]);

/*PRE: los archivos binarios deben haber sido abiertos correctamente*/
/*POST: el procedimiento calculara que presos realizaron una sola maldicion y los escribira en el archivo perdonables*/
void calcular_presos_perdonables (FILE* crucio, FILE* imperius, FILE* perdonables);

/*PRE: el usuario debe haber ingresado fecha y conducta*/
/*POST: en caso de que fecha y conducta sean invalidoz se mostrara una ayuda, de lo contrarioel programa seguira su curso mostrando los presos liberados*/
void chequear_validez_parametros (char conducta, char fecha [MAX_FECHA]);

/*PRE: los archivos enviados a esta funcion deben haber sido abiertos correctamente*/
/*POST: el procedimiento cargara en los nuevos archivos de crucio e imperius a los presos que aun no hayan sido liberados*/
void actualizar_archivos (FILE* crucio, FILE* crucio_nuevo, FILE* imperius, FILE* imperius_nuevo, FILE* liberados);

/*PRE: el archivo liberados debe haber sido correctamente abierto*/
/*POST: el procedimiento imprimira los nombres de los liberados*/
void imprimir_liberados (FILE* liberados);




size_t presos_leidos_binario (FILE* archivo, preso_t* preso) {
  return fread(preso, sizeof(preso_t), CANTIDAD_REGISTROS_A_LEER, archivo);
}


int presos_leidos_texto (FILE* archivo, char nombre[MAX_NOMBRE]) {
  return fscanf (archivo, FORMATO_LEER_NOMBRES, nombre);
}


void escribir_preso (FILE* archivo, preso_t preso) {
  fwrite(&preso, sizeof(preso_t), CANTIDAD_REGISTROS_A_ESCRIBIR, archivo);
}


void escribir_nombre_preso (FILE* archivo, char nombre [MAX_NOMBRE]) {
  fprintf (archivo, FORMATO_ESCRIBIR_NOMBRES, nombre);
}


void formar_nombre_archivo_liberados (char fecha [MAX_FECHA], char nombre_archivo_liberados [MAX_NOMBRE_ARCHIVO]) {    
    strcpy(nombre_archivo_liberados, COMIENZO_ARCHIVO_LIBERADOS);
    strcat(nombre_archivo_liberados, fecha);
    strcat(nombre_archivo_liberados, EXTENSION_ARCHIVO_TEXTO);
}    

void mostrar_ayuda() {
    char comando_elegido[MAX_NOMBRE_COMANDO];
    printf ("Esta ayuda se mostrara:\n -Si usted ha decidido ejecutar el comando en cuestion\n -Si alguno de los argumentos de la linea de ejecucion ha sido ingresado erroneamente\n -Si se ha ingresado una cantidad incorrecta de argumentos.\nEscriba el comando sobre el cual desea informarse (perdonables; liberar; actualizar; mostrar_liberados; ayuda):\n");
    scanf ("%[^\n]", comando_elegido);
    if (strcmp(COMANDO_PERDONABLES, comando_elegido)==0)
        printf ("Comando perdonables:\n-Que hace?\nDados dos archivos binarios con los presos que han realizado cada maldicion (crucio.dat e imperius.dat), crea un nuevo archivo vinario con aquellos presos que pueden ser perdonados (realizaron una sola maldicion)\n-Como se utiliza?\nEl usuario debe ingresar (luego de './azkaban perdonables') el nombre del archivo a crear con la extension '.dat' (en caso de que el archivo ya exista, se sobreescribe.\n");
    else if (strcmp(COMANDO_LIBERAR, comando_elegido)==0)
        printf ("Comando liberar:\n-Que hace?\nDado un archivo binario de presos perdonables, crea un archivo de texto (de nombre 'liberados_aaaamm.txt') con los nombres de los presos a ser liberados segun la fecha y conducta que ingrese el usuario\n-Como se utiliza?\nEl usuario debe ingresar (luego de './azkaban liberar') el nombre del archivo de presos perdonables (que debe ser EL MISMO que el ingresado en el comando perdonables), seguido de la fecha de liberacion (formato aaaamm) y de la conducta (B(buena), R(regular) o M(mala)) (en caso de que el archivo ya exista, no se sobreescribe.\n");
    else if (strcmp(COMANDO_ACTUALIZAR, comando_elegido)==0)
        printf ("Comando actualizar:\n-Que hace?\nDado el archivo de presos liberados, se actualizaran los dos archivos binarios (crucio.dat e imperius.dat) sacando de estos los presos que figuren en el archivo liberados\n-Como se utiliza?\nEl usuario debe ingresar (luego de './azkaban actualizar') la misma fecha ingresada en el comando liberar (de formato aaaamm).\n");
    else if (strcmp(COMANDO_MOSTRAR_LIBERADOS, comando_elegido)==0)
        printf ("Comando mostrar_liberados:\n-Que hace?\nDado el archivo de presos liberados, se imprime por pantalla los nombres de estos presos que han sido liberados\n-Como se utiliza?\nEl usuario debe ingresar (luego de './azkaban mostrar_liberados') la misma fecha ingresada en el comando liberar y actualizar (de formato aaaamm).\n");
    else 
        printf ("Comando inexistente");
}

void calcular_presos_perdonables (FILE* crucio, FILE* imperius, FILE* perdonables) {
    preso_t preso_crucio, preso_imperius;   
    size_t leidos_crucio = presos_leidos_binario (crucio, &preso_crucio);
    size_t leidos_imperius = presos_leidos_binario (imperius, &preso_imperius);

    while ((leidos_crucio>NO_LEYO) && (leidos_imperius>NO_LEYO)) {
        if (strcmp(preso_crucio.nombre,preso_imperius.nombre)<0) {    
            escribir_preso (perdonables, preso_crucio);
            leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
        }
        else if (strcmp(preso_crucio.nombre,preso_imperius.nombre)>0) {
            escribir_preso (perdonables, preso_imperius);
            leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
        }
        else {
            leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
            leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
        }
    }
    while (leidos_crucio>NO_LEYO) {
        escribir_preso (perdonables, preso_crucio);
        leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
    }
    while (leidos_imperius>NO_LEYO) {
        escribir_preso (perdonables, preso_imperius);
        leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
    }
}

int presos_perdonables (char archivo_perdonables [MAX_NOMBRE_ARCHIVO]) {
    FILE* crucio = fopen(ARCHIVO_CRUCIO, "r");
    if(crucio == NULL) return FALLO_EN_APERTURA;

    FILE* imperius = fopen(ARCHIVO_IMPERIUS, "r");
    if(imperius == NULL) {
        fclose(crucio);
        return FALLO_EN_APERTURA;
    }
    
    FILE* perdonables = fopen(archivo_perdonables, "w");
    if(perdonables == NULL) {
        fclose(crucio);
        fclose(imperius);
        return FALLO_EN_APERTURA;
    }
    
    calcular_presos_perdonables (crucio, imperius, perdonables);

    fclose(perdonables);
    fclose(crucio);
    fclose(imperius);
    return 0;
}

void chequear_validez_parametros (char conducta, char fecha [MAX_FECHA]) {
    if ((conducta!=CONDUCTA_BUENA) && (conducta!=CONDUCTA_REGULAR) && (conducta!=CONDUCTA_MALA))
        mostrar_ayuda();
    size_t largo=strlen(fecha); 
    if (largo>LARGO_FECHA)
        mostrar_ayuda();
}

int presos_liberados (char archivo_perdonables[MAX_NOMBRE_ARCHIVO], char fecha [MAX_FECHA], char conducta) {
    chequear_validez_parametros (conducta, fecha);    

    FILE* perdonables = fopen(archivo_perdonables, "r");
    if(perdonables == NULL) return FALLO_EN_APERTURA;

    preso_t preso;
    char nombre_archivo_liberados [MAX_NOMBRE_ARCHIVO];
    formar_nombre_archivo_liberados (fecha, nombre_archivo_liberados);
    
    FILE* liberados = fopen(nombre_archivo_liberados, "r");
    if(liberados != NULL) {
        fclose (perdonables);
        fclose (liberados);
        return YA_EXISTE_LIBERADOS;
    } 
    else {        
        liberados = fopen(nombre_archivo_liberados, "w");
        size_t leidos= presos_leidos_binario (perdonables, &preso);
        while (leidos>NO_LEYO) {
            if ((strcmp(fecha,preso.fecha)>0) || (strcmp(fecha,preso.fecha)==0)) {
                if (conducta==CONDUCTA_BUENA) {
                    if (preso.conducta==CONDUCTA_BUENA)
                        escribir_nombre_preso (liberados, preso.nombre);
                }
                else if (conducta==CONDUCTA_REGULAR) {
                    if (preso.conducta==CONDUCTA_REGULAR || preso.conducta==CONDUCTA_BUENA)
                        escribir_nombre_preso (liberados, preso.nombre);
                }
                else if (conducta==CONDUCTA_MALA) {
                    if (preso.conducta==CONDUCTA_MALA || preso.conducta==CONDUCTA_REGULAR || preso.conducta==CONDUCTA_BUENA)
                        escribir_nombre_preso (liberados, preso.nombre);
                }
            }
            leidos= presos_leidos_binario (perdonables, &preso);
        }
        fclose (perdonables);
        fclose (liberados);
        return 0;
    }
}

void actualizar_archivos (FILE* crucio, FILE* crucio_nuevo, FILE* imperius, FILE* imperius_nuevo, FILE* liberados){
    preso_t preso_crucio, preso_imperius;
    char nombre[MAX_NOMBRE];
    size_t leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
    size_t leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
    int leidos_liberados= presos_leidos_texto (liberados, nombre);

    while (leidos_crucio>NO_LEYO && leidos_imperius>NO_LEYO && leidos_liberados>NO_LEYO ) {
        if (strcmp(preso_crucio.nombre,nombre)==0){
            leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
            leidos_liberados= presos_leidos_texto (liberados, nombre);
        }
        else if (strcmp(preso_imperius.nombre,nombre)==0){
            leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
            leidos_liberados= presos_leidos_texto (liberados, nombre);
        }
        else if (strcmp(preso_crucio.nombre,nombre)<0) {
            escribir_preso (crucio_nuevo, preso_crucio);
            leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
        }
        else if (strcmp(preso_imperius.nombre,nombre)<0) {
            escribir_preso (imperius_nuevo, preso_imperius);
            leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
        }
        else{
			leidos_liberados= presos_leidos_texto (liberados, nombre);
		}
    }
    while (leidos_liberados>NO_LEYO && leidos_crucio>NO_LEYO ) {
        if (strcmp(preso_crucio.nombre,nombre)==0) {
            leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
            leidos_liberados= presos_leidos_texto (liberados, nombre);
        }
        else if (strcmp(preso_crucio.nombre,nombre)<0) {
            escribir_preso (crucio_nuevo, preso_crucio);
            leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
        }
        else{
			leidos_liberados= presos_leidos_texto (liberados, nombre);
		}
    }
    while (leidos_liberados>NO_LEYO && leidos_imperius>NO_LEYO ) {
        if (strcmp(preso_imperius.nombre,nombre)==0) {
            leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
            leidos_liberados= presos_leidos_texto (liberados, nombre);
        }
        else if (strcmp(preso_imperius.nombre,nombre)<0) {
            escribir_preso (imperius_nuevo, preso_imperius);
            leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
        }
        else{
			leidos_liberados= presos_leidos_texto (liberados, nombre);
		}
    }
    while(leidos_crucio>NO_LEYO ) {
        escribir_preso (crucio_nuevo, preso_crucio);
        leidos_crucio= presos_leidos_binario (crucio, &preso_crucio);
    }
    while(leidos_imperius>NO_LEYO ) {
        escribir_preso (imperius_nuevo, preso_imperius);
        leidos_imperius= presos_leidos_binario (imperius, &preso_imperius);
    }
}

int archivos_actualizados (char fecha [MAX_FECHA]) {
    char nombre_archivo_liberados [MAX_NOMBRE_ARCHIVO];
    formar_nombre_archivo_liberados (fecha, nombre_archivo_liberados);

    FILE* crucio= fopen (ARCHIVO_CRUCIO,"r");
    if(crucio == NULL) return FALLO_EN_APERTURA;

    FILE* crucio_nuevo= fopen (ARCHIVO_CRUCIO_NUEVO,"w");
    if(crucio_nuevo == NULL) {
        fclose(crucio);
        return FALLO_EN_APERTURA;
    }
    FILE* imperius= fopen (ARCHIVO_IMPERIUS,"r");
    if(imperius == NULL) {
        fclose(crucio);
        fclose(crucio_nuevo);
        return FALLO_EN_APERTURA;
    }
    FILE* imperius_nuevo= fopen (ARCHIVO_IMPERIUS_NUEVO,"w");
    if(imperius == NULL) {
        fclose(crucio);
        fclose(crucio_nuevo);
        fclose(imperius);
        return FALLO_EN_APERTURA;
    }
    FILE* liberados= fopen (nombre_archivo_liberados,"r");
    if(liberados == NULL) {
        fclose(crucio);
        fclose(imperius);
        fclose(imperius);
        fclose(imperius_nuevo);
        return FALLO_EN_APERTURA;
    }

    actualizar_archivos (crucio, crucio_nuevo,  imperius, imperius_nuevo, liberados);

    fclose (crucio);
    remove (ARCHIVO_CRUCIO);
    fclose (crucio_nuevo);
    rename (ARCHIVO_CRUCIO_NUEVO, ARCHIVO_CRUCIO);

    fclose (imperius);
    remove (ARCHIVO_IMPERIUS);
    fclose (imperius_nuevo);
    rename (ARCHIVO_IMPERIUS_NUEVO, ARCHIVO_IMPERIUS);
    fclose (liberados);

    return 0;
}

void imprimir_liberados (FILE* liberados) {
    char nombre [MAX_NOMBRE];
    int leidos_liberados= presos_leidos_texto (liberados, nombre);   
    while (leidos_liberados>NO_LEYO) {
        printf (FORMATO_ESCRIBIR_NOMBRES, nombre);
        leidos_liberados= presos_leidos_texto (liberados, nombre);
    }
}

int liberados_por_pantalla (char fecha [MAX_FECHA]) {
    char nombre_archivo_liberados [MAX_NOMBRE_ARCHIVO];
    formar_nombre_archivo_liberados (fecha, nombre_archivo_liberados);

    FILE* liberados = fopen(nombre_archivo_liberados, "r");
    if(liberados == NULL) return FALLO_EN_APERTURA;    

    imprimir_liberados (liberados);

    fclose (liberados);
    return 0;
}