void drawMenu()
{
	window.clear(sf::Color::Black);
	for (int i = 0; i < 4; i++) window.draw(menuEntries[i]);
	window.display();
}
