#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define WHITE 7
#define BLUE 3
#define LBLUE 9
#define RED 4
#define GREEN 2
#define LGREEN 10
#define YELLOW 6

typedef struct	{
	char N_SHIP [25];
	int SIZE;
}	SHIP;

HANDLE wHnd;
HANDLE rHnd;

void SetColor(int ForgC);
int MENU (void);
void SHOW1 (int m_n1 [10][10], int m_n2 [10][10], int T);
void SHOW2 (int m_n1 [10][10], int m_n2 [10][10], int T);
int WATER (int m_n1 [10][10], int m_n2 [10][10], int A, int B, int C, int D, int E, int TURN);
void FILL_PVP (int m_n1 [10][10], int m_n2 [10][10]);												//PVP --> Player Vs Player
void FILL_PVC (int m_n1 [10][10], int m_n2 [10][10]);												//PVC --> Player Vs Cpu
void GAME_PVP (int m_n1 [10][10],int m_n2 [10][10]);												//PVP --> Player Vs Player
void GAME_PVC (int m_n1 [10][10],int m_n2 [10][10]);												//PVC --> Player Vs Cpu

int main (int argc, char* argv[])	{
	int M_N1 [10][10], M_N2[10][10], turn = 0, flag = 0, M = 0, i, j;
	char D;
	
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    
    SetConsoleTitle("BATTLESHIPS by Zeby");
	
	SMALL_RECT windowSize = {0, 0, 100, 600};							//CONSOLE SIZE
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	while (flag == 0)	{
		for (i = 0; i < 10; i++)	{
			for (j = 0; j < 10; j++)	{
				M_N1 [i][j] = 0;
				M_N2 [i][j] = 0;
			}
		}
		M = MENU ();
		switch (M)	{
			case 1:
				FILL_PVP (M_N1, M_N2);
				GAME_PVP (M_N1, M_N2);
				break;

			case 2:
				FILL_PVC (M_N1, M_N2);
				GAME_PVC (M_N1, M_N2);
				break;
		}
		
		do
		{
			fflush (stdin);
			SetColor (WHITE);
			printf ("\n\n\t\tDo you want to play again? (Y/N): ");
			scanf ("%c", &D);
			tolower (D);
		} while ((D != 'y') && (D != 'n'));

		if (D == 'y')	{
			flag = 0;
		}	else	{
			flag = 1;
			exit (0);
		}
	}
	system ("pause");
}

void SetColor(int ForgC)	{													//FUNCTION TO SET COLOR IN CONSOLE

     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))	{
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }

     return;
}

int MENU (void)	{
	int D = 0;

	do
	{
		system ("cls");
		SetColor (BLUE);
		printf ("\n\n\t\t\tWelcome to Battlehips!\n\n");
		SetColor (RED);
		printf ("\n\nChoose an option:\n\t1) Against another player.\n\t2) Against the CPU.");
		SetColor (WHITE);
		printf ("\n\nDecision: ");
		scanf ("%d", &D);
	} while ((D < 1) || (D > 2));

	return D;
}

