void startSelectMapScreen()
{
	setSelectMapScreenVariables();
	setSelectMapScreenEvents();
	updateFunction = updateSelectMapScreen;
	drawFunction = drawSelectMapScreen;
}
