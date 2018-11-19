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

bool checkMapFile(const char *fileName)
{
	//check file existance
	FILE *file = fopen(fileName, "rb");
	if (!file) return false;

	//check start and end cells
	unsigned int mapWidth; fscanf(file, "%u", &mapWidth);
	if ((mapWidth < 8) || (mapWidth > 128)) return false; //width too small or too big
	unsigned int mapHeight; fscanf(file, "%u", &mapHeight);
	if ((mapHeight < 8) || (mapHeight > 128)) return false; //height too small or too big
	unsigned int x1; fscanf(file, "%u", &x1);
	if (x1 > mapWidth) return false; //coordinate is out of map
	unsigned int y1; fscanf(file, "%u", &y1);
	if (y1 > mapHeight) return false; //coordinate is out of map

	//creating path map of read size
	std::vector<std::vector<char> > pathMap;
	pathMap.resize(mapWidth);
	for (unsigned int i = 0; i < mapWidth; i++)
	{
		pathMap[i].resize(mapHeight);
		for (unsigned int j = 0; j < mapHeight; j++)
			pathMap[i][j] = 0;
	}
	pathMap[x1][y1] = BEGIN;

	//check rocks coordinates
	int	rockX,
		rockY;
	while (true)
	{
		fscanf(file, "%d", &rockX);
		if (rockX == -1) break; //flag that means that all rocks coordinates read
		if ((rockX < 0) || (rockX > int(mapWidth))) return false; //coordinate is out of map

		fscanf(file, "%d", &rockY);
		if ((rockY < 0) || (rockY > int(mapHeight))) return false; //coordinate is out of map

		if (pathMap[rockX][rockY]) return false; //something already written on this cell
		pathMap[rockX][rockY] = ROCK;
	}

	//check path
	unsigned int	x2 = x1,
					y2 = y1;
	bool continueOnlyIfItIsTheLastCell = false;
	unsigned int pathesFromCell = 0;
	while (!feof(file))
	{
		if (continueOnlyIfItIsTheLastCell) return false;

		char c = char(fgetc(file));
		if (c == RIGHT) ++x2;
		else if (c == LEFT) --x2;
		else if (c == UP) --y2;
		else if (c == DOWN) ++y2;
		else break; //unknown direction

		if (pathMap[x2][y2]) return false; //something already written on this cell;

		pathesFromCell = 0; //let's count them
		if (x2) //LEFT
			if (pathMap[x2-1][y2] && (pathMap[x2-1][y2] != ROCK)) ++pathesFromCell;
		if ((x2+1) < pathMap.size()) //RIGHT
			if (pathMap[x2+1][y2] && (pathMap[x2+1][y2] != ROCK)) ++pathesFromCell;
		if (y2) //UP
			if (pathMap[x2][y2-1] && (pathMap[x2][y2-1] != ROCK)) ++pathesFromCell;
		if ((y2+1) < pathMap[0].size()) //DOWN
			if (pathMap[x2][y2+1] && (pathMap[x2][y2+1] != ROCK)) ++pathesFromCell;
		if ((pathesFromCell > 2) || (!pathesFromCell))
			continueOnlyIfItIsTheLastCell = true; //wrong number of pathes

		pathMap[x2][y2] = PATH;
	}
	if (pathesFromCell != 1) return false; //only one path from the end cell
	pathMap[x2][y2] = END;

	fclose(file);
	return true;
}
