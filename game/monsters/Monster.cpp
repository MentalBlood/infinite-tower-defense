class Monster;

void monsterCome(Monster*);

class Monster
{
	protected:
		sf::Vector2f position;
		const float radius,
					speed;

	private:
		sf::Transform	transform,
						rotationTransform;
		float scale,
			  currentRotatioAngle;

		unsigned int currentDirectionIndex;
		float distanceToNextDirectionLeft;

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

		void rotate(float angle)
		{
			rotationTransform.rotate(angle);
			currentRotatioAngle += angle;
		}

		void rotate(char direction)
		{
			if (direction == UP) rotate(-90 - currentRotatioAngle);
			else if (direction == DOWN) rotate(90 - currentRotatioAngle);
			else if (direction == RIGHT) rotate(0 - currentRotatioAngle);
			else if (direction == LEFT) rotate(180 - currentRotatioAngle);
		}

	protected:
		std::vector<sf::VertexArray> graphicalElements;

		void move(const sf::Vector2f &offset)
		{
			transform.translate(offset);
			position += offset*scale;
		}

		void changeScale(float delta)
		{
			transform.scale(sf::Vector2f(delta, delta));
			scale *= delta;
		}

	public:
		const unsigned int damage;

		Monster(unsigned int damage, const float speed, float health):
			position(sf::Vector2f(0, 0)), radius(gameMap->getCellSize() / 2.5), speed(speed),
			scale(1), currentRotatioAngle(0), currentDirectionIndex(0),
			distanceToNextDirectionLeft(gameMap->getCellSize()),
			health(health), came(false), dead(false), damage(damage)
		{
			rotate((*gameMap->getPathPointer())[0]);
		}

		void goToSpawnPoint()
		{
			move(gameMap->getSpawnPoint());
			changeScale(gameMap->getScale());
		}

		virtual ~Monster()
		{}

		void draw()
		{
			for (unsigned int i = 0; i < graphicalElements.size(); i++)
				window.draw(graphicalElements[i], transform * rotationTransform);
		}

		void moveInCorrectDirection()
		{ moveDistance(elapsed.asMilliseconds() * speed); }

		void drag()
		{
			transform.translate(gameDragOffset / scale);
			position += sf::Vector2f(gameDragOffset);
		}

		void drag(const sf::Vector2f & offset)
		{
			transform.translate(offset / scale);
			position += sf::Vector2f(offset);
		}

		void changeScale()
		{
			if ((gameScaleDelta < 1.0) && (scale < (0.1 / gameScaleDelta))) return;

			drag((gameScaleDelta - 1) * (position - gameScaleCenter));

			transform.scale(sf::Vector2f(gameScaleDelta, gameScaleDelta));
			scale *= gameScaleDelta;
		}

		void sufferDamage(float damage)
		{
			if (dead) return;
			if (damage >= health) dead = true;
			else health -= damage;
		}

		virtual void animate() =0;

		const sf::Vector2f & getPosition()
		{ return position; }

		float getScale()
		{ return scale; }

		bool isCame()
		{ return came; }

		bool isDead()
		{ return dead; }

		float getHealth()
		{ return health; }

		float getRadius()
		{ return radius; }

		void die()
		{ dead = true; }
};
