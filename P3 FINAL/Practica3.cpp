//Belén Serrano Antón
//Andrea del Vado Puell

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "utilsWin.h"

using namespace std;

const int DIM = 4;
const int BITS = 6;
const int META = 64;
const double PROB2 = 0.95;
const double PROB4 = 1 - PROB2;

//Tabla
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

void inicializa(tTablero tablero); //Comienza una nueva partida con un nuevo tablero
void nuevaFicha(tTablero tablero); //Añade un 2 o un 4 al tablero
int logaritmo(int num); //Devuleve el exponente al que esá elevado 2 para dar num
void visualizaF(const tTablero tablero, int fila); //muestra en consola el interior del tablero
void celda (const tTablero tablero, int fila); //Muestra en cosola la fila del tablero.
void bordeSuperior();
void bordeInferior(); 
void bordeInter();
void visualiza(const tTablero tablero, int puntos, int totalPuntos); //Muestra en consola el tablero entero.
bool carga(tTablero tablero, int & puntos); //Carga una partida de un archivo
void guarda(const tTablero tablero, int puntos); //Guarda una partida dejada a medias en un archivo
int mayor(const tTablero tablero); //Devuelve el mayor numero encontrado en el array para compararlo con la meta
bool lleno(const tTablero tablero); //Devuelve true si está lleno y false si el tablero tiene alguna casilla libre.
tResultado mueveFichas(tTablero tablero, tDireccion direccion, int & puntos, int & total); //Mueve las fichas cada vez que se quiere hacer un movimiento y devuelve el resultado del juego.
tOpcion menu();
void limpiar();
void pause();


int main(){

	srand(time(NULL));
	tTablero tablero;
	tResultado juego = Jugando;
	char Chrguardar;
	tOpcion op;
	tDireccion direccion;

	int puntos = 0, totalPuntos = 0;

	if (carga(tablero, totalPuntos))
		visualiza(tablero, puntos, totalPuntos);

	else {

		cout << endl << "No se pudo continuar una partida. Empezamos una nueva." << endl << endl;
		visualiza(tablero, puntos, totalPuntos);
	}

	op = menu(); 

	while ((op != OP_Salir) && (juego == Jugando)){

		direccion = tDireccion(int(op));

		limpiar();

		juego = mueveFichas(tablero,direccion, puntos,totalPuntos);
		visualiza(tablero, puntos, totalPuntos);

		if(juego == Gana) 
			cout << "¡Enhorabuena! Ha ganado el juego! " << endl;

		else if(juego == Pierde) 
			cout << "Lo siento... Ha perdido el juego. " << endl;

		else op = menu();
	}

	if (op == OP_Salir){

		cout << endl << "¿Quieres guardar la partida para continuar en otro momento? (s/n)" << endl;
		cin >> Chrguardar;

		while (Chrguardar != 's' && Chrguardar != 'n'){

			cin.clear();	
			cin.sync();

			cout << "Error al leer la respuesta. Introduzca s / n:" << endl;
			cin >> Chrguardar;
		}

		if (Chrguardar == 's'){ 

			cout << endl;

			guarda(tablero, totalPuntos);
			cout << "Archivo guardado." << endl;
		}
	}

	pause();

	return 0;
}

void inicializa(tTablero tablero){

	int aleatorio1, aleatorio2, numTabAleat, j = 0;

	for (int i = 0; i < DIM; i++){
		j = 0;

		while (j < DIM){

			tablero[i][j] = 1;
			j++;
		}
	}

	aleatorio1 = rand() % (15 + 1); 

	tablero[aleatorio1 / 4][aleatorio1 % 4] = 2;

	aleatorio2 = rand() % (15 + 1);

	while (aleatorio1 == aleatorio2){

		aleatorio2 = rand() % (15 + 1);
	}

	double azar = rand() / double(RAND_MAX); // da lugar a un real en el rango [0, 1] 

	if (azar < PROB2) 
		numTabAleat = 2;

	else numTabAleat = 4;

	tablero[aleatorio2 / 4][aleatorio2 % 4] = numTabAleat;
}

void nuevaFicha(tTablero tablero){

	int aleatorio = rand() % (DIM*DIM);
	int numTabAleat;
	double azar = rand() / double(RAND_MAX);

	if (azar < PROB2) numTabAleat = 2;
	else numTabAleat = 4;

	while (tablero[aleatorio / DIM][aleatorio % DIM] != 1){
		aleatorio = rand() % (DIM*DIM);
	}

	tablero[aleatorio / DIM][aleatorio % DIM] = numTabAleat;
}

int logaritmo(int num){

	int exponente = 0, numAux = 1, cont =0;

	while (num != numAux && cont < num){

		numAux = numAux * 2;
		exponente++;
		cont++;
	}

	if(cont >= num) 
		exponente = 1;

	return exponente;
}

