sf::Font menuFont;

sf::Color	menuFontColor(0, 175, 70),
			menuSelectedEntryColor(215, 215, 60);

int menuFontSize,
	menuSelectedEntryNumber = 0;

float menuY1;

sf::Text menuEntries[4];

void updateMenuVariables()
{
	menuFontSize = sqrt(windowSize.x*windowSize.y) / 20;
	menuY1 = float(windowSize.y) / 10;
	for (int i = 0; i < 4; i++)
	{
		menuEntries[i].setCharacterSize(menuFontSize);
		menuEntries[i].setPosition(sf::Vector2<float>(float(windowSize.x) / 20, menuY1 + i*menuFontSize*1.5));
	}
}

void setMenuVariables()
{
	if (!menuFont.loadFromFile("fonts/Signal-Regular.otf"))
		window.close();

	updateMenuVariables();
	
	for (int i = 0; i < 4; i++)
	{
		menuEntries[i].setFont(menuFont);
		menuEntries[i].setFillColor(menuFontColor);
	}

	menuEntries[menuSelectedEntryNumber].setFillColor(menuSelectedEntryColor);

	menuEntries[0].setString("start");
	menuEntries[1].setString("developer mode");
	menuEntries[2].setString("map editor");
	menuEntries[3].setString("exit");
}
