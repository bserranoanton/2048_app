//Belén Serrano Antón
//Andrea del Vado Puell

#include "funcionesPrincipales.h"
#include "utilsWin.h"


void modosJuego(tJuego2048 & juego2048, const tListaExp listaExp){

	int i = 0;
	bool enc = false;

	cout << endl << "Elige la dimension del tablero " << endl;
	cout << "Dimension: " ;
	cin >> juego2048.dimen;

	while(juego2048.dimen <= 3 || juego2048.dimen >= DIM){

		cout << "Por favor, elija una dimensíon mayor o igual que 3 y menor que " << DIM ;
		cin >> juego2048.dimen;
	}

	cout << endl << "Elija la meta, esta debe ser una potencia de 2." << endl;
	cout << "Meta: " ;
	cin >> juego2048.meta;

	while(juego2048.meta != listaExp[i] && i < expMetaMax){

		if(juego2048.meta < listaExp[i]){

			cout << "Elija un numero que sea multiplo de dos por favor: " ;
			cin >> juego2048.meta;
			i = 0;
		}

		else i++;	
	}
	cout << endl;

	juego2048.Tpuntos = 0;
}

void inicializa(tJuego2048 & juego2048){

	int aleatorio1, aleatorio2, numTabAleat, j = 0;

	for (int i = 0; i < juego2048.dimen; i++){

		j = 0;

		while (j < juego2048.dimen){

			juego2048.tablero[i][j] = 0;
			j++;
		}
	}

	aleatorio1 = rand() % ((juego2048.dimen * juego2048.dimen - 1) + 1); //Numero entre 0 (15) y dim^2 -1

	juego2048.tablero[aleatorio1 / juego2048.dimen][aleatorio1 % juego2048.dimen] = 1;

	aleatorio2 = rand() % ((juego2048.dimen * juego2048.dimen - 1) + 1);

	while (aleatorio1 == aleatorio2){

		aleatorio2 = rand() % ((juego2048.dimen * juego2048.dimen - 1) + 1);
	}

	double azar = rand() / double(RAND_MAX); // da lugar a un real en el rango [0, 1] 

	if (azar < PROB2) numTabAleat = 1;
	else numTabAleat = 2;

	juego2048.tablero[aleatorio2 / juego2048.dimen][aleatorio2 % juego2048.dimen] = numTabAleat;
}

void nuevaFicha(tJuego2048 & juego2048){

	int aleatorio = rand() % (juego2048.dimen * juego2048.dimen);
	int numTabAleat;
	double azar = rand() / double(RAND_MAX);

	if (azar < PROB2) 
		numTabAleat = 1;

	else numTabAleat = 2;

	while (juego2048.tablero[aleatorio / juego2048.dimen][aleatorio % juego2048.dimen] != 0){

		aleatorio = rand() % (juego2048.dimen * juego2048.dimen);
	}

	juego2048.tablero[aleatorio / juego2048.dimen][aleatorio % juego2048.dimen] = numTabAleat;
}

void hacerArrayExp(tListaExp listaExp){

	int i = 1, potencia = 1;

	listaExp[0] = potencia;

	while (i < expMetaMax){
		potencia = potencia * 2;

		listaExp[i] = potencia;
		i++;
	}
}

bool carga(tJuego2048 & juego2048){

	ifstream arch;
	string nomb;
	bool cargar;
	int num;

	cout << "Introduce el nombre del archivo donde tienes tu partida(Intro para empezar una nueva):  ";

	getline(cin, nomb);

	arch.open(nomb);

	if (!arch.is_open()) {

		cargar = false;
		inicializa(juego2048);
		juego2048.puntos = 0;
	}

	else{

		arch >> juego2048.meta;
		arch >> juego2048.dimen; 

		cargar = true;

		for (int i = 0; i < juego2048.dimen; i++){

			for (int j = 0; j < juego2048.dimen; j++){
				arch >> num;
				juego2048.tablero[i][j] = num;
			}
		}

		arch >> juego2048.Tpuntos;

		arch.close();
	}

	juego2048.puntos = 0;
	juego2048.celdasLibres = celdasLibres(juego2048);

	return cargar;
}