bool carga(tTablero tablero, int & puntos){

	ifstream arch;
	string nomb;
	bool cargar;

	cout << "Introduce el nombre del archivo donde tienes tu partida (Intro para empezar una nueva):  ";
	getline(cin, nomb);

	arch.open(nomb);
	if (!arch.is_open()) {

		cargar = false;
		inicializa(tablero);
		puntos = 0;
	}

	else{

		int metaArch, dimArch;

		arch >> metaArch;
		arch >> dimArch; 

		if (metaArch != META || dimArch != DIM){

			cargar = false;
			inicializa(tablero);
			puntos = 0;
		}

		else{

			cargar = true;
			int num;

			for (int i = 0; i < DIM; i++){

				for (int j = 0; j < DIM; j++){
					arch >> num;
					tablero[i][j] = num;
				}
			}

			arch >> puntos;
		}

		arch.close();
	}

	return cargar;
}

void guarda(const tTablero tablero, int puntos){

	ofstream arch;
	string nomb;

	cout << "Introduce el nombre del archivo para guardar la partida:" << endl;
	cin.sync();
	getline(cin, nomb);

	arch.open(nomb);

	if (arch.is_open()){

		cout << "Partida guardada en: " << nomb << endl;
		arch << META << " " << DIM << endl;
		arch << endl;

		for (int i = 0; i < DIM; i++){

			for (int j = 0; j < DIM; j++){
				arch << tablero[i][j] << endl;
			}

			arch << endl;
		}

		arch << puntos;
		arch.close();
	}

	else cout << "Problemas al guardar." << endl;

}

void bordeSuperior(){

	int cont = 5, celda = ((DIM * BITS) - 1);

	cout << esquiIzqSup;

	for (int i = 0; i < celda; i++){
		if (i == cont){ 
			cout << formaT; 
			cont = cont + BITS; 
		}

		else cout << lineaHorizontal;
	}

	cout << esquiDerSup;
	cout << endl;
}

void bordeInter(){

	int cont = 5, celda = ((DIM * BITS) - 1);

	cout << formaTIzq;

	for (int i = 0; i < celda; i++){

		if (i == cont){ 
			cout << cruz; 
			cont = cont + BITS; 
		}

		else cout << lineaHorizontal;
	}

	cout << formaTDer;
	cout << endl;

}

void visualizaF(const tTablero tablero, int fila){

	int expColor;

	celda(tablero, fila);
	cout << lineaVertical; 

	for(int i = 0; i < DIM; i++){

		int expColor = logaritmo(tablero[fila][i]);

		if(tablero[fila][i] == 1) {

			background(expColor);
			cout << right << setw(5) << "" << lineaVertical;
		}

		else{
			background(expColor);
			cout << right << setw(5) << tablero [fila][i];
			background(0);
			cout << lineaVertical; 

		}
	}

	cout << endl;
	celda(tablero, fila);
}

//muestra la primera y la ultima linea de caracteres de la celda
void celda (const tTablero tablero, int fila){

	int cont, celda = (DIM * BITS), expColor;

	cout << lineaVertical; 

	for(int i = 0; i < DIM; i++){

		int expColor = logaritmo(tablero[fila][i]);

		if(tablero[fila][i] == 1) {

			background(expColor);
			cout << right << setw(5) << "" << lineaVertical;
		}

		else{
			background(expColor);
			cout << right << setw(5) << "";
			background(0);
			cout << lineaVertical; 

		}
	}

	cout << endl;
} 

void bordeInferior(){

	int cont = 5,  celda = (DIM * BITS) - 1;
	cout << esquiIzqInf;

	for (int i = 0; i < celda; i++){

		if (i == cont){ 
			cout << formaTinver;
			cont = cont + BITS; 
		}

		else	cout << lineaHorizontal;
	}

	cout << esquiDerInf;
	cout << endl;
}

void visualiza(const tTablero tablero, int puntos, int totalPuntos){

	int cont;

	cout  << "Jugada: "  << puntos;
	cout << "   Total puntos: " << totalPuntos;
	cout << "   Meta: " << META << endl;

	bordeSuperior();

	for(int j = 0; j < DIM; j++){

		visualizaF(tablero,j);
		if(j != DIM-1)bordeInter();	 
	}

	bordeInferior();
}

tOpcion menu(){

	tOpcion op;
	int tecla;

	cout << endl << "Usa las flechas para inclinar el tablero. (Esc para salir)." << endl;						
	tecla = getKey();	
	cout << endl;

	while((tecla != TE_Salir) && (tecla != TE_Abajo) && (tecla != TE_Arriba) && (tecla != TE_Derecha) && (tecla != TE_Izquierda)){

		//cout << "Por favor, use las flechas o la tecla esc para salir." << endl;	
		tecla = getKey();
	}

	if (tecla == TE_Salir) op = OP_Salir;
	else if (tecla == TE_Abajo)op = OP_Abajo;
	else if (tecla == TE_Arriba)op = OP_Arriba;
	else if (tecla == TE_Derecha)op = OP_Derecha;
	else if (tecla == TE_Izquierda)op =OP_Izquierda;

	return op;
}

