void drawSelectMapScreen()
{
	printf("drawSelectMapScreen\n");
	window.clear(sf::Color::Black);
	selectMapScreenMapsList->draw();
	window.display();
	printf("drawed\n");
}
