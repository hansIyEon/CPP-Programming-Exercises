#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <time.h>

void main()
{
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;
	MonsterWorld game(w, h);

	game.add(new Zombie("좀비", "◎", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어", "★", rand() % w, rand() % h));
	game.add(new KGhost("고스트", "♥", rand() % w, rand() % h));
	game.add(new Jiangshi("나는 한시연", "↔", rand() % w, rand() % h, true));
	game.add(new Jiangshi("취업하고싶다", "↕", rand() % w, rand() % h, false));
	game.play(500, 10);
	printf("------게임 종료-------------------\n");
}