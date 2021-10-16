#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

//Constantes
const char suelo = ' ';
const char EMPTY = ' ';
const char muro = '#';
const char jugador = '@';
const int FONDO = '1';
const int TEXTO = '2';
const int WARNING = '3';

//Funciones
void inicio();
void mapa();
int posiblemover(int y, int x);

int main()
{
	initscr();

	cbreak;
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	start_color();

	inicio();
	endwin();

	return 0;
}

void inicio()
{
	attron(A_DIM);
	box(stdscr, 0, 0);
	attroff(A_DIM);

	attron(A_BLINK);
	mvwprintw(stdscr, 28, 20, "[J] Jugar");
	mvwprintw(stdscr, 28, 50, "[I] Instrucciones");
	mvwprintw(stdscr, 28, 85, "[S] Salir");
	attroff(A_BLINK);

	char opcion;
	refresh();

	while (opcion = wgetch(stdscr))
	{
		switch (opcion)
		{
		case 'j':
			werase(stdscr);
			mapa();
			break;

		case 'i':
			wclear(stdscr);
			box(stdscr, 0, 0);
			wattron(stdscr, A_BLINK);
			mvwprintw(stdscr, 0, COLS / 12, " [J] JUGAR ");
			mvwprintw(stdscr, 0, (COLS / 12) * 10, " [S] SALIR ");
			wattroff(stdscr, A_BLINK);
			wattron(stdscr, A_STANDOUT);
			mvwprintw(stdscr, 0, (COLS / 12) * 5, " INSTRUCCIONES ");
			wattroff(stdscr, A_STANDOUT);

			mvwprintw(stdscr, 8, 10, "Bienvenido, Contendiente: ");
			mvwprintw(stdscr, 11, 15, "Tu voluntad ha traído grandes recompensas pues has sido seleccionado para representar");
			mvwprintw(stdscr, 12, 15, "al Kandorak 378-BWZ en el proximo encuentro de la Fedreacion Instrumentalista y sus");
			mvwprintw(stdscr, 13, 15, "derivados.");
			mvwprintw(stdscr, 15, 15, "Tal honor es otorgado solo a aquellos que sean capaces de enferntar sus mas grandes");
			mvwprintw(stdscr, 16, 15, "miedos en el crisol e la batalla pues, de perder, tu Kandorak sera borrado del");
			mvwprintw(stdscr, 17, 15, "algoritmo de La Gran Semilla.");

			mvwprintw(stdscr, 19, 15, "Como La Gran Semilla decreto, tendras la de elegir tu propio Galo (Avatar) con");
			mvwprintw(stdscr, 20, 15, "caracteristicas que te llevaran a la victoria...o a la derrota.");
			mvwprintw(stdscr, 25, 15, "QUE NUESTRA ESENCIA ELEMENTAL PERDURE POR LA NOCHE");
			mvwprintw(stdscr, 26, 15, "LARGA VIDA AL COMBATE");
			mvwprintw(stdscr, 27, 15, "LARGA VIDA A LA GRAN SEMILLA");
			mvwprintw(stdscr, 32, 65, "Honorable Federacion Instrumentalista");
			break;
		case 's':
			werase(stdscr);
			endwin();
			exit(EXIT_SUCCESS);
			break;

		default:
			break;
		}
	}
}

void mapa()
{
	int y, x;

	init_pair(FONDO, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(TEXTO, COLOR_YELLOW, COLOR_BLACK);
	init_pair(WARNING, COLOR_RED, COLOR_BLACK);

	box(stdscr, 0, 0);

	attron(COLOR_PAIR(WARNING));
	mvwprintw(stdscr, 39, 12, " IG II ");
	mvwprintw(stdscr, 39, 90, " [s] Salir ");
	attroff(COLOR_PAIR(WARNING));
	attron(COLOR_PAIR(TEXTO));
	mvwprintw(stdscr, 39, 40, " Tu personaje es... ");
	wattron(stdscr, A_BLINK);
	mvwprintw(stdscr, 0, 12, " Vida: ");
	wattroff(stdscr, A_BLINK);
	attroff(COLOR_PAIR(TEXTO));

	attron(COLOR_PAIR(FONDO));
	// Suelo
	for (y = 1; y < LINES - 1; y++)
	{
		mvhline(y, 1, suelo, COLS - 3);
	}

	// Muros
	for (y = 2; y < LINES / 3 - 1; y++)
	{

		mvhline(y, 2, muro, COLS / 12);
		mvhline(y + 15, 2, muro, COLS / 12);
		mvhline(y + 18, 20, muro, COLS / 10);
		mvhline(y, 40, muro, COLS / 12);
		mvhline(y, 65, muro, COLS / 20);
		mvhline(y + 8, 65, muro, COLS / 12);
		mvhline(y + 18, 65, muro, COLS / 7);
		mvhline(y + 18, 101, muro, COLS / 7);
		mvhline(y + 3, 83, muro, COLS / 4);
	}

	for (y = 5; y < LINES / 2; y++)
	{

		mvhline(y, 20, muro, COLS / 12);
	}

	for (y = 15; y < LINES / 2; y++)
	{

		mvhline(y, 20, muro, COLS / 5);
		mvhline(y + 10, 30, muro, COLS / 5);
		mvhline(y + 18, 30, muro, COLS / 5);
		mvhline(y + 18, 60, muro, COLS / 4);
		mvhline(y + 18, 101, muro, COLS / 7);
	}
	attroff(COLOR_PAIR(FONDO));

	int yc = 30;
	int xc = 5;
	char ch;

	mvaddch(yc, xc, jugador);
	move(yc, xc);
	refresh();

	ch = getch();

	if (KEY_UP)
	{
		if ((y > 0) && posiblemover(y - 1, x))
		{
			mvaddch(y, x, EMPTY);
			y = y - 1;
			refresh();
		}
	}
}

int posiblemover(int y, int x)
{
	int testch;
	testch = mvinch(y, x);
	return ((testch == suelo) || (testch == EMPTY));
}