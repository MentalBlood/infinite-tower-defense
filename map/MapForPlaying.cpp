class MapForPlaying
{
	private:
		float zoom;

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

		unsigned int	mapWidth, mapHeight,
						x1, y1,
						x2, y2;

		float mapPositionX,
			  mapPositionY;

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

		void createPathMap()
		{
			pathMap.resize(mapWidth);
			for (unsigned int i = 0; i < mapWidth; i++)
				pathMap[i].resize(mapHeight);
		}

		void loadFile(const char *fileName)
		{
			FILE *file = fopen(fileName, "rb");

			//read start and end cells
			fscanf(file, "%d%d%d%d", &mapWidth, &mapHeight, &x1, &y1);
			//creating path map of read size
			createPathMap();
			pathMap[x1][y1] = BEGIN;

			//read rocks coordinates
			int rockX,
				rockY;
			while (true)
			{
				fscanf(file, "%d", &rockX);
				if (rockX == -1) break;

				fscanf(file, "%d", &rockY);
				pathMap[rockX][rockY] = ROCK;
			}

			//read path
			path.clear();
			x2 = x1;
			y2 = y1;
			while (!feof(file))
			{
				char c = char(fgetc(file));
				if (c == RIGHT) ++x2;
				else if (c == LEFT) --x2;
				else if (c == UP) --y2;
				else if (c == DOWN) ++y2;
				else break;
				pathMap[x2][y2] = PATH;
				path.push_back(c);
			}
			pathMap[x2][y2] = END;

			fclose(file);
		}

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
		MapForPlaying(const char *fileName,
			sf::Color towerCellBordersColor, sf::Color towerCellFillColor, sf::Color cellSelectorColor):
			zoom(1), cellSelectorX(0), cellSelectorY(0),
			towerCellTexture(NULL), pathCellTexture(NULL), cellSelectorTexture(NULL), startCellTexture(NULL),
			endCellTexture(NULL), rockCellTexture(NULL),
			towerCellBordersColor(towerCellBordersColor), towerCellFillColor(towerCellFillColor),
			cellSelectorColor(cellSelectorColor), cellSelectorPressed(false)
		{
			loadFile(fileName);
		}

		~MapForPlaying()
		{
			delete towerCellTexture;
			delete pathCellTexture;
			delete cellSelectorTexture;
			delete startCellTexture;
			delete endCellTexture;
			delete rockCellTexture;
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

		void setPosition(float x, float y)
		{
			mapPositionX = x;
			mapPositionY = y;
		}

		void changeZoom()
		{
			if ((gameScaleDelta < 1.0) && (zoom < (0.1 / gameScaleDelta))) return;

			mapPositionX += (1 - gameScaleDelta) * (gameScaleCenter.x - mapPositionX);
			mapPositionY += (1 - gameScaleDelta) * (gameScaleCenter.y - mapPositionY);

			zoom *= gameScaleDelta;
			zoomTextures();
		}

		sf::Vector2f getPosition()
		{ return sf::Vector2f(mapPositionX, mapPositionY); }

		sf::Vector2f getSpawnPoint()
		{
			return sf::Vector2f(mapPositionX + realCellTextureSize * (x1 + 0.5),
								mapPositionY + realCellTextureSize * (y1 + 0.5));
		}

		float getScale()
		{ return zoom; }

		const std::vector<char>* getPathPointer()
		{ return &path; }

		float getCellSize()
		{ return float(cellTextureSize); }

		float getRealCellSize()
		{ return realCellTextureSize; }

		sf::Vector2f getSelectorPosition()
		{
			return sf::Vector2f(mapPositionX + realCellTextureSize * cellSelectorX,
								mapPositionY + realCellTextureSize * cellSelectorY);
		}

		sf::Vector2f getSelectorCenteredPosition()
		{ return getSelectorPosition() + sf::Vector2f(realCellTextureSize/2, realCellTextureSize/2); }

		bool selectorOnCellWhichFitsForTower()
		{ return !pathMap[cellSelectorX][cellSelectorY]; }

		bool selectorOnTower()
		{ return (pathMap[cellSelectorX][cellSelectorY] == -1); }

		void setTowerOnCell()
		{ pathMap[cellSelectorX][cellSelectorY] = -1; }

		void removeTower()
		{ pathMap[cellSelectorX][cellSelectorY] = 0; }

		void moveCellSelector(char direction)
		{
			if ((direction == LEFT) && (cellSelectorX))
				--cellSelectorX;
			else
			if ((direction == RIGHT) && ((cellSelectorX+1) < mapWidth))
				++cellSelectorX;
			else
			if ((direction == DOWN) && ((cellSelectorY+1) < mapHeight))
				++cellSelectorY;
			else
			if ((direction == UP) && cellSelectorY)
				--cellSelectorY;
		}

		bool moveCellSelectorToMouse(float x, float y)
		{
			int selectedCellX = int((x - mapPositionX) / realCellTextureSize),
				selectedCellY = int((y - mapPositionY) / realCellTextureSize);

			if ((selectedCellX == int(cellSelectorX)) && (selectedCellY == int(cellSelectorY))) return true;

			if ((selectedCellX < 0) || (selectedCellX >= int(mapWidth)) ||
				(selectedCellY < 0) || (selectedCellY >= int(mapHeight))) return false;

			cellSelectorX = selectedCellX;
			cellSelectorY = selectedCellY;

			return true;
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
};
