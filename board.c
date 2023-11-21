#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#define N_BOARD		15 


#define N_COINPOS		12
#define MAX_COIN		4

static int board_status[N_BOARD]; // ������ ���¸� �迭�� �����Ѵ�. 
static int board_coin[N_BOARD]; // coin�� �迭�� �����Ѵ�.
static int board_sharkPosition; // ����� ��ġ ���� 

int board_initboard(void) {
	
	int i;
	
	for (i=0;i<N_BOARD;i++){
		// ����� ���� �ʱ�ȭ 
		board_status[i] = BOARDSTATUS_OK;
		board_coin[i] = 0;
	} 
	
	for (i=0;i<N_COINPOS;i++) {
		// coin��  �Ҵ��ϴ� �ڵ�
		int flag = 0;
		while(flag == 0){
			int allocPos = rand()%N_BOARD;
			if (board_coin[allocPos] == 0) {
				board_coin[allocPos] = 1 + rand()%MAX_COIN; // coin�� 1~4 ������ ������ �Ҵ�� 
				flag = 1; // while���� �������� �� �ִ�. 
			}
		}	
		
	}
	
	return 0;
		
}
int board_printBoardStatus(void) {
	// ������ ���¸� ����ϱ� ���� �ڵ� 
	int i;
	printf("-------------------------------BOARD STATUS---------------------------------");
	printf("\n");
	for (i=0;i<N_BOARD;i++){
		printf("|");
		if (board_status[i] == BOARDSTATUS_NOK)
			printf("X");
		else
			printf("O");
		
	}printf("\n");
	printf("----------------------------------------------------------------------------");	
	return 0;	
}


int board_getBoardStatus(int pos){
	return board_status[pos];	
} // pos��� ��ġ�� ���� ���¸� ��ȯ�ϴ� �Լ� 

int board_getBoardCoin(int pos){
	int coin = board_coin[pos];  // coin ������ pos������ ������  �����ص� 
	board_coin[pos]=0; 			 // ������ ���¸� �ʱ�ȭ�ϴ� �ڵ� 
	return coin;                 // coin ���� ��ȯ 
}

#if 0
int board_getSharkPostition(void);
int board_stepShark(void);
#endif

