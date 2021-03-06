void mapEditorResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateMapEditorVariables();
}

void mapEditorExit()
{
	delete mapEditorMap;
	if (mapEditorFileNameDialog)
		mapEditorCloseFileNameDialog();
	if (mapEditorWrongMapMessage)
		mapEditorCloseWrongMapMessage();
	if (mapEditorFileAlreadyExistsQuestion)
		mapEditorCloseFileAlreadyExistsQuestion();
	if (editingNewMap) startNewMapSettings();
	else startChooseNewOrSavedMapToEditDialog();
}

void mapEditorKeyPressed()
{
	if (mapEditorWrongMapMessage)
	{
		if ((event.key.code == sf::Keyboard::Return) || (event.key.code == sf::Keyboard::Escape))
			mapEditorCloseWrongMapMessage();
		return;
	}

	if (mapEditorFileAlreadyExistsQuestion)
	{
		if ((event.key.code == sf::Keyboard::Return) || (event.key.code == sf::Keyboard::Escape))
			mapEditorCloseFileAlreadyExistsQuestion();
		return;
	}

	if (mapEditorFileNameDialog)
	{
		if (event.key.code == sf::Keyboard::Escape)
			mapEditorCloseFileNameDialog();
		return;
	}

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
	else if (event.key.code == sf::Keyboard::R)
		mapEditorMap->startSettingRocks();
	else if ((event.key.code == sf::Keyboard::Z) && event.key.control)
	{
		if (event.key.shift) mapEditorMap->redo();
		else mapEditorMap->undo();
	}
	else if (event.key.code == sf::Keyboard::X)
		mapEditorMap->print_actions();
	else if (event.key.code == sf::Keyboard::PageUp)
		mapEditorMap->changeZoom(1.02, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	else if (event.key.code == sf::Keyboard::PageDown)
		mapEditorMap->changeZoom(0.98, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	else if (event.key.code == sf::Keyboard::Escape) mapEditorExit();
}

void mapEditorKeyReleased()
{
	if (mapEditorFileNameDialog || mapEditorWrongMapMessage) return;

	if (event.key.code == sf::Keyboard::Space)
		mapEditorMap->unpressCellSelector();
	else if (event.key.code == sf::Keyboard::R)
		mapEditorMap->finishSettingRocks();
}

void mapEditorTextEntered()
{
	if ((!mapEditorFileNameDialog) || (mapEditorFileAlreadyExistsQuestion)) return;
	if ((event.text.unicode < 128) && (event.text.unicode != 27))
		mapEditorFileNameDialog->processCharacter(event.text.unicode);
}

void mapEditorMouseButtonPressed()
{
	if (mapEditorWrongMapMessage)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			mapEditorWrongMapMessage->tryToPress(event.mouseButton.x, event.mouseButton.y);
		return;
	}

	if (mapEditorFileAlreadyExistsQuestion)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			mapEditorFileAlreadyExistsQuestion->tryToPress(event.mouseButton.x, event.mouseButton.y);
		return;
	}

	if (mapEditorFileNameDialog) return;

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		for (std::list<TwoConditionButton>::iterator i = mapEditorButtons.begin();
			i != mapEditorButtons.end(); i++)
			if (i->tryToPress(event.mouseButton.x, event.mouseButton.y))
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
	mapEditorMap->unpressCellSelector();
	if (event.mouseButton.button != sf::Mouse::Left) return;
	for (std::list<TwoConditionButton>::iterator i = mapEditorButtons.begin();
		i != mapEditorButtons.end(); i++)
		i->unpress();
	if (mapEditorWrongMapMessage)
		mapEditorWrongMapMessage->unpress();
	else
	if (mapEditorFileAlreadyExistsQuestion)
		mapEditorFileAlreadyExistsQuestion->unpress();
	else
		mapEditorMapDragging = false;
}

void mapEditorMouseMoved()
{
	if (mapEditorFileNameDialog || mapEditorWrongMapMessage) return;

	if (mapEditorMapDragging)
		mapEditorMap->setPosition(
				mapEditorMapDraggingMapInitialCoordinates.x + event.mouseMove.x - mapEditorMapDraggingMouseX1, 
				mapEditorMapDraggingMapInitialCoordinates.y + event.mouseMove.y - mapEditorMapDraggingMouseY1);
	else
		mapEditorMap->moveCellSelectorToMouse(event.mouseMove.x, event.mouseMove.y);
}

void mapEditorMouseWheelScrolled()
{
	if (mapEditorFileNameDialog || mapEditorWrongMapMessage) return;
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		mapEditorMap->changeZoom(1 + event.mouseWheelScroll.delta/50,
								event.mouseWheelScroll.x, event.mouseWheelScroll.y);
}

void setMapEditorEvents()
{
	events[1] = mapEditorResized; //resized
	events[4] = mapEditorTextEntered; //text entered
	events[5] = mapEditorKeyPressed; //key pressed
	events[6] = mapEditorKeyReleased; //key released
	events[8] = mapEditorMouseWheelScrolled; //mouse wheel scrolled
	events[9] = mapEditorMouseButtonPressed; //mouse button pressed
	events[10] = mapEditorMouseButtonReleased; //mouse button released
	events[11] = mapEditorMouseMoved; //mouse moved
}
