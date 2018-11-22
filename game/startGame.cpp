void startGame(std::string mapFileName)
{
	mapFileName = "maps/" + mapFileName + ".tdm";
	setGameVariables(mapFileName.data());
	setGameEvents();
	updateFunction = updateGame;
	drawFunction = drawGame;
}
