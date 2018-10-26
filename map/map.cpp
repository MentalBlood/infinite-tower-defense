#define UP 1
#define RIGHT 2
#define LEFT 3
#define DOWN 4

#define EMPTY 0
#define PATH 1
#define BEGIN 2
#define END 3

class Map
{
	private:
		int mapHeight, mapWidth,
			x1, y1,
			x2, y2;

		float mapPositionX,
			  mapPositionY,
			  zoom;

		unsigned int cellTextureSize;
		float realCellTextureSize;

		sf::Texture *towerCellTexture,
					*pathCellTexture,
					*cellSelectorTexture,
					*startCellTexture,
					*endCellTexture;

		sf::Sprite	towerCellSprite,
					pathCellSprite,
					cellSelectorSprite,
					startCellSprite,
					endCellSprite;

		int cellSelectorX,
			cellSelectorY;

		bool cellSelectorPressed;

		sf::Color	towerCellBordersColor,
					towerCellFillColor,
					cellSelectorColor;

		std::vector<char> path;
		std::vector<std::vector<char> > pathMap;

		void createPathMap()
		{
			pathMap.resize(mapWidth);
			for (int i = 0; i < mapWidth; i++)
			{
				pathMap[i].resize(mapHeight);
				for (int j = 0; j < mapHeight; j++)
					pathMap[i][j] = 0;
			}
		}

		void clearPathMap()
		{
			for (int i = 0; i < pathMap.size(); i++)
				for (int j = 0; j < pathMap[i].size(); j++)
					pathMap[i][j] = 0;
		}

	public:
		Map(int width, int height,
			sf::Color towerCellBordersColor, sf::Color towerCellFillColor, sf::Color cellSelectorColor):
			x1(0), y1(0), x2(width - 1), y2(height - 1), zoom(1),
			towerCellTexture(NULL), pathCellTexture(NULL), cellSelectorTexture(NULL), startCellTexture(NULL), endCellTexture(NULL),
			towerCellBordersColor(towerCellBordersColor), towerCellFillColor(towerCellFillColor),
			cellSelectorColor(cellSelectorColor), cellSelectorPressed(false)
		{
			mapWidth = width;
			mapHeight = height;
			createPathMap();

			pathMap[0][0] = 2;
			pathMap[width-1][height-1] = 3;
		}

		Map(char *fileName)
		{
			loadFile(fileName);
		}

		~Map()
		{
			delete towerCellTexture;
			delete pathCellTexture;
			delete cellSelectorTexture;
		}

		void loadFile(char *fileName)
		{
			FILE *file = fopen(fileName, "rb");
			fscanf(file, "%d%d%d%d", &mapWidth, &mapHeight, &x1, &y1);

			//read path
			x2 = x1;
			y2 = y1;
			while (true)
			{
				char c = char(fgetc(file));
				if (!c) break;
				if (c == RIGHT) ++x2;
				else if (c == LEFT) --x2;
				else if (c == UP) --y2;
				else if (c == DOWN) ++y2;
				path.push_back(c);
			}

			createPathMap();
		}

