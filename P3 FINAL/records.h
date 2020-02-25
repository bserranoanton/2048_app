//Belén Serrano Antón
//Andrea del Vado Puell

#ifndef records_H
#define records_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAXrecords = 10;
const string CENTINELA = "???";

typedef struct{

	string nomb;
	int puntuacion;

}tRecord;

typedef tRecord tListaRecords[MAXrecords];

void cargar (string nombArch ,tListaRecords & lista); //Carga una lista de records ya guardada o inicializa la lista con 0 records
void guardarR(string nombArch, tListaRecords &  lista); //Guarda la lista de records modificada
void mostrar(const tListaRecords & lista); //Mueestra los records al usuario
void insertar(tListaRecords & lista, int TPuntos, string nombPers); //Si ha habido algún nuevo records lo inserta 
																	//ordenadamente en la lista
void nuevoRecord(tListaRecords & lista, int puntos); //Indica si hay un nuevo record o no, en el caso de que así sea llama a 
				//insertar(tListaRecords & lista, int TPuntos, string nombPers).

#endif