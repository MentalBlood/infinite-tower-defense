void drawMenu()
{
	window.clear(sf::Color::Black);
	for (unsigned int i = 0; i < menuEntries.size(); i++)
		window.draw(menuEntries[i]);
	window.display();
}
