#include "Ranking.h"
extern int play3x3Puzzle();

void main()
{
	loadRanking((char*)"ranking.txt");
	int rank = play3x3Puzzle();
	printRanking();
	storeRanking((char*)"ranking.txt");
}
