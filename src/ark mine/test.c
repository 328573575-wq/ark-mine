#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void cleanScreen() {
#ifdef _WIN32
	system("cls");
#endif // _WIN32
}
void menu() {
	printf("************************************************\n");
	printf("**************阿米娅的奇妙冒险******************\n");
	printf("************************************************\n");
	printf("**************1.START  0.EXIT*******************\n");
	printf("************************************************\n");
}

void DispalyBoard(char board[ROWS][COLS],int row,int col) {
	for (int k = 0; k <= col; k++) {
		printf("%d ", k);
	}
	printf("\n");
	for (int i = 1; i <= row; i++) {
		printf("%d ", i);
		for (int j = 1; j <= col; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
void InitBoard(char board[ROWS][COLS], int rows, int cols,char set) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = set;
		}
	}
}

void plot(char show[ROWS][COLS],int row,int col,struct PLAYER player) {
	printf("整合运动的一支小队进入了一片秘密区域，你和阿米娅将秘密潜入歼灭敌方（回车继续）\n");
	getchar();
	DispalyBoard(show,row,col);											
	printf("阿米娅：Dr.%s，这个区域我们曾经没有探索过，我们可以使用无人机来探测整个地区的轮廓\n",player.name);
	getchar();
	printf("阿米娅：我们一共有五天的时间可以行动，每天可以探索十个区域,可能是事件区域也有可能是空白区域,不同区域每天会更新位置\n");
	printf("阿米娅：每次探索一个区域，如果是空白区域的话无人机会告诉我们周围八个区域有几个事件区域\n");
	getchar();
	printf("阿米娅：事件中我们可能会碰到商店或者敌方干员，如果我们进入战斗事件，那时就拜托Dr.%s您指挥我作战了！！！\n",player.name);
	getchar();
}

struct PLAYER setPlayer() {
	struct PLAYER player;
	player.hp = 50;
	player.atk = 15;
	player.shield = 0;
	player.eco = 500;
	player.nian = 0;
	player.dec_e_atk = 0;
	player.eventnum = 0;
	player.enemynum = 0;
	player.day = 1;
	printf("请输入角色昵称>>>");
	scanf("%s", player.name);
	printf("阿米娅的初始数值为\n血量:%d\n攻击:%d\n护盾:%d\n龙门币:%d\n", player.hp, player.atk, player.shield, player.eco);
	printf("回车继续冒险");
	getchar();
	getchar();
	return player;
}
struct ENE setEnemy(struct PLAYER* player){
	struct ENE enemy = {0};
	enemy.is_player_defend = 0;
	int randenemy = player->enemynum % 3 + 1;
	switch (randenemy) {
	case 1 :
		strcpy(enemy.name, "整合运动神奇小兵");
		enemy.hp = 30;
		if (player->dec_e_atk != 0) {
			printf("\n因为黑人牙膏的作用，敌方攻击力减少%d\n", player->dec_e_atk);
		}
		enemy.atk = 10 * player->day - player->dec_e_atk;
		if (enemy.atk < 0) {
			enemy.atk = 1;
		}
		enemy.shield = 10;
		break;

	case 2:
		strcpy(enemy.name, "整合运动术士");
		enemy.hp = 20;
		if (player->dec_e_atk != 0) {
			printf("\n因为黑人牙膏的作用，敌方攻击力减少%d\n", player->dec_e_atk);
		}
		enemy.atk = 30  - player->dec_e_atk;
		if (enemy.atk < 0) {
			enemy.atk = 1;
		}
		enemy.shield = 5;
		break;

	case 3:
		strcpy(enemy.name, "整合运动重装");
		enemy.hp = 50;
		if (player->dec_e_atk != 0) {
			printf("\n因为黑人牙膏的作用，敌方攻击力减少%d\n", player->dec_e_atk);
		}
		enemy.atk = 5 * player->day - player->dec_e_atk;
		if (enemy.atk < 0) {
			enemy.atk = 1;
		}
		enemy.shield = 10;
		break;
	}

	player->enemynum++;
	return enemy;

}

int  countmine(char board[ROWS][COLS], int r, int c) {
	int count = 0;
	for (int i = r - 1; i <= r + 1; i++) {
		for (int j = c - 1; j <= c + 1; j++) {
			count =count+ board[i][j] - '0';
		}
	}

	return count;
}
void setmine(char board[ROWS][COLS], int row, int col) {
	int r = 0;
	int c = 0;
	int enemy = ENEMY;
	while (enemy > 0) {
		r = rand() % row + 1;
		c = rand() % col + 1;
		if (board[r][c] == '0') {
			board[r][c] = '1';
			enemy--;
		}
	}
	
}
void findmine(char board[ROWS][COLS], char showboard[ROWS][COLS], int row, int col,struct PLAYER *player) {
	int r;
	int c;
	for (int move = 10; move > 0;move--) {		//每天移动次数

		DispalyBoard(showboard, ROW, COL);
		printf("\n");

		printf("你还剩余 %d 个无人机\n", move);
		printf("阿米娅：博士，无人机系统要求按行，列顺序输入,中间带空格且不要有字母，不然无人机系统可能会出故障的！！\n");
		printf("请输入无人机侦察的坐标>>>");
		if (scanf("%d%d", &r, &c) != 2) {			//
			printf("\n阿米娅：Dr.%s,我不是跟您说过了这么输入会出现故障吗..... 无人机坠毁了", player->name);
			while (getchar() != '\n');				//清空缓冲区
			getchar();
			cleanScreen();
			continue;								//下一回合
		}
		if (r >= 1 && r <= row && c >= 1 && c <= col) {			//判断坐标合不合法
			if (board[r][c] == '1') {							//判断有没有事件
				if (showboard[r][c] != '@') {					//判断之前来没来过
					cleanScreen();

					event(player);								//触发事件，并将事件格改变字符
					showboard[r][c] = '@';
					cleanScreen();
				}
				else {
					printf("阿米娅：Dr.%s，这里已经什么都不剩了（悲），你浪费了一个无人机",player->name);
					getchar();
					getchar();
					cleanScreen();
				}
			}
			else {
				if (showboard[r][c] != '*') {				//判断之前来没来过
					printf("阿米娅：Dr.%s，原地踏步是没有意义的，你浪费了一个无人机",player->name);
					getchar();
					getchar();
					cleanScreen();
				}
				else {
					int num = 0;						//计算周围八个格有几个事件
					num = countmine(board, r, c);
					showboard[r][c] = num + '0';
					cleanScreen();
				}
			}
		}
		else {
			printf("英雄可不能临阵脱逃，你浪费掉了一个无人机");
			getchar();
			getchar();
			cleanScreen();
		}
	}
}

	

int main() {
	srand(time(0));			//变化种子数
	int input=0;
	do {
		menu();
		printf("请选择>>>");
		scanf("%d", &input);
		
		switch (input) {
		case START :
			cleanScreen();        
			game();
			break;

		case EXIT :
			cleanScreen();
			printf("冒险结束了\n");
			break;

		case 1145 :
			printf("这是一个水印，made by linzik\n");
			break;

		default :
			cleanScreen();
			printf("阿米娅提示您：要开始冒险请输入正确数字哦\n");
			break;
		}

	} while (input);

	return 0;
}