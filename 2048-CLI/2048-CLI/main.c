#include <stdlib.h>

#include <time.h>
#include "curses.h"

#define cellX  6
#define cellY  12




struct vector;

typedef struct vector vector;
void showanimation(int[4][4], vector[4][4]);
void printscore(void);

unsigned int score, best=0;

enum direction  {
	UP,
	DOWN,
	LEFT,
	RIGHT


};


struct vector {

	int X;
	int Y;


};



void printgrid(void){
	int x, y;
	for (x = 0; x < 5; x++){
		mvhline(x*cellX, cellY, '-', cellY*4);

	}
	for (x = 1; x < 6; x++){
		mvvline(1, x * cellY, '|', cellX * 4);

	}
	
	for (x = 1; x < 6; x++){
		for (y = 0; y < 5; y++){
			mvprintw(cellX*y , cellY*x, "+");


		}
	}


}

void printnumber(int a[4][4]){
	int x, y;
	for (x = 0; x < 4; x++){
		for (y = 0; y < 4; y++){
			if (a[x][y] != 0 )
				mvprintw(cellX*y + cellX/2, cellY*(x+1) + cellY/2,"%d" ,a[x][y]);


		}
	}

	printscore();

}


void printscore(void){
	


	mvprintw(cellX, cellY * 5 + cellY / 2 , "Best  : %d", best);
	mvprintw(cellX+1, cellY * 5 + cellY / 2, "Score : %d", score);



}


void govector(int a[4][4], vector dir, vector ani[4][4]){
	int x, y, k, lastmerge;
	int i, j;


	if (dir.X + dir.Y < 0){
		x = 0;
		y = 0;
	}
	else {
		x = 3;
		y = 3;

	}
	for (i = 0; i < 4; i++){
		lastmerge = -1;
		for (j = 0; j<4; j++){

			if (a[x - dir.X * j][y - dir.Y*j] != 0){
				for (k = j-1; k >lastmerge; k--){


					if (a[x - dir.X * k][y - dir.Y*k] == 0){
						a[x - dir.X * k][y - dir.Y*k] = a[x - dir.X * (k + 1)][y - dir.Y*(k + 1)];
						a[x - dir.X * (k + 1)][y - dir.Y*(k + 1)] = 0;
						ani[x - dir.X * j][y - dir.Y*j].X += dir.X;
						ani[x - dir.X * j][y - dir.Y*j].Y += dir.Y;
					

					}
					else if (a[x - dir.X * k][y - dir.Y*k] == a[x - dir.X * (k + 1)][y - dir.Y*(k + 1)]){
						a[x - dir.X * k][y - dir.Y*k] = a[x - dir.X * k][y - dir.Y*k] * 2;
						score += a[x - dir.X * k][y - dir.Y*k];
						if (score > best)
							best = score;
						a[x - dir.X * (k + 1)][y - dir.Y*(k + 1)] = 0;
						ani[x - dir.X * j][y - dir.Y*j].X += dir.X;
						ani[x - dir.X * j][y - dir.Y*j].Y += dir.Y;
						lastmerge = k;

					}
					else {
						break;
					}
				}
			}


		}
		x = (x - dir.Y) % 4;
		y = (y - dir.X) % 4;

	}



}




void right(int a[4][4]){
	vector dir, ani[4][4] = { { 0, 0 }, };
	int b[4][4];
	dir.X = 1;
	dir.Y = 0;
	memcpy(b, a, sizeof(int)* 4 * 4);
	govector(a, dir,ani);

	showanimation(b, ani);
}
void left(int a[4][4]){
	vector dir, ani[4][4] = { { 0, 0 }, };
	int b[4][4];

	memcpy(b, a, sizeof(int)* 4 * 4);
	dir.X = -1;
	dir.Y = 0;

	govector(a, dir, ani);
	showanimation(b, ani);
}

void up(int a[4][4]){
	vector dir, ani[4][4] = { { 0, 0 }, };
	int b[4][4];
	dir.X = 0;
	dir.Y = -1;
	memcpy(b, a, sizeof(int)* 4 * 4);
	govector(a, dir, ani);
	showanimation(b, ani);
}
void down(int a[4][4]){
	vector dir, ani[4][4] = { { 0, 0 }, };
	int b[4][4];
	dir.X = 0;
	dir.Y = 1;
	memcpy(b, a, sizeof(int)* 4 * 4);
	govector(a, dir, ani);
	showanimation(b, ani);
}

