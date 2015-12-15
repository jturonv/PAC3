/**
* @file filtres.c
* @author Josep Turón i Viñas
* @version 2.0
* @date Desembre del 2015
* @brief Codi de les funcions de filtres
* @section Descripció
* Aquest fitxer conté el codi font escrit amb llenguatge C d'una sèrie de filtres que actuen sobre un fitxer de text passat com a paràmetre d'entrada, i realitzen diverses operacions sobre ell.
* @attention Cal disposar d'un arxiu de text en format pla per a poder executar aquest codi.
* @section Llicència
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details at
* https://www.gnu.org/copyleft/gpl.html
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filtres.h"

/**
* Aquesta funció rep una variable de tipus enter (num) i mitjançant un punter de memòria la recorre caràcter a caràcter, l'imprimeix al dispositiu de sortida (per defecte en pantalla), i avança fins al caràcter següent.
* @brief Funció que serveix per imprimir per pantalla el contingut d'una variable caràcter a caràcter. No retorna cap valor (void).
* @param num Variable de tipus enter que volem imprimir en pantalla. Paràmetre d'entrada.
*/
void printstr(int num)
{
	int aux, i;
	char *nstr;

        aux = 1;
	nstr = (char *)malloc( 10 );
        for( i = 1; i < num; i*=10 ) aux++;
        nstr = (char *)malloc( aux + 2 );
        sprintf(nstr, "%d ", num);
        write( 1, nstr, strlen( nstr ) );
}
/**
* Aquest filtre rep un descriptor de fitxer de tipus enter (fd) i amb la funció read dins un bucle el tracta caràcter a caràcter i el va imprimint pel dispositiu de sortida, fins a completar les 3 primeres línies del fitxer, que detecta analitzant el caràcter de salt de línia \n i augmentant un comptador (count) fins arribar a 3.
* @brief Filtre que mostra les tres primeres línies del fitxer d'entrada. No retorna cap valor (void).
* @param fd Descriptor del fitxer d'entrada. Paràmetre d'entrada.
*/
void fs_head( int fd )
{
	int count = 0;
	char c;

	while( read( fd, &c, 1 ) && (count < 3) ){
		write( 1, &c, 1 );
		if ( c == '\n' ) count++;
	}
}

/**
* Aquest filtre rep un descriptor de fitxer de tipus enter (fd) i amb la funció read dins un bucle el tracta caràcter a caràcter i l'analitza detectant caràcters separadors de paraules o línies. Utilitza unes variables internes (nc, np, nl) per portar el compte del número de caràcters, paraules i línies del fitxer i crida a la funció printstr que les imprimirà pel dispositiu de sortida.
* @brief Filtre que compta el número de caràcters, paraules i línies del fitxer d'entrada. No retorna cap valor (void).
* @param fd Descriptor del fitxer d'entrada. Paràmetre d'entrada.
*/
void fs_wc( int fd )
{
	int nl = 0, np = 0, nc = 0, sep = 0;
	char c;
	
	while( read( fd, &c, 1 ) ){
		nc++;
		switch( c ){
			case '\n': nl++;
			case '\t':
			case ' ': if( !sep ) np++; 
				  break;
			default: sep = 0;
		}
	 }
	printstr( nc );
	printstr( np );
	printstr( nl );
	c = 10;
	write( 1, &c, 1 );
}

/**
* Aquest filtre rep un descriptor de fitxer de tipus enter (fd) i amb la funció read dins un bucle el tracta caràcter a caràcter i l'analitza detectant caràcters separadors de línies. Utilitza una variable interna per portar el compte del número de línia (nl), a cada salt crida a la funció printstr que imprimeix aquest número de línia pel dispositiu de sortida i a continuació imprimeix un a un els caràcters de la línia, fins al següent salt.
* @brief Filtre que numera les línies del fitxer d'entrada. No retorna cap valor (void).
* @param fd Descriptor del fitxer d'entrada. Paràmetre d'entrada.
*/
void fs_nl( int fd )
{
	int nl = 1, new = 1;
	char c;

	while( read( fd, &c, 1) ){
		if( new ){
			printstr( nl );
			nl++;
			new = 0;
		}
		if ( c == '\n' ) new = 1;
		write( 1, &c, 1 );		
	}
}

/**
* Aquest filtre rep un descriptor de fitxer de tipus enter (fd) i un número enter (col), amb la funció read dins un bucle tracta el fitxer caràcter a caràcter i l'analitza detectant caràcters separadors de paraules o línies. Utilitza una variable interna (pal) per a portar el compte del número de paraula que està tractant, i si aquesta correspon a la posició introduïda amb la posició col, la imprimeix pel dispositiu de sortida mitjançant la funció printstr.
* @brief Filtre que mostra només la paraula en la posició indicada del fitxer d'entrada. No retorna cap valor (void).
* @param fd Descriptor del fitxer d'entrada. Paràmetre d'entrada.
* @param col Valor que indica la posició de la paraula que es desitja mostrar. Paràmetre d'entrada.
*/
void fs_cut( int fd, int col )
{
	char c;
	int pal = 1, nc = 0;

	while( read( fd, &c, 1 ) ){
		if ( c == '\n' ){
			if(pal >= col) write( 1, &c, 1 );
			pal = 1;
			nc = 0;
		} 
		else if ( pal == col ){ nc++; write( 1, &c, 1 );}
		if (( c == '\t' ) || ( c == ' ' )) pal++;
	}
}