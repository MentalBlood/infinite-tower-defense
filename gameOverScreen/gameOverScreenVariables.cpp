Message *gameOverScreenMessage;

void updateGameOverScreenVariables()
{ gameOverScreenMessage->updatePositionAndSize(); }

void startDeveloperMode();

void gameOverScreenExit()
{
	delete gameOverScreenMessage;
	gameOverScreenMessage = NULL;
	if (developerMode)
		startDeveloperMode();
	else
		startSelectMapScreen();
}

void setGameOverScreenVariables()
{
	gameOverScreenMessage = new Message(gameOverScreenExit, "game over", "fuck you",
										messageFont,
										0, 0, 1, 1, 4,
										sf::Color(0, 0, 0), sf::Color(192, 64, 64), sf::Color(64, 0, 0));
}
