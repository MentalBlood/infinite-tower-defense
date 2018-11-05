Message *helpScreenMessage;

void updateHelpScreenVariables()
{
	helpScreenMessage->updatePositionAndSize();
}

void helpScreenExit()
{
	delete helpScreenMessage;
	helpScreenMessage = NULL;
	startFunctions[0]();
}

void setHelpScreenVariables()
{
	helpScreenMessage = new Message(helpScreenExit, "press esc to return to previous screen", "OK",
									"fonts/messageFont.otf",
									0, 0, 1, 1,
									sf::Color(0, 0, 0), sf::Color(64, 128, 64), sf::Color(192, 192, 192));
}
