class MapChange
{
	public:
		unsigned int cellX, cellY;
		char was, become;

		MapChange(unsigned int x, unsigned int y, char was, char become): cellX(x), cellY(y), was(was), become(become)
		{}
};

class EditorAction
{
	private:
		std::vector<MapChange> mapChanges;

	public:
		//just one cell changed
		EditorAction(unsigned int cellX, unsigned int cellY, char was, char become)
		{ mapChanges.push_back(MapChange(cellX, cellY, was, become)); }

		//start or end cell moved
		EditorAction(char movingCell, char toCell, unsigned int fromX, unsigned int fromY,
					unsigned int toX, unsigned int toY, char movingCellFrom)
		{
			mapChanges.push_back(MapChange(fromX, fromY, movingCell, movingCellFrom));
			mapChanges.push_back(MapChange(toX, toY, toCell, movingCell));
		}

		//map reseted
		EditorAction(std::vector<std::vector<char> > &pathMap)
		{
			for (unsigned int i = 0; i < pathMap.size(); i++)
				for (unsigned int j = 0; j < pathMap[i].size(); j++)
					//start cell is in left upper corner by default
					if ((!i) && (!j) && (pathMap[i][j] != BEGIN))
						mapChanges.push_back(MapChange(i, j, pathMap[i][j], BEGIN));
					else
					//end cell is in right bottom corner by default
					if ((i+1 == pathMap.size()) && (j+1 == pathMap[0].size()) && (pathMap[i][j] != END))
						mapChanges.push_back(MapChange(i, j, pathMap[i][j], END));
					else
					//other cells are empty by default
					if (pathMap[i][j] != EMPTY)
						mapChanges.push_back(MapChange(i, j, pathMap[i][j], EMPTY));
		}

		void undo(	std::vector<std::vector<char> > &pathMap,
					unsigned int *x1, unsigned int *y1, unsigned int *x2, unsigned int *y2,
					char *startNowWhereWas, char *endNowWhereWas)
		{
			if (mapChanges.size() > 1)
			{
				for (unsigned int i = 0; i < mapChanges.size(); i++)
				{
					if (mapChanges[i].was == BEGIN)
					{
						*x1 = mapChanges[i].cellX;
						*y1 = mapChanges[i].cellY;
						*startNowWhereWas = mapChanges[i].become;
					}
					else
					if (mapChanges[i].was == END)
					{
						*x2 = mapChanges[i].cellX;
						*y2 = mapChanges[i].cellY;
						*endNowWhereWas = mapChanges[i].become;
					}
					pathMap[mapChanges[i].cellX][mapChanges[i].cellY] = mapChanges[i].was;
				}
			}
			else
				pathMap[mapChanges[0].cellX][mapChanges[0].cellY] = mapChanges[0].was;
		}

		void redo(	std::vector<std::vector<char> > &pathMap,
					unsigned int *x1, unsigned int *y1, unsigned int *x2, unsigned int *y2,
					char *startNowWhereWas, char *endNowWhereWas)
		{
			if (mapChanges.size() > 1)
			{
				for (unsigned int i = 0; i < mapChanges.size(); i++)
				{
					if (mapChanges[i].become == BEGIN)
					{
						*x1 = mapChanges[i].cellX;
						*y1 = mapChanges[i].cellY;
						*startNowWhereWas = mapChanges[i].was;
					}
					else
					if (mapChanges[i].become == END)
					{
						*x2 = mapChanges[i].cellX;
						*y2 = mapChanges[i].cellY;
						*endNowWhereWas = mapChanges[i].was;
					}
					pathMap[mapChanges[i].cellX][mapChanges[i].cellY] = mapChanges[i].become;
				}
			}
			else
				pathMap[mapChanges[0].cellX][mapChanges[0].cellY] = mapChanges[0].become;
		}

		void print()
		{
			for (unsigned int i = 0; i < mapChanges.size(); i++)
				printf("(%d, %d): %d -> %d\n", mapChanges[i].cellX, mapChanges[i].cellY, mapChanges[i].was, mapChanges[i].become);
		}
};

class MapForEditing : public Map
{
	private:
		bool draggingStartCell,
			 draggingEndCell,
			 settingRocks;

		int lastActionIndex;

		char startNowWhereWas,
			 endNowWhereWas;

		std::vector<EditorAction> actions;

		void createPathMap()
		{
			pathMap.resize(mapWidth);
			for (unsigned int i = 0; i < mapWidth; i++)
			{
				pathMap[i].resize(mapHeight);
				for (unsigned int j = 0; j < mapHeight; j++)
					pathMap[i][j] = 0;
			}
		}

		void clearPathMap()
		{
			for (unsigned int i = 0; i < pathMap.size(); i++)
				for (unsigned int j = 0; j < pathMap[i].size(); j++)
					pathMap[i][j] = 0;
		}

		void writePath()
		{
			path.clear();

			unsigned int	x = x1,
							y = y1;

			char lastDirection = -1;
			
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
			FILE *file = fopen(fileName, "rb");

			//read start and end cells
			fscanf(file, "%u%u%u%u", &mapWidth, &mapHeight, &x1, &y1);
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
			}
			pathMap[x2][y2] = END;

