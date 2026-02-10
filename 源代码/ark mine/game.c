#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void game() {
	char mine[ROWS][COLS] = { 0 };		//设置地图和事件地图
	char show[ROWS][COLS] = { 0 };
	InitBoard(mine, ROWS, COLS, '0');			//最开始初始化地图和事件地图
	InitBoard(show, ROWS, COLS, '*');
	
	struct PLAYER player = setPlayer();			//设置玩家
	cleanScreen();			//清空屏幕
	plot(show, ROW, COL, player);		//进入剧情
	cleanScreen();			//清空屏幕
	//开始游戏

	for (int day = 1; day <= 5; day++) {		//不同的天数

		InitBoard(mine, ROWS, COLS, '0');			//每天初始化地图和事件地图
		InitBoard(show, ROWS, COLS, '*');


		printf("阿米娅小贴士提醒您：今天是第%d天     如果争端能够避免，那我们应当沉默——如果战斗是必要的，那就战斗到最后！\n\n", day);
		
		setmine(mine, ROW, COL);		//设置随机事件点

		findmine(mine,show, ROW, COL,&player);		//每天的行动

		printf("来到了每天结束的坎诺特商店环节\n");
		shop(&player);	//每天结束的商店事件									
		player.day++;	//记录天数来递增难度;
		cleanScreen();			//每天结束清空屏幕
	}

	if (player.nian != 0) {
		end_2();
	}
	else {
		boss(player);
	}
}


void event(struct PLAYER *player) {
	int what_event = rand()%100+1;
	if (what_event <= 20) {
		printf("\n---遭遇战---\n");
		battle(player);
	}
	else if (what_event<=30){
		printf("\n---爆金币事件：坎诺特商店---");
		shop(player);
	}
	else {
		printf("\n---奖励事件：藏在草丛中的宝物---");
		award(player);
		getchar();
		getchar();
		cleanScreen();
	}
}

void shop(struct PLAYER* player) {
	int choice=0;
	printf("\n五年投资，三年模拟，坎老师的奇妙小商店 ps:生意不好做，坎老师也收龙门币了\n\n");
	printf("你现在有  %d张龙门币\n", player->eco);
	
	printf("1.防身手册（增加自身护盾值 10点）45￥\n");
	printf("2.幸运大乐透 45￥\n");
	printf("3.请坎诺特降价 1￥\n");
	printf("4.铃兰的相册（可爱小铃兰，可以增加自身攻击力10点）350￥\n");
	printf("5.黑人牙膏（任务途中要保持口腔卫生哦，使敌方攻击力减弱20点，重复购买不叠加） 500￥\n");
	printf("6.龙泡泡玩偶  年款 （软绵绵的龙泡泡可爱捏，有着未知效果） 1145￥\n");
	
	
	printf("坎诺特：来看看有什么需要的吧>>>");
	if (scanf("%d", &choice) == 1) {				//判断输入的是数字
		if (choice <= 6 && choice >= 1) {			//判断数字合法
			switch (choice) {
			case 1:									//商品效果
				if (player->eco >= 45) {
					printf("\n购买成功\n");
					player->shield += 10;
					player->eco -= 45;
				}
				else {
					printf("\n乖孩子买东西要付钱哦（浪费了一次购买机会）\n");
				}
				break;
			case 2:
				if (player->eco >= 45) {
					int randeco = 0;
					printf("\n购买成功\n");
					randeco=rand() % 31 + 30;
					player->eco += randeco;
					printf("\n获得了%d张龙门币\n", randeco);
					player->eco -= 45;
				}
				else {
					printf("\n乖孩子买东西要付钱哦（浪费了一次购买机会）\n");
				}
				break;
			case 3:
				printf("\n坎诺特：这里不是明日方舟，我不会跟你打架，但是谢谢你的龙门币了\n");
				player->eco -= 1;
				break;
			case 4:
				if (player->eco >= 350) {
					printf("\n购买成功\n");
					player->atk += 10;
					player->eco -= 350;
				}
				else {
					printf("\n乖孩子买东西要付钱哦（浪费了一次购买机会）\n");
				}
				break;
			case 5:
				if (player->eco >= 500) {
					printf("\n购买成功\n");
					player->dec_e_atk=20;
					player->eco -= 500;
				}
				else {
					printf("\n乖孩子买东西要付钱哦（浪费了一次购买机会）\n");
				}
				break;
			case 6:
				if (player->eco >= 1145) {
					printf("\n购买成功\n");
					player->nian = 1;
					player->eco -= 1145;
				}
				else {
					printf("\n乖孩子买东西要付钱哦（浪费了一次购买机会）\n");
				}
				break;
			}

			getchar();
			getchar();
		}
		else {
			printf("坎诺特：你故意找茬是吧\n");
			printf("阿米娅：Dr.%s !!! 我们的钱被偷了！！！", player->name);
			printf("\n你损失了%d张龙门币", player->eco / 5);
			player->eco -= player->eco / 5;
			getchar();
			getchar();
		}
	}
	else {
		printf("\n这是一个没有任何用的彩蛋，你成功浪费了一次商店机会\n");
		getchar();
		getchar();
	}
}

