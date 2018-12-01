void gameResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateGameVariables();
}

void gameClear()
{
	printf("1\n");
	delete gameMap;
	printf("2\n");
	gameMap = NULL;
	printf("3\n");
	deleteTimers<Monster*>();
	printf("4\n");
	deleteTimers<char>();
	printf("5\n");
	deleteTimers<Tower*>();
	printf("6\n");
	deleteSplinters();
	printf("7\n");
	deleteGrid();
	printf("8\n");
	shots.clear();
	printf("9\n");
	monsters.clear();
	printf("10\n");
	towers.clear();
	printf("11\n");
	delete addingTower;
	printf("12\n");
	addingTower = NULL;
	printf("13\n");
	delete currentSecondsToNextWaveText;
	printf("14\n");
	delete currentWaveNumberText;
	printf("15\n");
	delete baseHealthText;
	printf("16\n");
	delete moneyText;
	printf("17\n");
	delete gameHelpButton;
	printf("18\n");
	clearMonsterParameters();
	printf("19\n");
}

void gameExit()
{
	gameClear();
	startSelectMapScreen();
}

void gameOver()
{
	gameClear();
	startGameOverScreen();
}

#define SCALE_DOWN 0
#define SCALE_UP 1

void changeScale(bool up)
{
	if (up)
		gameScaleDelta = 1.02;
	else
	{
		gameScaleDelta = 0.98;
		if ((gameScale * gameScaleDelta) < 0.1)
			return;
	}
	gameScaleCenter.x = event.mouseWheelScroll.x;
	gameScaleCenter.y = event.mouseWheelScroll.y;
	gameMap->changeZoom();
	mapPosition = gameMap->getPosition();
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		(*i)->updateScale();
	for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
		(*i)->changeScale();
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
		(*i)->updateScale();
	scaleSplinters();
	if (addingTower)
	{
		addingTower->refreshScale();
		addingTower->goToCellSelector();
	}
}

std::list<Tower*>::iterator getTowerUnderSelector()
{
	if (!gameMap->selectorOnTower()) return towers.end();
	sf::Vector2f cellSelectorPosition = gameMap->getSelectorCenteredPosition();
	for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
		if ((*i)->havePoint(cellSelectorPosition))
			return i;
	return towers.end();
}

bool tryToShowTowerUpgradeInfo()
{
	std::list<Tower*>::iterator towerUnderSelector = getTowerUnderSelector();
	if (towerUnderSelector != towers.end())
	{
		currentShowingUpgradeInfoTower = (*towerUnderSelector);
		return true;
	}
	return false;
}

void hideTowerUpgradeInfo()
{ currentShowingUpgradeInfoTower = NULL; }

void tryToDeleteTower()
{
	std::list<Tower*>::iterator towerUnderSelector = getTowerUnderSelector();
	if (towerUnderSelector != towers.end())
	{
		money += (*towerUnderSelector)->getCostWithUpgrades() / 2;
		deleteTimersWithSuchArgument<Tower*>(*towerUnderSelector);
		if ((*towerUnderSelector) == currentShowingUpgradeInfoTower)
			hideTowerUpgradeInfo();
		delete (*towerUnderSelector);
		towers.erase(towerUnderSelector);
		gameMap->removeTower();
		updateMoneyText();
	}
}

void tryToShowHideTowerRangeRadius()
{
	std::list<Tower*>::iterator towerUnderSelector = getTowerUnderSelector();
	if (towerUnderSelector != towers.end())
		(*towerUnderSelector)->showHideRangeCircle();
}

void tryToGetDistanceCoveredByTower()
{
	std::list<Tower*>::iterator towerUnderSelector = getTowerUnderSelector();
	if (towerUnderSelector != towers.end())
		printf("tower covers distance %f\n", getDistanceCoveredByTower((*towerUnderSelector)));
	else
		printf("no tower here\n");
}

void tryToSetAddingTower()
{
	if (!addingTower) return;
	if (gameMap->selectorOnCellWhichFitsForTower())
	{
		towers.push_back(addingTower);
		gameMap->setTowerOnCell();
		addingTower->hideRangeCircle();
		tryToShoot(addingTower);
	}
	else
	{
		money += addingTower->getCost();
		updateMoneyText();
		delete addingTower;
	}
	addingTower = NULL;
}

void moveCellSelector(char direction)
{
	gameMap->moveCellSelector(direction);
	if (addingTower) addingTower->goToCellSelector();
}

