void newMapSettingsResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateNewMapSettingsVariables();
}

void newMapSettingsExit()
{
	newMapSettings.clear();
	startFunctions[1]();
}

void newMapSettingsKeyPressed()
{
	if (event.key.code == sf::Keyboard::Up)
	{
		if (!newMapSettingsSelectedSettingNumber) return;
		newMapSettings[newMapSettingsSelectedSettingNumber].unselect();
		--newMapSettingsSelectedSettingNumber;
		newMapSettings[newMapSettingsSelectedSettingNumber].select();
	}
	else
	if (event.key.code == sf::Keyboard::Down)
	{
		if (newMapSettingsSelectedSettingNumber == newMapSettings.size()-1) return;
		newMapSettings[newMapSettingsSelectedSettingNumber].unselect();
		++newMapSettingsSelectedSettingNumber;
		newMapSettings[newMapSettingsSelectedSettingNumber].select();
	}
	else
	if (event.key.code == sf::Keyboard::Left)
		newMapSettings[newMapSettingsSelectedSettingNumber].decreaseValue();
	else
	if (event.key.code == sf::Keyboard::Right)
		newMapSettings[newMapSettingsSelectedSettingNumber].increaseValue();
	else
	if (event.key.code == sf::Keyboard::Return)
	{
		startMapEditor(newMapSettings[0].getValue(), newMapSettings[1].getValue());
		newMapSettings.clear();
	}
	else
	if (event.key.code == sf::Keyboard::Escape)
		newMapSettingsExit();
}

void newMapSettingsMouseButtonPressed()
{

}

void newMapSettingsMouseMoved()
{
	if (event.mouseMove.y < newMapSettingsY1)
	{
		newMapSettings[newMapSettingsSelectedSettingNumber].unselect();
		newMapSettingsSelectedSettingNumber = 0;
		newMapSettings[0].select();
		return;
	}

	if (event.mouseMove.y > newMapSettingsY1 + 1.5*newMapSettings.size()*newMapSettingsFontSize)
	{
		newMapSettings[newMapSettingsSelectedSettingNumber].unselect();
		newMapSettingsSelectedSettingNumber = newMapSettings.size()-1;
		newMapSettings[newMapSettings.size()-1].select();
		return;
	}

	int index = int(event.mouseMove.y - newMapSettingsY1) / (1.5*newMapSettingsFontSize);
	if (index == newMapSettingsSelectedSettingNumber) return;
	newMapSettings[newMapSettingsSelectedSettingNumber].unselect();
	newMapSettingsSelectedSettingNumber = index;
	newMapSettings[index].select();
}

void newMapSettingsMouseWheelScrolled()
{
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		if (event.mouseWheelScroll.delta > 0)
			newMapSettings[newMapSettingsSelectedSettingNumber].increaseValue();
		else
			newMapSettings[newMapSettingsSelectedSettingNumber].decreaseValue();
	}
}

void setNewMapSettingsEvents()
{
	events[1] = newMapSettingsResized; //resized
	events[4] = nothing; //text entered
	events[5] = newMapSettingsKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = newMapSettingsMouseWheelScrolled; //mouse wheel scrolled
	events[9] = newMapSettingsMouseButtonPressed; //mouse button pressed
	events[10] = nothing; //mouse button released
	events[11] = newMapSettingsMouseMoved; //mouse moved
}