//MOVEMENTS CHECK AND FILL THE BOARD
int WATER (int m_n1 [10][10], int m_n2 [10][10], int A, int B, int C, int D, int E, int TURN)	{
	int i = 0, flag = 0;
		if (((A == C) || (B == D)) && ((A - C == E) || (C - A == E) || (B - D == E) || (D - B == E)))	{	//CHECKS USER INPUT
			if ((A == C) && (B > D))	{				//CHECK DOWN
				if (TURN == 0)	{
					for (i = B; i > D; i--)	{
						if (m_n1 [i][A] == 0)	{
							flag++;
						} else {
							flag--;
						}
					}
					if (flag == E)	{						//FLAG HAS TO BE EQUAL TO E (SIZE OF SHIP) TO CHECK IF THE POSITION ISN'T TAKEN
						for (i = B; i > D; i--)	{
							m_n1 [i][A] = E;
						}
						return 1;
					} else {
						return 0;
					}
			}	else	{
					for (i = B; i > D; i--)	{
						if (m_n2 [i][A] == 0)	{
							flag++ ;
						} else {
							flag--;
						}
					}
					if (flag == E)	{
						for (i = B; i > D; i--)	{
							m_n2 [i][A] = E;
						}				
						return 1;
					} else {
						return 0;
					}							
				}
			} else if ((A == C) && (D > B))	{		//CHECK UP
				if (TURN == 0)	{
					for (i = B; i < D; i++)	{
						if (m_n1 [i][A] == 0)	{
							flag++;
						} else {
							flag--;
						}
					}
					if (flag == E)	{
						for (i = B; i < D; i++)	{
							m_n1 [i][A] = E;
						}
						return 1;
					} else {
						return 0;
					}
				}	else	{
					for (i = B; i < D; i++)	{
						if (m_n2 [i][A] == 0)	{
							flag++;
						} else {
							flag--;
						}
					}
					if (flag == E)	{
						for (i = B; i < D; i++)	{
							m_n2 [i][A] = E;
						}
						return 1;
					} else {
						return 0;
					}				
				}
			} else if ((A > C) && (B == D))	{		//CHECK LEFT
				if (TURN == 0)	{
					for (i = A; i > C; i--)	{
						if (m_n1 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i > C; i--)	{
							m_n1 [B][i] = E;
						}
						return 1;	
					}	else	{
						return 0;
					}
				}	else	{
					for (i = A; i > C; i--)	{
						if (m_n2 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i > C; i--)	{
							m_n2 [B][i] = E;
						}
						return 1;	
					}	else	{
						return 0;
					}								
				}
			} else if ((C > A) && (B == D))	{		//CHECK RIGHT
				if (TURN == 0)	{
					for (i = A; i < C; i++)	{
						if (m_n1 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i < C; i++)	{
							m_n1 [B][i] = E;
						}
						return 1;
					} else 	{
						return 0;
					}
				}	else	{
					for (i = A; i < C; i++)	{
						if (m_n2 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i < C; i++)	{
							m_n2 [B][i] = E;
						}
						return 1;
					} else 	{
						return 0;
					}				
				}
			}
		}	else	{
			return 0;
		}
}

void SHOW1 (int m_n1 [10][10], int m_n2 [10][10], int T)	{					//SHOW FILL
	int i, j;
	if (T == 0)	{
		SetColor(WHITE);
		printf ("Player %d.\nW = Water with hit || H = Hit || X = Sunk.\n\n", T+1);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if (m_n1 [i][j] == 0)	{
					SetColor(LBLUE);
					printf ("*\t");
				}	else	{
					SetColor(GREEN);
					printf ("B\t");
				}
			}
			printf ("\n");
		}
		printf ("\n\n");
	}	else {
		SetColor(WHITE);
		printf ("Player %d.\nW = Water || H = Hit || X = Sunk.\n\n", T+1);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if (m_n2 [i][j] == 0)	{
					SetColor(LBLUE);
					printf ("*\t");
				}	else	{
					SetColor(GREEN);
					printf ("B\t");
				}
			}
			printf ("\n");
		}
		printf ("\n\n");	
	}
}

void SHOW2 (int m_n1 [10][10], int m_n2 [10][10], int T)	{					//SHOW GAME
	int i, j;
	if ((T - 1) % 2 == 0)	{
		SetColor(LGREEN);
		printf ("Player 1.\t\t\t\t\t\t\t\tTurn: %d.\nW = Water || H = Hit || X = Sunk.\n\nBoard of player 2.\n\n", T);
		SetColor(WHITE);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if ((m_n2 [i][j] >= -5) && (m_n2 [i][j] < -1))	{
					SetColor (YELLOW);
					printf ("H\t");
				}	else if (m_n2 [i][j] == 1)	{
					SetColor (BLUE);
					printf ("W\t");
				}	else if (m_n2 [i][j] == -10)	{
					SetColor (RED);
					printf ("X\t");
				}	else	{
					SetColor (LBLUE);
					printf ("*\t");
				}
				
			}
			printf ("\n");
		}
		printf ("\n\n");
	}	else {
		SetColor(LGREEN);
		printf ("Player 2.\t\t\t\t\t\t\t\tTurn: %d.\nW = Water || H = Hit || X = Sunk.\n\nBoard of player 1.\n\n", T);
		SetColor(WHITE);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if ((m_n1 [i][j] >= -5) && (m_n1 [i][j] < -1))	{
					SetColor (YELLOW);
					printf ("H\t");
				}	else if (m_n1 [i][j] == 1)	{
					SetColor (BLUE);
					printf ("W\t");
				}	else if (m_n1 [i][j] == -10)	{
					SetColor (RED);
					printf ("X\t");
				}	else	{
					SetColor (LBLUE);
					printf ("*\t");
				}
			}
			printf ("\n");
		}
		printf ("\n\n");	
	}
}

