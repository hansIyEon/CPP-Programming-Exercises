#include "MonsterWorld.h"
#include <time.h>
void main()
{
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;

	MonsterWorld game(w, h);
	Monster m("����", "��", rand() % w, rand() % h);
	Monster d("������", "��", rand() % w, rand() % h);
	Monster b("���״�", "��", rand() % w, rand() % h);
	Monster g("��Ʈ", "��", rand() % w, rand() % h);
	game.add(m);
	game.add(d);
	game.add(b);
	game.add(g);
	game.play(500, 10);
	printf("------���� ����-------------------\n");
}