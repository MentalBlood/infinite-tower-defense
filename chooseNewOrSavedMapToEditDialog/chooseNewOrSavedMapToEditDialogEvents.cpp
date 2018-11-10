void chooseNewOrSavedMapToEditDialogResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateChooseNewOrSavedMapToEditDialogVariables();
}

void chooseNewOrSavedMapToEditDialogTextEntered()
{
	if ((!chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog) || chooseNewOrSavedMapToEditDialogWrongFileNameMessage) return;

	if ((event.text.unicode < 128) && (event.key.code != 27))
		chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog->processCharacter(event.text.unicode);
}

void chooseNewOrSavedMapToEditDialogExit()
{
	if (chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog)
	{
		delete chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog;
		chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog = NULL;
	}
	startMenu();
}

void chooseNewOrSavedMapToEditDialogKeyPressed()
{
	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
	{
		if ((event.key.code == sf::Keyboard::Escape) || (event.key.code == 58)) //58 is Enter
			chooseNewOrSavedMapToEditDialogCloseWrongFileNameMessage();
		return;
	}

	if (chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog)
	{
		if (event.key.code == sf::Keyboard::Escape)
			chooseNewOrSavedMapToEditDialogCloseSavedMapFileNameDialog();
		return;
	}

	if (event.key.code == sf::Keyboard::Escape)
		chooseNewOrSavedMapToEditDialogExit();
}

void chooseNewOrSavedMapToEditDialogMouseButtonPressed()
{
	if (event.mouseButton.button != sf::Mouse::Left) return;
	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
	{
		chooseNewOrSavedMapToEditDialogWrongFileNameMessage->tryToPress(event.mouseButton.x, event.mouseButton.y);
		return;
	}
	if (chooseNewOrSavedMapToEditDialogNewMapButton->tryToPress(event.mouseButton.x, event.mouseButton.y)) return;
	chooseNewOrSavedMapToEditDialogSavedMapButton->tryToPress(event.mouseButton.x, event.mouseButton.y);
}

void chooseNewOrSavedMapToEditDialogMouseButtonReleased()
{
	if (event.mouseButton.button != sf::Mouse::Left) return;
	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
		chooseNewOrSavedMapToEditDialogWrongFileNameMessage->unpress();
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
