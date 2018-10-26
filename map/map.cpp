#define UP 1
#define RIGHT 2
#define LEFT 3
#define DOWN 4

class Map
{
	private:
		int mapHeight, mapWidth,
			x1, y1,
			x2, y2;
		float mapPositionX, mapPositionY,
			  zoom;

		unsigned int cellTextureSize;
		float realCellTextureSize;
		sf::Texture *towerCellTexture,
					*pathCellTexture,
					*cellSelectorTexture;
		sf::Sprite	towerCellSprite,
					pathCellSprite,
					cellSelectorSprite;
		sf::Color	towerCellBordersColor,
					towerCellFillColor,
					cellSelectorColor;

		std::vector<char> path;
		std::vector<std::vector<bool> > pathMap;

	public:
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

		Map(int width, int height,
			sf::Color towerCellBordersColor, sf::Color towerCellFillColor, sf::Color cellSelectorColor):
			x1(0), y1(0), x2(1), y2(0), zoom(1), towerCellTexture(NULL), pathCellTexture(NULL), cellSelectorTexture(NULL),
			towerCellBordersColor(towerCellBordersColor), towerCellFillColor(towerCellFillColor),
			cellSelectorColor(cellSelectorColor)
		{
			mapWidth = width;
			mapHeight = height;
			createPathMap();

			path.push_back(RIGHT);

			pathMap[0][0] = true;
			pathMap[1][0] = true;
		}

		Map(char *fileName): towerCellTexture(NULL), pathCellTexture(NULL), cellSelectorTexture(NULL), zoom(1)
		{
			loadFile(fileName);
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
			printf("setTextures\n");
			//1 drawing tower cell texture
			cellTextureSize = 32;
			realCellTextureSize = cellTextureSize * zoom;
			sf::RenderTexture towerCellRenderTexture;
			if (!towerCellRenderTexture.create(cellTextureSize, cellTextureSize)) Closed();
			towerCellRenderTexture.clear(sf::Color(0, 0, 0, 0));

			//1.1 drawing borders
			printf("drawing borders\n");
			float cellSize = cellTextureSize * cellRelativeSize;
			float indent = (cellTextureSize - cellSize) / 2;
			float bordersThickness = cellSize / 8;
			sf::VertexArray borders;
			makeVertexArrayFrame(&borders, indent, indent, cellSize, cellSize, bordersThickness, towerCellBordersColor);

			//1.2 drawing fill
			printf("drawing fill\n");
			sf::VertexArray fill;
			makeVertexArrayQuad(&fill, indent + bordersThickness, indent + bordersThickness,
								cellSize - 2*bordersThickness, cellSize - 2*bordersThickness,
								towerCellFillColor);

			towerCellRenderTexture.draw(borders);
			towerCellRenderTexture.draw(fill);
			towerCellRenderTexture.display();

			//1.3 setting texture to sprite
			printf("setting texture to sprite\n");
			if (towerCellTexture) delete towerCellTexture;
			towerCellTexture = new sf::Texture(towerCellRenderTexture.getTexture());
			towerCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			towerCellSprite.setTexture(*towerCellTexture);

			//2 drawing path cell texture
			printf("drawing path cell texture\n");
			sf::RenderTexture pathCellRenderTexture;
			if (!pathCellRenderTexture.create(cellTextureSize, cellTextureSize)) Closed();

			pathCellRenderTexture.clear(sf::Color(0, 0, 0, 0));
			pathCellRenderTexture.display();

			//setting texture to sprite
			printf("setting texture to sprite\n");
			if (pathCellTexture) delete pathCellTexture;
			pathCellTexture = new sf::Texture(pathCellRenderTexture.getTexture());
			pathCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			pathCellSprite.setTexture(*pathCellTexture);

			//3 drawing cell selector texture
			printf("drawing cell selector texture\n");
			sf::RenderTexture cellSelectorRenderTexture;
			if (!cellSelectorRenderTexture.create(cellTextureSize, cellTextureSize));

			sf::VertexArray cellSelectorVertexArray;
			makeVertexArrayFrame(&cellSelectorVertexArray, 0, 0, cellTextureSize, cellTextureSize,
														indent, cellSelectorColor);

			cellSelectorRenderTexture.clear(sf::Color(0, 0, 0, 0));
			cellSelectorRenderTexture.draw(cellSelectorVertexArray);
			cellSelectorRenderTexture.display();

			//setting texture to sprite
			printf("setting texture to sprite\n");
			if (cellSelectorTexture) delete cellSelectorTexture;
			cellSelectorTexture = new sf::Texture(cellSelectorRenderTexture.getTexture());
			cellSelectorSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			cellSelectorSprite.setTexture(*cellSelectorTexture);
			printf("OK\n");
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
			realCellTextureSize = cellTextureSize * zoom;
		}

