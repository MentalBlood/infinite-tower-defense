float vectorLengthSquare(const sf::Vector2f & vector)
{ return vector.x * vector.x + vector.y * vector.y; }

float vectorLength(const sf::Vector2f & vector)
{ return sqrt(vector.x * vector.x + vector.y * vector.y); }

sf::Vector2f unitVector(sf::Vector2f distanceVector)
{ return distanceVector / vectorLength(distanceVector); }

sf::Vector2f unitVector(sf::Vector2f & A, sf::Vector2f & B)
{
	sf::Vector2f distanceVector = B - A;
	return distanceVector / vectorLength(distanceVector);
}

float triangleHeightSquareFromSidesLengthsSquares(float a2, float b2, float c2)
{ return (b2 + c2 - (a2 + pow(b2 - c2, 2) / a2) / 2) / 2; }

float triangleHeightSquare(float a, float b, float c)
{
	float a2 = a*a,
		  b2 = b*b,
		  c2 = c*c;

	return (b2 + c2 - (a2 + pow(b2 - c2, 2) / a2) / 2) / 2;
}

float triangleHeightSquare(sf::Vector2f & A, sf::Vector2f & B, sf::Vector2f & C)
{
	float a2 = vectorLengthSquare(B - C),
		  b2 = vectorLengthSquare(A - C),
		  c2 = vectorLengthSquare(A - B);

	return (b2 + c2 - (a2 + pow(b2 - c2, 2) / a2) / 2) / 2;
}

sf::Vector2f solveQuadraticEquation(float a, float b, float c)
{
	float D = b*b - 4*a*c;
	if (D < 0) return sf::Vector2f(-1, -1);
	float sqrtD = sqrt(D);
	return sf::Vector2f(-b/2 + sqrtD, -b/2 - sqrtD);
}

sf::Vector2f vectorsMultiplication(sf::Vector2f a, sf::Vector2f b)
{ return sf::Vector2f(a.x * b.x, a.y * b.y); }

class Shot : public GraphicalEntity
{
	private:
		bool	finished,
				homing;

		Monster *monster;
		sf::Vector2f	initialMonsterPosition,
						lastMonsterPosition,
						unitMovementVector;

		float distanceLeft,
			  speed,
			  damage,
			  monsterRadius;

	public:
		Shot(Tower *tower, Monster *monster, float relativeRadius):
		GraphicalEntity(tower->getPosition(), gameMap->getCellSize() * relativeRadius, monster->getScale(), 0),
		finished(false), homing(tower->areShotsHoming()), monster(monster),
		initialMonsterPosition(monster->getPosition()), lastMonsterPosition(monster->getPosition()),
		unitMovementVector(unitVector(getDistanceVector(monster->getPosition()))),
		distanceLeft(tower->getRange()), speed(tower->getShellsSpeed()), damage(tower->getDamage()),
		monsterRadius(monster->getRadius())
		{
			rotateToPoint(initialMonsterPosition);
		}

		virtual ~Shot()
		{}

		void updatePosition()
		{
			drag(gameDragOffset);
			if (!homing)
				initialMonsterPosition += sf::Vector2f(gameDragOffset);
			if (!monster)
				lastMonsterPosition += sf::Vector2f(gameDragOffset);
		}

		void refreshLastMonsterPosition()
		{
			if (!monster || !homing) return;
			lastMonsterPosition = monster->getPosition();
			rotateToPoint(lastMonsterPosition);
			unitMovementVector = unitVector(getDistanceVector(lastMonsterPosition));
		}

		void checkMonsterExistance()
		{
			if (!monster || !homing) return;
			if (monster->isDead() || monster->isCame())
				monster = NULL;
		}

		void moveInCorrectDirection(float distance)
		{
			move(unitMovementVector * distance);
			distanceLeft -= distance;
		}

		void moveCorrectlyUsingGrid()
		{
			printf("moveCorrectlyUsingGrid\n");
			float maxDistanceToMove = speed * elapsed.asSeconds();
			if (maxDistanceToMove > (distanceLeft * scale))
			{
				maxDistanceToMove = distanceLeft * scale;
				finished = true;
			}

			std::list<Monster*> *monstersWhichCanTouch = getMonstersWhichCanTouch(getPosition());
			sf::Vector2f movementVector = unitMovementVector * maxDistanceToMove;
			if (!monstersWhichCanTouch)
			{
				moveInCorrectDirection(maxDistanceToMove);
				return;
			}

			sf::Vector2f positionAfterMovement = getPosition() +  movementVector;

			for (	std::list<Monster*>::iterator i = monstersWhichCanTouch->begin();
					i != monstersWhichCanTouch->end(); i++)
			{
				sf::Vector2f monsterPosition = (*i)->getPosition();
				float R2 = pow((radius + (*i)->getRadius()) * scale, 2);
				if (vectorLengthSquare(monsterPosition - positionAfterMovement) < R2)
				{	//have already reached
					(*i)->sufferDamage(damage);
					finished = true;
					continue;
				}

				float a2 = vectorLengthSquare(positionAfterMovement - getPosition()),
					  b2 = vectorLengthSquare(monsterPosition - positionAfterMovement),
					  c2 = vectorLengthSquare(monsterPosition - getPosition());
				float h2 = triangleHeightSquareFromSidesLengthsSquares(a2, b2, c2);

				if ((h2 > R2) || //passing by
					(vectorLength(vectorsMultiplication(monsterPosition - getPosition(), positionAfterMovement - getPosition())) > vectorLengthSquare(positionAfterMovement - getPosition()))) //did not reach
					continue;

				(*i)->sufferDamage(damage); //will reach after the movement
				finished = true;
			}

			if (!finished) moveInCorrectDirection(maxDistanceToMove);
			printf("moved\n");
		}

		void updateScale()
		{
			sf::Vector2f shift = changeScale(gameScaleDelta, gameScaleCenter);
			lastMonsterPosition += shift;
			if (!homing)
				initialMonsterPosition += shift;
		}

		bool isFinished()
		{ return finished; }

		virtual void animate() =0;
};
