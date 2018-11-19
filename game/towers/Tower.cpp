class Tower
{
	private:
		TowerSpecification *specification;
		float rangeSquare;
		sf::Sprite sprite;

	public:
		Tower(TowerSpecification *specification):
		specification(specification), rangeSquare(specification->getRange() * specification->getRange()),
		sprite(specification->getTexture())
		{
			sprite.setTextureRect(sf::IntRect(0, 0, gameMap->getCellSize(), gameMap->getCellSize()));
			sprite.setOrigin(gameMap->getCellSize()/2, gameMap->getCellSize()/2);
			goToCellSelector();
			refreshScale();
		}

		~Tower()
		{}

		void drag()
		{ sprite.move(gameDragOffset); }

		void goToCellSelector()
		{
			sprite.setPosition(gameMap->getSelectorPosition()
			+ gameMap->getScale() * sf::Vector2f(gameMap->getCellSize()/2, gameMap->getCellSize()/2));
		}

		void refreshScale()
		{ sprite.setScale(sf::Vector2f(gameMap->getScale(), gameMap->getScale())); }

		void changeScale()
		{
			if ((gameScaleDelta < 1.0) && (sprite.getScale().x < (0.1 / gameScaleDelta))) return;
			refreshScale();
			sprite.move((gameScaleDelta - 1) * (sprite.getPosition() - gameScaleCenter));
		}

		void draw()
		{ window.draw(sprite); }

		bool havePoint(const sf::Vector2f & point)
		{
			sf::Vector2f position = sprite.getPosition();
			return	((point.x < (position.x + gameMap->getRealCellSize()/2)) &&
					(point.x > (position.x - gameMap->getRealCellSize()/2)) &&
					(point.y < (position.y + gameMap->getRealCellSize()/2)) &&
					(point.y > (position.y - gameMap->getRealCellSize()/2)));
		}

		const sf::Vector2f & getPosition()
		{ return sprite.getPosition(); }

		float getRangeSquare()
		{ return rangeSquare; }

		float getShotsDelay()
		{ return specification->getShotsDelay(); }

		char getShotType()
		{ return specification->getShotType(); }

		float getDamage()
		{ return specification->getDamage(); }

		float getRange()
		{ return specification->getRange(); }

		float getShellsSpeed()
		{ return specification->getShellsSpeed(); }

		unsigned int getCost()
		{ return specification->getCost(); }
};
