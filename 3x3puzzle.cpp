#include "Ranking.h"
#include <Windows.h>   //Sleep() �Լ��� ���� ����
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define DIM 3


int flag;
double tElap = 0;
double d;
void savegame(char* filename);
enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };  //���� Ű�� ���� �ƽ�Ű�ڵ�
static int DirKey[4] = { Left,Right,Up,Down };    // 0~3�� ����Ű�� ���� �ƽ�Ű�ڵ�� �ٲٱ� ���� ���̺�
static int map[DIM][DIM];  //�����
static int x, y;           //��ĭ�� ��ġ(��:y, ��:x)
static int nMove;          //�̵��� Ƚ��
static clock_t tStart;     //���� �ð�

static void init()  //�ʱ����Լ�, ��� ���� ������ ���ڸ��� ����. ������ �ڸ��� ��ĭ�� ��(y,x=3)
{					//���� �߻��� ���� �ð�, �̵� Ƚ���� �ʱ�ȭ ��.
	for (int i = 0; i < DIM * DIM - 1; i++)
	{
		map[i / DIM][i % DIM] = i + 1;
	}
	map[DIM - 1][DIM - 1] = 0;
	x = DIM - 1; y = DIM - 1;

	srand(time(NULL));  //���� �߻� ���� ����
	tStart = clock();   //���� �ð� ����
	nMove = 0;          // �̵� Ƚ�� �ʱ�ȭ

}

static void display() //������ ȭ�鿡 ���� ���� ����ϴ� �Լ�. �̵� Ƚ���� �ҿ�ð��� ����Ͽ�
{					  //�Բ� ����� ��. map[r][c]�� 0�̸� �����̰� �ƴϸ� �ش� ���� ��ȣ�� �����

	system("cls");   //���� ����� ���� ��� ������!!
	printf("\n ������ ����,�����Ϸ��� 0�� ��������\n");
	printf("\t3x3 Puzzle\n\t");
	printf("-------------------\n\t");
	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			if (map[r][c] > 0)
				printf("%3d", map[r][c]);
			else
				printf(" ");
		}
		printf("\n\t");
	}
	printf("-------------------\n\t");
	clock_t t1 = clock();

	if (flag == 0)
	{
		d = double(t1 - tStart) / CLOCKS_PER_SEC;
		printf("\n\t �̵�Ƚ��:%6d\n\t�ҿ�ð�:%6.1lf\n\n", nMove, d);
	}
	if (flag == 1)
	{

		d = (double(t1 - tStart) / CLOCKS_PER_SEC) + tElap;
		printf("\n\t �̵�Ƚ��:%6d\n\t�ҿ�ð�:%6.1lf\n\n", nMove, d);
	}

}
/*
   ȭ��ǥ Ű�� �ƽ�Ű �ڵ带 dir�� ���޹޾� �ش� �������� ���� ������ �����̴� �Լ�. ���� ������
   �����̸� ���� ��ġ�� �ݴ�� �������� �ϸ�, ���� ��ġ�� ��Ÿ���� ���� x �Ǵ� y�� ���ŵǾ�� ��.
   ��� ������ �˻��ؾ� �ϴµ�, ���� ��� ������ ȭ��ǥ�� �������µ� ������ �� ���� ��(x==0)�̸�
   ���������� ������ ������ �����Ƿ� �̵��� �� ����. ��� ���⿡ ���� �� ������ �˻��ؼ� ó���ؾ� ��.
*/

static bool move(int dir)
{
	if (dir == Right && x > 0)  //�� : �� ���� ������ �˻�
	{
		map[y][x] = map[y][x - 1];  // ���� ���������� �̵�
		map[y][--x] = 0;            //���� �������� �̵�
	}
	else if (dir == Left && x < DIM - 1)  // �� : �� ������ ������ �˻�
	{
		map[y][x] = map[y][x + 1];   // ���� �������� �̵�
		map[y][++x] = 0;             // ���� ���������� �̵�
	}
	else if (dir == Up && y < DIM - 1)   // �� : �� �Ʒ��� ������ �˻�
	{
		map[y][x] = map[y + 1][x];   //���� ���� �̵�
		map[++y][x] = 0;             //���� �Ʒ��� �̵�
	}
	else if (dir = Down && y > 0)    //��: �� ���� ������ �˻�
	{
		map[y][x] = map[y - 1][x];   //���� �Ʒ��� �̵�
		map[--y][x] = 0;             //���� ���� �̵�
	}
	else return false;

	nMove++;
	return true;
}
static void shuffle(int nShuffle)   // ���� ������ ���� Ƚ���� �Է¹޾� �������� ��ĭ�� ������ ������
{									//���� �Լ�. ������ �߻��Ͽ� �̵� ������ �����ϰ� �̵��� �õ���.
	for (int i = 0; i < nShuffle; i++)
	{
		int key = DirKey[rand() % 4];
		if (move(key) == false)  //���� �̵��� �� ���� �����̸� move()���� false�� ��ȯ�ϹǷ�
		{						 //�ٽ� ������ ��(i�� ����)
			i--;
			continue;
		}
		display();
		Sleep(50);    //���̴� ������ �� �� �ֵ��� 50msec�� ��ٸ�. �� õõ�� �����̷���
					  // �� ū ������ Sleep()�ϸ� ��. ������ msec��.
	}
}
static bool isDone()  //������ �� ���߾��������� �˻��ϴ� �Լ�. ��� ������ ���ڸ��� �ְ� ��������
{					  //������ ������ ���� �Ϸ�.
	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			if (map[r][c] != r * DIM + c + 1)
				return (r == DIM - 1) && (c == DIM - 1);
		}
	}
	return true;
}
static int getDirKey()  //����Ű�� �޾Ƶ��̴� �Լ�. Ű�� ������ �ٷ� ������.
{
	//int key = getche();
	return getche() == 224 ? getche() : 0;
}

