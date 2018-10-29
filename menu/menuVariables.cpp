sf::Font menuFont;

sf::Color	menuFontColor(0, 175, 70),
			menuSelectedEntryColor(215, 215, 60);

int menuFontSize,
	menuSelectedEntryNumber = 0;

float menuY1;

sf::Text menuEntries[4];
void (*menuFunctions[4])();

void updateMenuVariables()
{
	menuFontSize = sqrt(windowSize.x * windowSize.y) / 16;
	menuY1 = float(windowSize.y) / 8;
	for (int i = 0; i < 4; i++)
	{
		menuEntries[i].setCharacterSize(menuFontSize);
		menuEntries[i].setPosition(float(windowSize.x) / 16, menuY1 + i*menuFontSize*1.5);
	}
}

void setMenuVariables()
{
	if (!menuFont.loadFromFile("fonts/menuFont.otf")) Closed();

	updateMenuVariables();
	
	for (int i = 0; i < 4; i++)
	{
		menuEntries[i].setFont(menuFont);
		menuEntries[i].setFillColor(menuFontColor);
	}

	menuEntries[menuSelectedEntryNumber].setFillColor(menuSelectedEntryColor);

	menuEntries[0].setString("start");
	menuFunctions[0] = nothing;
	menuEntries[1].setString("developer mode");
	menuFunctions[1] = nothing;
	menuEntries[2].setString("map editor");
	menuFunctions[2] = startChooseNewOrSavedMapToEditDialog;
	menuEntries[3].setString("exit");
	menuFunctions[3] = Closed;
}