		void setTextures(float cellRelativeSize)
		{
			//1 drawing tower cell texture
			cellTextureSize = 32;
			realCellTextureSize = cellTextureSize * zoom;
			sf::RenderTexture RenderTexture;
			if (!RenderTexture.create(cellTextureSize, cellTextureSize)) Closed();
			RenderTexture.clear(sf::Color(0, 0, 0, 0));

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

			RenderTexture.clear(sf::Color(0, 0, 0, 0));
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

			//5 drawing cell selector texture
			if (!RenderTexture.create(cellTextureSize, cellTextureSize));

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

		void setPosition(float x, float y)
		{
			mapPositionX = x;
			mapPositionY = y;
		}

		void zoomTextures()
		{
			towerCellSprite.setScale(zoom, zoom);
			pathCellSprite.setScale(zoom, zoom);
			cellSelectorSprite.setScale(zoom, zoom);
			startCellSprite.setScale(zoom, zoom);
			endCellSprite.setScale(zoom, zoom);

			realCellTextureSize = cellTextureSize * zoom;
		}

		void changeZoom(float delta, float mouseX, float mouseY)
		{
			if ((delta < 1.0) && (zoom < (0.1 / delta))) return;

			float correctionDelta = realCellTextureSize * (delta - 1),
				  realMapWidth = mapWidth * realCellTextureSize,
				  realMapHeight = mapHeight * realCellTextureSize;
			mapPositionX -= mapWidth * correctionDelta * ((mouseX - mapPositionX) / realMapWidth);
			mapPositionY -= mapHeight * correctionDelta * ((mouseY - mapPositionY) / realMapHeight);

			zoom *= delta;
			zoomTextures();
		}

		sf::Vector2f getPosition()
		{ return sf::Vector2f(mapPositionX, mapPositionY); }

		void pressOnCell()
		{
			if (pathMap[cellSelectorX][cellSelectorY] == EMPTY)
				pathMap[cellSelectorX][cellSelectorY] = PATH;
			else
			if (pathMap[cellSelectorX][cellSelectorY] == PATH)
				pathMap[cellSelectorX][cellSelectorY] = EMPTY;
		}

		void pressCellSelector()
		{
			if (cellSelectorPressed) return;
			cellSelectorPressed = true;
			pressOnCell();
		}

		void unpressCellSelector()
		{
			cellSelectorPressed = false;
		}

		void moveCellSelector(char direction)
		{
			printf("moveCellSelector\n");
			if (direction == LEFT)
			{
				if (cellSelectorX) --cellSelectorX;
			}
			else
			if (direction == RIGHT)
			{
				if ((cellSelectorX+1) < mapWidth) ++cellSelectorX;
			}
			else
			if (direction == DOWN)
			{
				if ((cellSelectorY+1) < mapHeight) ++cellSelectorY;
			}
			else
			if (direction == UP)
			{
				if (cellSelectorY) --cellSelectorY;
			}

			if (cellSelectorPressed) pressOnCell();
		}

		void moveCellSelectorToMouse(float x, float y)
		{
			int selectedCellX = int((x - mapPositionX) / realCellTextureSize),
				selectedCellY = int((y - mapPositionY) / realCellTextureSize);

			if ((selectedCellX == cellSelectorX) && (selectedCellY == cellSelectorY)) return;
			
			if ((selectedCellX < 0) || (selectedCellX >= mapWidth) ||
				(selectedCellY < 0) || (selectedCellY >= mapHeight)) return;
			cellSelectorX = selectedCellX;
			cellSelectorY = selectedCellY;

			if (cellSelectorPressed) pressOnCell();
		}

		void draw()
		{
			float cellSpriteX = mapPositionX, 
				  cellSpriteY = mapPositionY;

			for (int i = 0; i < pathMap.size(); i++, cellSpriteX += realCellTextureSize)
			{
				for (int j = 0; j < pathMap[i].size(); j++, cellSpriteY += realCellTextureSize)
				{
					if (pathMap[i][j])
					{
						pathCellSprite.setPosition(cellSpriteX, cellSpriteY);
						window.draw(pathCellSprite);
					}
					else
					{
						towerCellSprite.setPosition(cellSpriteX, cellSpriteY);
						window.draw(towerCellSprite);
					}
				}
				cellSpriteY = mapPositionY;
			}

			startCellSprite.setPosition(x1*realCellTextureSize + mapPositionX, y1*realCellTextureSize + mapPositionY);
			window.draw(startCellSprite);

			endCellSprite.setPosition(x2*realCellTextureSize + mapPositionX, y2*realCellTextureSize + mapPositionY);
			window.draw(endCellSprite);

			cellSelectorSprite.setPosition(cellSelectorX * realCellTextureSize + mapPositionX,
											cellSelectorY * realCellTextureSize + mapPositionY);
			window.draw(cellSelectorSprite);
		}
};
