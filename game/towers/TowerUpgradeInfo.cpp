class TowerUpgradeInfo
{
	private:
		TowerSpecification *specification;
		sf::Sprite towerPreviewSprite;
		TwoConditionButton *button;
		static sf::VertexArray	border,
								fill;
		static float bordersThickness,
					 x, y, width, height;

		char textString[256],
			 buttonString[64];
		sf::Text text;

		static float textRelativeHeight,
					 buttonRelativeHeight;

	public:
		TowerUpgradeInfo(TowerSpecification *specification):
		specification(new TowerSpecification(specification)), towerPreviewSprite(sf::Sprite(specification->getTexture())),
		button(NULL)
		{
			text.setFont(fonts[towerInfoFont]);
			text.setFillColor(sf::Color(196, 255, 0));
			updatePositionAndSize();
		}

		void refreshText()
		{
			int charactersWritten = 0;
			for (unsigned int i = 0; i < towerParametersCount; i++)
			{
				if (i)
					charactersWritten += sprintf(textString + charactersWritten, "\n\n");
				charactersWritten += sprintf(textString + charactersWritten, "%s\n%-6.2f -> %6.2f",
											 towerParameterTypeName[i],
											 specification->getParameterValue(towerParameterType(i)),
											 specification->getNextParameterValue(towerParameterType(i)));
			}
			text.setString(sf::String(textString));
			fitTextIntoRectangle(&text, x + 2 * bordersThickness,
										(height - 4 * bordersThickness) * (1 - textRelativeHeight - buttonRelativeHeight),
										width - 4 * bordersThickness,
										height * textRelativeHeight);
		}

		void updateButtonPositionAndSize()
		{
			if (!button)
				button = new TwoConditionButton(nothing, nothing, "", upgradeButtonFont,
					sf::Color(196, 255, 0), sf::Color(16, 32, 64), sf::Color(8, 8, 8),
					towersPanelRelativeX + 2 * bordersThickness / windowSize.x,
					towersPanelRelativeY + (towersPanelRelativeHeight - 2 * bordersThickness / windowSize.y) * (1 - buttonRelativeHeight),
					towersPanelRelativeWidth - 4 * bordersThickness / windowSize.x,
					(towersPanelRelativeHeight - 2 * bordersThickness / windowSize.y) * buttonRelativeHeight,
					2);
			else
				button->updatePositionAndSize();
		}

		void refreshButtonText()
		{
			char costString[32];
			int costStringLength = sprintf( costString, "(costs %u)",
											specification->getUpgradeCost());
			char stringFormat[32];
			sprintf(stringFormat, "%%%ds\n%s", costStringLength - 2, costString);
			sprintf(buttonString, stringFormat, "upgrade");
			button->setString(buttonString);
		}

		void updatePositionAndSize()
		{
			x = towersPanelRelativeX * windowSize.x,
			y = towersPanelRelativeY * windowSize.y,
			width = towersPanelRelativeWidth * windowSize.x,
			height = towersPanelRelativeHeight * windowSize.y;
			bordersThickness = sqrt(width * height) / 64;

			makeVertexArrayFrame(&border, x, y, width, height, bordersThickness, sf::Color(8, 8, 8));
			makeVertexArrayQuad(&fill,
								x + bordersThickness, y + bordersThickness,
								width - 2 * bordersThickness, height - 2 * bordersThickness,
								sf::Color(8, 16, 32));

			float towerPreviewSpriteRealSize = minf((height - 4 * bordersThickness) * (1 - textRelativeHeight),
													  width - 4 * bordersThickness);
			towerPreviewSprite.setPosition(	x + width / 2 - towerPreviewSpriteRealSize / 2, 
											y + 2 * bordersThickness);
			towerPreviewSprite.setScale(towerPreviewSpriteRealSize
										/ towerPreviewSprite.getTexture()->getSize().x,
										towerPreviewSpriteRealSize
										/ towerPreviewSprite.getTexture()->getSize().y);

			refreshText();
			updateButtonPositionAndSize();
			refreshButtonText();
		}

		void tryToUpgrade()
		{
			if (specification->getUpgradeCost() > money) return;
			money -= specification->getUpgradeCost();
			specification->setNextValues();

			refreshText();
			refreshButtonText();
			updateMoneyText();
		}

		bool tryToPress(float mouseX, float mouseY)
		{
			bool valueToReturn = button->tryToPress(mouseX, mouseY);
			if (valueToReturn)
				tryToUpgrade();
			return valueToReturn;
		}

		void unpressButton()
		{ button->unpress(); }

		void draw()
		{
			window.draw(border);
			window.draw(fill);
			window.draw(towerPreviewSprite);
			window.draw(text);
			button->draw();
		}
};

float TowerUpgradeInfo::textRelativeHeight = 0.4,
	  TowerUpgradeInfo::buttonRelativeHeight = 0.2,
	  TowerUpgradeInfo::x,
	  TowerUpgradeInfo::y,
	  TowerUpgradeInfo::width,
	  TowerUpgradeInfo::height,
	  TowerUpgradeInfo::bordersThickness;
sf::VertexArray TowerUpgradeInfo::fill,
				TowerUpgradeInfo::border;
