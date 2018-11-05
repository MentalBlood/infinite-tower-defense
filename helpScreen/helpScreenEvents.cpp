void helpScreenResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateHelpScreenVariables();
}

void helpScreenKeyPressed()
{
	if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
		helpScreenExit();
}

void helpScreenMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
		helpScreenMessage->tryToPress(event.mouseButton.x, event.mouseButton.y);
}

void helpScreenMouseButtonReleased()
{
	if (event.mouseButton.button == sf::Mouse::Left)
		helpScreenMessage->unpress();
}

void setHelpScreenEvents()
{
	events[1] = helpScreenResized; //resized
	events[4] = nothing; //text entered
	events[5] = helpScreenKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = nothing; //mouse wheel scrolled
	events[9] = helpScreenMouseButtonPressed; //mouse button pressed
	events[10] = helpScreenMouseButtonReleased; //mouse button released
	events[11] = nothing; //mouse moved
}
