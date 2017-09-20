

#ifndef HEAD_H
#define HEAD_H

#define     MAXLEVEL 15
typedef struct CARD {
	int number;
	int level;
	char *flower;
	char point;
}card;//��

typedef struct DECK {
	int top;
	int arr[55];
}deck;//�ƶ�

typedef struct PLAYERS {
	int id;
	int status;
	card handcard[21];
	int size;
}players;//���

typedef struct GAMES {
	int type;
	int level;
	int sum;
	int who;
	int count;
	int arr[16];
}games;//����

typedef struct BUFFERS {
	int arr[16];
	int brr[20];
	int sum;
}buffers;//���ƻ�����
		 /*--------------------------------*/
void game_init();
void turning();
void handcard_sort();
void print();
int win();
void turn_switch();

#endif // HEAD_H

