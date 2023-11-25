#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#define N_BOARD		15 


#define N_COINPOS		12
#define MAX_COIN		4


#define MAX_SHARKSTEP	6
#define SHARK_INITPOS	-4

static int board_status[N_BOARD]; // 보드의 상태를 배열로 정의한다. 
static int board_coin[N_BOARD]; // coin을 배열로 정의한다.
static int board_sharkPosition; // 상어의 위치 정의 

int board_initboard(void) {
	
	int i;
	
	for (i=0;i<N_BOARD;i++){
		// 보드랑 코인 초기화 
		board_status[i] = BOARDSTATUS_OK;
		board_coin[i] = 0;
	} 
	
	board_sharkPosition = SHARK_INITPOS;
	
	
	
	for (i=0;i<N_COINPOS;i++) {
		// 특정 칸에만 coin을 놓고자 할 때, 그 특정 칸의 개수를 N_COINPOS라고 한다. 
		// coin을  할당하는 코드
		int flag = 0;
		while(flag == 0){
			int allocPos = rand()%N_BOARD;
			if (board_coin[allocPos] == 0) {
				board_coin[allocPos] = rand()%MAX_COIN + 1;  
				flag = 1; //flag=1 이 되면 while문을 빠져나갈 수 있다. 
			}
		}	
		
	}
	
	return 0;
		
}
int board_printBoardStatus(void) {
	// 보드의 상태를 출력하기 위한 코드 
	int i;
	printf("-------------------------BOARD STATUS-------------------------\n");
	printf("\n");
	for (i=0;i<N_BOARD;i++){
		printf("|");
		if (board_status[i] == BOARDSTATUS_NOK)
			printf("X");
		else
			printf("O");
		
	}printf("|\n");
	printf("--------------------------------------------------------------\n");	
	return 0;	
}


int board_getBoardStatus(int pos){
	return board_status[pos];	
} // pos라는 위치의 보드 상태를 반환하는 함수 

int board_getBoardCoin(int pos){
	int coin = board_coin[pos];  // coin 변수에 pos에서의 동전값  저장해둠 
	board_coin[pos]=0; 			 // 동전의 상태를 초기화하는 코드 
	return coin;                 // coin 변수 반환 
}


// int board_getSharkPosition(void);
	
int board_stepShark(void) {
	int step = rand()%MAX_SHARKSTEP + 1;
	int i;
	for (i= board_sharkPosition + 1;i<=board_sharkPosition+step;i++) {
		if (i >= 0 && i < N_BOARD) 
			board_status[i] = BOARDSTATUS_NOK;
	}
	
	board_sharkPosition += step;
	return board_sharkPosition;
	
}




