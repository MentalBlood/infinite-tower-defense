void gameResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateGameVariables();
}

void gameExit()
{
	delete gameMap;
	gameMap = NULL;
	deleteTimers();
	monsters.clear();
	delete currentSecondsToNextWaveText;
	delete currentWaveNumberText;
	delete baseHealthText;
	startFunctions[3]();
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
		gameMap->changeZoom(1.02, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	else if (event.key.code == sf::Keyboard::PageDown)
		gameMap->changeZoom(0.98, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	else if (event.key.code == sf::Keyboard::Escape) gameExit();
	else if (event.key.code == sf::Keyboard::S) spawn(TYPE_A);
	else if (event.key.code == sf::Keyboard::W) spawnWave(1, TYPE_B, 8, 1);
	else if (event.key.code == sf::Keyboard::C) startWaving();
}

void gameMouseWheelScrolled()
{
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		float delta = 1 + event.mouseWheelScroll.delta/50;
		gameMap->changeZoom(delta, event.mouseWheelScroll.x, event.mouseWheelScroll.y);
		for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
			(*i)->changeScale(delta, sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
	}
}

float gameDraggingPreviousMouseX0,
	  gameDraggingPreviousMouseY0;

void gameMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		gameMapDragging = true;
		gameMapDraggingMouseX1 = event.mouseButton.x;
		gameMapDraggingMouseY1 = event.mouseButton.y;
		gameDraggingPreviousMouseX0 = event.mouseButton.x;
		gameDraggingPreviousMouseY0 = event.mouseButton.y;
		gameMapDraggingMapInitialCoordinates = gameMap->getPosition();
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
		for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
			(*i)->drag(sf::Vector2f(	event.mouseMove.x - gameDraggingPreviousMouseX0,
											event.mouseMove.y - gameDraggingPreviousMouseY0));
		gameDraggingPreviousMouseX0 = event.mouseMove.x;
		gameDraggingPreviousMouseY0 = event.mouseMove.y;
	}
	else
		gameMap->moveCellSelectorToMouse(event.mouseMove.x, event.mouseMove.y);
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