void FILL_PVP (int m_n1 [10][10], int m_n2 [10][10])	{
	int i, j, fill = 0, x1, x2, y1, y2, flag = 0;
	SHIP S[4];																 //aircraft = 5, battleship = 4, cruiser = 3, submarine = 2;
	
	S[0].SIZE = 5;
	S[1].SIZE = 4;
	S[2].SIZE = 3;
	S[3].SIZE = 2;
	
	strcpy (S[0].N_SHIP, "Aircraft carrier");
	strcpy (S[1].N_SHIP, "Battleship");
	strcpy (S[2].N_SHIP, "Cruiser");
	strcpy (S[3].N_SHIP, "Submarine");	
	
	while (fill < 2)	{
		for (i = 0; i < 4; i++)	{
			do	{
				system ("cls");
				SHOW1 (m_n1, m_n2, fill);						
				SetColor(WHITE);
				printf ("%s (%d blocks)\n", S[i].N_SHIP, S[i].SIZE);
				printf ("\tInitial coordinate (L): ");
				scanf ("%d", &y1);
				y1--;
				printf ("\tInitial coordinate (C): ");
				scanf ("%d", &x1);
				x1--;
				printf ("\tEnd coordinate (L): ");
				scanf ("%d", &y2);
				y2--;
				printf ("\tEnd coordinate (C): ");
				scanf ("%d", &x2);
				x2--;
			}	while (WATER (m_n1, m_n2, x1, y1, x2, y2, S[i].SIZE, fill) == 0);
		}
		system ("cls");
		printf ("\t\tYour ships on the board are: \n\n");
		SHOW1 (m_n1, m_n2, fill);
		sleep (5);
		
		fill++;	
	}
	
}

void FILL_PVC (int m_n1 [10][10], int m_n2 [10][10])	{
	int rn, i, j, fill = 0, x1, x2, y1, y2, flag = 0;
	time_t t;
	SHIP S[4];
	
	S[0].SIZE = 5;
	S[1].SIZE = 4;
	S[2].SIZE = 3;
	S[3].SIZE = 2;
	
	strcpy (S[0].N_SHIP, "Aircraft carrier");
	strcpy (S[1].N_SHIP, "Battleship");
	strcpy (S[2].N_SHIP, "Cruiser");
	strcpy (S[3].N_SHIP, "Submarine");

	srand(time(NULL));

	while (fill < 2)	{
		for (i = 0; i < 4; i++)	{
			do	{
				if (fill == 0)	{
					system ("cls");
					SHOW1 (m_n1, m_n2, fill);						
					SetColor(WHITE);
					printf ("%s (%d blocks)\n", S[i].N_SHIP, S[i].SIZE);
					printf ("\tInitial coordinate (L): ");
					scanf ("%d", &y1);
					y1--;
					printf ("\tInitial coordinate (C): ");
					scanf ("%d", &x1);
					x1--;
					printf ("\tEnd coordinate (L): ");
					scanf ("%d", &y2);
					y2--;
					printf ("\tEnd coordinate (C): ");
					scanf ("%d", &x2);
					x2--;
				}	else if (fill == 1)	{
						do {
							rn = rand () % 10;
							if (rn < 10)	{
								y1 = rn;
							}
						} while (y1 + S[i].SIZE > 10);
						do {
							rn = rand () % 10;
							if (rn < 10)	{
								x1 = rn;
							}
						} while (x1 + S[i].SIZE > 10);
					rn = rand () % 4;
					if (rn == 0)	{
						y2 = y1 - S[i].SIZE;
						x2 = x1;
					}	else if (rn == 1)	{
						y2 = y1 + S[i].SIZE;
						x2 = x1;
					}	else if (rn == 2)	{
						x2 = x1 + S[i].SIZE;
						y2 = y1;
					}	else if (rn == 3)	{
						x2 = x1 - S[i].SIZE;
						y2 = y1;
					}
				}
			}	while (WATER (m_n1, m_n2, x1, y1, x2, y2, S[i].SIZE, fill) == 0);
		}
		system ("cls");
		if (fill == 0)	{
			printf ("\t\tYour ships on the board are: \n\n");
			SHOW1 (m_n1, m_n2, fill);			
		}
		sleep (5);
		
		fill++;	
	}
}

