void startSelectMapScreen()
{
	developerMode = false;
	setSelectMapScreenVariables();
	setSelectMapScreenEvents();
	updateFunction = updateSelectMapScreen;
	drawFunction = drawSelectMapScreen;
}
