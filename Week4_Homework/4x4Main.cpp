#include "Ranking.h"
extern int playFifteenPuzzle();
void main()
{
	loadRanking((char*)"ranking.txt");
	int rank = playFifteenPuzzle();
	printRanking();
	storeRanking((char *)"ranking.txt");
}