void GAME_PVP (int m_n1 [10][10],int m_n2 [10][10])	{
	int TURN = 0, y, x, PLAYER = 0, flag = 0, i = 0, j = 0, P1 = 0, P2 = 0;

	while (PLAYER == 0)	{
		do {
			system ("cls");
			flag = 0;
			SHOW2 (m_n1, m_n2, TURN+1);
			SetColor (WHITE);
			printf ("Time to shoot!\n");
			printf ("\tLine: ");
			scanf ("%d", &y);
			y--;
			printf ("\tColumn: ");
			scanf ("%d", &x);
			x--;
			if (TURN % 2 == 0)	{										//CHECK FOR POSITIONS WITH SHOTS
				if ((m_n2 [y][x] == 1) || (m_n2 [y][x] < -1))	{
					flag == -1;
				}
			}	else	{
				if ((m_n1 [y][x] == 1) || (m_n1 [y][x] < -1))	{
					flag == -1;
				}
			}
		} while ((y < 0) && (y > 10) && (x < 0) && (x > 10) && (flag == -1));

		if (TURN % 2 == 0)	{
			if ((m_n2 [y][x] > 1) && (m_n2 [y][x] <= 5)) 	{
				P2--;
				m_n2 [y][x] *= -1;															//MULTIPLY POS WITH -1 FOR HITS
			}	else	{
				m_n2 [y][x] = 1;															//1 FOR WATER
			}
		}	else	{
			if ((m_n1 [y][x] > 1) && (m_n1 [y][x] <= 5)) 	{
				P1--;
				m_n1 [y][x] *= -1;
			}	else	{
				m_n1 [y][x] = 1;
			}			
		}

		if (P1 == -54)	{
			PLAYER = -1;
		}	else if	(P2 == -54)	{
			PLAYER = -2;
		}
		
		if (PLAYER == 0)	{
			system ("cls");
			printf ("\t\t\tCHECK YOUR SHOT\n\n");
			SHOW2 (m_n1, m_n2, TURN+1);
			sleep (5);
			TURN ++;
		}
	}

	if (PLAYER == -1)	{
		system ("cls");
		printf ("\n\n\t\t Player 2 is the winner!\n");
		sleep (5);
	}	else if (PLAYER == -2)	{
		system ("cls");
		printf ("\n\n\t\t Player 1 is the winner!\n");
		sleep (5);
	}
}

void GAME_PVC (int m_n1 [10][10],int m_n2 [10][10])	{
	int TURN = 0, y, x, PLAYER = 0, flag = 0, i = 0, j = 0, P1 = 0, P2 = 0;

	while (PLAYER == 0)	{
		do {
			system ("cls");
			flag = 0;
			SHOW2 (m_n1, m_n2, TURN+1);
			SetColor (WHITE);
			printf ("Time to shoot!\n");
			printf ("\tLine: ");
			scanf ("%d", &y);
			y--;
			printf ("\tColumn: ");
			scanf ("%d", &x);
			x--;
			if (TURN % 2 == 0)	{										//CHECK FOR POSITIONS WITH SHOTS
				if (m_n2 [y][x] == 1)	{
					flag == -1;
				}
			}	else	{
				if (m_n1 [y][x] == 1)	{
					flag == -1;
				}
			}
		} while ((y < 0) && (y > 10) && (x < 0) && (x > 10) && (flag == -1));

		if (TURN % 2 == 0)	{
			if ((m_n2 [y][x] != 0) && (m_n2 [y][x] != 1))	{
				P2--;
				m_n1 [y][x] *= -1;															//MULTIPLY POS WITH -1 FOR HITS
			}	else	{
				m_n2 [y][x] = 1;															//1 FOR WATER
			}
		}	else	{
			if ((m_n1 [y][x] != 0) && (m_n1 [y][x] != 1))	{
				P1--;
				m_n1 [y][x] *= -1;
			}	else	{
				m_n1 [y][x] = 1;
			}			
		}

		if (P1 == -54)	{
			PLAYER = -1;
		}	else if	(P2 == -54)	{
			PLAYER = -2;
		}
		
		if (PLAYER == 0)	{
			system ("cls");
			printf ("\t\t\tCHECK YOUR SHOT\n\n");
			SHOW2 (m_n1, m_n2, TURN+1);
			sleep (5);
			TURN ++;
		}
	}

	if (PLAYER == -1)	{
		system ("cls");
		printf ("\n\n\t\t Player 2 is the winner!\n");
		sleep (5);
	}	else if (PLAYER == -2)	{
		system ("cls");
		printf ("\n\n\t\t Player 1 is the winner!\n");
		sleep (5);
	}
}
