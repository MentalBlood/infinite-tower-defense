#define UP 1
#define RIGHT 2
#define LEFT 3
#define DOWN 4

#define EMPTY 0
#define PATH 1
#define BEGIN 2
#define END 3
#define ROCK 4

#define CHANGE_CELL 0
#define MOVE_BEGIN 1
#define MOVE_END 2

class MapChange
{
	public:
		int cellX, cellY;
		char was, become;

		MapChange(int x, int y, char was, char become): cellX(x), cellY(y), was(was), become(become)
		{}
};

class EditorAction
{
	private:
		std::vector<MapChange> mapChanges;

	public:
		//just one cell changed
		EditorAction(int cellX, int cellY, char was, char become)
		{ mapChanges.push_back(MapChange(cellX, cellY, was, become)); }

		//start or end cell moved
		EditorAction(char movingCell, char toCell, int fromX, int fromY, int toX, int toY)
		{
			mapChanges.push_back(MapChange(fromX, fromY, movingCell, EMPTY));
			mapChanges.push_back(MapChange(toX, toY, toCell, movingCell));
		}

		//map reseted
		EditorAction(std::vector<std::vector<char> > &pathMap)
		{
			for (int i = 0; i < pathMap.size(); i++)
				for (int j = 0; j < pathMap[i].size(); j++)
					//start cell is in left upper corner by default
					if ((!i) && (!j) && (pathMap[i][j] != BEGIN))
						mapChanges.push_back(MapChange(i, j, pathMap[i][j], BEGIN));
					else
					//end cell is in right bottom corner by default
					if ((i == (pathMap.size()-1)) && (j == (pathMap[0].size()-1)) && (pathMap[i][j] != END))
						mapChanges.push_back(MapChange(i, j, pathMap[i][j], END));
					else
					//other cells are empty by default
					if (pathMap[i][j] != EMPTY)
						mapChanges.push_back(MapChange(i, j, pathMap[i][j], EMPTY));
		}

		void undo(std::vector<std::vector<char> > &pathMap, int *x1, int *y1, int *x2, int *y2)
		{
			if (mapChanges.size() > 1)
			{
				for (int i = 0; i < mapChanges.size(); i++)
				{
					pathMap[mapChanges[i].cellX][mapChanges[i].cellY] = mapChanges[i].was;
					if (mapChanges[i].was == BEGIN)
					{
						*x1 = mapChanges[i].cellX;
						*y1 = mapChanges[i].cellY;
					}
					else
					if (mapChanges[i].was == END)
					{
						*x2 = mapChanges[i].cellX;
						*y2 = mapChanges[i].cellY;
					}
				}
			}
			else
				pathMap[mapChanges[0].cellX][mapChanges[0].cellY] = mapChanges[0].was;
		}

		void redo(std::vector<std::vector<char> > &pathMap, int *x1, int *y1, int *x2, int *y2)
		{
			if (mapChanges.size() > 1)
			{
				for (int i = 0; i < mapChanges.size(); i++)
				{
					pathMap[mapChanges[i].cellX][mapChanges[i].cellY] = mapChanges[i].become;
					if (mapChanges[i].become == BEGIN)
					{
						*x1 = mapChanges[i].cellX;
						*y1 = mapChanges[i].cellY;
					}
					else
					if (mapChanges[i].become == END)
					{
						*x2 = mapChanges[i].cellX;
						*y2 = mapChanges[i].cellY;
					}
				}
			}
			else
				pathMap[mapChanges[0].cellX][mapChanges[0].cellY] = mapChanges[0].become;
		}

