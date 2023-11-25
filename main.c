#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DIE		6
#define N_PLAYER	3
#define MAX_CHARNAME		200 // 200자 이내 문자열 

// player의 상태를 나타내는 매크로 
#define PLAYERSTATUS_LIVE	0
#define PLAYERSTATUS_DIE	1
#define PLAYERSTATUS_END	2	

int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME]; // 이름은 2차원배열로 선언 
int player_coin[N_PLAYER];
int player_status[N_PLAYER]; // player의 상태를 저장하는 변수 
char player_statusString[3][MAX_CHARNAME] = {"LIVE","DIE","END"}; 
// 사용자가 player의 상태를 알 수 있게 하기 위한 변수


 

 



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void opening(void){
	printf("============================================================================\n");
	printf("****************************************************************************\n");
	printf("				SHARK GAME										\n");
	printf("****************************************************************************\n");
	printf("============================================================================\n");	
}

int rolldie(void) {
	return rand()%MAX_DIE +1;
}

void printPlayerPosition(int player){
	int i;
	for(i=0;i<N_BOARD;i++) {
		printf("|");
		if (i == player_position[player]){
			printf("%c",player_name[player][0]); // player 이름의 첫글자 출력 
		}
		else {
			if(board_getBoardStatus(i) == BOARDSTATUS_NOK) 
				printf("X");
			else printf(" ");
		}
	}
	printf("|\n");
}

void printPlayerStatus(void) {
	int i;
	printf("player status ---\n");
	for(i=0;i<N_PLAYER;i++) {
		printf("%s : pos %i, coin %i ,status : %s\n",player_name[i],player_position[i],
		player_coin[i],player_statusString[player_status[i]]);
	}
	printf("---------------\n");
}

void checkDie(void){
	int i;
	for (i=0;i<N_PLAYER;i++){
		if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK) {
			player_status[i] = PLAYERSTATUS_DIE;
			printf("%s player는 죽었음\n",player_name[i]);
		}
	}
}

int game_end(void) {
	int i;
	int flag_end = 1;
	
	// if all the players are died?
	for (i=0;i<N_PLAYER;i++){
		if (player_status[i] == PLAYERSTATUS_LIVE){
			flag_end = 0;
			break;	
		} 
	}
	return flag_end;
}


int getAlivePlayer(void) {
	int i;
	int cnt = 0;
	for (i=0;i<N_PLAYER;i++) {
		if (player_status[i] == PLAYERSTATUS_END)
			cnt++;
	}
	return cnt;
}

int getWinner(void) {
	int i;
	int winner = 0;
	int max_coin = -1;
	
	
	for (i=0;i<N_PLAYER;i++){
		if (player_status[i] == PLAYERSTATUS_END) {
		
			if (player_coin[i] > max_coin)	{
				max_coin = player_coin[i];
				winner = i;
				}
		}
	}
	
	return winner;
}




int main(int argc, char *argv[]) {
	int pos = 0;
	int i;
	int turn = 0;
	
	srand((unsigned)time(NULL));
	
	// 0. opening
	opening();
	
	//1. 초기화& 플레이어 이름 설정
	board_initboard();
	
	
	//1-2. 플레이어 초기화
	for (i=0;i<N_PLAYER;i++){
		player_position[i] = 0;
		player_coin[i] = 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		// player name
		printf("PLAYER %i 's name : ",i);
		scanf("%s",player_name[i]);
	} 
	
	//2. 반복문(플레이어 turn) 
	do {
		int step;
		int coinResult;
		char c;
		
		if (player_status[turn] != PLAYERSTATUS_LIVE) 
		// 밑의 코드를 hit하지 않는 조건 
		{
			turn = (turn +1) %N_PLAYER;
			continue; // 다시 위로 뒤돌아감 
		}		
		
		
		
		//2-1. 플레이어 상태 출력
		board_printBoardStatus();
		for (i=0;i<N_PLAYER;i++)
			printPlayerPosition(i);
		printPlayerStatus();
		
		
		//2-2. 주사위 던지기
		printf("%s turn!!",player_name[turn]);
		printf("press any key to roll a dice\n");
		scanf("%d",&c);
		fflush(stdin);
		step = rolldie();
		
		//2-3. 이동
		player_position[turn] += step;
		if (player_position[turn] >= N_BOARD){
			player_position[turn] = N_BOARD - 1;
		}
		if (player_position[turn] == N_BOARD-1)
			player_status[turn] = PLAYERSTATUS_END;
			
		printf("%s가 Dice result : %d\n",player_name[turn],step);
		printf("%s의 현재위치 : %d\n",player_name[turn],player_position[turn]);
		
		//2-4. 동전 줍기
		coinResult = board_getBoardCoin(pos); 
		player_coin[turn] += coinResult;
		printf("%s가 %i 개의 동전을 주웠음, total coin : %i\n",player_name[turn],
				coinResult,player_coin[turn]);
		printf("\n");		
		//2-5. 다음 turn
		turn = (turn + 1)% N_PLAYER; // wrap around
		
		//2-6. if (모든 플레이어가 한번씩 턴을 돔) 
		              // 상어동작 
		              
		if (turn == 0) {
			// 상어 동작//
			int shark_pos = board_stepShark();
			printf("상어의 현재위치 : %d\n",shark_pos);
			checkDie();
		}
	}while(game_end() == 0);
	
	// 마지막 결과 확인용 코드 
	board_printBoardStatus();
		for (i=0;i<N_PLAYER;i++)
			printPlayerPosition(i);
		printPlayerStatus();
		
		              
	//3. 정리(승자 계산, 출력 등) 
	printf("%d players are alive!\n",getAlivePlayer());

	for (i=0;i<N_PLAYER;i++){
		if (player_status[i] == PLAYERSTATUS_END) {
			printf("Winner is %s\n",player_name[getWinner()]);
		}
	}
	printf("\n");
	printf("GAME END\n");

	 
	
	system("PAUSE");
	return 0;
}