void award(struct PLAYER* player) {
	int aw = player->eventnum % 5 + 1;
	if (aw <= 1) {
		int randlongmb = rand() % 114 + 1;
		printf("\n你找到一张幸运大乐透，看来是可以获得 1~114 张龙门币，你获得了%d张",randlongmb);
		player->eco += randlongmb;
	}
	else if (aw <= 2) {
		int longmb = 114;
		printf("\n你发现了前人爆的龙门币%d张", longmb);
		player->eco += longmb;
	}
	else if (aw <= 3) {
		printf("\n你找到一只水陈，你觉得你的攻击性和防御力增强了（攻击力加3+3 防御力加 3）");
		player->atk += 6;
		player->shield += 3;
	}
	else if (aw <= 4) {
		printf("\n你发现了在草丛中睡觉的作者，因为作者被你吵醒了所以本次没有奖励（哎嘿");
	}
	else {
		int rand_hp = rand() % 11 + 10;
		printf("\n你发现藏在草丛中的铃兰手办，可爱的模样让你心情愉悦（生命值随机增加%d）",rand_hp);
		player->hp+=rand_hp;
	}
	player->eventnum++;
}

void print_battle(struct PLAYER* player, struct ENE* enemy,int round) {
	printf("遭遇敌人：%s\n", enemy->name);
	printf("阿米娅状态》》hp:%d    伤害:%d    护盾值:%d\n", player->hp, player->atk, player->shield);
	printf("%s状态》》hp:%d    伤害:%d    护盾值:%d\n", enemy->name, enemy->hp, enemy->atk, enemy->shield);
	printf("第%d轮\n", round);
	printf("草丛树木草丛树木草丛树木草丛树木草丛树Ciallo丛树木草丛树木草丛树木草丛树木草丛树木草丛树木草\n\n");

	printf("                            阿米娅                            %s                                \n", enemy->name);
	printf("    Dr.%s\n\n", player->name);
	printf("草丛树木草丛树木草丛树木草丛树木草丛树木草丛树木草丛树木草丛树木草丛树木草丛树木草丛树木草丛\n\n");
}

void playerturn(struct PLAYER* player, struct ENE* enemy,int round) {
	int choice=0;
	printf("1.普攻  2.奇美拉（真伤无视防御力,每三回合可以释放一次）  3.防御\n");
	int right = 1;
	do {
		printf("请选择策略>>");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			enemy->hp =enemy->hp - player->atk + enemy->shield;
			printf("\n成功造成伤害%d", player->atk - enemy->shield);
			if (enemy->hp <= 0) {
				enemy->hp = 0;
			}
			right = 0;
			break;
		case 2:if (round % 3 == 0) {
			enemy->hp = enemy->hp - player->atk;
			printf("\n成功造成真伤%d", player->atk);
			if (enemy->hp < 0) {
				enemy->hp = 0;
			}
			right = 0;
		}
			  else {
			printf("\n未满三回合\n");
		}
			break;
		case 3:
			printf("你进行了一次防御\n");
			enemy->is_player_defend = 1;
			right = 0;
			break;
		}
	} while (right);
	
}
void enemyturn(struct PLAYER* player, struct ENE* enemy, int round) {
	int choice = 0;
	choice = rand() % 4 + 1;		//简单敌方随机战斗
	if (choice <= 3) {
		int realatk = 0;
		if (player->shield >= enemy->atk) {
			realatk = 0;
		}
		else {
			realatk = enemy->atk - player->shield;
		}
		printf("\n敌方对你造成了%d点伤害\n",realatk);
		player->hp -= realatk;
		if (player->hp <= 0) {
			player->hp = 0;
		}
	}
	else {
		printf("\n敌人恢复了5滴血量\n");
		enemy->hp += 5;
	}
}