		void print()
		{
			for (int i = 0; i < mapChanges.size(); i++)
				printf("(%d, %d): %d -> %d\n", mapChanges[i].cellX, mapChanges[i].cellY, mapChanges[i].was, mapChanges[i].become);
		}
};

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
					*endCellTexture,
					*rockCellTexture;

		sf::Sprite	towerCellSprite,
					pathCellSprite,
					cellSelectorSprite,
					startCellSprite,
					endCellSprite,
					rockCellSprite;

		int cellSelectorX,
			cellSelectorY;

		bool cellSelectorPressed,
			 draggingStartCell,
			 draggingEndCell,
			 settingRocks;

		sf::Color	towerCellBordersColor,
					towerCellFillColor,
					cellSelectorColor;

		std::vector<char> path;
		std::vector<std::vector<char> > pathMap;
		char startNowWhereWas,
			 endNowWhereWas;

		std::vector<EditorAction> actions;
		int lastActionIndex;

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

		void writePath()
		{
			path.clear();

			int x = x1,
				y = y1;

			char lastDirection;
			
			while (!((x == x2) && (y == y2)))
			{
				if (lastDirection != RIGHT)
					if (x) //LEFT
						if ((pathMap[x-1][y] == PATH) || (pathMap[x-1][y] == END))
						{
							--x;
							path.push_back(LEFT);
							lastDirection = LEFT;
							continue;
						}
				if (lastDirection != LEFT)
					if (x < (pathMap.size()-1)) //RIGHT
						if ((pathMap[x+1][y] == PATH) || (pathMap[x+1][y] == END))
						{
							++x;
							path.push_back(RIGHT);
							lastDirection = RIGHT;
							continue;
						}
				if (lastDirection != DOWN)
					if (y) //UP
						if ((pathMap[x][y-1] == PATH) || (pathMap[x][y-1] == END))
						{
							--y;
							path.push_back(UP);
							lastDirection = UP;
							continue;
						}
				if (lastDirection != UP)
					if (y < (pathMap[0].size()-1)) //DOWN
						if ((pathMap[x][y+1] == PATH) || (pathMap[x][y+1] == END))
						{
							++y;
							path.push_back(DOWN);
							lastDirection = DOWN;
							continue;
						}
			}
		}

		void loadFile(const char *fileName)
		{
			printf("loadFile\n");
			FILE *file = fopen(fileName, "rb");
			printf("file opened\n");

			//read start and end cells
			printf("read start and end cells\n");
			fscanf(file, "%d%d%d%d", &mapWidth, &mapHeight, &x1, &y1);
			//creating path map of read size
			createPathMap();
			pathMap[x1][y1] = BEGIN;

			//read rocks coordinates
			printf("read rocks coordinates\n");
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
			printf("read path\n");
			x2 = x1;
			y2 = y1;
			while (!feof(file))
			{
				char c = char(fgetc(file));
				printf("%d\n", c);
				if (c == RIGHT) ++x2;
				else if (c == LEFT) --x2;
				else if (c == UP) --y2;
				else if (c == DOWN) ++y2;
				else break;
				pathMap[x2][y2] = PATH;
			}
			pathMap[x2][y2] = END;

			printf("closing file\n");
			fclose(file);
		}

		void changeCell(int x, int y, char newCell)
		{
			//erasing "future" actions
			if (lastActionIndex != (actions.size()-1))
				actions.erase(actions.begin() + lastActionIndex+1, actions.end());
			++lastActionIndex;

			actions.push_back(EditorAction(x, y, pathMap[x][y], newCell));
			pathMap[x][y] = newCell;
		}

		void moveCell(int fromX, int fromY, int toX, int toY)
		{
			//erasing "future" actions
			if (lastActionIndex != (actions.size()-1))
				actions.erase(actions.begin() + lastActionIndex+1, actions.end());
			++lastActionIndex;

			//start cell was moved
			if (pathMap[fromX][fromY] == BEGIN)
			{
				pathMap[fromX][fromY] = startNowWhereWas;
				x1 = toX;
				y1 = toY;
				startNowWhereWas = pathMap[toX][toY];
				pathMap[toX][toY] = BEGIN;
			}
			//end cell was moved
			else
			{
				pathMap[fromX][fromY] = endNowWhereWas;
				x2 = toX;
				y2 = toY;
				endNowWhereWas = pathMap[toX][toY];
				pathMap[toX][toY] = END;
			}

			actions.push_back(EditorAction(pathMap[fromX][fromY], pathMap[toX][toY], fromX, fromY, toX, toY));
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

		void pressOnCell()
		{
			if (pathMap[cellSelectorX][cellSelectorY] == EMPTY)
				changeCell(cellSelectorX, cellSelectorY, PATH);
			else
			if (pathMap[cellSelectorX][cellSelectorY] == PATH)
				changeCell(cellSelectorX, cellSelectorY, EMPTY);
			else
			if (pathMap[cellSelectorX][cellSelectorY] == ROCK)
				changeCell(cellSelectorX, cellSelectorY, EMPTY);
			if (pathMap[cellSelectorX][cellSelectorY] == BEGIN)
				draggingStartCell = true;
			else
			if (pathMap[cellSelectorX][cellSelectorY] == END)
				draggingEndCell = true;
		}

		void setRockOnCell()
		{
			if (pathMap[cellSelectorX][cellSelectorY] < 2)
				changeCell(cellSelectorX, cellSelectorY, ROCK);
			else
			if (pathMap[cellSelectorX][cellSelectorY] == ROCK)
				changeCell(cellSelectorX, cellSelectorY, EMPTY);
		}

	public:
		Map(int width, int height,
			sf::Color towerCellBordersColor, sf::Color towerCellFillColor, sf::Color cellSelectorColor):
			x1(0), y1(0), x2(width - 1), y2(height - 1), zoom(1), cellSelectorX(0), cellSelectorY(0),
			towerCellTexture(NULL), pathCellTexture(NULL), cellSelectorTexture(NULL), startCellTexture(NULL),
			endCellTexture(NULL), rockCellTexture(NULL),
			towerCellBordersColor(towerCellBordersColor), towerCellFillColor(towerCellFillColor),
			cellSelectorColor(cellSelectorColor), cellSelectorPressed(false), draggingStartCell(false),
			draggingEndCell(false), settingRocks(false), lastActionIndex(-1),
			startNowWhereWas(EMPTY), endNowWhereWas(EMPTY)
		{
			mapWidth = width;
			mapHeight = height;
			createPathMap();

			pathMap[0][0] = 2;
			pathMap[width-1][height-1] = 3;
		}

		Map(const char *fileName,
			sf::Color towerCellBordersColor, sf::Color towerCellFillColor, sf::Color cellSelectorColor):
			zoom(1), cellSelectorX(0), cellSelectorY(0),
			towerCellTexture(NULL), pathCellTexture(NULL), cellSelectorTexture(NULL), startCellTexture(NULL),
			endCellTexture(NULL), rockCellTexture(NULL),
			towerCellBordersColor(towerCellBordersColor), towerCellFillColor(towerCellFillColor),
			cellSelectorColor(cellSelectorColor), cellSelectorPressed(false), draggingStartCell(false),
			draggingEndCell(false), settingRocks(false), lastActionIndex(-1),
			startNowWhereWas(EMPTY), endNowWhereWas(EMPTY)
		{
			loadFile(fileName);
		}

		~Map()
		{
			delete towerCellTexture;
			delete pathCellTexture;
			delete cellSelectorTexture;
			delete startCellTexture;
			delete endCellTexture;
			delete rockCellTexture;
		}

		bool check()
		{
			for (int i = 0; i < pathMap.size(); i++)
			{
				for (int j = 0; j < pathMap[0].size(); j++)
				{
					if ((pathMap[i][j] == EMPTY) || (pathMap[i][j] == ROCK)) continue;

					int pathesFromCell = 0;

					if (i) //LEFT
						if (pathMap[i-1][j] && (pathMap[i-1][j] != ROCK)) ++pathesFromCell;
					if (i < (pathMap.size()-1)) //RIGHT
						if (pathMap[i+1][j] && (pathMap[i+1][j] != ROCK)) ++pathesFromCell;
					if (j) //UP
						if (pathMap[i][j-1] && (pathMap[i][j-1] != ROCK)) ++pathesFromCell;
					if (j < (pathMap[0].size()-1)) //DOWN
						if (pathMap[i][j+1] && (pathMap[i][j+1] != ROCK)) ++pathesFromCell;


					if (pathMap[i][j] == PATH)
					{
						if (pathesFromCell != 2) return false;
					}
					else //BEGIN or END
						if (pathesFromCell != 1) return false;
				}
			}
			return true;
		}

		void save(const char *fileName)
		{
			FILE *file = fopen(fileName, "wb");

			//write width, height and start cell coordinates
			fprintf(file, "%d %d %d %d", mapWidth, mapHeight, x1, y1);

			//write rocks coordinates
			for (int i = 0; i < pathMap.size(); i++)
				for (int j = 0; j < pathMap[0].size(); j++)
					if (pathMap[i][j] == ROCK)
						fprintf(file, " %d %d", i, j);
			//end rocks coordinates flag
			fprintf(file, " %d", -1);

			//write enemies path
			writePath();
			for (int i = 0; i < path.size(); i++)
				putc(path[i], file);

			fclose(file);
		}

		void undo()
		{
			if (lastActionIndex == -1) return;

			actions[lastActionIndex].undo(pathMap, &x1, &y1, &x2, &y2);
			--lastActionIndex;
		}

		void redo()
		{
			if (lastActionIndex >= int(actions.size()-1)) return;

			++lastActionIndex;
			actions[lastActionIndex].redo(pathMap, &x1, &y1, &x2, &y2);
		}

		void print_actions()
		{
			for (int i = 0; i < actions.size(); i++)
			{
				printf("\t%d\t\n", i);
				actions[i].print();
				printf("\n");
			}
		}

		void reset()
		{
			//erasing "future" actions
			actions.erase(actions.begin() + lastActionIndex+1, actions.end());

			actions.push_back(EditorAction(pathMap));
			clearPathMap();
			
			pathMap[0][0] = 2;
			pathMap[mapWidth-1][mapHeight-1] = 3;

			x1 = 0; y1 = 0;
			x2 = mapWidth - 1; y2 = mapHeight - 1;

			cellSelectorX = 0;
			cellSelectorY = 0;
			++lastActionIndex;
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

			//5 setting rock cell texture
			if (!rockCellTexture) delete rockCellTexture;
			rockCellTexture = new sf::Texture();
			rockCellTexture->loadFromFile("textures/rockCell.png");
			rockCellSprite.setTextureRect(sf::IntRect(0, 0, cellTextureSize, cellTextureSize));
			rockCellSprite.setTexture(*rockCellTexture);

			//6 drawing cell selector texture
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

		void startSettingRocks()
		{
			if (cellSelectorPressed || settingRocks) return;
			settingRocks = true;
			setRockOnCell();
		}

		void finishSettingRocks()
		{ settingRocks = false; }

		void pressCellSelector()
		{
			if (cellSelectorPressed) return;
			cellSelectorPressed = true;
			pressOnCell();
		}

		void unpressCellSelector()
		{
			cellSelectorPressed = false;
			draggingStartCell = false;
			draggingEndCell = false;
		}

		void moveCellSelector(char direction)
		{
			int oldCellSelectorX = cellSelectorX,
				oldCellSelectorY = cellSelectorY;

			if (direction == LEFT)
			{
				if (cellSelectorX) --cellSelectorX;
				else return;
			}
			else
			if (direction == RIGHT)
			{
				if ((cellSelectorX+1) < mapWidth) ++cellSelectorX;
				else return;
			}
			else
			if (direction == DOWN)
			{
				if ((cellSelectorY+1) < mapHeight) ++cellSelectorY;
				else return;
			}
			else
			if (direction == UP)
			{
				if (cellSelectorY) --cellSelectorY;
				else return;
			}

			if (settingRocks) setRockOnCell();
			else
			if (draggingStartCell)
			{
				if (pathMap[cellSelectorX][cellSelectorY] == END)
				{
					draggingEndCell = false;
					cellSelectorX = oldCellSelectorX;
					cellSelectorY = oldCellSelectorY;
					return;
				}
				moveCell(oldCellSelectorX, oldCellSelectorY, cellSelectorX, cellSelectorY);
				x1 = cellSelectorX; y1 = cellSelectorY;
			}
			else
			if (draggingEndCell)
			{
				if (pathMap[cellSelectorX][cellSelectorY] == BEGIN)
				{
					draggingStartCell = false;
					cellSelectorX = oldCellSelectorX;
					cellSelectorY = oldCellSelectorY;
					return;
				}
				moveCell(oldCellSelectorX, oldCellSelectorY, cellSelectorX, cellSelectorY);
				x2 = cellSelectorX; y2 = cellSelectorY;
			}
			else
			if (cellSelectorPressed) pressOnCell();
		}

		bool moveCellSelectorToMouse(float x, float y)
		{
			int selectedCellX = int((x - mapPositionX) / realCellTextureSize),
				selectedCellY = int((y - mapPositionY) / realCellTextureSize);

			if ((selectedCellX == cellSelectorX) && (selectedCellY == cellSelectorY)) return true;

			if ((selectedCellX < 0) || (selectedCellX >= mapWidth) ||
				(selectedCellY < 0) || (selectedCellY >= mapHeight)) return false;

			if (settingRocks)
			{
				cellSelectorX = selectedCellX;
				cellSelectorY = selectedCellY;
				setRockOnCell();
				return false;
			}
			else
			if (draggingStartCell)
			{
				if (pathMap[selectedCellX][selectedCellY] == END)
				{
					unpressCellSelector();
					return false;
				}
				moveCell(x1, y1, selectedCellX, selectedCellY);
				x1 = selectedCellX; y1 = selectedCellY;

				cellSelectorX = selectedCellX;
				cellSelectorY = selectedCellY;

				return false;
			}
			else
			if (draggingEndCell)
			{
				if (pathMap[selectedCellX][selectedCellY] == BEGIN)
				{
					unpressCellSelector();
					return false;
				}
				moveCell(x2, y2, selectedCellX, selectedCellY);
				x2 = selectedCellX; y2 = selectedCellY;

				cellSelectorX = selectedCellX;
				cellSelectorY = selectedCellY;

				return false;
			}

			cellSelectorX = selectedCellX;
			cellSelectorY = selectedCellY;

			if (cellSelectorPressed)
			{
				pressOnCell();
				return false;
			}

			return true;
		}

		void draw()
		{
			float cellSpriteX = mapPositionX, 
				  cellSpriteY = mapPositionY;

			for (int i = 0; i < pathMap.size(); i++, cellSpriteX += realCellTextureSize)
			{
				if (((cellSpriteX + realCellTextureSize) < 0) || (cellSpriteX > windowSize.x)) continue;
				for (int j = 0; j < pathMap[i].size(); j++, cellSpriteY += realCellTextureSize)
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

			cellSelectorSprite.setPosition(cellSelectorX * realCellTextureSize + mapPositionX,
											cellSelectorY * realCellTextureSize + mapPositionY);
			window.draw(cellSelectorSprite);
		}
};
