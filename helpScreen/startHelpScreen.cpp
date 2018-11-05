void startHelpScreen()
{
	setHelpScreenVariables();
	setHelpScreenEvents();
	updateFunction = updateHelpScreen;
	drawFunction = drawHelpScreen;
}
