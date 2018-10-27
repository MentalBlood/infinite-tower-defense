void mapEditorResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateMapEditorVariables();
}

void mapEditorExit()
{
	delete mapEditorMap;
	startFunctions[1]();
}

void mapEditorKeyPressed()
{
	if (event.key.code == sf::Keyboard::Up)
		mapEditorMap->moveCellSelector(UP);
	else if (event.key.code == sf::Keyboard::Down)
		mapEditorMap->moveCellSelector(DOWN);
	else if (event.key.code == sf::Keyboard::Right)
		mapEditorMap->moveCellSelector(RIGHT);
	else if (event.key.code == sf::Keyboard::Left)
		mapEditorMap->moveCellSelector(LEFT);
	else if (event.key.code == sf::Keyboard::Space)
		mapEditorMap->pressCellSelector();
	else if (event.key.code == sf::Keyboard::PageUp) mapEditorMap->changeZoom(1.02, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	else if (event.key.code == sf::Keyboard::PageDown) mapEditorMap->changeZoom(0.98, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	else if (event.key.code == sf::Keyboard::End) mapEditorExit();
}

void mapEditorKeyReleased()
{
	if (event.key.code == sf::Keyboard::Space)
		mapEditorMap->unpressCellSelector();
}

void mapEditorMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		for (int i = 0; i < mapEditorButtons.size(); i++)
			if (mapEditorButtons[i].tryToPress(event.mouseButton.x, event.mouseButton.y))
				return;
		mapEditorMapDragging = true;
		mapEditorMapDraggingMouseX1 = event.mouseButton.x;
		mapEditorMapDraggingMouseY1 = event.mouseButton.y;
		mapEditorMapDraggingMapInitialCoordinates = mapEditorMap->getPosition();
	}
	else
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		if (mapEditorMap->moveCellSelectorToMouse(event.mouseButton.x, event.mouseButton.y))
			mapEditorMap->pressCellSelector();
	}
}

void mapEditorMouseButtonReleased()
{
	mapEditorMapDragging = false;
	mapEditorMap->unpressCellSelector();
	for (int i = 0; i < mapEditorButtons.size(); i++)
		mapEditorButtons[i].unpress();
}

void mapEditorMouseMoved()
{
	if (mapEditorMapDragging)
	{
		mapEditorMap->setPosition(
				mapEditorMapDraggingMapInitialCoordinates.x + event.mouseMove.x - mapEditorMapDraggingMouseX1, 
				mapEditorMapDraggingMapInitialCoordinates.y + event.mouseMove.y - mapEditorMapDraggingMouseY1);
	}
	else
	mapEditorMap->moveCellSelectorToMouse(event.mouseMove.x, event.mouseMove.y);
}

void mapEditorMouseWheelScrolled()
{
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		mapEditorMap->changeZoom(1 + event.mouseWheelScroll.delta/50, event.mouseWheelScroll.x, event.mouseWheelScroll.y);
}

void setMapEditorEvents()
{
	events[1] = mapEditorResized; //resized
	events[4] = nothing; //text entered
	events[5] = mapEditorKeyPressed; //key pressed
	events[6] = mapEditorKeyReleased; //key released
	events[8] = mapEditorMouseWheelScrolled; //mouse wheel scrolled
	events[9] = mapEditorMouseButtonPressed; //mouse button pressed
	events[10] = mapEditorMouseButtonReleased; //mouse button released
	events[11] = mapEditorMouseMoved; //mouse moved
}