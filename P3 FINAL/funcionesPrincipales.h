//Belén Serrano Antón
//Andrea del Vado Puell

#ifndef funcionesPrincipales_H
#define funcionesPrincipales_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

const int DIM = 13; //Máxima dimensión
const int BITS = 6; //Bits de las casillas (para hacer el tablero)
const double PROB2 = 0.95;
const double PROB4 = 1 - PROB2;
const int expMetaMax = 12; //2048

//Chars de la tabla
const char esquiIzqSup = char(218);
const char esquiDerSup = char(191);
const char esquiIzqInf = char(192);
const char esquiDerInf = char(217);
const char lineaVertical = char(179);
const char lineaHorizontal = char(196);
const char formaT = char(194);
const char formaTinver = char(193);
const char formaTIzq = char(195);
const char formaTDer = char(180);
const char cruz = char(197);

typedef enum{ Arriba, Abajo, Derecha , Izquierda }tDireccion;
typedef enum{ OP_Arriba, OP_Abajo, OP_Derecha,OP_Izquierda , OP_Salir}tOpcion;
typedef int tTablero[DIM][DIM];
typedef enum{Pierde, Gana, Jugando} tResultado;
typedef int tListaExp[expMetaMax];

typedef struct{
	int meta;
	int dimen; 
	tTablero tablero;
	int Tpuntos; 
	int puntos; 
	tDireccion direccion;
	int celdasLibres;
	int mayor;
}tJuego2048;

void modosJuego(tJuego2048 & juego2048, const tListaExp listaExp); //Permite comenzar una partida eligiendo la dimensión y la meta
void inicializa(tJuego2048 & juego2048); //En el caso de que se abra una nueva partida pone las dos fichas iniciales en el tablero
void nuevaFicha(tJuego2048 & juego2048); //Pone la nueva ficha después de ejecutar el movimiento del tablero
void hacerArrayExp(tListaExp listaExp); //Hace el array de exponentes (una única vez, al comienzo)
tOpcion menu(); //Pide al usuario la dirección del movimiento o si quiere abandonar la partida
bool carga(tJuego2048 & juego2048); //Carga de un .txt una partida previamente guardada
void guarda(const tJuego2048 juego2048); //En el caso de que se abandone una partida, perimite guardarla (pide nombre de archivo)
void bordeSuperior(const tJuego2048 juego2048); // Hace el borde superior del tablero
void bordeInferior(const tJuego2048 juego2048); //Hace el borde inferior del tablero
void bordeInter(const tJuego2048 juego2048); //Hace el borde que separa las casillas del tablero
void celda(const tJuego2048 juego2048, int fila); //Hace los chars correspondientes a las filas superior e inferior a la fila en la que
													//está el número del tablero
void visualizaF(tJuego2048 & juego2048, int fila, const tListaExp listaExp);  // Muestra las casillas completas del tablero
void visualiza(tJuego2048 & juego2048, const tListaExp listaExp); //Muestra el tablero completo, con los puntos
int celdasLibres(const tJuego2048 juego2048); //Devuelve el número de celdas libres del tablero
tResultado mueveFichas(tJuego2048 & juego2048, const tListaExp listaExp); //Función que hace los movimientos del tablero
void limpiar(); //Limpia la consola después de cada movimiento
void pause(); //Hace una pausa justo antes de finalizar la ejecución

#endif