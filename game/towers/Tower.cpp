void changeBool(bool *something)
{
	if (*something == true)
		*something = false;
	else
		*something = true;
}

class Tower
{
	private:
		TowerSpecification *specification;
		float rangeSquare;
		sf::Sprite sprite;
		bool drawRangeCircle;
		GraphicalEntity *rangeCircle;

	public:
		Tower(TowerSpecification *specification):
		specification(specification), rangeSquare(specification->getRange() * specification->getRange()),
		sprite(specification->getTexture()), drawRangeCircle(true)
		{
			std::vector<sf::VertexArray> *rangeCircleGraphicalElements =
										new std::vector<sf::VertexArray>;
			rangeCircleGraphicalElements->resize(1);
			makeVertexArrayRing(&(*rangeCircleGraphicalElements)[0], 0, 0, 0, specification->getRange(),
								64, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
			rangeCircle = new GraphicalEntity(rangeCircleGraphicalElements,
						sf::Vector2f(0, 0), specification->getRange(), 1, 0);
			rangeCircle->changeScale(gameMap->getScale());
			sprite.setTextureRect(sf::IntRect(0, 0, gameMap->getCellSize(), gameMap->getCellSize()));
			sprite.setOrigin(gameMap->getCellSize()/2, gameMap->getCellSize()/2);
			goToCellSelector();
			sprite.setScale(sf::Vector2f(gameMap->getScale(), gameMap->getScale()));
		}

		~Tower()
		{}

		void drag()
		{
			sprite.move(gameDragOffset);
			rangeCircle->drag(gameDragOffset);
		}

		void goToCellSelector()
		{
			sf::Vector2f newPosition = gameMap->getSelectorPosition()
			+ gameMap->getScale() * sf::Vector2f(gameMap->getCellSize()/2, gameMap->getCellSize()/2);
			sprite.setPosition(newPosition);
			rangeCircle->dragTo(newPosition);
		}

		void refreshScale()
		{
			sprite.setScale(sf::Vector2f(gameMap->getScale(), gameMap->getScale()));
			rangeCircle->changeScale(gameScaleDelta);
		}

		void changeScale()
		{
			sprite.setScale(sf::Vector2f(gameMap->getScale(), gameMap->getScale()));
			sprite.move((gameScaleDelta - 1) * (sprite.getPosition() - gameScaleCenter));

			rangeCircle->changeScale(gameScaleDelta, gameScaleCenter);
		}

		void draw()
		{
			if (drawRangeCircle)
				rangeCircle->draw();
			window.draw(sprite);
		}

		bool havePoint(const sf::Vector2f & point)
		{
			sf::Vector2f position = sprite.getPosition();
			return	((point.x < (position.x + gameMap->getRealCellSize()/2)) &&
					(point.x > (position.x - gameMap->getRealCellSize()/2)) &&
					(point.y < (position.y + gameMap->getRealCellSize()/2)) &&
					(point.y > (position.y - gameMap->getRealCellSize()/2)));
		}

		void showRangleCircle()
		{ drawRangeCircle = true; }

		void hideRangeCircle()
		{ drawRangeCircle = false; }

		void showHideRangeCircle()
		{ changeBool(&drawRangeCircle); }

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
