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
		char textString[64];
		sf::Text text;

	public:
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
			sprintf(textString, "damage: %u\nrange: %.1f",
					specification->getDamage(),
					specification->getRange());
			text.setString(sf::String(textString));
			fitTextIntoRectangle(&text, x + width/2, y + 2*bordersThickness,
										width/2 - bordersThickness, height - 2*bordersThickness);
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
								width - 2*bordersThickness, height - 2*bordersThickness,
								sf::Color(sf::Color(192, 192, 192)));
			refreshText();

			
			float towerPreviewSpriteRealSize = minf(height - 4*bordersThickness, 
													(width - 2*bordersThickness)/2	);
			towerPreviewSprite.setPosition(	x + 2*bordersThickness, 
											y + height/2 - towerPreviewSpriteRealSize/2);
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
};
