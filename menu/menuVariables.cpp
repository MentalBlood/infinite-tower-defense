sf::Color	menuFontColor(0, 175, 70),
			menuSelectedEntryColor(215, 215, 60);

unsigned int menuFontSize,
			 menuSelectedEntryNumber = 0;

float menuY1;

std::vector<sf::Text> menuEntries;
std::vector<void (*)()> menuFunctions;

void updateMenuVariables()
{
	menuFontSize = sqrt(windowSize.x * windowSize.y) / 16;
	menuY1 = float(windowSize.y) / 8;
	for (unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries[i].setCharacterSize(menuFontSize);
		menuEntries[i].setPosition(float(windowSize.x) / 16, menuY1 + i*menuFontSize*1.5);
	}
}

void setMenuVariables()
{
	if (menuEntries.size())
	{
		updateMenuVariables();
		return;
	}

	menuEntries.resize(5);
	menuFunctions.resize(5);

	updateMenuVariables();
	
	for (unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries[i].setFont(fonts[menuFont]);
		menuEntries[i].setFillColor(menuFontColor);
	}

	menuEntries[menuSelectedEntryNumber].setFillColor(menuSelectedEntryColor);

	menuEntries[0].setString("start");
	menuFunctions[0] = startSelectMapScreen;
	menuEntries[1].setString("developer mode");
	menuFunctions[1] = startDeveloperMode;
	menuEntries[2].setString("map editor");
	menuFunctions[2] = startChooseNewOrSavedMapToEditDialog;
	menuEntries[3].setString("help");
	menuFunctions[3] = startHelpScreen;
	menuEntries[4].setString("exit");
	menuFunctions[4] = Closed;
}

void clearMenuVariables()
{
	menuEntries.clear();
	menuFunctions.clear();
}
