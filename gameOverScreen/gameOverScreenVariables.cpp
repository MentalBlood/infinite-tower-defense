Message *gameOverScreenMessage;

void updateGameOverScreenVariables()
{
	gameOverScreenMessage->updatePositionAndSize();
}

void gameOverScreenExit()
{
	delete gameOverScreenMessage;
	gameOverScreenMessage = NULL;
	startSelectMapScreen();
}

void setGameOverScreenVariables()
{
	gameOverScreenMessage = new Message(gameOverScreenExit, "game over",
										"fuck you",
										"fonts/messageFont.otf",
										0, 0, 1, 1,
										sf::Color(0, 0, 0), sf::Color(192, 64, 64),
										sf::Color(64, 0, 0));
}