void showanimation(int a[4][4], vector ani[4][4]){
	int i, x,y;

	for (i = 0; i < cellX*cellY; i++){
		clear();
		printgrid();
		for (x = 0; x < 4; x++){
			for (y = 0; y < 4; y++){
				if (a[x][y] != 0)
					mvprintw(cellX*y + cellX / 2 + ani[x][y].Y*i/(cellX*2), cellY*(x + 1) + cellY / 2 + ani[x][y].X*i/cellX, "%d", a[x][y]);


			}
		}
		printscore();
		refresh();
		//_sleep(1);




	}



}


int keyprocess(char a, int t[4][4]){
	switch (a)
	{
	case 'w':
		up(t);
		break;
	case 's':
		down(t);
		break;
	case 'a':
		left(t);
		break;
	case 'd':
		right(t);
		break;



	default:
		return -1;
	}


}
int randgen(int a[16]){
	int k;

	for (k = 0; k < 16; k++){
		if (a[k] == 0)
			break;
	}
	if (k == 16)
		return -1;


	do {
		k = rand() % 16;

	} while (a[k] != 0);
	a[k] = (rand()%2+1)*2;


}

void resettable(int a[16]){
	int i;
	for (i = 0; i < 16; i++){
		a[i] = 0;

	}
}

int gamestart(void){
	int table[4][4] = { 0, };
	int end;
	score = 0;
	randgen(table);
	while (1){
		//clear();
		clear();
		//mvprintw(play_x,play_y,"O");    /* Print Hello World */



		printgrid();
		printnumber(table);



		while (keyprocess(getch(), table) == -1){}
		end = randgen(table);
		if (checkgameover(table)){
			gameover();
			if (getch() == 'r'){
				
				resettable(table);
				score = 0;
				randgen(table);
			}


		}
		refresh();                    /* Print it on to the real screen */

		//keyprocess(getch(),table);

	}



}

void gameinit(){
	srand(time(NULL));

	initscr();                    /* Start curses mode */

	start_color();
	noecho();
	curs_set(FALSE);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));
	//nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);


}

void title(){
	int x, y,maxx,maxy;
	clear();
	getmaxyx(stdscr,maxy, maxx);
	y = maxy / 2- 8;
	x = maxx / 2 - 18;
	mvprintw(y, x, " _______  _______  _   ___   _____  ");
	mvprintw(y + 1, x, "|       ||  _    || | |   | |  _  | ");
	mvprintw(y + 2, x, "|____   || | |   || |_|   | | |_| | ");
	mvprintw(y + 3, x, " ____|  || | |   ||       ||   _   |");
	mvprintw(y + 4, x, "| ______|| |_|   ||___    ||  | |  |");
	mvprintw(y + 5, x, "| |_____ |       |    |   ||  |_|  |");
	mvprintw(y + 6, x, "|_______||_______|    |___||_______|");

	
	mvhline(0, 0, ACS_HLINE, maxx/2 -1);
	mvvline(0, 0, ACS_VLINE, maxy -1 );
	mvhline(maxy - 1, 0, ACS_HLINE, maxx/2 -1);
	mvvline(0, maxx-3, ACS_VLINE, maxy -1);
	
	mvaddch(0, 0, ACS_ULCORNER);
	mvaddch(maxy - 1, 0, ACS_LLCORNER);
	mvaddch(0, maxx/2 -1 , ACS_URCORNER);
	mvaddch(maxy - 1, maxx/2 -1, ACS_LRCORNER);
	

	mvprintw(y + 14, x+5, "Press any key to start.");
	mvprintw(maxy-2, 1, "(c) Wonsup Yoon, Yonsei University 2015");
	refresh();


}

int checkgameover(int a[4][4]){
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 3; j++){
			if (a[i][j] == 0)
				return 0;
			if (a[j][i] == 0)
				return 0;
			if (a[i][j] == a[i][j + 1])
				return 0;
			if (a[j][i] == a[j + 1][i])
				return 0;
		}
	}

	return 1;


}

int gameover(){
	WINDOW *over;
	
	int maxy, maxx;
	int winx, winy;

	winx = 40;
	winy = 8;

	getmaxyx(stdscr, maxy, maxx);
	clear();
	over = newwin(winy, winx, maxy / 2 -winy/2, maxx / 2 - winx/2);
	mvwprintw(over,1,winx/2 - 5 ,"Game Over!");

	mvwprintw(over, 3, winx / 2 - 5, "Score: %d", score);

	mvwprintw(over, 5, winx / 2 - 10, "Press R key to retry", score);

	//box(over, 0, 0);
	wborder(over, '|', '|', '-', '-', '+', '+', '+', '+');
	refresh();
	wrefresh(over);
	



}
                                    


int main() {


	gameinit();
	title();
	
	getch();
	gamestart();
	
	
	
	
	endwin();                     /* End curses mode */



	return 0; 
}