float vectorLengthSquare(const sf::Vector2f & vector)
{ return vector.x * vector.x + vector.y * vector.y; }

float vectorLength(const sf::Vector2f & vector)
{ return sqrt(vector.x * vector.x + vector.y * vector.y); }

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

class Shot : public GraphicalEntity
{
	private:
		bool	finished,
				homing;

		Monster *monster;
		sf::Vector2f	initialMonsterPosition,
						lastMonsterPosition;

		float distanceLeft,
			  speed,
			  damage,
			  monsterRadius;

	public:
		Shot(Tower *tower, Monster *monster, float relativeRadius):
		GraphicalEntity(tower->getPosition(), gameMap->getCellSize() * relativeRadius, monster->getScale(), 0),
		finished(false), homing(tower->areShotsHoming()), monster(monster),
		initialMonsterPosition(monster->getPosition()), lastMonsterPosition(monster->getPosition()),
		distanceLeft(tower->getRange()), speed(tower->getShellsSpeed()), damage(tower->getDamage()),
		monsterRadius(monster->getRadius())
		{
			rotateToPoint(lastMonsterPosition);
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
			if (!monster) return;
			lastMonsterPosition = monster->getPosition();
			if (homing) rotateToPoint(lastMonsterPosition);
		}

		void checkMonsterExistance()
		{
			if (!monster) return;
			if (monster->isDead() || monster->isCame())
				monster = NULL;
		}

		void moveCorrectly()
		{
			if (homing)
			{
				sf::Vector2f distanceVector = getDistanceVector(lastMonsterPosition);
				float distanceLength = vectorLength(distanceVector);
				sf::Vector2f unitDistanceVector = distanceVector / distanceLength;
				float maxDistanceToMove = speed * elapsed.asSeconds();
				if (maxDistanceToMove > (distanceLeft * scale))
				{
					maxDistanceToMove = distanceLeft * scale;
					finished = true;
				}
				if (!monster)
				{
					if ((distanceLength - maxDistanceToMove) <= (radius * scale))
					{
						move(unitDistanceVector * radius);
						finished = true;
					}
					else
					{
						move(unitDistanceVector * maxDistanceToMove);
						distanceLeft -= maxDistanceToMove;
					}
					return;
				}

				float minDistance = monsterRadius + radius;
				if ((distanceLength - maxDistanceToMove) <= (minDistance * scale))
				{
					move(unitDistanceVector * minDistance);
					monster->sufferDamage(damage);
					finished = true;
				}
				else
				{
					move(unitDistanceVector * maxDistanceToMove);
					distanceLeft -= maxDistanceToMove;
				}
			}
			else //not homing
			{
				sf::Vector2f distanceVector = getDistanceVector(initialMonsterPosition);
				float distanceLength = vectorLength(distanceVector);
				sf::Vector2f unitDistanceVector = distanceVector / distanceLength;
				float maxDistanceToMove = speed * elapsed.asSeconds();
				if (maxDistanceToMove > (distanceLeft * scale))
				{
					maxDistanceToMove = distanceLeft * scale;
					finished = true;
				}
				if (!monster)
				{
					if ((distanceLength - maxDistanceToMove) <= (radius * scale))
					{
						move(unitDistanceVector * radius);
						finished = true;
					}
					else
					{
						move(unitDistanceVector * maxDistanceToMove);
						distanceLeft -= maxDistanceToMove;
					}
					return;
				}

				sf::Vector2f arrowHeadNow = getPosition() + unitDistanceVector * radius * scale;
				sf::Vector2f arrowHeadAfterMovement = arrowHeadNow
													+ unitDistanceVector * maxDistanceToMove;
				float a2 = vectorLengthSquare(arrowHeadAfterMovement - arrowHeadNow),
					  b2 = vectorLengthSquare(lastMonsterPosition - arrowHeadAfterMovement),
					  c2 = vectorLengthSquare(lastMonsterPosition - arrowHeadNow);
				float h2 = triangleHeightSquareFromSidesLengthsSquares(a2, b2, c2);
				if (h2 > monsterRadius) //passing by
				{
					move(unitDistanceVector * maxDistanceToMove);
					distanceLeft -= maxDistanceToMove;
					return;
				}

				float a = sqrt(a2);
				float distanceToMonster = a - sqrt(pow(monsterRadius * getScale(), 2) - h2) - sqrt(c2 - h2);
				if (distanceToMonster > a) //didn't reach
				{
					move(unitDistanceVector * maxDistanceToMove);
					distanceLeft -= maxDistanceToMove;
					return;
				}

				move(unitDistanceVector * distanceToMonster);
				monster->sufferDamage(damage);
				finished = true;
			}
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
