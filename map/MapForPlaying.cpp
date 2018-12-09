class MapForPlaying : public Map
{
	private:
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

	public:
		MapForPlaying(const char *fileName):
		Map(0, 0)
		{
			loadFile(fileName);
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

		sf::Vector2f getRelativeSpawnPoint()
		{
			return sf::Vector2f(cellTextureSize * (x1 + 0.5),
								cellTextureSize * (y1 + 0.5));
		}

		sf::Vector2f getSpawnPoint()
		{
			return sf::Vector2f(mapPositionX + realCellTextureSize * (x1 + 0.5),
								mapPositionY + realCellTextureSize * (y1 + 0.5));
		}

		float getScale()
		{ return zoom; }

		std::vector<char>* getPathPointer()
		{ return &path; }

		std::vector<std::vector<char> >* getPathMapPointer()
		{ return &pathMap; }

		float getCellSize()
		{ return float(cellTextureSize); }

		float getRealCellSize()
		{ return realCellTextureSize; }

		sf::Vector2u getMapSize()
		{ return sf::Vector2u(mapWidth, mapHeight); }

		sf::Vector2f getRelativeSelectorPosition()
		{
			return sf::Vector2f(cellTextureSize * (cellSelectorX + 0.5),
								cellTextureSize * (cellSelectorY + 0.5));
		}

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

		void moveCellSelectorToCell(unsigned int x, unsigned int y)
		{
			cellSelectorX = x;
			cellSelectorY = y;
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
};
