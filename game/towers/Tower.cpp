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
		TowerUpgradeInfo *upgradeInfo;

	public:
		Tower(TowerSpecification *specificationToCopy):
		specification(new TowerSpecification(specificationToCopy)), rangeSquare(specification->getParameterValue(RANGE) * specification->getParameterValue(RANGE)),
		sprite(specification->getTexture()), drawRangeCircle(true), rangeCircle(NULL)
		{
			upgradeInfo = new TowerUpgradeInfo(specification);
			refreshRangeCircle();
			sprite.setTextureRect(sf::IntRect(0, 0, gameMap->getCellSize(), gameMap->getCellSize()));
			sprite.setOrigin(gameMap->getCellSize()/2, gameMap->getCellSize()/2);
			goToCellSelector();
			sprite.setScale(sf::Vector2f(gameMap->getScale(), gameMap->getScale()));
		}

		~Tower()
		{
			delete upgradeInfo;
			delete specification;
			delete rangeCircle;
		}

		void refreshRangeCircle()
		{
			if (rangeCircle)
			{
				if (specification->getParameterValue(RANGE) == rangeCircle->getRadius())
					return;
				else
					delete rangeCircle;
			}

			rangeSquare = pow(specification->getParameterValue(RANGE), 2);
			std::vector<sf::VertexArray> *rangeCircleGraphicalElements =
										new std::vector<sf::VertexArray>;
			rangeCircleGraphicalElements->resize(1);
			makeVertexArrayCircle(&(*rangeCircleGraphicalElements)[0], 0, 0, specification->getParameterValue(RANGE),
								64, sf::Color::Transparent, sf::Color(255, 255, 255, 128));
			rangeCircle = new GraphicalEntity(rangeCircleGraphicalElements,
						sf::Vector2f(0, 0), specification->getParameterValue(RANGE), 1, 0);
			rangeCircle->changeScale(gameMap->getScale());
			rangeCircle->drag(sprite.getPosition());
		}

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

		void changeScale(float delta)
		{
			sprite.scale(delta, delta);
			rangeCircle->changeScale(delta);
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

		char getShotType()
		{ return specification->getShotType(); }

		bool areShotsHoming()
		{ return specification->areShotsHoming(); }

		float getParameterValue(enum towerParameterType parameterType)
		{ return specification->getParameterValue(parameterType); }

		unsigned int getCost()
		{ return specification->getCost(); }

		unsigned int getCostWithUpgrades()
		{ return specification->getCostWithUpgrades(); }

		TowerUpgradeInfo* getUpgradeInfo()
		{ return upgradeInfo; }
};
