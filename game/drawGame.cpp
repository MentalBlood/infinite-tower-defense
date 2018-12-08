void drawGame()
{
	window.clear(sf::Color::Black);
	windowSize = window.getSize();
	
	gameMap->draw();

	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		(*i)->draw();

	for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
		(*i)->draw();

	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
		(*i)->draw();

	gameMap->drawCellSelector();
	if (addingTower) addingTower->draw();

	drawSplinters();

	if (printTowersLevels)
		for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
			(*i)->drawLevelText();

	drawGameInfo();
	if (towersPanelOpened)
	{
		if (currentShowingUpgradeInfoTower)
			currentShowingUpgradeInfoTower->getUpgradeInfo()->draw();
		else
			drawTowersPanel();
	}
	towersPanelOpenCloseButton->draw();
	gameHelpButton->draw();
	
	window.display();
}
