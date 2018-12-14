#include "getDistanceCoveredByTower.cpp"
#include "VirtualTower.cpp"
#include "VirtualMap.cpp"

VirtualMapCell* getNextActionCell()
{
	VirtualMapCell *maxActionProfitCell = (*towersCellsList->begin());
	double maxActionProfit = (*towersCellsList->begin())->getMaxActionProfitValue();
	for (std::list<VirtualMapCell*>::iterator i = ++towersCellsList->begin(); i != towersCellsList->end(); i++)
	{
		double currentCellActionProfit = (*i)->getMaxActionProfitValue();
		if (currentCellActionProfit > maxActionProfit)
		{
			maxActionProfit = currentCellActionProfit;
			maxActionProfitCell = (*i);
		}
	}
	return maxActionProfitCell;
}

void makeVirtualAction(FILE *logFile)
{
	VirtualMapCell *maxActionProfitCell = getNextActionCell();
	if (logFile)
	{
		maxActionProfitCell->getMaxProfitAction().printToFile(logFile);
		fprintf(logFile, "actionProfitValue = %lf, totalProfit = %f => ",
			maxActionProfitCell->getMaxActionProfitValue(), currentProfitValue);
	}
	lastActionProfitValue = maxActionProfitCell->getMaxActionProfitValue();
	currentProfitValue += lastActionProfitValue;
	maxActionProfitCell->makeAction();
}

void makeVirtualActions(unsigned int number, const char *logFileName)
{
	if (!logFileName)
	{
		for (unsigned int i = 0; i < number; i++)
			makeVirtualAction(NULL);
		return;
	}

	FILE *logFile = fopen(logFileName, "wb");
	for (unsigned int i = 0; i < number; i++)
	{
		fprintf(logFile, "action %u: ", i+1);
		makeVirtualAction(logFile);
	}
	fprintf(logFile, "averageProfitValue = %f\n", currentProfitValue / number);
	fclose(logFile);
	return;
}

VirtualMapCell *nextActionCell;
unsigned int nextActionCost;

void setNextAction()
{
	if (!towersCellsList->size()) return;
	nextActionCell = getNextActionCell();
	nextActionCost = nextActionCell->getMaxProfitActionCost();
}

void setTower(unsigned int x, unsigned int y, TowerSpecification *specification)
{
	gameMap->moveCellSelectorToCell(x, y);
	if (addingTower)
		delete addingTower;
	addingTower = new Tower(specification);
	addingTower->hideRangeCircle();
	towers.push_back(addingTower);
	gameMap->setTowerOnCell();
	tryToShoot(addingTower);
	addingTower = NULL;
}

void upgradeTower(unsigned int x, unsigned int y)
{
	gameMap->moveCellSelectorToCell(x, y);
	std::list<Tower*>::iterator towerUnderSelector = getTowerUnderSelector();
	if (towerUnderSelector == towers.end()) return;
	(*towerUnderSelector)->upgradeAnyway();
}

void tryToMakeNextAction()
{
	if (!towersCellsList->size()) return;
	if (money < nextActionCost) return;
	sf::Vector2u actionCellCoordinates = nextActionCell->getPosition();
	if (nextActionCell->getMaxProfitAction().getType() == UPGRADE)
		upgradeTower(actionCellCoordinates.x, actionCellCoordinates.y);
	else
		setTower(actionCellCoordinates.x, actionCellCoordinates.y,
				 (*baseTowersSpecifications)[nextActionCell->getMaxProfitAction().getType()-1]);
	money -= nextActionCost;
	updateMoneyText();
	++actionsNumber;
	nextActionCell->makeAction();
	setNextAction();
}

float monstersRewardCoefficient = 0;

void setMonstersRewardCoefficient()
{
	fillVirtualMap();
	printf("towersCellsList size = %lu\n", towersCellsList->size());
	if (!towersCellsList->size()) return;
	unsigned int actionsNumber = towersCellsList->size() * 200;
	if (actionsNumber > 2000)
		actionsNumber = 2000;
	printf("actionsNumber = %u\n", actionsNumber);
	makeVirtualActions(actionsNumber, NULL);
	//printf("lastProfitValue = %f\n", lastActionProfitValue);
	float a = monstersParameters[HEALTH]->getMultiplier();
	monstersRewardCoefficient = a * (a - 1) / (lastActionProfitValue * (a - 1.0/pow(a, 2)));
	deleteVirtualMap();
}
