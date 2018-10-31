void selectMapScreenResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateSelectMapScreenVariables();
}

void selectMapScreenKeyPressed()
{
	if (event.key.code == sf::Keyboard::Up)
		selectMapScreenMapsList->selectPrevious();
	else if (event.key.code == sf::Keyboard::Down)
		selectMapScreenMapsList->selectNext();
	else if (event.key.code == sf::Keyboard::Return)
		selectMapScreenMapsList->selectThis();
}

void selectMapScreenMouseWheelScrolled()
{
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		if (event.mouseWheelScroll.delta > 0) selectMapScreenMapsList->selectNext();
		else selectMapScreenMapsList->selectPrevious();
	}
}

void selectMapScreenMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
		if (selectMapScreenMapsList->selectByMouse(event.mouseButton.y))
			selectMapScreenMapsList->selectThis();
}

void selectMapScreenMouseMoved()
{
	selectMapScreenMapsList->selectByMouse(event.mouseMove.y);
}

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