void battle(struct PLAYER* player) {
	struct ENE enemy = setEnemy(player);
	int round=1;
	print_battle(player, &enemy,round);
	while (1) {
		playerturn(player,&enemy,round);
		if (enemy.hp <= 0) {
			printf("恭喜你打败了%s", enemy.name);
			printf("\n获得龙门币114张,回血50点(回车键继续)\n");
			player->eco += 114;
			player->hp += 50;
			getchar();
			getchar();
			cleanScreen();
			break;
		}
		getchar();
		getchar();
		cleanScreen();
		print_battle(player, &enemy, round);

		if (enemy.is_player_defend == 1) {
			printf("\n你成功防御了一次敌方攻击\n");
			enemy.is_player_defend = 0;
		}
		else {
			enemyturn(player, &enemy, round);
		}

		if (player->hp <= 0) {
			printf("\n在危机时刻你替阿米娅抵挡了一次攻击，阿米娅带着晕厥的你撤退了\n");
			printf("\n你们去求助坎诺特，阿米娅基础血量恢复至20点，你损失了100张龙门币(回车键继续)\n");
			player->hp += 20;
			player->eco -= 100;
			getchar();
			getchar();
			cleanScreen();
			break;
		}
		printf("\n(回车键继续)\n");
		getchar();
		getchar();

		round++;
		cleanScreen();
		print_battle(player, &enemy, round);
	}

	printf("\n作战结束\n");
	getchar();
	getchar();
	

}

void boss(struct PLAYER player) {
	int boss_hp = player.atk + player.eco + player.hp + 1;
	printf("\n终于，在经历了五天的作战后，你们找到了敌人的总部\n");
	getchar();
	printf("你们看到了那令人畏惧不已的..........\n");
	getchar();
	printf("你突然被一团黑雾包裹起来，你意识到你们被袭击了....\n");
	printf("???；%s，你终于来了\n", player.name);
	printf("ps:接下来你可以随便使用你看到的任何数据攻击？？？\n");
	int temp = 0;
	while (player.atk > 0) {
		printf("\n敌方剩余%d血量\n", boss_hp);
		printf("剩余%d攻击力，请选择你要输出的攻击值大小(如果你输入的数值大于已有数据，实际输出会按已有最大值计算)>>>",player.atk);
		scanf("%d",&temp);
		getchar();
		if (temp > player.atk || temp < 0) {
			temp = player.atk;
		}
		player.atk -= temp;
		boss_hp -= temp;
	}
	while (player.eco > 0) {
		printf("\n敌方剩余%d血量\n", boss_hp);
		printf("剩余%d张龙门币，请选择你要输出的龙门币大小(如果你输入的数值大于已有数据，实际输出会按已有最大值计算)>>>", player.eco);
		scanf("%d", &temp);
		getchar();
		if (temp > player.eco || temp < 0) {
			temp = player.eco;
		}
		player.eco -= temp;
		boss_hp -= temp;
	}
	
	printf("\n敌方剩余%d血量\n", boss_hp);
	printf("剩余%d点血量，请选择你要输出的血量(如果你输入的数值大于已有数据，实际输出会按已有最大值计算)>>>", player.hp);
	scanf("%d", &temp);
	getchar();
	if (temp <=0) {
		end_1();
	}
	else {
		bad_end();

		printf("\n这是一个神秘的力量：如果你可以重新选的话，你会输入什么>>>");
		scanf("%d", &temp);
		if (temp <= 0) {
			end_1();
		}
		else {
			printf("....不知悔改....");
			getchar();
		}
	}
}