void guarda(const tJuego2048 juego2048){

	ofstream arch;
	string nomb;

	cout << "Introduce el nombre del archivo para guardar la partida: ";

	cin.sync();
	getline(cin, nomb);

	arch.open(nomb);

	if (arch.is_open()){

		cout << endl << "Partida guardada en: " << nomb << endl;
		arch << juego2048.meta << " " << juego2048.dimen << endl;
		arch << endl;

		for (int i = 0; i < juego2048.dimen; i++){

			for (int j = 0; j < juego2048.dimen; j++){
				arch << juego2048.tablero[i][j] << endl;
			}

			arch << endl;
		}

		arch << juego2048.Tpuntos;
		arch.close();
	}

	else cout << "Problemas al guardar." << endl;
}

void visualiza(tJuego2048 & juego2048, const tListaExp listaExp){

	cout  << "Jugada: "  << juego2048.puntos;
	cout << "   Total puntos: " << juego2048.Tpuntos;
	cout << "   Meta: " << juego2048.meta << endl;

	bordeSuperior(juego2048);

	for(int j = 0; j < juego2048.dimen; j++){

		visualizaF(juego2048,j, listaExp);

		if (j != juego2048.dimen - 1)
			bordeInter( juego2048);
	}

	bordeInferior(juego2048);
}

void visualizaF(tJuego2048  & juego2048, int fila, const tListaExp listaExp){

	celda(juego2048, fila);
	cout << lineaVertical; 

	for(int i = 0; i < juego2048.dimen; i++){

		if(juego2048.tablero[fila][i] == 0) {

			background(juego2048.tablero[fila][i]);
			cout << right << setw(5) << "" << lineaVertical;
		}

		else{

			background(juego2048.tablero[fila][i]);
			cout << right << setw(5) << listaExp[juego2048.tablero [fila][i]];
			background(0);
			cout << lineaVertical; 
		}
	}

	cout << endl;
	celda(juego2048, fila);
}

void celda(const tJuego2048 juego2048, int fila){

	cout << lineaVertical; 

	for(int i = 0; i < juego2048.dimen; i++){

		if(juego2048.tablero[fila][i] == 0) {

			background(juego2048.tablero[fila][i]);
			cout << right << setw(5) << "" << lineaVertical;
		}

		else{

			background(juego2048.tablero[fila][i]);
			cout << right << setw(5) << "";
			background(0);
			cout << lineaVertical; 
		}
	}

	cout << endl;
} 

