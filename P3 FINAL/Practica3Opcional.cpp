//Belén Serrano Antón
//Andrea del Vado Puell

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "funcionesPrincipales.h"
#include "utilsWin.h"
#include "records.h"

using namespace std;

int main(){

	srand(time(NULL));

	tListaRecords listaR;
	tJuego2048 juego2048;
	tListaExp listaExp;
	tResultado juego = Jugando;
	tRecord record;
	string nombArch, nombPers;
	tOpcion op;
	char Chrguardar;

	juego2048.meta = 16;
	juego2048.dimen = 4;
	juego2048.mayor = 2;

	hacerArrayExp(listaExp);

	if (carga(juego2048)){

		visualiza(juego2048, listaExp);	
		nombArch = "records_" + to_string(juego2048.meta) + "_" + to_string(juego2048.dimen) + ".txt";
	}

	else {
		cout << "No se pudo continuar una partida. Empezamos una nueva." << endl;

		modosJuego(juego2048, listaExp);

		nombArch = "records_" + to_string(juego2048.meta) + "_" + to_string(juego2048.dimen) + ".txt";

		inicializa(juego2048);
		juego2048.celdasLibres = celdasLibres(juego2048);
		visualiza(juego2048, listaExp);		
	}

	op = menu(); 

	while ((op != OP_Salir) && (juego == Jugando)){

		juego2048.direccion = tDireccion(int(op));
		limpiar();
		juego = mueveFichas(juego2048, listaExp);		
		visualiza(juego2048, listaExp);

		if(juego != Jugando){

			if(juego == Gana) 
				cout << "¡Enhorabuena! Ha ganado el juego! " << endl;

			else if(juego == Pierde) 
				cout << "Lo siento... Ha perdido el juego. " << endl;

			cargar(nombArch, listaR);
			nuevoRecord(listaR, juego2048.Tpuntos);
			mostrar(listaR);
			guardarR(nombArch, listaR);	
		}

		else op = menu();
	}

	if (op == OP_Salir){


		cout << "¿Quieres guardar la partida para continuar en otro momento? (s/n):  ";
		cin >> Chrguardar;

		while (Chrguardar != 's' && Chrguardar != 'n'){

			cin.clear();	
			cin.sync();

			cout << "Error al leer la respuesta. Introduzca s / n:" << endl;
			cin >> Chrguardar;
		}

		if (Chrguardar == 's'){ 

			cout << endl;
			guarda(juego2048);
		}
	}

	pause();

	return 0;
}