void end_2() {
	printf("\n终于，在经历了五天的作战后，你们找到了敌人的临时总部\n");
	getchar();
	printf("你们看到了那令人畏惧不已的..........\n");
	getchar();
	printf("超级战斗机甲--大丑\nblingbling....你兜里的龙泡泡开始发光，变成了巨大的怪兽\n");
	getchar();
	printf("?\n");
	getchar();
	printf("???\n");
	getchar();
	printf("摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚\n\n");
	printf("摄影器械                     幕布                 摄影器械                  道具\n\n");
	printf("       阿米娅    你                 森蚺 大丑                        摄影机 年");
	printf("\n垃圾桶                     灯光                 灯光                  道具");
	printf("\n\n摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚摄影棚\n");
	getchar();
	printf("\n你：我们不是要跟整合运动战斗吗\n"); 
	getchar();
	printf("年：我感觉在片尾变成机甲大战超级巨兽会很不错哎\n");
	getchar();
	printf("你：这不算欺骗消费者吗，明明电影名叫整合运动1 秘密行动\n");
	getchar();
	printf("年：那就改成整合超级机甲大战龙泡泡巨兽1吧\n");
	getchar();
	printf("你：问题太多了，还有你森蚺怎么真把大丑开过来了\n");
	getchar();
	printf("森蚺：正好大丑有些新功能想试一试咯\n");
	getchar();
	printf("你：你的意思是你真的要对我们开火吗......\n");
	getchar();

	printf("（在吵吵闹闹中你们协商完成了最后的拍摄）\n");
	getchar();
	printf("阿米娅：有时候放松放松也挺好的呢\n");
	getchar();
	printf("你：是啊....但是我感觉有比答应年拍电影更好的休闲方式，走吧天也晚了，吃点什么吧\n");
	getchar();
	printf("阿米娅：嗯！\n");
	getchar();
	printf("（你看着阿米娅，内心涌现出一种愧疚的感情，你甩了甩头，消去了这莫名奇妙的情绪，带着阿米娅离开了影棚）\n");
	getchar();
	cleanScreen();
	printf("end 2 只是一场莫名其妙的电影罢了\n");
	getchar();
	cleanScreen();
}
void end_1() {
	printf("\n???：.....也许我们并不是第一次相遇....博士\n"); 
	getchar();
	printf("(黑雾散开了)");
	getchar();
	printf("阿米娅：博士，你没事吧！！！");
	getchar();
	printf("你：........");
	getchar();
	printf("阿米娅：博士?");
	getchar();
	printf("(你抬眼望去，你和阿米娅坐在公园的草坪上，远处能天使和德克萨斯正拿着各种食物走过来)");
	getchar();
	printf("你：这是哪...");
	printf("阿米娅：博士?今天我们不是来野营吗，从刚才你就一直在发呆....");
	getchar();
	printf("(你抱紧了阿米娅)");
	printf("阿米娅：博士!!!!!!????????");
	getchar();
	getchar();

	cleanScreen();
	printf("end 1 珍惜身边的人，无论虚拟与否");
	getchar();
	cleanScreen();

	
	
}
void bad_end() {
	cleanScreen();
	printf("\n(倒地声)\n");
	printf("??? : ...........\n");
	printf("(黑雾散开了一小片)\n");
	getchar();
	printf("(你看着倒地的阿米娅)\n");
	getchar();
	printf("??? : 原来你这么想赢吗.......即使消耗他人的生命\n");
	getchar();
	printf("(黑雾彻底散开了，映入你眼帘的是被毁灭的敌方营地)\n");
	printf("你站在废墟中间，站在阿米娅的身边.......");
	getchar();
	cleanScreen();
	printf("BAD END\n");
	getchar();
	cleanScreen();
}