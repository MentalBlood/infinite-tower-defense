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

void selectMapScreenKeyPressed()
{
	if (event.key.code == sf::Keyboard::Up)
		selectMapScreenMapsList->selectPrevious();
	else if (event.key.code == sf::Keyboard::Down)
		selectMapScreenMapsList->selectNext();
	else if (event.key.code == sf::Keyboard::Return)
		selectMapScreenMapsList->selectThis();
	else if (event.key.code == sf::Keyboard::Escape)
		selectMapScreenExit();
}

void selectMapScreenMouseWheelScrolled()
{
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		if (event.mouseWheelScroll.delta > 0) selectMapScreenMapsList->selectPrevious();
		else selectMapScreenMapsList->selectNext();
	}
}

void selectMapScreenMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
		selectMapScreenMapsList->selectThis(event.mouseButton.x, event.mouseButton.y);
}

void selectMapScreenMouseMoved()
{ selectMapScreenMapsList->selectByMouse(event.mouseMove.x, event.mouseMove.y); }

void setSelectMapScreenEvents()
{
	events[1] = selectMapScreenResized; //resized
	events[4] = nothing; //text entered
	events[5] = selectMapScreenKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = selectMapScreenMouseWheelScrolled; //mouse wheel scrolled
	events[9] = selectMapScreenMouseButtonPressed; //mouse button pressed
	events[10] = nothing; //mouse button released
	events[11] = selectMapScreenMouseMoved; //mouse moved
}
