void drawGame()
{
	window.clear(sf::Color::Black);
	gameMap->draw();
	for (unsigned int i = 0; i < monsters.size(); i++)
		monsters[i]->draw();
	window.display();
}
