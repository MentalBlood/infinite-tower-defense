class Monster
{
	protected:
		sf::Vector2f position;

	private:
		const float radius;
		sf::Transform transform;
		float scale;

		unsigned int currentDirectionIndex;
		float distanceToNextDirectionLeft;

		const std::vector<char> *path;
		const unsigned int *mapCellSize;

		void functionAtArrive()
		{
			changeScale(0.3);
		}

		void moveDistanceInCurrentDirection(float distance)
		{
			if ((*path)[currentDirectionIndex] == RIGHT)
				move(sf::Vector2f(distance, 0));
			else if ((*path)[currentDirectionIndex] == LEFT)
				move(sf::Vector2f(-distance, 0));
			else if ((*path)[currentDirectionIndex] == UP)
				move(sf::Vector2f(0, -distance));
			else if ((*path)[currentDirectionIndex] == DOWN)
				move(sf::Vector2f(0, distance));
		}

		void moveDistance(float distance)
		{
			printf("move distance %f\n", distance);
			if (distanceToNextDirectionLeft < distance)
			{
				moveDistanceInCurrentDirection(distanceToNextDirectionLeft);
				++currentDirectionIndex;
				if (currentDirectionIndex == path->size())
				{
					functionAtArrive();
					return;
				}
				float distanceExcess = distance - distanceToNextDirectionLeft;
				distanceToNextDirectionLeft = *mapCellSize;
				moveDistance(distanceExcess);
			}
			else
			{
				moveDistanceInCurrentDirection(distance);
				distanceToNextDirectionLeft -= distance;
			}
		}

	protected:
		std::vector<sf::VertexArray> graphicalElements;

	public:
		Monster(sf::Vector2f position, float radius, MapForPlaying *map):
			position(position), radius(radius), scale(1), currentDirectionIndex(0),
			distanceToNextDirectionLeft(*map->getCellSize()), path(map->getPathPointer()), mapCellSize(map->getCellSize())
		{}

		void draw()
		{
			for (unsigned int i = 0; i < graphicalElements.size(); i++)
				window.draw(graphicalElements[i], transform);
		}

		void move(const sf::Vector2f &offset)
		{
			transform.translate(offset);
			position += offset*scale;
		}

		void moveInCorrectDirection()
		{
			float elapsedMilliseconds = elapsed.asMilliseconds();
			printf("elapsed %f milliseconds, move distance is %f\n", elapsedMilliseconds, elapsedMilliseconds/16);
			moveDistance(elapsed.asMilliseconds()/16);
		}

		void drag(const sf::Vector2f &offset)
		{
			transform.translate(offset / scale);
			position += sf::Vector2f(offset);
		}

		void rotate(float angle)
		{ transform.rotate(angle, sf::Vector2f(0, 0)); }

		void changeScale(float delta)
		{
			transform.scale(sf::Vector2f(delta, delta));
			scale *= delta;
		}

		void changeScale(float delta, const sf::Vector2f &center)
		{
			if ((delta < 1.0) && (scale < (0.1 / delta))) return;

			sf::Vector2f shift = (delta - 1) * (position - center);
			drag(shift);

			transform.scale(sf::Vector2f(delta, delta));
			scale *= delta;
		}

		sf::Vector2f getPosition()
		{ return position; }

		float getScale()
		{ return scale; }
};
