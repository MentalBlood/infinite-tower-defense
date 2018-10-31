void chooseNewOrSavedMapToEditDialogResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateChooseNewOrSavedMapToEditDialogVariables();
}

void chooseNewOrSavedMapToEditDialogTextEntered()
{
	if (!chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog) return;

	if (event.text.unicode < 128)
		chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog->processCharacter(event.text.unicode);
}

void chooseNewOrSavedMapToEditDialogExit()
{
	if (chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog)
	{
		delete chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog;
		chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog = NULL;
	}
	startFunctions[0]();
}

void chooseNewOrSavedMapToEditDialogKeyPressed()
{
	if (event.key.code == sf::Keyboard::Escape)
		chooseNewOrSavedMapToEditDialogExit();
}

void chooseNewOrSavedMapToEditDialogMouseButtonPressed()
{
	if (chooseNewOrSavedMapToEditDialogNewMapButton->tryToPress(event.mouseButton.x, event.mouseButton.y)) return;
	chooseNewOrSavedMapToEditDialogSavedMapButton->tryToPress(event.mouseButton.x, event.mouseButton.y);
}

void chooseNewOrSavedMapToEditDialogMouseButtonReleased()
{
	chooseNewOrSavedMapToEditDialogNewMapButton->unpress();
	chooseNewOrSavedMapToEditDialogSavedMapButton->unpress();
}

void setChooseNewOrSavedMapToEditDialogEvents()
{
	events[1] = chooseNewOrSavedMapToEditDialogResized; //resized
	events[4] = chooseNewOrSavedMapToEditDialogTextEntered; //text entered
	events[5] = chooseNewOrSavedMapToEditDialogKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = nothing; //mouse wheel scrolled
	events[9] = chooseNewOrSavedMapToEditDialogMouseButtonPressed; //mouse button pressed
	events[10] = chooseNewOrSavedMapToEditDialogMouseButtonReleased; //mouse button released
	events[11] = nothing; //mouse moved
}
