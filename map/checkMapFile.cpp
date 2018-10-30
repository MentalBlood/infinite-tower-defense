bool checkMapFile(const char *fileName)
{
	printf("checkMapFile\n");
	//check file existance
	printf("chek file existance\n");
	FILE *file = fopen(fileName, "rb");
	if (!file) return false;
	printf("ok\n");

	//check start and end cells
	printf("check start and end cells\n");
	int mapWidth; fscanf(file, "%d", &mapWidth);
	if ((mapWidth < 8) || (mapWidth > 32)) return false; //width too small or too big
	int mapHeight; fscanf(file, "%d", &mapHeight);
	if ((mapHeight < 8) || (mapHeight > 32)) return false; //height too small or too big
	int x1; fscanf(file, "%d", &x1);
	if ((x1 < 0) || (x1 > mapWidth)) return false; //coordinate is out of map
	int y1; fscanf(file, "%d", &y1);
	if ((y1 < 0) || (y1 > mapHeight)) return false; //coordinate is out of map
	printf("ok\n");

	//creating path map of read size
	printf("creating path map of read size\n");
	std::vector<std::vector<char> > pathMap;
	pathMap.resize(mapWidth);
	for (int i = 0; i < mapWidth; i++)
	{
		pathMap[i].resize(mapHeight);
		for (int j = 0; j < mapHeight; j++)
			pathMap[i][j] = 0;
	}
	pathMap[x1][y1] = BEGIN;
	printf("ok\n");

	//check rocks coordinates
	printf("check rocks coordinates\n");
	int rockX,
		rockY;
	while (true)
	{
		fscanf(file, "%d", &rockX);
		printf("rockX = %d\n", rockX);
		if (rockX == -1) break; //flag that means that all rocks coordinates read
		if ((rockX < 0) || (rockX > mapWidth)) return false; //coordinate is out of map

		fscanf(file, "%d", &rockY);
		printf("rockY = %d\n", rockY);
		if ((rockY < 0) || (rockY > mapHeight)) return false; //coordinate is out of map

		if (pathMap[rockX][rockY]) return false; //something already written on this cell
		pathMap[rockX][rockY] = ROCK;
	}
	printf("ok\n");

	//check path
	printf("check path\n");
	int x2 = x1,
		y2 = y1;
	bool continueOnlyIfItIsTheLastCell = false;
	int pathesFromCell;
	while (!feof(file))
	{
		if (continueOnlyIfItIsTheLastCell) return false;

		char c = char(fgetc(file));
		printf("%d\n", c);
		if (c == RIGHT) ++x2;
		else if (c == LEFT) --x2;
		else if (c == UP) --y2;
		else if (c == DOWN) ++y2;
		else break; //unknown direction

		if (pathMap[x2][y2]) return false; //something already written on this cell;

		pathesFromCell = 0; //let's count them
		if (x2) //LEFT
			if (pathMap[x2-1][y2] && (pathMap[x2-1][y2] != ROCK)) ++pathesFromCell;
		if (x2 < (pathMap.size()-1)) //RIGHT
			if (pathMap[x2+1][y2] && (pathMap[x2+1][y2] != ROCK)) ++pathesFromCell;
		if (y2) //UP
			if (pathMap[x2][y2-1] && (pathMap[x2][y2-1] != ROCK)) ++pathesFromCell;
		if (y2 < (pathMap[0].size()-1)) //DOWN
			if (pathMap[x2][y2+1] && (pathMap[x2][y2+1] != ROCK)) ++pathesFromCell;
		if ((pathesFromCell > 2) || (!pathesFromCell))
			continueOnlyIfItIsTheLastCell = true; //wrong number of pathes

		pathMap[x2][y2] = PATH;
	}
	if (pathesFromCell != 1) return false; //only one path from the end cell
	pathMap[x2][y2] = END;
	printf("ok\n");

	fclose(file);
	return true;
}
