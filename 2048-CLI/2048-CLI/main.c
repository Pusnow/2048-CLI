#include <stdlib.h>

#include <time.h>
#include "curses.h"

#define cellX  6
#define cellY  10

int pipe[10];

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



}

void goright(int a[4][4]){
	int x, y,k;

	for (y = 0; y < 4; y++){
		for (x = 3; x >= 0; x--){

			if (a[x][y] == 0){
				for (k = x - 1; k >= 0; k--){
					if (a[k][y] != 0){
						a[x][y] = a[k][y];
						a[k][y] = 0;
						break;
					}
				}
			}
		}

	}
}

void mergeright(int a[4][4]){
	int x, y;

	for (y = 0; y < 4; y++){
		for (x = 3; x > 0; x--){
			if (a[x][y] == a[x - 1][y]){
				a[x][y] = 2 * a[x][y];
				a[x - 1][y] = 0;
			}
		}
	}


}


void goleft(int a[4][4]){
	int x, y, k;
	for (y = 0; y < 4; y++){
		for (x = 0; x < 4; x++){

			if (a[x][y] == 0){
				for (k = x + 1; k < 4; k++){
					if (a[k][y] != 0){
						a[x][y] = a[k][y];
						a[k][y] = 0;
						break;
					}
				}
			}
		}
	}
}
void mergeleft(int a[4][4]){
	int x, y;

	for (y = 0; y < 4; y++){
		for (x = 0; x < 3; x++){
			if (a[x][y] == a[x + 1][y]){
				a[x][y] = 2 * a[x][y];
				a[x + 1][y] = 0;
			}
		}
	}


}


void godown(int a[4][4]){
	int x, y, k;
	for (x = 0; x < 4; x++){
		for (y = 3; y >= 0; y--){

			if (a[x][y] == 0){
				for (k = y - 1; k >=0; k--){
					if (a[x][k] != 0){
						a[x][y] = a[x][k];
						a[x][k] = 0;
						break;
					}
				}
			}
		}

	}
}

void mergedown(int a[4][4]){
	int x, y;

	for (x = 0; x < 4; x++){
		for (y = 3; y > 0; y--){
			if (a[x][y] == a[x][y-1]){
				a[x][y] = 2 * a[x][y];
				a[x ][y-1] = 0;
			}
		}
	}


}

void goup(int a[4][4]){
	int x, y, k;
	
	for (x = 0; x < 4; x++){
		for (y = 0; y < 3; y++){
			if (a[x][y] == 0){
				for (k = y + 1; k < 4; k++){
					if (a[x][k] != 0){
						a[x][y] = a[x][k];
						a[x][k] = 0;
						break;
					}
				}
			}
		}

	}
}

void mergeup(int a[4][4]){
	int x, y;

	for (x = 0; x < 4; x++){
		for (y = 0; y < 3; y++){
			if (a[x][y] == a[x][y+1]){
				a[x][y] = 2 * a[x][y];
				a[x ][y+1] = 0;
			}
		}
	}


}




void right(int a[4][4]){
	goright(a);
	mergeright(a);
	goright(a);
}
void left(int a[4][4]){
	goleft(a);
	mergeleft(a);
	goleft(a);
}

void up(int a[4][4]){
	goup(a);
	mergeup(a);
	goup(a);
}
void down(int a[4][4]){
	godown(a);
	mergedown(a);
	godown(a);
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