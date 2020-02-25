//Belén Serrano Antón
//Andrea del Vado Puell

#include "records.h"

void cargar(string nombArch, tListaRecords & lista) {

	bool cargar = false;
	int archRecord, i;
	string nombPers;
	ifstream arch;

	arch.open(nombArch);

	if (arch.is_open()){

		arch >> nombPers;
		i = 0;

		while (i < MAXrecords && nombPers != CENTINELA){

			lista[i].nomb = nombPers;
			arch >> archRecord;

			lista[i].puntuacion = archRecord;
			arch >> nombPers;

			i++;
		}

		if (i < MAXrecords - 1)
			lista[i].nomb = CENTINELA;

		arch.close();
	}

	else
		lista[0].nomb = CENTINELA;	
}

void guardarR(string nombArch,  tListaRecords & lista){

	ofstream arch;
	int i = 0;

	arch.open(nombArch);

	while (i < MAXrecords && lista[i].nomb != CENTINELA){

		arch << lista[i].nomb <<  " " << lista[i].puntuacion << endl;	
		i++;
	}

	if (i < MAXrecords - 1)
		arch << CENTINELA;	

	arch.close();
}

void mostrar(const tListaRecords & lista){

	int i = 0;

	if (lista[0].puntuacion == -1)
		cout << "No hay records almacenados para este tipo de partida. " << endl;

	else {
		cout << "Los records obtenidos hasta ahora son:" << endl;

		while( i < MAXrecords && lista[i].nomb != CENTINELA){

			cout << " " << i+1 << ". " << setw(20) << left << lista[i].nomb << lista[i].puntuacion << endl;
			i++;
		}
	}
}


void insertar(tListaRecords & lista, int TPuntos, string nombPers){

	bool pos = false; 

	int i = 0;

	while( i < MAXrecords && !pos){

		if(lista[i].nomb != CENTINELA  && lista[i].puntuacion > TPuntos ) 
			i++;

		else{
			pos = true;

			for(int j = MAXrecords-1; j > i; j--)			
				lista[j] = lista[j-1];

			lista[i].puntuacion = TPuntos;
			lista[i].nomb = nombPers;
		}
	}
}

void nuevoRecord(tListaRecords & lista, int puntos){

	string nomPers;
	int i = 0;

	while (i < MAXrecords && lista[i].nomb != CENTINELA){
		i++;
	}

	if (i < MAXrecords && lista[i].nomb == CENTINELA) {

		cout << endl << "Enhorabuena, la lista de records no se ha llenado." << endl;
		cout << "Introduce tu nombre para que podamos ponerlo en la lista: ";

		cin.sync();
		getline(cin, nomPers);

		insertar(lista, puntos, nomPers);	

		cout << endl;
	}

	else if ( i == MAXrecords && lista[MAXrecords-1].puntuacion < puntos){

		cout << endl << "Enhorabuena, tienes un nuevo record." << endl;
		cout << "Introduce tu nombre para que podamos ponerlo en la lista:" << endl;

		cin.sync();
		getline(cin, nomPers);

		insertar(lista, puntos, nomPers);		
	}

	else cout << "Lo sentimos, pero esta vez no has entrado en la lista de records." << endl;
}
