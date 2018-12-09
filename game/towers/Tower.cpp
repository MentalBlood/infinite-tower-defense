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
		const sf::Vector2f positionOnMap;
		bool drawRangeCircle;
		GraphicalEntity *rangeCircle;
		unsigned int currentLevel;
		char levelString[16];
		sf::Text levelText;
		TowerUpgradeInfo *upgradeInfo;

	public:
		Tower(TowerSpecification *specificationToCopy):
		specification(new TowerSpecification(specificationToCopy)), rangeSquare(pow(specification->getParameterValue(RANGE) + float(gameMap->getCellSize()) / 4.0, 2)),
		sprite(specification->getTexture()), positionOnMap(gameMap->getRelativeSelectorPosition()),
		drawRangeCircle(true), rangeCircle(NULL), currentLevel(1), levelString("1")
		{
			upgradeInfo = new TowerUpgradeInfo(specification);
			refreshRangeCircle();
			sprite.setTextureRect(sf::IntRect(0, 0, gameMap->getCellSize(), gameMap->getCellSize()));
			sprite.setOrigin(gameMap->getCellSize()/2, gameMap->getCellSize()/2);
			goToCellSelector();
			sprite.setScale(sf::Vector2f(gameMap->getScale(), gameMap->getScale()));
			levelText.setFont(fonts[towerUpgradeInfoFont]);
			levelText.setString(levelString);
			levelText.setFillColor(sf::Color(255, 255, 255, 196));
			refreshLevelTextPositionAndSize();
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

			rangeSquare = pow(specification->getParameterValue(RANGE) +
							  float(gameMap->getCellSize()) / 4.0, 2);
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

		void refreshLevelTextPositionAndSize()
		{
			fitTextIntoRectangle(&levelText,
								 sprite.getPosition().x - gameMap->getRealCellSize() / 2,
								 sprite.getPosition().y - gameMap->getRealCellSize() / 2,
								 gameMap->getRealCellSize(),
								 gameMap->getRealCellSize());
		}

		void printNextLevel()
		{
			++currentLevel;
			sprintf(levelString, "%d", currentLevel);
			levelText.setString(levelString);
			refreshLevelTextPositionAndSize();
		}

		void drag()
		{
			sprite.move(gameDragOffset);
			rangeCircle->drag(gameDragOffset);
			levelText.move(gameDragOffset);
		}

		void goToCellSelector()
		{
			sf::Vector2f newPosition = gameMap->getSelectorPosition()
			+ gameMap->getScale() * sf::Vector2f(gameMap->getCellSize()/2, gameMap->getCellSize()/2);
			sprite.setPosition(newPosition);
			rangeCircle->dragTo(newPosition);
			refreshLevelTextPositionAndSize();
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

			refreshLevelTextPositionAndSize();

			rangeCircle->changeScale(gameScaleDelta, gameScaleCenter);
		}

		void draw()
		{
			if (drawRangeCircle)
				rangeCircle->draw();
			window.draw(sprite);
		}

		void drawLevelText()
		{ window.draw(levelText); }

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

		void upgrade()
		{
			if (specification->getParameterValue(UPGRADE_COST) > money) return;
			money -= specification->getParameterValue(UPGRADE_COST);
			upgradeAnyway();
		}

		void upgradeAnyway()
		{
			specification->setNextValues();
			upgradeInfo->refreshText();
			upgradeInfo->refreshButtonText();
			updateMoneyText();
			refreshRangeCircle();
			printNextLevel();
		}

		const sf::Vector2f & getPosition()
		{ return sprite.getPosition(); }

		const sf::Vector2f & getRelativePosition()
		{ return positionOnMap; }

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
