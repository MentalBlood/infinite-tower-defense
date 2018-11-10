void startGameOverScreen()
{
	setGameOverScreenVariables();
	setGameOverScreenEvents();
	updateFunction = updateGameOverScreen;
	drawFunction = drawGameOverScreen;
}
