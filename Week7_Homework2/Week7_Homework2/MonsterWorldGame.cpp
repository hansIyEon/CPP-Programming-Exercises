#include "MonsterWorld.h"
#include <time.h>
void main()
{
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;

	MonsterWorld game(w, h);
	Monster m("몬스터", "※", rand() % w, rand() % h);
	Monster d("도깨비", "◎", rand() % w, rand() % h);
	Monster b("별그대", "★", rand() % w, rand() % h);
	Monster g("고스트", "♥", rand() % w, rand() % h);
	game.add(m);
	game.add(d);
	game.add(b);
	game.add(g);
	game.play(500, 10);
	printf("------게임 종료-------------------\n");
}