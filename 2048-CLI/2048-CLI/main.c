#include <stdlib.h>

#include <time.h>
#include "curses.h"

#define cellX  6
#define cellY  12




struct vector;

typedef struct vector vector;
void showanimation(int[4][4], vector[4][4]);

unsigned int score;

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

	mvprintw(cellX, cellY * 5 + cellY/2, "Score : %d", score);

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
		refresh();
		//_sleep(1);




	}



}


void keyprocess(char a, int t[4][4]){
	printw("%d", a);
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
		break;
	}


}
void randgen(int a[16]){
	int k;
	do {
		k = rand() % 16;

	} while (a[k] != 0);
	a[k] = 2;


}

int main() {

	int i = 0;
	int row, col;
	int play_x=0, play_y=0;
	int table[4][4] = { 0, };
	char key = 0;
	score = 0;
	srand(time(NULL));
	table[0][1] = table[0][2] = 2;
	table[0][3] = 4;
	table[1][0] = table[2][0] = 2;
	table[3][0] = 4;
	initscr();                    /* Start curses mode */
	
	start_color();
	noecho();
	curs_set(FALSE);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));

	getmaxyx(stdscr, row, col);              /* get the number of rows and columns */
	//nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	while (1){
		//clear();
		clear();
		//mvprintw(play_x,play_y,"O");    /* Print Hello World */
		
		
		
		printgrid();
		printnumber(table);
		mvprintw(3, 3, "%d",key);


		keyprocess(getch(),table);
		randgen(table);
		refresh();                    /* Print it on to the real screen */
		play_x++;
		
		//keyprocess(getch(),table);
		
	}
	endwin();                     /* End curses mode */



	return 0; 
}