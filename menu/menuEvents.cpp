void menuResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateMenuVariables();
}

void menuKeyPressed()
{
	if (event.key.code == sf::Keyboard::Up)
	{
		if (!menuSelectedEntryNumber) return;
		menuEntries[menuSelectedEntryNumber].setFillColor(menuFontColor);
		--menuSelectedEntryNumber;
		menuEntries[menuSelectedEntryNumber].setFillColor(menuSelectedEntryColor);
	}
	else
	if (event.key.code == sf::Keyboard::Down)
	{
		if ((menuSelectedEntryNumber+1) == menuEntries.size()) return;
		menuEntries[menuSelectedEntryNumber].setFillColor(menuFontColor);
		++menuSelectedEntryNumber;
		menuEntries[menuSelectedEntryNumber].setFillColor(menuSelectedEntryColor);
	}
	else
	if (event.key.code == sf::Keyboard::Return)
		menuFunctions[menuSelectedEntryNumber]();
}

void menuMouseButtonPressed()
{
	if (event.mouseButton.button == sf::Mouse::Left)
		menuFunctions[menuSelectedEntryNumber]();
}

void menuMouseMoved()
{
	if (event.mouseMove.y < menuY1)
	{
		menuEntries[menuSelectedEntryNumber].setFillColor(menuFontColor);
		menuSelectedEntryNumber = 0;
		menuEntries[0].setFillColor(menuSelectedEntryColor);
		return;
	}

	if (event.mouseMove.y > menuY1 + 1.5*menuEntries.size()*menuFontSize)
	{
		menuEntries[menuSelectedEntryNumber].setFillColor(menuFontColor);
		menuSelectedEntryNumber = menuEntries.size()-1;
		menuEntries[menuEntries.size()-1].setFillColor(menuSelectedEntryColor);
		return;
	}

	int index = int(event.mouseMove.y - menuY1) / (1.5*menuFontSize);
	if (index == int(menuSelectedEntryNumber)) return;
	menuEntries[menuSelectedEntryNumber].setFillColor(menuFontColor);
	menuSelectedEntryNumber = index;
	menuEntries[index].setFillColor(menuSelectedEntryColor);
}

void setMenuEvents()
{
	events[1] = menuResized; //resized
	events[4] = nothing; //text entered
	events[5] = menuKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = nothing; //mouse wheel scrolled
	events[9] = menuMouseButtonPressed; //mouse button pressed
	events[10] = nothing; //mouse button released
	events[11] = menuMouseMoved; //mouse moved
}
