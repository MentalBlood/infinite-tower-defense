void drawNewMapSettings()
{
	window.clear(sf::Color::Black);
	for (int i = 0; i < newMapSettings.size(); i++)
		newMapSettings[i].draw();
	window.display();
}
