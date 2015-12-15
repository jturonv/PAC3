/**
* @file filtres.h
* @author Josep Turón i Viñas
* @version 2.0
* @date Desembre del 2015
* @brief Capçalera de les funcions de filtres
*
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
void fs_head( int fd );
void fs_wc( int fd );
void fs_nl( int fd );
void fs_cut( int  fd, int col );