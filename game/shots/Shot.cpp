class Shot
{
	private:
		sf::Transform	transform,
						rotationTransform;
		sf::Vector2f position;

		bool finished;

		Tower *tower;
		Monster *monster;
		sf::Vector2f lastMonsterPosition;

		float scale,
			  currentRotatioAngle;

		void drag(const sf::Vector2f & offset)
		{
			transform.translate(offset / scale);
			position += sf::Vector2f(offset);
		}

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

		void rotate(float angle)
		{
			rotationTransform.rotate(angle);
			currentRotatioAngle += angle;
		}

		void rotateInDirection(float angle)
		{
			rotate(angle - currentRotatioAngle);
		}

		void rotateToMonster()
		{
			sf::Vector2f distanceVector = monster->getPosition() - position;
			float angle = 180.0 / M_PI * atan(distanceVector.y / distanceVector.x);
			if (distanceVector.x < 0) angle += 180;
			rotateInDirection(angle);
		}

	protected:
		std::vector<sf::VertexArray> graphicalElements;
		float radius;

	public:
		Shot(Tower *tower, Monster *monster):
		finished(false), tower(tower), monster(monster), lastMonsterPosition(monster->getPosition()),
		scale(1), currentRotatioAngle(0), radius(gameMap->getCellSize()/8)
		{
			changeScale(monster->getScale());
			drag(tower->getPosition());
			rotateToMonster();
		}

		virtual ~Shot()
		{}

		void drag()
		{
			transform.translate(gameDragOffset / scale);
			position += sf::Vector2f(gameDragOffset);
		}

		void move()
		{
			if (monster)
			{
				if (monster->isDead() || monster->isCame())
					monster = NULL;
				else
					lastMonsterPosition = monster->getPosition();
			}
			sf::Vector2f distanceVector = lastMonsterPosition - position;
			float distanceLength = sqrt(distanceVector.x * distanceVector.x
										+ distanceVector.y * distanceVector.y);
			if (!monster)
			{
				move(distanceVector / distanceLength * float(256 * elapsed.asSeconds()));
				if (distanceLength <= (gameMap->getCellSize() / 8 * scale))
					finished = true;
				return;
			}

			if (distanceLength <= (monster->getRadius() + radius) * scale)
			{
				monster->sufferDamage(tower->getDamage());
				finished = true;
			}
			else
			{
				rotateToMonster();
				move(distanceVector / distanceLength * float(256 * elapsed.asSeconds()));
			}
		}

		void changeScale()
		{
			if ((gameScaleDelta < 1.0) && (scale < (0.1 / gameScaleDelta))) return;

			drag((gameScaleDelta - 1) * (position - gameScaleCenter));

			transform.scale(sf::Vector2f(gameScaleDelta, gameScaleDelta));
			scale *= gameScaleDelta;
		}

		bool isFinished()
		{ return finished; }

		void draw()
		{
			for (unsigned int i = 0; i < graphicalElements.size(); i++)
				window.draw(graphicalElements[i], transform * rotationTransform);
		}

		virtual void animate() =0;
};
