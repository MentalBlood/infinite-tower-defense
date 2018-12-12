void drawSelectMapScreen()
{
	window.clear(sf::Color::Black);
	selectMapScreenMapsList->draw();
	if (selectMapScreenDeleteMapQuestion)
		selectMapScreenDeleteMapQuestion->draw();
	window.display();
}
