void gameResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateGameVariables();
}

void gameClear()
{
	delete gameMap;
	gameMap = NULL;
	deleteTimers<Monster*>();
	deleteTimers<char*>();
	monsters.clear();
	towers.clear();
	shots.clear();
	delete addingTower;
	addingTower = NULL;
	delete currentSecondsToNextWaveText;
	delete currentWaveNumberText;
	delete baseHealthText;
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
		gameScaleDelta = 0.98;
	gameScaleCenter.x = event.mouseWheelScroll.x;
	gameScaleCenter.y = event.mouseWheelScroll.y;
	gameMap->changeZoom();
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		(*i)->changeScale();
	for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
		(*i)->changeScale();
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
		(*i)->changeScale();
	if (addingTower)
	{
		addingTower->refreshScale();
		addingTower->goToCellSelector();
	}
}

void gameKeyPressed()
{
	if (event.key.code == sf::Keyboard::Up)
		gameMap->moveCellSelector(UP);
	else if (event.key.code == sf::Keyboard::Down)
		gameMap->moveCellSelector(DOWN);
	else if (event.key.code == sf::Keyboard::Right)
		gameMap->moveCellSelector(RIGHT);
	else if (event.key.code == sf::Keyboard::Left)
		gameMap->moveCellSelector(LEFT);
	else if (event.key.code == sf::Keyboard::PageUp)
		changeScale(SCALE_UP);
	else if (event.key.code == sf::Keyboard::PageDown)
		changeScale(SCALE_DOWN);
	else if (event.key.code == sf::Keyboard::Escape) gameExit();
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

void gameMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (towersInfoStack->click(event.mouseButton.x, event.mouseButton.y)) return;
		gameMapDragging = true;
		gameMapDraggingMouseX1 = event.mouseButton.x;
		gameMapDraggingMouseY1 = event.mouseButton.y;
		gameDraggingPreviousMouseX0 = event.mouseButton.x;
		gameDraggingPreviousMouseY0 = event.mouseButton.y;
		gameMapDraggingMapInitialCoordinates = gameMap->getPosition();
	}
	else
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		if (!addingTower) return;
		if (gameMap->selectorOnCellWhichFitsForTower())
		{
			towers.push_back(addingTower);
			tryToShoot(addingTower);
		}
		else
			delete addingTower;
		addingTower = NULL;
	}
}

void gameMouseButtonReleased()
{
	gameMapDragging = false;
}

void gameMouseMoved()
{
	if (gameMapDragging)
	{
		gameMap->setPosition(
		gameMapDraggingMapInitialCoordinates.x + event.mouseMove.x - gameMapDraggingMouseX1, 
		gameMapDraggingMapInitialCoordinates.y + event.mouseMove.y - gameMapDraggingMouseY1);
		gameDragOffset.x = event.mouseMove.x - gameDraggingPreviousMouseX0;
		gameDragOffset.y = event.mouseMove.y - gameDraggingPreviousMouseY0;
		for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
			(*i)->drag();
		for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
			(*i)->drag();
		for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
			(*i)->drag();
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