void bordeSuperior( const tJuego2048 juego2048){

	int cont = 5, celda = ((juego2048.dimen * BITS) - 1);

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

void bordeInter( const tJuego2048 juego2048){

	int cont = 5, celda = ((juego2048.dimen * BITS) - 1);

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

void bordeInferior (const tJuego2048 juego2048){

	int cont = 5,  celda = (juego2048.dimen * BITS) - 1;

	cout << esquiIzqInf;

	for (int i = 0; i < celda; i++){

		if (i == cont){ 
			cout << formaTinver;
			cont = cont + BITS; 
		}

		else cout << lineaHorizontal;
	}

	cout << esquiDerInf;
	cout << endl;
}

tOpcion menu(){

	tOpcion op;

	cout << endl;

	cout << "Usa las flechas para inclinar el tablero. (Esc para salir)." << endl;
	int tecla = getKey();

	cout << endl;

	while((tecla != TE_Salir) && (tecla != TE_Abajo) && (tecla != TE_Arriba) && (tecla != TE_Derecha) && (tecla != TE_Izquierda)){

		//cout << "Por favor, use las flechas o la tecla esc para salir." << endl;
		//cin.sync();
		tecla = getKey();
	}	

	if (tecla == TE_Salir) op = OP_Salir;
	else if (tecla == TE_Abajo)op = OP_Abajo;
	else if (tecla == TE_Arriba)op = OP_Arriba;
	else if (tecla == TE_Derecha)op = OP_Derecha;
	else if (tecla == TE_Izquierda)op =OP_Izquierda;

	return op;
}


int celdasLibres(const tJuego2048 juego2048){

	int libres = 0;

	for (int i = 0; i < juego2048.dimen; i++){

		for (int j = 0; j < juego2048.dimen; j++){

			if (juego2048.tablero[i][j] == 0)
				libres++;
		}	
	}

	return libres;
}

tResultado mueveFichas(tJuego2048 & juego2048 , const tListaExp listaExp){

	tResultado juego = Jugando;
	bool mover = false;
	int ini, fin, mf, mc, tope, inc, i, j, cont	, incF, incC;;
	int varComienzoi, VarComienzoj;

	juego2048.puntos = 0;

	if (juego2048.direccion == 0 /*arriba*/){
		ini = 0; fin = juego2048.dimen - 1; mf = 0; mc = 0; inc = 1; i = 0; j = 0;
		varComienzoi = 0; VarComienzoj = 0;
	}

	else if (juego2048.direccion == 1 /*abajo*/){
		ini = juego2048.dimen - 1; fin = 0; mf = juego2048.dimen - 1; mc = 0; inc = -1; i = ini; j = 0;
		varComienzoi = juego2048.dimen - 1; VarComienzoj = 0;
	}

	else if (juego2048.direccion == 2 /*derecha*/){
		ini = juego2048.dimen - 1; fin = 0; mf = fin; mc = ini;   inc = -1; i = fin; j = ini;
		varComienzoi = fin; VarComienzoj = ini;  
	} /// i no se mueve


	else if (juego2048.direccion == 3 /*izq*/){
		ini = 0; fin = juego2048.dimen - 1; mf = ini; mc = ini; inc = 1; i = ini; j = 0;
		varComienzoi = ini; VarComienzoj = ini;  
	}///i no se mueve

	while ((((int(juego2048.direccion) >= 2) && i < juego2048.dimen && j != fin) || (int(juego2048.direccion) == 0 && i < juego2048.dimen && j <= fin)) ||

		(int(juego2048.direccion) == 1 && (j < juego2048.dimen))){

			cont = 0;

			while (cont < juego2048.dimen) {

				if (((juego2048.direccion == 2 || juego2048.direccion == 3) && j == VarComienzoj) ||
					((juego2048.direccion == 0 || juego2048.direccion == 1) && i == varComienzoi)){

						if (juego2048.tablero[i][j] == 0) {

							if (juego2048.direccion == 2 || juego2048.direccion == 3) 
								mc = j; 
							else  mf = i;  // movimiento de arriba a abajo
						}

						else {

							if (juego2048.direccion == 2 || juego2048.direccion == 3) 
								mc += inc;
							else  mf += inc;  // arriba-abajo
						}

						tope = juego2048.tablero[i][j];
				}

				else {

					if (juego2048.tablero[i][j] != 0){

						juego2048.tablero[mf][mc] = juego2048.tablero[i][j];

						if (mf != i || mc != j){ 
							juego2048.tablero[i][j] = 0; ////!!!
							mover = true;
						} 			

						if (juego2048.direccion == 2 || juego2048.direccion == 3){
							incF = 0; incC = inc;
						}

						else { 
							incF = inc; 
							incC = 0; 
						}

						if ((((mf != fin || mc != ini) && juego2048.direccion >= 2) || ((mf <= fin || mc <= ini) 
							&& juego2048.direccion < 2)) && juego2048.tablero[mf][mc] == tope){

								juego2048.tablero[mf - incF][mc - incC] = 1 + juego2048.tablero[mf][mc];

								int ver = juego2048.tablero[mf - incF][mc - incC];

								juego2048.puntos += listaExp[juego2048.tablero[mf - incF][mc - incC]];

								if(listaExp[juego2048.tablero[mf - incF][mc - incC]]> juego2048.mayor) 
									juego2048.mayor = listaExp[juego2048.tablero[mf - incF][mc - incC]];

								juego2048.tablero[mf][mc] = 0;

								mover = true;
								tope = 0; 
						}

						else {

							tope = juego2048.tablero[mf][mc];
							mf += incF;
							mc += incC;
						}
					}
				}

				cont++;

				if (juego2048.direccion == 2 || juego2048.direccion == 3)
					j += inc;
				else  i += inc;  //arriba-abajo
			}

			//Se vuelven a inicializar las variables: 

			if (juego2048.direccion == 2) {
				i += 1; 
				j = juego2048.dimen - 1; 
			}
			else if (juego2048.direccion == 3){ 
				i += 1; 
				j = 0;  
			}
			else if (juego2048.direccion == 0){ 
				j += 1; 
				i = 0; 
			}
			else if (juego2048.direccion == 1){ 
				j += 1;
				i = juego2048.dimen - 1;
			}

			mf = i;
			mc = j;
			tope = juego2048.tablero[i][j]; 
	}

	juego2048.Tpuntos += juego2048.puntos;
	juego2048.celdasLibres = celdasLibres(juego2048);

	if(juego2048.celdasLibres == 0 && !mover) 
		juego = Pierde;

	else if( juego2048.mayor >= juego2048.meta)
		juego = Gana;

	else{
		nuevaFicha(juego2048);
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

