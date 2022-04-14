#include "Ranking.h"
extern int playPuzzle();

void main()
{
	loadRanking((char*)"ranking.txt");
	int rank = playPuzzle();
	printRanking();
	storeRanking((char*)"ranking.txt");
}