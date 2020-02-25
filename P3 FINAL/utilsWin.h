//Belén Serrano Antón
//Andrea del Vado Puell

#ifndef utilsWin_H
#define utilsWin_H


#include <windows.h>

const int TE_Salir = VK_ESCAPE;
const int TE_Arriba = VK_UP;
const int TE_Abajo = VK_DOWN;
const int TE_Derecha = VK_RIGHT;
const int TE_Izquierda = VK_LEFT;

void background(int color); //hace el fondo de colores del tablero
int getKey(); //Lee las teclas especiales (flechas y esc)

#endif