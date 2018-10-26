void mapEditorResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateMapEditorVariables();
}

void mapEditorKeyPressed()
{
	if (event.key.code == sf::Keyboard::Up)
		mapEditorMap->changePath(UP);
	else if (event.key.code == sf::Keyboard::Down)
		mapEditorMap->changePath(DOWN);
	else if (event.key.code == sf::Keyboard::Right)
		mapEditorMap->changePath(RIGHT);
	else if (event.key.code == sf::Keyboard::Left)
		mapEditorMap->changePath(LEFT);
	else if (event.key.code == sf::Keyboard::PageUp) mapEditorMap->changeZoom(0.02);
	else if (event.key.code == sf::Keyboard::PageDown) mapEditorMap->changeZoom(-0.02);
}

void mapEditorMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		mapEditorMapDragging = true;
		mapEditorMapDraggingMouseX1 = event.mouseButton.x;
		mapEditorMapDraggingMouseY1 = event.mouseButton.y;
		mapEditorMapDraggingMapInitialCoordinates = mapEditorMap->getPosition();
	}
	else
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		mapEditorMap->checkMouseForNewPathCells(event.mouseButton.x, event.mouseButton.y, true);
		mapEditorAddingPathByMouse = true;
	}
}

void mapEditorMouseButtonReleased()
{
	mapEditorMapDragging = false;
	mapEditorAddingPathByMouse = false;
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
	if (mapEditorAddingPathByMouse)
		mapEditorMap->checkMouseForNewPathCells(event.mouseMove.x, event.mouseMove.y, false);
}

void mapEditorMouseWheelScrolled()
{
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		mapEditorMap->changeZoom(event.mouseWheelScroll.delta/50);
	}
}

void setMapEditorEvents()
{
	events[1] = mapEditorResized; //resized
	events[4] = nothing; //text entered
	events[5] = mapEditorKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = mapEditorMouseWheelScrolled; //mouse wheel scrolled
	events[9] = mapEditorMouseButtonPressed; //mouse button pressed
	events[10] = mapEditorMouseButtonReleased; //mouse button released
	events[11] = mapEditorMouseMoved; //mouse moved
}
