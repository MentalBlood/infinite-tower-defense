class Monster : public GraphicalEntity
{
	protected:
		sf::Vector2f position;
		float speed;

	private:
		unsigned int currentDirectionIndex;
		float distanceToNextDirectionLeft;

		const float initialHealth;
		float health;

		bool came,
			 dead;

		void functionAtArrive()
		{ came = true; }

		void moveDistanceInCurrentDirection(float distance)
		{
			if ((*gameMap->getPathPointer())[currentDirectionIndex] == RIGHT)
				move(sf::Vector2f(distance, 0));
			else if ((*gameMap->getPathPointer())[currentDirectionIndex] == LEFT)
				move(sf::Vector2f(-distance, 0));
			else if ((*gameMap->getPathPointer())[currentDirectionIndex] == UP)
				move(sf::Vector2f(0, -distance));
			else if ((*gameMap->getPathPointer())[currentDirectionIndex] == DOWN)
				move(sf::Vector2f(0, distance));
		}

		void moveDistance(float distance)
		{
			if (distanceToNextDirectionLeft < distance)
			{
				moveDistanceInCurrentDirection(distanceToNextDirectionLeft);
				++currentDirectionIndex;
				if (currentDirectionIndex == gameMap->getPathPointer()->size())
				{
					functionAtArrive();
					return;
				}
				float distanceExcess = distance - distanceToNextDirectionLeft;
				distanceToNextDirectionLeft = gameMap->getCellSize();
				rotate((*gameMap->getPathPointer())[currentDirectionIndex]);
				moveDistance(distanceExcess);
			}
			else
			{
				moveDistanceInCurrentDirection(distance);
				distanceToNextDirectionLeft -= distance;
			}
		}

		void rotate(char direction)
		{
			if (direction == UP) rotateInDirection(-90);
			else if (direction == DOWN) rotateInDirection(90);
			else if (direction == RIGHT) rotateInDirection(0);
			else if (direction == LEFT) rotateInDirection(180);
		}

	public:
		const unsigned int damage;

		Monster(unsigned int damage, const float speed, float healthArg):
		GraphicalEntity(sf::Vector2f(0, 0), gameMap->getCellSize() / 2.5, 1, 0),
		speed(speed), currentDirectionIndex(0), distanceToNextDirectionLeft(gameMap->getCellSize()),
		initialHealth(healthArg), health(healthArg), came(false), dead(false), damage(damage)
		{
			rotate((*gameMap->getPathPointer())[0]);
		}

		void goToSpawnPoint()
		{
			changeScale(gameMap->getScale());
			drag(gameMap->getSpawnPoint());
		}

		virtual ~Monster()
		{}

		void moveInCorrectDirection()
		{ moveDistance(elapsed.asMilliseconds() * speed); }

		void updatePosition()
		{ drag(gameDragOffset); }

//		void updateScaleWithoutShifting()
//		{ changeScale(gameScaleDelta); }

		void updateScale()
		{ changeScale(gameScaleDelta, gameScaleCenter); }

		void die()
		{
			collapse();
			dead = true;
		}

		void sufferDamage(float damage)
		{
			if (dead) return;
			if (damage >= health) die();
			else health -= damage;
		}

		virtual void animate() =0;

		bool isCame()
		{ return came; }

		bool isDead()
		{ return dead; }

		float getInitialHealth()
		{ return initialHealth; }

		float getHealth()
		{ return health; }

		unsigned int getDamage()
		{ return damage; }

		float getSpeed()
		{ return speed; }
};
