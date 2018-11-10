void drawGameOverScreen()
{
	printf("drawGameOverScreen\n");
	window.clear(sf::Color::Black);
	gameOverScreenMessage->draw();
	window.display();
	printf("OK\n");
}
