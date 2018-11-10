void gameOverScreenResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateGameOverScreenVariables();
}

void gameOverScreenKeyPressed()
{
	if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
		gameOverScreenExit();
}

void gameOverScreenMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
		gameOverScreenMessage->tryToPress(event.mouseButton.x, event.mouseButton.y);
}

void gameOverScreenMouseButtonReleased()
{
	if (event.mouseButton.button == sf::Mouse::Left)
		gameOverScreenMessage->unpress();
}

void setGameOverScreenEvents()
{
	events[1] = gameOverScreenResized; //resized
	events[4] = nothing; //text entered
	events[5] = gameOverScreenKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = nothing; //mouse wheel scrolled
	events[9] = gameOverScreenMouseButtonPressed; //mouse button pressed
	events[10] = gameOverScreenMouseButtonReleased; //mouse button released
	events[11] = nothing; //mouse moved
}
