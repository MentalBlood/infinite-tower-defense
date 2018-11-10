void drawGame()
{
	window.clear(sf::Color::Black);
	gameMap->draw();
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		(*i)->draw();
	drawGameInfo();
	window.display();
}
