void newMapSettingsResized()
{
	windowSize = window.getSize();
	window.setView(sf::View(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y))));
	updateNewMapSettingsVariables();
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
		startMapEditor(newMapSettings[0].getValue(), newMapSettings[1].getValue());
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

	if (event.mouseMove.y > newMapSettingsY1 + 6*newMapSettingsFontSize)
	{
		newMapSettings[newMapSettingsSelectedSettingNumber].unselect();
		newMapSettingsSelectedSettingNumber = newMapSettings.size()-1;
		newMapSettings[newMapSettings.size()-1].select();
		return;
	}

	int index = int(event.mouseMove.y - newMapSettingsY1) / (6.0/newMapSettings.size()*newMapSettingsFontSize);
	if (index == newMapSettingsSelectedSettingNumber) return;
	newMapSettings[newMapSettingsSelectedSettingNumber].unselect();
	newMapSettingsSelectedSettingNumber = index;
	newMapSettings[index].select();
}

void setNewMapSettingsEvents()
{
	events[1] = newMapSettingsResized; //resized
	events[4] = nothing; //text entered
	events[5] = newMapSettingsKeyPressed; //key pressed
	events[6] = nothing; //key released
	events[8] = nothing; //mouse wheel scrolled
	events[9] = newMapSettingsMouseButtonPressed; //mouse button pressed
	events[10] = nothing; //mouse button released
	events[11] = newMapSettingsMouseMoved; //mouse moved
}