		void changeZoom(float delta)
		{
			if ((delta < 0) && (zoom < (0.1 + delta))) return;

			float correctionDelta = realCellTextureSize * (((zoom+delta)/zoom) - 1) / 2;
			mapPositionX -= mapWidth * correctionDelta;
			mapPositionY -= mapHeight * correctionDelta;

			zoom += delta;
			zoomTextures();
		}

		sf::Vector2f getPosition()
		{ return sf::Vector2f(mapPositionX, mapPositionY); }

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

			cellSelectorSprite.setPosition(x2 * realCellTextureSize + mapPositionX,
											y2 * realCellTextureSize + mapPositionY);
			window.draw(cellSelectorSprite);
		}

		bool cellFitsForPath(int x, int y, char direction)
		{
			if ((x == x1) && (y == y1)) return false;

			if (direction == RIGHT)
			{
				printf("RIGHT\n");
				if ((x+1) < mapWidth)
					if (pathMap[x+1][y]) return false;
				if ((y+1) < mapHeight)
					if (pathMap[x][y+1]) return false;
				if (y)
					if (pathMap[x][y-1]) return false;
			}
			else
			if (direction == LEFT)
			{
				printf("LEFT\n");
				if (x)
					if (pathMap[x-1][y]) return false;
				if ((y+1) < mapHeight)
					if (pathMap[x][y+1]) return false;
				if (y)
					if (pathMap[x][y-1]) return false;
			}
			else
			if (direction == UP)
			{
				printf("UP\n");
				if ((x+1) < mapWidth)
					if (pathMap[x+1][y]) return false;
				if (x)
					if (pathMap[x-1][y]) return false;
				if (y)
					if (pathMap[x][y-1]) return false;
			}
			else
			if (direction == DOWN)
			{
				printf("DOWN\n");
				if ((x+1) < mapWidth)
					if (pathMap[x+1][y]) return false;
				if (x)
					if (pathMap[x-1][y]) return false;
				if ((y+1) < mapWidth)
					if (pathMap[x][y+1]) return false;
			}
			return true;
		}

		bool changePath(char pathDirection)
		{
			printf("%d + %d = %d\n", pathDirection, path[path.size()-1], pathDirection + path[path.size()-1]);
			if ((pathDirection + path[path.size()-1]) == 5) //if moving backward (see defines)
				if (path.size() > 1)
				{
					path.pop_back();
					pathMap[x2][y2] = false;
					if (pathDirection == RIGHT) ++x2;
					else if (pathDirection == LEFT) --x2;
					else if (pathDirection == UP) --y2;
					else if (pathDirection == DOWN) ++y2;
					return true;
				}

			if (pathDirection == RIGHT)
			{
				if (((x2 + 1) < mapWidth) && cellFitsForPath(x2+1, y2, pathDirection)) ++x2;
				else return false;
			}
			else if (pathDirection == LEFT)
			{
				if (x2 && cellFitsForPath(x2-1, y2, pathDirection)) --x2;
				else return false;
			}
			else if (pathDirection == UP)
			{
				if (y2 && cellFitsForPath(x2, y2-1, pathDirection)) --y2;
				else return false;
			}
			else if (pathDirection == DOWN)
			{
				if (((y2 + 1) < mapHeight) && cellFitsForPath(x2, y2+1, pathDirection)) ++y2;
				else return false;
			}

			path.push_back(pathDirection);
			pathMap[x2][y2] = true;

			return true;
		}
};