int mayor(const tTablero tablero){

	int mayor = tablero[0][0];

	for(int i = 0; i < DIM; i++){
		for(int j = 0; j < DIM; j++){

			if(tablero[i][j] >= mayor)
				mayor = tablero[i][j];
		}	
	}

	return mayor;
}

bool lleno(const tTablero tablero){

	int j, i = 0;
	bool lleno = true;

	while(lleno && (i < DIM)){
		j = 0;

		while(lleno && (j < DIM)){

			if(tablero[i][j] == 1) 
				lleno = false;

			j++;
		}

		i++;
	}

	return lleno;
}

tResultado mueveFichas(tTablero tablero, tDireccion direccion, int & puntos, int & total){

	tResultado juego = Jugando;
	bool mover = false;
	puntos = 0;

	int ini, fin, mf, mc, tope, inc, i, j, cont, incF, incC;;
	int varComienzoi, VarComienzoj;

	if (direccion == 0 /*arriba*/){
		ini = 0; fin = DIM - 1; mf = 0; mc = 0; inc = 1; i = 0; j = 0;
		varComienzoi = 0; VarComienzoj = 0;
	}

	else if (direccion == 1 /*abajo*/){
		ini = DIM - 1; fin = 0; mf = DIM - 1; mc = 0; inc = -1; i = ini; j = 0;
		varComienzoi = DIM - 1; VarComienzoj = 0;
	}

	else if (direccion == 2 /*derecha*/){
		ini = DIM - 1; fin = 0; mf = fin; mc = ini;   inc = -1; i = fin; j = ini;
		varComienzoi = fin; VarComienzoj = ini; 
	} // i no se mueve


	else if (direccion == 3 /*izq*/){
		ini = 0; fin = DIM - 1; mf = ini; mc = ini; inc = 1; i = ini; j = 0;
		varComienzoi = ini; VarComienzoj = ini; 
	}//i no se mueve

	while ((((int(direccion) >= 2) && i < DIM && j != fin) || (int(direccion) == 0 && i < DIM && j <= fin)) || (int(direccion) == 1 && (j < DIM))){

		cont = 0;

		while (cont < DIM) {

			if (((direccion == 2 || direccion == 3) && j == VarComienzoj) || ((direccion == 0 || direccion == 1) && i == varComienzoi)){

				if (tablero[i][j] == 1) {

					if (direccion == 2 || direccion == 3) 
						mc = j; 

					else  mf = i;  // movimiento de arriba a abajo
				}

				else {

					if (direccion == 2 || direccion == 3) 
						mc += inc;

					else  mf += inc;  // arriba-abajo
				}

				tope = tablero[i][j];
			}

			else {

				if (tablero[i][j] != 1){

					tablero[mf][mc] = tablero[i][j];

					if (mf != i || mc != j){ 
						tablero[i][j] = 1;
						mover = true;
					}

					if (direccion == 2 || direccion == 3){
						incF = 0;
						incC = inc;
					}

					else { incF = inc; incC = 0; }

					if ((((mf != fin || mc != ini) && direccion >= 2) || ((mf <= fin || mc <= ini) && direccion < 2)) && tablero[mf][mc] == tope){


						tablero[mf - incF][mc - incC] = 2 * tablero[mf][mc];
						puntos += tablero[mf - incF][mc - incC];
						tablero[mf][mc] = 1;
						mover = true;
						tope = 1; 
					}

					else {

						tope = tablero[mf][mc];
						mf += incF;
						mc += incC;
					}
				}
			}

			cont++;

			if (direccion == 2 || direccion == 3)
				j += inc;

			else i += inc; //arriba-abajo
		}

		//Se vuelven a inicializar las variables: 

		if (direccion == 2) { 
			i += 1; 
			j = DIM - 1;
		}
		else if (direccion == 3){
			i += 1; 
			j = 0; 
		}
		else if (direccion == 0){
			j += 1; 
			i = 0; 
		}
		else if (direccion == 1){ 
			j += 1;
			i = DIM - 1; 
		}

		mf = i;
		mc = j;
		tope = tablero[i][j];
	}

	total += puntos;

	if(lleno(tablero) && !mover) 
		juego = Pierde;

	else if( mayor(tablero) >= META)
		juego = Gana;

	else{
		nuevaFicha(tablero);
		juego = Jugando;
	}

	return juego;
}

void limpiar(){
	system("cls");
}
void pause(){
	cout << endl;
	system("pause");
}
