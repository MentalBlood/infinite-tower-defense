sf::Vector2u mapSize;
sf::Vector2f mapPosition;
std::vector<std::vector<std::list<Monster*> > > *grid = NULL;

void setGrid()
{
	mapPosition = gameMap->getPosition();
	mapSize = gameMap->getMapSize();
	grid = new std::vector<std::vector<std::list<Monster*> > >;
	grid->resize(mapSize.x);
	for (unsigned int i = 0; i < mapSize.x; i++)
		(*grid)[i].resize(mapSize.y);
}

void deleteGrid()
{
	delete grid;
	grid = NULL;
}

void clearGrid()
{
	for (unsigned int i = 0; i < mapSize.x; i++)
		for (unsigned int j = 0; j < mapSize.y; j++)
			(*grid)[i][j].clear();
}

void addMonsterInGridCell(Monster *monster, unsigned int x, unsigned int y)
{
	(*grid)[x][y].push_back(monster);
}

void updateMonsterInGrid(Monster *monster)
{
	sf::Vector2f floatCoordinatesInGrid =
		(monster->getPosition() - mapPosition) / gameMap->getRealCellSize();
	sf::Vector2u coordinatesInGrid = sf::Vector2u(	int(floatCoordinatesInGrid.x),
													int(floatCoordinatesInGrid.y));
	addMonsterInGridCell(monster, coordinatesInGrid.x, coordinatesInGrid.y);

	sf::Vector2f coordinatesRelativeToGridCell =
		sf::Vector2f(	floatCoordinatesInGrid.x - coordinatesInGrid.x,
						floatCoordinatesInGrid.y - coordinatesInGrid.y);

	if ((coordinatesInGrid.x != 0) && (coordinatesRelativeToGridCell.x < 0.5))
		addMonsterInGridCell(monster, coordinatesInGrid.x - 1, coordinatesInGrid.y);
	else
	if ((coordinatesInGrid.x < (mapSize.x - 1)) && (coordinatesRelativeToGridCell.x > 0.5))
		addMonsterInGridCell(monster, coordinatesInGrid.x + 1, coordinatesInGrid.y);
	else
	if ((coordinatesInGrid.y != 0) && (coordinatesRelativeToGridCell.y < 0.5))
		addMonsterInGridCell(monster, coordinatesInGrid.x, coordinatesInGrid.y - 1);
	else
	if ((coordinatesInGrid.y < (mapSize.y - 1)) && (coordinatesRelativeToGridCell.y > 0.5))
		addMonsterInGridCell(monster, coordinatesInGrid.x, coordinatesInGrid.y + 1);
}

sf::Vector2i getCoordinatesInGrid(sf::Vector2f absoluteCoordinates)
{
	sf::Vector2f floatCoordinatesInGrid =
		(absoluteCoordinates - mapPosition) / gameMap->getRealCellSize();
	return sf::Vector2i(int(floatCoordinatesInGrid.x),
						int(floatCoordinatesInGrid.y));
}

void removeMonsterFromGridCell(Monster *monster, unsigned int x, unsigned int y)
{
	std::list<Monster*> *listWithThisMonster = &(*grid)[x][y];

	for (std::list<Monster*>::iterator i = listWithThisMonster->begin();
		i != listWithThisMonster->end(); i++)
		if ((*i) == monster)
		{
			listWithThisMonster->erase(i);
			return;
		}
}

void removeMonsterFromGrid(Monster *monster)
{
	sf::Vector2f floatCoordinatesInGrid =
		(monster->getPosition() - mapPosition) / gameMap->getRealCellSize();
	sf::Vector2u coordinatesInGrid = sf::Vector2u(	int(floatCoordinatesInGrid.x),
													int(floatCoordinatesInGrid.y));
	removeMonsterFromGridCell(monster, coordinatesInGrid.x, coordinatesInGrid.y);

	sf::Vector2f coordinatesRelativeToGridCell =
		sf::Vector2f(	floatCoordinatesInGrid.x - coordinatesInGrid.x,
						floatCoordinatesInGrid.y - coordinatesInGrid.y);

	if ((coordinatesInGrid.x != 0) && (coordinatesRelativeToGridCell.x < 0.5))
		removeMonsterFromGridCell(monster, coordinatesInGrid.x - 1, coordinatesInGrid.y);
	else
	if ((coordinatesInGrid.x < (mapSize.x - 1)) && (coordinatesRelativeToGridCell.x > 0.5))
		removeMonsterFromGridCell(monster, coordinatesInGrid.x + 1, coordinatesInGrid.y);
	else
	if ((coordinatesInGrid.y != 0) && (coordinatesRelativeToGridCell.y < 0.5))
		removeMonsterFromGridCell(monster, coordinatesInGrid.x, coordinatesInGrid.y - 1);
	else
	if ((coordinatesInGrid.y < (mapSize.y - 1)) && (coordinatesRelativeToGridCell.y > 0.5))
		removeMonsterFromGridCell(monster, coordinatesInGrid.x, coordinatesInGrid.y + 1);
}

void updateMonstersCoordinatesInGrid()
{
	clearGrid();
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		updateMonsterInGrid((*i));
}

std::list<Monster*>* getMonstersWhichCanTouch(sf::Vector2f & position)
{
	sf::Vector2i coordinatesInGrid = getCoordinatesInGrid(position);
	if ((coordinatesInGrid.x < 0) || (coordinatesInGrid.x >= int(mapSize.x))) return NULL;
	if ((coordinatesInGrid.y < 0) || (coordinatesInGrid.y >= int(mapSize.y))) return NULL;
	return &(*grid)[coordinatesInGrid.x][coordinatesInGrid.y];
}
