#include "getDistanceCoveredByTower.cpp"
#include "VirtualTower.cpp"
#include "VirtualMap.cpp"

VirtualMapCell* getNextActionCell()
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
	currentProfitValue += maxActionProfitCell->getMaxActionProfitValue();
	maxActionProfitCell->makeAction();
}

float makeVirtualActions(unsigned int number, const char *logFileName)
{
	if (!logFileName)
	{
		for (unsigned int i = 0; i < number; i++)
			makeVirtualAction(NULL);
		return currentProfitValue / number;
	}

	FILE *logFile = fopen(logFileName, "wb");
	for (unsigned int i = 0; i < number; i++)
	{
		fprintf(logFile, "action %u: ", i+1);
		makeVirtualAction(logFile);
	}
	float averageProfitValue = currentProfitValue / number;
	fprintf(logFile, "averageProfitValue = %f\n", averageProfitValue);
	fclose(logFile);
	return averageProfitValue;
}

VirtualMapCell *nextActionCell;
unsigned int nextActionCost;

void setNextAction()
{
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
	if (money < nextActionCost) return;
	sf::Vector2u actionCellCoordinates = nextActionCell->getPosition();
	if (nextActionCell->getMaxProfitAction().getType() == UPGRADE)
		upgradeTower(actionCellCoordinates.x, actionCellCoordinates.y);
	else
		setTower(actionCellCoordinates.x, actionCellCoordinates.y,
				 (*baseTowersSpecifications)[nextActionCell->getMaxProfitAction().getType()-1]);
	money -= nextActionCost;
	updateMoneyText();
	nextActionCell->makeAction();
	setNextAction();
}

float monstersRewardCoefficient = 0;

void setMonstersRewardCoefficient()
{
	fillVirtualMap();
	float averageProfitValue = makeVirtualActions(2000, NULL);
	float a = monstersParameters[HEALTH]->getMultiplier();
	monstersRewardCoefficient = a * (a - 1) / (averageProfitValue * (a - 1.0/pow(a, 1)));
	deleteVirtualMap();
}
