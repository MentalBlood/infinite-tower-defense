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
	maxActionProfitCell->getMaxProfitAction().printToFile(logFile);
	maxActionProfitCell->makeAction();
}

void makeVirtualActions(unsigned int number, const char *logFileName)
{
	FILE *logFile = fopen(logFileName, "wb");
	for (unsigned int i = 0; i < number; i++)
	{
		fprintf(logFile, "action %u: ", i+1);
		makeVirtualAction(logFile);
	}
	fclose(logFile);
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
	{
		printf("setting tower with type %d\n", nextActionCell->getMaxProfitAction().getType()-1);
		setTower(actionCellCoordinates.x, actionCellCoordinates.y,
				 (*baseTowersSpecifications)[nextActionCell->getMaxProfitAction().getType()-1]);
	}
	money -= nextActionCost;
	nextActionCell->makeAction();
	setNextAction();
}
