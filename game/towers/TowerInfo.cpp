class TowerInfo
{
	private:
		TowerSpecification *specification;
		sf::Sprite towerPreviewSprite;

		float relativeX,
			  relativeY,
			  relativeWidth,
			  relativeHeight,
			  x, y, width, height,
			  bordersThickness;

		sf::VertexArray borders, fill;

		sf::Font font;
		char textString[128];
		sf::Text text;

	public:
		static float relativeSeparatorPosition;

		TowerInfo(	TowerSpecification *specification,
					float relativeX, float relativeY, float relativeWidth, float relativeHeight):
		specification(specification), towerPreviewSprite(sf::Sprite(specification->getTexture())),
		relativeX(relativeX), relativeY(relativeY),
		relativeWidth(relativeWidth), relativeHeight(relativeHeight)
		{
			if (!font.loadFromFile("fonts/towerInfoFont.otf")) Closed();
			text.setFont(font);
			text.setFillColor(sf::Color(192, 64, 64));
			updatePositionAndSize();
		}

		~TowerInfo()
		{ delete specification; }

		void refreshText()
		{
			sprintf(textString, "damage: %.1f\nrange: %.1f\nshots/sec: %.2f\nshells speed: %.0f\n\nCOST: %u",
					specification->getDamage(),
					specification->getRange(),
					1.0 / specification->getShotsDelay(),
					specification->getShellsSpeed(),
					specification->getCost());
			text.setString(sf::String(textString));
			fitTextIntoRectangle(&text, x + width * relativeSeparatorPosition, y + 2*bordersThickness,
										width * (1 - relativeSeparatorPosition) - bordersThickness,
										height - 2 * bordersThickness);
		}

		void updatePositionAndSize()
		{
			x = windowSize.x * relativeX;
			y = windowSize.y * relativeY;
			width = windowSize.x * relativeWidth;
			height = windowSize.y * relativeHeight;
			bordersThickness = sqrt(width * height) / 64;

			makeVertexArrayFrame(&borders, x, y, width, height, bordersThickness,
								sf::Color(32, 128, 32, 192));
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2 * bordersThickness, height - 2 * bordersThickness,
								sf::Color(sf::Color(192, 192, 192)));
			refreshText();

			
			float towerPreviewSpriteRealSize = minf(height - 4 * bordersThickness, 
													(width - 5 * bordersThickness) * relativeSeparatorPosition);
			towerPreviewSprite.setPosition(	x + 5 * bordersThickness, 
											y + height / 2 - towerPreviewSpriteRealSize / 2);
			towerPreviewSprite.setScale(towerPreviewSpriteRealSize
										/ towerPreviewSprite.getTexture()->getSize().x,
										towerPreviewSpriteRealSize
										/ towerPreviewSprite.getTexture()->getSize().y);
		}

		void changePositionAndSize(	float newRelativeX, float newRelativeY,
									float newRelativeWidth, float newRelativeHeight)
		{
			relativeX = newRelativeX;
			relativeY = newRelativeY;
			relativeWidth = newRelativeWidth;
			relativeHeight = newRelativeHeight;

			updatePositionAndSize();
		}

		void draw()
		{
			window.draw(borders);
			window.draw(fill);
			window.draw(text);
			window.draw(towerPreviewSprite);
		}

		void click()
		{
			if (addingTower)
			{
				if ((money + addingTower->getCost()) < specification->getCost()) return;
				money += addingTower->getCost();
			}
			else
				if (money < specification->getCost()) return;
			money -= specification->getCost();
			updateMoneyText();
			addingTower = new Tower(specification);
		}
};

float TowerInfo::relativeSeparatorPosition = 0.25;
