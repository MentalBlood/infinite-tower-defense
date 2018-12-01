sf::Vector2f testMonsterPosition;
float distanceToNextDirectionLeft,
	  distanceCoveredByTower;
std::vector<char> *pathPointer;
unsigned int testMonsterCurrentDirectionIndex;
bool testMonsterCame,
	 coveredByTower;

void resetTestMonsterPosition()
{
	pathPointer = gameMap->getPathPointer();
	testMonsterPosition = gameMap->getRelativeSpawnPoint();
	testMonsterCurrentDirectionIndex = 0;
	distanceToNextDirectionLeft = gameMap->getCellSize();
	testMonsterCame = false;
}

float distanceFromTestMonsterToPointSquare(float x, float y)
{ return vectorLengthSquare(testMonsterPosition - sf::Vector2f(x, y)); }

float distanceFromTestMonsterToPoint(float x, float y)
{ return vectorLength(testMonsterPosition - sf::Vector2f(x, y)); }

void moveTestMonsterInCurrentDirection(float distance)
{
	if ((*pathPointer)[testMonsterCurrentDirectionIndex] == RIGHT)
		testMonsterPosition += sf::Vector2f(distance, 0);
	else if ((*pathPointer)[testMonsterCurrentDirectionIndex] == LEFT)
		testMonsterPosition += sf::Vector2f(-distance, 0);
	else if ((*pathPointer)[testMonsterCurrentDirectionIndex] == UP)
		testMonsterPosition += sf::Vector2f(0, -distance);
	else if ((*pathPointer)[testMonsterCurrentDirectionIndex] == DOWN)
		testMonsterPosition += sf::Vector2f(0, distance);
	if (coveredByTower)
		distanceCoveredByTower += distance;
}

void moveTestMonster(float distance)
{
	if (distanceToNextDirectionLeft < distance)
	{
		moveTestMonsterInCurrentDirection(distanceToNextDirectionLeft);
		++testMonsterCurrentDirectionIndex;
		if (testMonsterCurrentDirectionIndex == pathPointer->size())
		{
			testMonsterCame = true;
			return;
		}
		float distanceExcess = distance - distanceToNextDirectionLeft;
		distanceToNextDirectionLeft = gameMap->getCellSize();
		moveTestMonster(distanceExcess);
	}
	else
	{
		moveTestMonsterInCurrentDirection(distance);
		distanceToNextDirectionLeft -= distance;
	}
}

float getDistanceCoveredByTower(float towerPositionX, float towerPositionY, float towerDamageRadius)
{
	distanceCoveredByTower = 0;
	resetTestMonsterPosition();
	float realDamageRadius = towerDamageRadius + float(gameMap->getCellSize()) / 4.0;

	while (!testMonsterCame)
	{
		coveredByTower = (distanceFromTestMonsterToPoint(towerPositionX, towerPositionY) <=
						  realDamageRadius);
		float distanceToMove = fmax(float(gameMap->getCellSize()) / 32.0,
									abs(distanceFromTestMonsterToPoint(towerPositionX, towerPositionY) -
										realDamageRadius));
		//printf("testMonsterCurrentDirectionIndex = %u, distanceToMove = %f, distanceCoveredByTower = %f\n",
			   testMonsterCurrentDirectionIndex, distanceToMove, distanceCoveredByTower);
		moveTestMonster(distanceToMove);
	}
	return distanceCoveredByTower;
}

float getDistanceCoveredByTower(Tower *tower)
{
	sf::Vector2f towerRelativePosition  = tower->getRelativePosition();
	return getDistanceCoveredByTower(towerRelativePosition.x, towerRelativePosition.y,
									 tower->getParameterValue(RANGE));
}
