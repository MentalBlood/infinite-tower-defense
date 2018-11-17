class Shot : public GraphicalEntity
{
	private:
		bool finished;

		Tower *tower;
		Monster *monster;
		sf::Vector2f lastMonsterPosition;

		float distanceLeft;

	public:
		Shot(Tower *tower, Monster *monster):
		GraphicalEntity(tower->getPosition(), gameMap->getCellSize()/8, monster->getScale(), 0),
		finished(false), tower(tower), monster(monster), lastMonsterPosition(monster->getPosition()),
		distanceLeft(tower->getRange())
		{
			rotateToPoint(lastMonsterPosition);
		}

		virtual ~Shot()
		{}

		void updatePosition()
		{
			drag(gameDragOffset);
			if (!monster)
				lastMonsterPosition += sf::Vector2f(gameDragOffset);
		}

		void refreshLastMonsterPosition()
		{
			if (!monster) return;
			lastMonsterPosition = monster->getPosition();
			rotateToPoint(lastMonsterPosition);
		}

		void checkMonsterExistance()
		{
			if (!monster) return;
			if (monster->isDead() || monster->isCame())
				monster = NULL;
		}

		void moveCorrectly()
		{
			sf::Vector2f distanceVector = getDistanceVector(lastMonsterPosition);
			float distanceLength = sqrt(distanceVector.x * distanceVector.x
										+ distanceVector.y * distanceVector.y);
			sf::Vector2f unitDistanceVector = distanceVector / distanceLength;
			float maxDistanceToMove = 256 * elapsed.asSeconds();
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

			float minDistance = monster->getRadius() + radius;
			if ((distanceLength - maxDistanceToMove) <= (minDistance * scale))
			{
				move(unitDistanceVector * minDistance);
				monster->sufferDamage(tower->getDamage());
				finished = true;
			}
			else
			{
				move(unitDistanceVector * maxDistanceToMove);
				distanceLeft -= maxDistanceToMove;
			}
		}

		void updateScale()
		{ lastMonsterPosition += changeScale(gameScaleDelta, gameScaleCenter); }

		bool isFinished()
		{ return finished; }

		virtual void animate() =0;
};
