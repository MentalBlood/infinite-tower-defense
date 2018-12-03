void chooseNewOrSavedMapToEditDialogResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateChooseNewOrSavedMapToEditDialogVariables();
}

void chooseNewOrSavedMapToEditDialogExit()
{
	if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog)
		chooseNewOrSavedMapToEditDialogCloseChooseMapDialog();
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

	if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog)
	{
		if (event.key.code == sf::Keyboard::Up)
			chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->selectPrevious();
		else if (event.key.code == sf::Keyboard::Down)
			chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->selectNext();
		else if (event.key.code == sf::Keyboard::Return)
			chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->selectThis();
		else if (event.key.code == sf::Keyboard::Escape)
			chooseNewOrSavedMapToEditDialogCloseChooseMapDialog();
		return;
	}

	if (event.key.code == sf::Keyboard::Escape)
		chooseNewOrSavedMapToEditDialogExit();
}

void chooseNewOrSavedMapToEditDialogMouseWheelScrolled()
{
	if (!chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog) return;

	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		if (event.mouseWheelScroll.delta > 0)
			chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->selectPrevious();
		else
			chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->selectNext();
	}
}

void chooseNewOrSavedMapToEditDialogMouseButtonPressed()
{
	if (event.mouseButton.button != sf::Mouse::Left) return;

	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
	{
		if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage->tryToPress(event.mouseButton.x, event.mouseButton.y))
			return;
	}
	else
	if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog)
	{
		if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->selectThis(event.mouseButton.x, event.mouseButton.y))
			return;
	}
	else
	{
		if (chooseNewOrSavedMapToEditDialogNewMapButton->tryToPress(event.mouseButton.x, event.mouseButton.y)) return;
		chooseNewOrSavedMapToEditDialogSavedMapButton->tryToPress(event.mouseButton.x, event.mouseButton.y);
	}
}

void chooseNewOrSavedMapToEditDialogMouseButtonReleased()
{
	if (event.mouseButton.button != sf::Mouse::Left) return;
	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
		chooseNewOrSavedMapToEditDialogWrongFileNameMessage->unpress();
	chooseNewOrSavedMapToEditDialogNewMapButton->unpress();
	chooseNewOrSavedMapToEditDialogSavedMapButton->unpress();
}

void chooseNewOrSavedMapToEditDialogMouseMoved()
{
	if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog)
		chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->selectByMouse(event.mouseMove.x, event.mouseMove.y);
}

void setChooseNewOrSavedMapToEditDialogEvents()
{
	events[1] = chooseNewOrSavedMapToEditDialogResized; //resized
	events[4] = nothing; //text entered
	events[5] = chooseNewOrSavedMapToEditDialogKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = chooseNewOrSavedMapToEditDialogMouseWheelScrolled; //mouse wheel scrolled
	events[9] = chooseNewOrSavedMapToEditDialogMouseButtonPressed; //mouse button pressed
	events[10] = chooseNewOrSavedMapToEditDialogMouseButtonReleased; //mouse button released
	events[11] = chooseNewOrSavedMapToEditDialogMouseMoved; //mouse moved
}
