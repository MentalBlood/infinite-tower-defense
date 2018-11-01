void startGame(std::string mapFileName)
{
	setGameVariables(mapFileName.data());
	setGameEvents();
	updateFunction = updateGame;
	drawFunction = drawGame;
}
