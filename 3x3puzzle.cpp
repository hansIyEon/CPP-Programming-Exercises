#include "Ranking.h"
#include <Windows.h>   //Sleep() 함수를 위해 포함
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define DIM 3


int flag;
double tElap = 0;
double d;
void savegame(char* filename);
enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };  //방향 키에 대한 아스키코드
static int DirKey[4] = { Left,Right,Up,Down };    // 0~3을 방향키에 대한 아스키코드로 바꾸기 위한 테이블
static int map[DIM][DIM];  //퍼즐맵
static int x, y;           //빈칸의 위치(행:y, 열:x)
static int nMove;          //이동한 횟수
static clock_t tStart;     //기준 시각

static void init()  //초기하함수, 모든 퍼즐 조각을 제자리로 보냄. 마지막 자리가 빈칸이 됨(y,x=3)
{					//난수 발생과 기준 시각, 이동 횟수도 초기화 함.
	for (int i = 0; i < DIM * DIM - 1; i++)
	{
		map[i / DIM][i % DIM] = i + 1;
	}
	map[DIM - 1][DIM - 1] = 0;
	x = DIM - 1; y = DIM - 1;

	srand(time(NULL));  //난수 발생 시작 설정
	tStart = clock();   //기준 시각 설정
	nMove = 0;          // 이동 횟수 초기화

}

static void display() //퍼즐을 화면에 보기 좋게 출력하는 함수. 이동 횟수와 소요시간을 계산하여
{					  //함께 출력해 줌. map[r][c]가 0이면 공백이고 아니면 해당 조각 번호를 출력함

	system("cls");   //전에 출력한 것을 모두 지워줌!!
	printf("\n 게임을 저장,종료하려면 0을 누르세요\n");
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
		printf("\n\t 이동횟수:%6d\n\t소요시간:%6.1lf\n\n", nMove, d);
	}
	if (flag == 1)
	{

		d = (double(t1 - tStart) / CLOCKS_PER_SEC) + tElap;
		printf("\n\t 이동횟수:%6d\n\t소요시간:%6.1lf\n\n", nMove, d);
	}

}
/*
   화살표 키의 아스키 코드를 dir로 전달받아 해당 방향으로 퍼즐 조각을 움직이는 함수. 퍼즐 조각을
   움직이면 공백 위치가 반대로 움직여야 하며, 공백 위치를 나타내는 변수 x 또는 y가 갱신되어야 함.
   경계 조건을 검사해야 하는데, 예를 들어 오른쪽 화살표가 눌러졌는데 공백이 맨 왼쪽 열(x==0)이면
   오른쪽으로 움직일 조각이 없으므로 이동할 수 없음. 모든 방향에 대해 이 조건을 검사해서 처리해야 함.
*/

static bool move(int dir)
{
	if (dir == Right && x > 0)  //→ : 맨 왼쪽 열인지 검사
	{
		map[y][x] = map[y][x - 1];  // 퍼즐 오른쪽으로 이동
		map[y][--x] = 0;            //공백 왼쪽으로 이동
	}
	else if (dir == Left && x < DIM - 1)  // ← : 맨 오른쪽 열인지 검사
	{
		map[y][x] = map[y][x + 1];   // 퍼즐 왼쪽으로 이동
		map[y][++x] = 0;             // 공백 오른쪽으로 이동
	}
	else if (dir == Up && y < DIM - 1)   // ↑ : 맨 아래쪽 열인지 검사
	{
		map[y][x] = map[y + 1][x];   //퍼즐 위로 이동
		map[++y][x] = 0;             //공백 아래로 이동
	}
	else if (dir = Down && y > 0)    //↓: 맨 위쪽 열인지 검사
	{
		map[y][x] = map[y - 1][x];   //퍼즐 아래로 이동
		map[--y][x] = 0;             //공백 위로 이동
	}
	else return false;

	nMove++;
	return true;
}
static void shuffle(int nShuffle)   // 퍼즐 조각을 섞는 횟수를 입력받아 무작위로 빈칸을 움직여 퍼즐을
{									//섞는 함수. 난수를 발생하여 이동 방향을 결정하고 이동을 시도함.
	for (int i = 0; i < nShuffle; i++)
	{
		int key = DirKey[rand() % 4];
		if (move(key) == false)  //만약 이동할 수 없는 방향이면 move()에서 false를 반환하므로
		{						 //다시 섞도록 함(i를 감소)
			i--;
			continue;
		}
		display();
		Sleep(50);    //섞이는 과정을 볼 수 있도록 50msec를 기다림. 더 천천히 움직이려면
					  // 더 큰 값으로 Sleep()하면 됨. 단위는 msec임.
	}
}
static bool isDone()  //퍼즐이 다 맞추어졌는지를 검사하는 함수. 모든 조각이 제자리에 있고 마지막에
{					  //공백이 있으면 게임 완료.
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
static int getDirKey()  //방향키를 받아들이는 함수. 키를 누르면 바로 반응함.
{
	//int key = getche();
	return getche() == 224 ? getche() : 0;
}

static int getSaveKey()
{
	//int key = getch();
	if (getch() == 48)
	{
		printf("\n게임이 저장된 후 종료합니다...");
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
	printf("\n퍼즐을 섞어주세요(엔터)...");
	getche();
	shuffle(100);   //퍼즐 조각을 100번 이동해 섞음
	printf("\n 게임이 시작됩니다...");
	getche();

	nMove = 0;              //이동횟수 초기화
	tStart = clock();		//기준 시각을 재설정
	while (!isDone)			//게임 종료 검사
	{
		move(getDirKey());   //키를 받아 퍼즐조각 이동
		display();			 //현재 상태를 화면에 출력
	}
	clock_t t1 = clock();
	double d = double(t1 - tStart) / CLOCKS_PER_SEC;
	return addRanking(nMove, d);  //랭킹 갱신
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
		printf("저장된 게임이 없습니다!!");
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

	printf("\n 이전 게임을 이어서 하겠습니까?(yes==>1, no==>0) :");
	scanf_s("%d", &flag);
	if (flag == 0)
	{
		init();
		display();
		printf("\n 퍼즐을 섞어주세요(엔터)...");
		getche();
		shuffle(20);

		backupInitMap();

		printf("\n 게임이 시작됩니다...");
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
		history[nHist] = getSaveKey();  //움직임 저장
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
	printf("\n 키를 눌러주세요...");
	getche();

	for (int i = 0; i < nHist; i++)
	{
		move(history[i]);
		display();
		Sleep(200);
	}


	return addRanking(nMove, end_time);

}