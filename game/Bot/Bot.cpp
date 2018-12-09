#include "getDistanceCoveredByTower.cpp"
#include "VirtualTower.cpp"
#include "VirtualMap.cpp"

bool makeVirtualAction(FILE *logFile)
{
	VirtualMapCell *maxActionProfitCell = NULL;
	float maxActionProfit = 0;
	for (std::list<VirtualMapCell*>::iterator i = towersCellsList->begin(); i != towersCellsList->end(); i++)
	{
		float currentCellActionProfit = (*i)->getMaxActionProfitValue();
		if (currentCellActionProfit > maxActionProfit)
		{
			maxActionProfit = currentCellActionProfit;
			maxActionProfitCell = (*i);
		}
	}
	if (maxActionProfitCell)
	{
		maxActionProfitCell->makeAction().printToFile(logFile);
		return true;
	}
	else
	{
		fprintf(logFile, "total despair\n");
		return false;
	}
}

void makeVirtualActions(unsigned int number, const char *logFileName)
{
	FILE *logFile = fopen(logFileName, "wb");
	for (unsigned int i = 0; i < number; i++)
	{
		fprintf(logFile, "action %u: ", i);
		makeVirtualAction(logFile);
	}
	fclose(logFile);
}
