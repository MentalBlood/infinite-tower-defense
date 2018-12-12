void selectMapScreenResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateSelectMapScreenVariables();
}

void selectMapScreenExit()
{
	delete selectMapScreenMapsList;
	selectMapScreenMapsList = NULL;
	startMenu();
}

void selectMapScreenCloseDeleteMapQuestion()
{
	delete selectMapScreenDeleteMapQuestion;
	selectMapScreenDeleteMapQuestion = NULL;
}

void selectMapScreenDeleteMap()
{
	//remove(("maps/" + selectMapScreenMapsList->getThis() + ".tdm").data());
	bool listHaveElements = selectMapScreenMapsList->deleteThis();
	selectMapScreenCloseDeleteMapQuestion();
	if (!listHaveElements)
		startMenu();
}

void selectMapScreenTryToDeleteMap()
{
	selectMapScreenDeleteMapQuestion =
		new Question(selectMapScreenDeleteMap, selectMapScreenCloseDeleteMapQuestion, "this will delete map",
					 "ok", "no",
					 messageFont,
					 0.3, 0.3, 0.4, 0.4, 2,
					 sf::Color(255, 255, 255), sf::Color(192, 64, 64), sf::Color(0, 0, 0), 4);
}

void selectMapScreenKeyPressed()
{
	if (selectMapScreenDeleteMapQuestion)
	{
		if (event.key.code == sf::Keyboard::Escape)
			selectMapScreenCloseDeleteMapQuestion();
		return;
	}
	if (event.key.code == sf::Keyboard::Up)
		selectMapScreenMapsList->selectPrevious();
	else if (event.key.code == sf::Keyboard::Down)
		selectMapScreenMapsList->selectNext();
	else if (event.key.code == sf::Keyboard::Return)
		selectMapScreenMapsList->selectThis();
	else if (event.key.code == sf::Keyboard::Delete)
		selectMapScreenTryToDeleteMap();
	else if (event.key.code == sf::Keyboard::Escape)
		selectMapScreenExit();
}

void selectMapScreenMouseWheelScrolled()
{
	if (selectMapScreenDeleteMapQuestion) return;
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		if (event.mouseWheelScroll.delta > 0) selectMapScreenMapsList->selectPrevious();
		else selectMapScreenMapsList->selectNext();
	}
}

void selectMapScreenMouseButtonPressed()
{
	if (selectMapScreenDeleteMapQuestion)
		selectMapScreenDeleteMapQuestion->tryToPress(event.mouseButton.x, event.mouseButton.y);
	else
		if (event.mouseButton.button == sf::Mouse::Left)
			selectMapScreenMapsList->selectThis(event.mouseButton.x, event.mouseButton.y);
}

void selectMapScreenMouseButtonReleased()
{
	if (selectMapScreenDeleteMapQuestion)
		selectMapScreenDeleteMapQuestion->unpress();
}

void selectMapScreenMouseMoved()
{
	if (selectMapScreenDeleteMapQuestion) return;
	selectMapScreenMapsList->selectByMouse(event.mouseMove.x, event.mouseMove.y);
}

void setSelectMapScreenEvents()
{
	events[1] = selectMapScreenResized; //resized
	events[4] = nothing; //text entered
	events[5] = selectMapScreenKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = selectMapScreenMouseWheelScrolled; //mouse wheel scrolled
	events[9] = selectMapScreenMouseButtonPressed; //mouse button pressed
	events[10] = selectMapScreenMouseButtonReleased; //mouse button released
	events[11] = selectMapScreenMouseMoved; //mouse moved
}
