List *selectMapScreenMapsList;

void fillMapsList(List *mapsList)
{
	const char path[128] = "maps";
	DIR *dir = opendir(path);
	if (!dir) Closed();

	struct dirent *entery;
	char fileName[256];
	while ((entery = readdir(dir)) != NULL)
	{
		sprintf(fileName,"%s/%s", path, entery->d_name);
		char *c = fileName;
		while (*c) ++c;
		while (*c != '.') --c;
		++c;
		if (*c != 't') continue;
		++c;
		if (*c != 'd') continue;
		++c;
		if (*c != 'm') continue;
		++c;
		if (*c) continue;

		if (checkMapFile(fileName))
		{
			//making user friendly name of map (without path and extension)
			char userFriendlyMapName[128];
			strcpy(userFriendlyMapName, entery->d_name);
			c = userFriendlyMapName;
			while (*c) ++c;
			while (*c != '.') --c;
			*c = 0;
			mapsList->addItem(userFriendlyMapName);
		}
	}

	closedir(dir);
	mapsList->updateItems();
}

void updateSelectMapScreenVariables()
{
	selectMapScreenMapsList->updatePositionAndSize();
}

void setSelectMapScreenVariables()
{
	selectMapScreenMapsList = new List(	"Select map to play on:", startGame,
										selectMapScreenFont, selectMapScreenFont,
										0, 0, 1, 1, 4,
										sf::Color(192, 92, 0), sf::Color(215, 215, 215),
										sf::Color(32, 32, 32), sf::Color(0, 0, 0), sf::Color(192, 92, 0));
	fillMapsList(selectMapScreenMapsList);
}
