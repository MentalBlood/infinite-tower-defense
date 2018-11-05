void spawn()
{
	//monsters.push_back(ModelA(gameMap->getSpawnPoint(), 19, gameMap->getCellTextureSize() / 2.5, 60, gameMap));
	monsters.push_back(ModelB(	gameMap->getSpawnPoint(), 25, gameMap->getCellTextureSize() / 2.5,
								sf::Color(0, 0, 0, 0), sf::Color(80, 80, 80),
								sf::Color(80, 80, 80, 0), sf::Color(180, 180, 180),
								gameMap));
	monsters[monsters.size()-1].changeScale(gameMap->getScale());
}
