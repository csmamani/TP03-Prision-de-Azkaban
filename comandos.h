#ifndef COMANDOS_H
#define COMANDOS_H

#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define MAX_NOMBRE_ARCHIVO 50


typedef struct preso {
    char nombre [MAX_NOMBRE]; 
    unsigned int edad;
    char conducta; //B buena, R regular o M mala
    unsigned int pabellon;
    unsigned int celda;
    char fecha [MAX_FECHA]; //formato aaaamm
    int maldicion_realizada; //1 crucio, 2 imperius
} preso_t;
 

/*PRE: el usuario debe ingresar la linea de ejecucion con el comando ayuda (si algun parametro es incorrecto tambien se accede a este procedimiento)*/
/*POST: el programa mostrara por pantalla una ayuda con la funcionalidad de cada comando (el usuario elegira sobre que comando desea informarse) y la forma de usarlo*/
void mostrar_ayuda();

/*PRE: el usuario debe ingresar la linea de ejecucion con el comando perdonables seguido del nombre del archivo con la extension ".dat" incluida*/
/*PRE: los archivos binarios (crucio.dat e imperius.dat) deben estar ordenados segun el nombre de los presos, el cual es unico*/
/*POST: el programa creara un archivo binario con los presos que hayan realizado una sola de las maldiciones*/
int presos_perdonables (char archivo_perdonables [MAX_NOMBRE_ARCHIVO]);

/*PRE: el usuario debe ingresar la linea de ejecucion con el comando liberar seguido del nombre del archivo, la fecha y la conducta deseadas*/
/*PRE: el nombre del archivo de presos perdonables debe ser el mismo que el ingresado en el comando perdonables*/
/*POST: el programa creara un archivo de texto con los nombres de los presos a liberar*/
/*POST: en caso de ya existir un archivo para la fecha ingresada, no se sobreescribira*/
int presos_liberados (char archivo_perdonables[MAX_NOMBRE_ARCHIVO], char fecha [MAX_FECHA], char conducta);

/*PRE: el usuario debe ingresar la linea de ejecucion con el comando actualizar seguido de la fecha deseada*/
/*PRE: la fecha ingresada debe ser la misma a la ingresada en el comando liberar*/
/*POST: el programa eliminara de los dos archivos binarios iniciales (crucio.dat e imperius.dat) a los presos que ya hayan sido liberados*/
int archivos_actualizados (char fecha [MAX_FECHA]);

/*PRE: el usuario debe ingresar la linea de ejecucion con el comando mostrar_liberados seguido de la fecha deseada*/
/*PRE: la fecha ingresada debe ser la misma a la ingresada en los comandos liberar y actualizar*/
/*POST: el programa mostrara por pantalla los nombres de los presos liberados en la fecha ingresada*/
int liberados_por_pantalla (char fecha [MAX_FECHA]);

#endif /*COMANDOS_H*/
