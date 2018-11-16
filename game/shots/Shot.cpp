class Shot
{
	private:
		sf::Transform	transform,
						rotationTransform;
		sf::Vector2f position;
		bool finished;

		void drag(const sf::Vector2f & offset)
		{
			transform.translate(offset / scale);
			position += sf::Vector2f(offset);
		}

		void changeScale(float delta)
		{
			transform.scale(sf::Vector2f(delta, delta));
			scale *= delta;
		}

	protected:
		Tower *tower;
		Monster *monster;

		std::vector<sf::VertexArray> graphicalElements;

		float scale,
			  currentRotatioAngle;

		void move(const sf::Vector2f &offset)
		{
			transform.translate(offset);
			position += offset*scale;
		}

	public:
		Shot(Tower *tower, Monster *monster):
		finished(false), tower(tower), monster(monster), scale(1), currentRotatioAngle(0)
		{
			changeScale(monster->getScale());
			drag(tower->getPosition());
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
			sf::Vector2f distanceVector = monster->getPosition() - position;
			float distanceLength = sqrt(distanceVector.x * distanceVector.x
										+ distanceVector.y * distanceVector.y);
			if (distanceLength <= (gameMap->getCellSize() / 8.0 * scale))
			{
				monster->sufferDamage(tower->getDamage());
				finished = true;
			}
			else
				move(distanceVector / distanceLength * float(512 * elapsed.asSeconds()));
		}

		void changeScale()
		{
			if ((gameScaleDelta < 1.0) && (scale < (0.1 / gameScaleDelta))) return;

			drag((gameScaleDelta - 1) * (position - gameScaleCenter));

			transform.scale(sf::Vector2f(gameScaleDelta, gameScaleDelta));
			scale *= gameScaleDelta;
		}

		bool monsterDead()
		{
			return (monster->isCame() || monster->isDead() || finished);
		}

		void draw()
		{
			for (unsigned int i = 0; i < graphicalElements.size(); i++)
				window.draw(graphicalElements[i], transform * rotationTransform);
		}

		virtual void animate() =0;
};
