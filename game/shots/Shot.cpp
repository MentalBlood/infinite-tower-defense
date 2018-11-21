float vectorLength(const sf::Vector2f & vector)
{ return sqrt(vector.x * vector.x + vector.y * vector.y); }

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
			/*else //not homing
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

				sf::Vector2f arrowHeadNow = position + unitDistanceVector * radius;
				sf::Vector2f arrowHeadAfterMovement = arrowHeadNow
													+ unitDistanceVector * maxDistanceToMove;
				float minDistance = monsterRadius + radius;
				if ((vectorLength(getDistanceVector(lastMonsterPosition)))
					<= (minDistance * scale))
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
			}*/
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
