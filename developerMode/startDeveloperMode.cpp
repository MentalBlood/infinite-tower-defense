void startDeveloperMode()
{
	developerMode = true;
	setSelectMapScreenVariables();
	setSelectMapScreenEvents();
	updateFunction = updateSelectMapScreen;
	drawFunction = drawSelectMapScreen;
}
