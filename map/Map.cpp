class Map
{
	protected:
		unsigned int	mapWidth, mapHeight,
						x1, y1,
						x2, y2;

		float mapPositionX,
			  mapPositionY,
			  zoom;

		unsigned int	cellSelectorX,
						cellSelectorY;

		sf::Texture *towerCellTexture,
					*pathCellTexture,
					*cellSelectorTexture,
					*startCellTexture,
					*endCellTexture,
					*rockCellTexture;

		sf::Color	towerCellBordersColor,
					towerCellFillColor,
					cellSelectorColor;

		bool cellSelectorPressed;

		unsigned int cellTextureSize;
		float realCellTextureSize;

		sf::Sprite	towerCellSprite,
					pathCellSprite,
					cellSelectorSprite,
					startCellSprite,
					endCellSprite,
					rockCellSprite;

		std::vector<char> path;
		std::vector<std::vector<char> > pathMap;

		void zoomTextures()
		{
			towerCellSprite.setScale(zoom, zoom);
			pathCellSprite.setScale(zoom, zoom);
			cellSelectorSprite.setScale(zoom, zoom);
			startCellSprite.setScale(zoom, zoom);
			endCellSprite.setScale(zoom, zoom);
			rockCellSprite.setScale(zoom, zoom);

			realCellTextureSize = cellTextureSize * zoom;
		}

	public:
		Map(unsigned int width, unsigned int height,
			sf::Color towerCellBordersColor, sf::Color towerCellFillColor, sf::Color cellSelectorColor):
		mapWidth(width), mapHeight(height), x1(0), y1(0), x2(width - 1), y2(height - 1), zoom(1),
		cellSelectorX(0), cellSelectorY(0),
		towerCellTexture(NULL), pathCellTexture(NULL), cellSelectorTexture(NULL), startCellTexture(NULL),
		endCellTexture(NULL), rockCellTexture(NULL),
		towerCellBordersColor(towerCellBordersColor), towerCellFillColor(towerCellFillColor),
		cellSelectorColor(cellSelectorColor), cellSelectorPressed(false)
		{}

		void setPosition(float x, float y)
		{
			mapPositionX = x;
			mapPositionY = y;
		}

		void draw()
		{
			float cellSpriteX = mapPositionX, 
				  cellSpriteY = mapPositionY;

			for (unsigned int i = 0; i < pathMap.size(); i++, cellSpriteX += realCellTextureSize)
			{
				if (((cellSpriteX + realCellTextureSize) < 0) || (cellSpriteX > windowSize.x)) continue;
				for (unsigned int j = 0; j < pathMap[i].size(); j++, cellSpriteY += realCellTextureSize)
				{
					if (((cellSpriteY + realCellTextureSize) < 0) || (cellSpriteY > windowSize.y)) continue;
					if (pathMap[i][j] == PATH)
					{
						pathCellSprite.setPosition(cellSpriteX, cellSpriteY);
						window.draw(pathCellSprite);
					}
					else
					if (pathMap[i][j] == EMPTY)
					{
						towerCellSprite.setPosition(cellSpriteX, cellSpriteY);
						window.draw(towerCellSprite);
					}
					else
					if (pathMap[i][j] == ROCK)
					{
						rockCellSprite.setPosition(cellSpriteX, cellSpriteY);
						window.draw(rockCellSprite);
					}
				}
				cellSpriteY = mapPositionY;
			}

			startCellSprite.setPosition(x1*realCellTextureSize + mapPositionX, y1*realCellTextureSize + mapPositionY);
			window.draw(startCellSprite);

			endCellSprite.setPosition(x2*realCellTextureSize + mapPositionX, y2*realCellTextureSize + mapPositionY);
			window.draw(endCellSprite);
		}

		void drawCellSelector()
		{
			cellSelectorSprite.setPosition(cellSelectorX * realCellTextureSize + mapPositionX,
											cellSelectorY * realCellTextureSize + mapPositionY);
			window.draw(cellSelectorSprite);
		}

		void setTextures(float cellRelativeSize)
		{
			//1 drawing tower cell texture
			cellTextureSize = 32;
			realCellTextureSize = cellTextureSize * zoom;
			sf::RenderTexture RenderTexture;
			if (!RenderTexture.create(cellTextureSize, cellTextureSize)) Closed();
			RenderTexture.clear(sf::Color(16, 32, 16));

			//1.1 drawing borders
			float cellSize = cellTextureSize * cellRelativeSize;
			float indent = (cellTextureSize - cellSize) / 2;
			float bordersThickness = cellSize / 8;
			sf::VertexArray borders;
			makeVertexArrayFrame(&borders, indent, indent, cellSize, cellSize, bordersThickness, towerCellBordersColor);

			//1.2 drawing fill
			sf::VertexArray fill;
			makeVertexArrayQuad(&fill, indent + bordersThickness, indent + bordersThickness,
								cellSize - 2*bordersThickness, cellSize - 2*bordersThickness,
								towerCellFillColor);

			RenderTexture.draw(borders);
			RenderTexture.draw(fill);
			RenderTexture.display();

			//1.3 setting texture to sprite
			if (towerCellTexture) delete towerCellTexture;
			towerCellTexture = new sf::Texture(RenderTexture.getTexture());
			towerCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			towerCellSprite.setTexture(*towerCellTexture);

			//2 drawing path cell texture
			if (!RenderTexture.create(cellTextureSize, cellTextureSize)) Closed();

			RenderTexture.clear(sf::Color(16, 32, 16));
			RenderTexture.display();

			//setting texture to sprite
			if (pathCellTexture) delete pathCellTexture;
			pathCellTexture = new sf::Texture(RenderTexture.getTexture());
			pathCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			pathCellSprite.setTexture(*pathCellTexture);

			//3 setting start cell texture
			if (!startCellTexture) delete startCellTexture;
			startCellTexture = new sf::Texture();
			startCellTexture->loadFromFile("textures/startCell.png");
			startCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			startCellSprite.setTexture(*startCellTexture);

			//4 setting end cell texture
			if (!endCellTexture) delete endCellTexture;
			endCellTexture = new sf::Texture();
			endCellTexture->loadFromFile("textures/endCell.png");
			endCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			endCellSprite.setTexture(*endCellTexture);

			//5 setting rock cell texture
			if (!rockCellTexture) delete rockCellTexture;
			rockCellTexture = new sf::Texture();
			rockCellTexture->loadFromFile("textures/rockCell.png");
			rockCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			rockCellSprite.setTexture(*rockCellTexture);

			//6 drawing cell selector texture
			if (!RenderTexture.create(cellTextureSize, cellTextureSize)) Closed();

			sf::VertexArray cellSelectorVertexArray;
			makeVertexArrayFrame(&cellSelectorVertexArray, 0, 0, cellTextureSize, cellTextureSize,
														indent, cellSelectorColor);

			RenderTexture.clear(sf::Color(0, 0, 0, 0));
			RenderTexture.draw(cellSelectorVertexArray);
			RenderTexture.display();

			//setting texture to sprite
			if (cellSelectorTexture) delete cellSelectorTexture;
			cellSelectorTexture = new sf::Texture(RenderTexture.getTexture());
			cellSelectorSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			cellSelectorSprite.setTexture(*cellSelectorTexture);
		}

		sf::Vector2f fitInRectangle(sf::Vector2f rectangleRelativePosition,
									sf::Vector2f rectangleRelativeSize)
		{
			windowSize = window.getSize();
			float realMapWidth = mapWidth * cellTextureSize,
				  realMapHeight = mapHeight * cellTextureSize;
			sf::Vector2f rectangleSize = sf::Vector2f(	rectangleRelativeSize.x * windowSize.x,
														rectangleRelativeSize.y * windowSize.y);
			if ((rectangleSize.x / rectangleSize.y) <= (realMapWidth / realMapHeight))
				zoom = rectangleSize.x / realMapWidth;
			else
				zoom = rectangleSize.y / realMapHeight;
			zoomTextures();

			realMapWidth = mapWidth * realCellTextureSize;
			realMapHeight = mapHeight * realCellTextureSize;

			float oldMapPositionX = mapPositionX,
				  oldMapPositionY = mapPositionY;

			mapPositionX = rectangleRelativePosition.x * windowSize.x
							+ (rectangleSize.x - realMapWidth) / 2;
			mapPositionY = rectangleRelativePosition.y * windowSize.y
							+ (rectangleSize.y - realMapHeight) / 2;

			return sf::Vector2f(mapPositionX - oldMapPositionX, mapPositionY - oldMapPositionY);
		}

		sf::Vector2f getCellCoordinates(unsigned int x, unsigned int y)
		{
			return sf::Vector2f(x * realCellTextureSize + mapPositionX,
								y * realCellTextureSize + mapPositionY);
		}
};
