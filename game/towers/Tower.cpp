class Tower
{
	private:
		TowerSpecification *specification;
		sf::Sprite sprite;

	public:
		Tower(TowerSpecification *specification):
		specification(specification), sprite(specification->getTexture())
		{
			sprite.setTextureRect(sf::IntRect(0, 0, gameMap->getCellSize(), gameMap->getCellSize()));
			goToCellSelector();
			refreshScale();
		}

		~Tower()
		{}

		void drag()
		{ sprite.move(gameDragOffset); }

		void goToCellSelector()
		{ sprite.setPosition(gameMap->getSelectorPosition()); }

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
};
