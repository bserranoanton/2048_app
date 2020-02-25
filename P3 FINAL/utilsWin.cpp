//Belén Serrano Antón
//Andrea del Vado Puell

#include "utilsWin.h"

void background(int color){

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | (color << 4));
}

int getKey() {

	int key;

	INPUT_RECORD record; DWORD num;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	do {
		ReadConsoleInput(hStdIn, &record, 1, &num);

	} 	while(record.EventType != KEY_EVENT );

	if (record.Event.KeyEvent.uChar.AsciiChar == 0) {
		ReadConsoleInput(hStdIn, &record, 1, &num);
		key = record.Event.KeyEvent.wVirtualKeyCode;
	} 

	else 
		key = record.Event.KeyEvent.uChar.AsciiChar;

	return key;
}