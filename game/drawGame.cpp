void drawGame()
{
	window.clear(sf::Color::Black);
	
	gameMap->draw();

	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		(*i)->draw();

	drawGameInfo();
	drawTowersPanel();

	for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
		(*i)->draw();

	gameMap->drawCellSelector();
	if (addingTower) addingTower->draw();
	
	window.display();
}