void gameKeyPressed()
{
	if ((event.key.code <= 35) && (event.key.code >= 27))
	{
		towersInfoStack->click(event.key.code - 26 - 1);
		tryToSetAddingTower();
	}
	else if (event.key.code == sf::Keyboard::Up)
		moveCellSelector(UP);
	else if (event.key.code == sf::Keyboard::Down)
		moveCellSelector(DOWN);
	else if (event.key.code == sf::Keyboard::Right)
		moveCellSelector(RIGHT);
	else if (event.key.code == sf::Keyboard::Left)
		moveCellSelector(LEFT);
	else if (event.key.code == sf::Keyboard::PageUp)
		changeScale(SCALE_UP);
	else if (event.key.code == sf::Keyboard::PageDown)
		changeScale(SCALE_DOWN);
	else if (event.key.code == sf::Keyboard::Space)
		changeBool(&pause);
	else if (event.key.code == sf::Keyboard::N)
		abandonTimers<char>();
	else if (event.key.code == sf::Keyboard::R)
		tryToShowHideTowerRangeRadius();
	else if (event.key.code == sf::Keyboard::S)
		tryToSetAddingTower();
	else if (event.key.code == sf::Keyboard::D)
		tryToGetDistanceCoveredByTower();
	else if (event.key.code == sf::Keyboard::Delete)
		tryToDeleteTower();
	else if (event.key.code == sf::Keyboard::Escape)
	{
		if (currentShowingUpgradeInfoTower)
			hideTowerUpgradeInfo();
		else
			gameExit();
	}
}

void gameMouseWheelScrolled()
{
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		if (event.mouseWheelScroll.delta > 0)
			changeScale(SCALE_UP);
		else
			changeScale(SCALE_DOWN);
	}
}

float gameDraggingPreviousMouseX0,
	  gameDraggingPreviousMouseY0;

bool itWasNotDraggingButClick;

void gameMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (event.mouseButton.x < (windowSize.x * towersPanelRelativeX))
			itWasNotDraggingButClick = true;
		else
		{
			itWasNotDraggingButClick = false;
			if (currentShowingUpgradeInfoTower)
			{
				if (currentShowingUpgradeInfoTower->getUpgradeInfo()->tryToPress(event.mouseButton.x, event.mouseButton.y))
					currentShowingUpgradeInfoTower->refreshRangeCircle();
			}
			else
				towersInfoStack->click(event.mouseButton.x, event.mouseButton.y);
			return;
		}
		
		if (gameHelpButton->tryToPress(event.mouseButton.x, event.mouseButton.y)) return;
		gameMapDragging = true;
		gameMapDraggingMouseX1 = event.mouseButton.x;
		gameMapDraggingMouseY1 = event.mouseButton.y;
		gameDraggingPreviousMouseX0 = event.mouseButton.x;
		gameDraggingPreviousMouseY0 = event.mouseButton.y;
		gameMapDraggingMapInitialCoordinates = gameMap->getPosition();
	}
	else
	if (event.mouseButton.button == sf::Mouse::Right)
		tryToSetAddingTower();
}

void gameMouseButtonReleased()
{
	gameMapDragging = false;
	gameHelpButton->unpress();
	if (currentShowingUpgradeInfoTower)
		currentShowingUpgradeInfoTower->getUpgradeInfo()->unpressButton();
	if (itWasNotDraggingButClick)
		if (!tryToShowTowerUpgradeInfo())
			hideTowerUpgradeInfo();
}

void gameMouseMoved()
{
	itWasNotDraggingButClick = false;
	if (gameMapDragging)
	{
		gameMap->setPosition(
			gameMapDraggingMapInitialCoordinates.x + event.mouseMove.x - gameMapDraggingMouseX1, 
			gameMapDraggingMapInitialCoordinates.y + event.mouseMove.y - gameMapDraggingMouseY1);
		mapPosition = gameMap->getPosition();
		gameDragOffset.x = event.mouseMove.x - gameDraggingPreviousMouseX0;
		gameDragOffset.y = event.mouseMove.y - gameDraggingPreviousMouseY0;
		dragGameObjects();
		gameDraggingPreviousMouseX0 = event.mouseMove.x;
		gameDraggingPreviousMouseY0 = event.mouseMove.y;
	}
	else
		gameMap->moveCellSelectorToMouse(event.mouseMove.x, event.mouseMove.y);
	if (addingTower) addingTower->goToCellSelector();
}

void setGameEvents()
{
	events[1] = gameResized; //resized
	events[4] = nothing; //text entered
	events[5] = gameKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = gameMouseWheelScrolled; //mouse wheel scrolled
	events[9] = gameMouseButtonPressed; //mouse button pressed
	events[10] = gameMouseButtonReleased; //mouse button released
	events[11] = gameMouseMoved; //mouse moved
}