			fclose(file);
		}

		void changeCell(int x, int y, char newCell)
		{
			//erasing "future" actions
			if ((unsigned int)(lastActionIndex+1) != actions.size())
				actions.erase(actions.begin() + lastActionIndex+1, actions.end());
			++lastActionIndex;

			actions.push_back(EditorAction(x, y, pathMap[x][y], newCell));
			pathMap[x][y] = newCell;
		}

		void moveCell(int fromX, int fromY, int toX, int toY)
		{
			//erasing "future" actions
			if ((unsigned int)(lastActionIndex+1) != actions.size())
				actions.erase(actions.begin() + lastActionIndex+1, actions.end());
			++lastActionIndex;

			
			//start cell was moved
			if (pathMap[fromX][fromY] == BEGIN)
			{
				actions.push_back(EditorAction(	pathMap[fromX][fromY], pathMap[toX][toY],
												fromX, fromY, toX, toY, startNowWhereWas));
				pathMap[fromX][fromY] = startNowWhereWas;
				x1 = toX;
				y1 = toY;
				startNowWhereWas = pathMap[toX][toY];
				pathMap[toX][toY] = BEGIN;
			}
			//end cell was moved
			else
			{
				actions.push_back(EditorAction(	pathMap[fromX][fromY], pathMap[toX][toY],
												fromX, fromY, toX, toY, endNowWhereWas));
				pathMap[fromX][fromY] = endNowWhereWas;
				x2 = toX;
				y2 = toY;
				endNowWhereWas = pathMap[toX][toY];
				pathMap[toX][toY] = END;
			}
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
				changeCell(cellSelectorX, cellSelectorY, PATH);
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
		MapForEditing(unsigned int width, unsigned int height):
		Map(width, height),
		draggingStartCell(false), draggingEndCell(false), settingRocks(false), lastActionIndex(-1),
		startNowWhereWas(EMPTY), endNowWhereWas(EMPTY)
		{
			createPathMap();

			pathMap[0][0] = 2;
			pathMap[width-1][height-1] = 3;
		}

		MapForEditing(const char *fileName):
		Map(0, 0),
		draggingStartCell(false), draggingEndCell(false), settingRocks(false), lastActionIndex(-1),
		startNowWhereWas(EMPTY), endNowWhereWas(EMPTY)
		{
			loadFile(fileName);
		}

		~MapForEditing()
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
			for (unsigned int i = 0; i < pathMap.size(); i++)
			{
				for (unsigned int j = 0; j < pathMap[0].size(); j++)
				{
					if ((pathMap[i][j] == EMPTY) || (pathMap[i][j] == ROCK)) continue;

					int pathesFromCell = 0;

					if (pathMap[i][j] == PATH)
					{
						if (i) //LEFT
							if (pathMap[i-1][j] && (pathMap[i-1][j] != ROCK)) ++pathesFromCell;
						if ((i+1) < pathMap.size()) //RIGHT
							if (pathMap[i+1][j] && (pathMap[i+1][j] != ROCK)) ++pathesFromCell;
						if (j) //UP
							if (pathMap[i][j-1] && (pathMap[i][j-1] != ROCK)) ++pathesFromCell;
						if ((j+1) < pathMap[0].size()) //DOWN
							if (pathMap[i][j+1] && (pathMap[i][j+1] != ROCK)) ++pathesFromCell;
					}
					else
					{
							if (i) //LEFT
								if (pathMap[i-1][j] == PATH) ++pathesFromCell;
							if ((i+1) < pathMap.size()) //RIGHT
								if (pathMap[i+1][j] == PATH) ++pathesFromCell;
							if (j) //UP
								if (pathMap[i][j-1] == PATH) ++pathesFromCell;
							if ((j+1) < pathMap[0].size()) //DOWN
								if (pathMap[i][j+1] == PATH) ++pathesFromCell;
					}


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
			fprintf(file, "%u %u %u %u", mapWidth, mapHeight, x1, y1);

			//write rocks coordinates
			for (unsigned int i = 0; i < pathMap.size(); i++)
				for (unsigned int j = 0; j < pathMap[0].size(); j++)
					if (pathMap[i][j] == ROCK)
						fprintf(file, " %d %d", i, j);
			//end rocks coordinates flag
			fprintf(file, " %d", -1);

			//write enemies path
			writePath();
			for (unsigned int i = 0; i < path.size(); i++)
				putc(path[i], file);

			fclose(file);
		}

		void undo()
		{
			if (lastActionIndex == -1) return;

			actions[lastActionIndex].undo(pathMap, &x1, &y1, &x2, &y2, &startNowWhereWas, &endNowWhereWas);
			--lastActionIndex;
		}

		void redo()
		{
			if (lastActionIndex >= int(actions.size()-1)) return;

			++lastActionIndex;
			actions[lastActionIndex].redo(pathMap, &x1, &y1, &x2, &y2, &startNowWhereWas, &endNowWhereWas);
		}

		void print_actions()
		{
			for (unsigned int i = 0; i < actions.size(); i++)
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

		void changeZoom(float delta, float mouseX, float mouseY)
		{
			if ((delta < 1.0) && (zoom < (0.1 / delta))) return;

			mapPositionX += (1 - delta) * (mouseX - mapPositionX);
			mapPositionY += (1 - delta) * (mouseY - mapPositionY);

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

			if ((selectedCellX == int(cellSelectorX)) && (selectedCellY == int(cellSelectorY))) return true;

			if ((selectedCellX < 0) || (selectedCellX >= int(mapWidth)) ||
				(selectedCellY < 0) || (selectedCellY >= int(mapHeight))) return false;

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
};