static int getSaveKey()
{
	//int key = getch();
	if (getch() == 48)
	{
		printf("\n������ ����� �� �����մϴ�...");
		savegame((char*)"savegame.txt");
		exit(0);
	}
	else if (getch() == 224)
	{
		int key = getDirKey();
		return key;
	}
}



int playFifteenPuzzle()
{
	init();
	display();
	printRanking();
	printf("\n������ �����ּ���(����)...");
	getche();
	shuffle(100);   //���� ������ 100�� �̵��� ����
	printf("\n ������ ���۵˴ϴ�...");
	getche();

	nMove = 0;              //�̵�Ƚ�� �ʱ�ȭ
	tStart = clock();		//���� �ð��� �缳��
	while (!isDone)			//���� ���� �˻�
	{
		move(getDirKey());   //Ű�� �޾� �������� �̵�
		display();			 //���� ���¸� ȭ�鿡 ���
	}
	clock_t t1 = clock();
	double d = double(t1 - tStart) / CLOCKS_PER_SEC;
	return addRanking(nMove, d);  //��ŷ ����
}

//replay
static int mapTmp[DIM][DIM];
static int history[1000];
static int nHist = 0, _x, _y;

void backupInitMap(bool backup = true)
{
	if (backup)
	{
		for (int r = 0; r < DIM; r++)
		{
			for (int c = 0; c < DIM; c++)
			{
				mapTmp[r][c] = map[r][c];
			}
		}
		_x = x;
		_y = y;
	}
	else
	{
		for (int r = 0; r < DIM; r++)
		{
			for (int c = 0; c < DIM; c++)
			{
				map[r][c] = mapTmp[r][c];
			}
		}
		x = _x;
		y = _y;
	}
}



//game save
static int mapPresent[DIM][DIM];

void savegame(char* filename)
{
	FILE* wp = fopen(filename, "w");

	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			mapPresent[r][c] = map[r][c];
			fprintf(wp, "%3d\n", mapPresent[r][c]);
		}
	}

	//clock_t end = clock();
	//double tElapsed = double(end - tStart)/CLOCKS_PER_SEC;
	fprintf(wp, "%d\n", nMove);
	fprintf(wp, "%lf\n", d);
	fprintf(wp, "%d\n", x);
	fprintf(wp, "%d\n", y);
	fprintf(wp, "%d\n", nHist);
	for (int c = 0; c < nHist; c++)
	{

		fprintf(wp, "%3d\n", history[c]);
	}
	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			//mapPresent[r][c] = map[r][c];
			fprintf(wp, "%3d\n", mapTmp[r][c]);
		}
	}
	fprintf(wp, "%d\n", _x);
	fprintf(wp, "%d\n", _y);
	//fprintf(wp, "%6.1lf\n", tStart);

	fclose(wp);
}

//game restart
void Restartsavegame(char* filename)
{
	FILE* rp = fopen(filename, "r");

	//int pmove;
	if (rp == NULL)
	{
		printf("����� ������ �����ϴ�!!");
		exit(0);
	}

	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{

			fscanf(rp, "%3d", &(map[r][c]));
		}
	}

	fscanf(rp, "%d", &nMove);
	fscanf(rp, "%lf", &tElap);
	fscanf(rp, "%d", &x);
	fscanf(rp, "%d", &y);
	fscanf(rp, "%d", &nHist);
	for (int c = 0; c < nHist; c++)
	{
		fscanf(rp, "%3d", &(history[c]));
	}
	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			//mapPresent[r][c] = map[r][c];
			fscanf(rp, "%3d\n", &(mapTmp[r][c]));
		}
	}
	fscanf(rp, "%d", &_x);
	fscanf(rp, "%d", &_y);
	//printf("%lf", tElap);		//tStart = tElap ;
	//tStart = clock();

	fclose(rp);
}



int play3x3Puzzle()
{

	printf("\n ���� ������ �̾ �ϰڽ��ϱ�?(yes==>1, no==>0) :");
	scanf_s("%d", &flag);
	if (flag == 0)
	{
		init();
		display();
		printf("\n ������ �����ּ���(����)...");
		getche();
		shuffle(20);

		backupInitMap();

		printf("\n ������ ���۵˴ϴ�...");
		getche();

		nMove = 0;
		nHist = 0;
		tStart = clock();
	}
	else if (flag == 1)
	{
		Restartsavegame((char*)"savegame.txt");

		tStart = clock();
		display();
	}


	while (!isDone())
	{
		history[nHist] = getSaveKey();  //������ ����
		move(history[nHist]);
		display();
		nHist++;

	}

	double end_time = d;

	printf("\n Replay...");
	getche();

	init();
	backupInitMap(false);
	display();
	printf("\n Ű�� �����ּ���...");
	getche();

	for (int i = 0; i < nHist; i++)
	{
		move(history[i]);
		display();
		Sleep(200);
	}


	return addRanking(nMove, end_time);

}