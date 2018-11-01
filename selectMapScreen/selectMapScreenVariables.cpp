List *selectMapScreenMapsList;

void selectMapScreenFillMapsList()
{
	const char path[128] = "maps";
	DIR *dir = opendir(path);
	if (!dir) Closed();

	struct dirent *entery;
	struct stat fileStatus;
	char fileName[256];
	while ((entery = readdir(dir)) != NULL)
	{
		sprintf(fileName,"%s/%s", path, entery->d_name);
		if (checkMapFile(fileName))
		{
			//making user friendly name of map (without path and extension)
			char userFriendlyMapName[128];
			strcpy(userFriendlyMapName, entery->d_name);
			char *c = userFriendlyMapName;
			while (*c)
				if (*c == '.')
				{
					*c = 0;
					break;
				}
				else ++c;

			selectMapScreenMapsList->addItem(userFriendlyMapName, fileName);
		}
	}

	closedir(dir);
}

void updateSelectMapScreenVariables()
{
	selectMapScreenMapsList->updatePositionAndSize();
}

void setSelectMapScreenVariables()
{
	selectMapScreenMapsList = new List(	"Select map to play on:", startGame,
										"fonts/selectMapScreenFont.otf", "fonts/selectMapScreenFont.otf",
										0, 0, 1, 1, 4,
										sf::Color(0, 175, 70), sf::Color(215, 215, 215),
										sf::Color(255, 255, 255, 64), sf::Color(32, 32, 32), sf::Color(0, 175, 60));
	selectMapScreenFillMapsList();
}
