List *selectMapScreenMapsList;

void selectMapScreenFillMapsList()
{
	printf("selectMapScreenFillMapsList\n");
	const char path[128] = "maps";
	DIR *dir = opendir(path);
	printf("dir opened\n");
	if (!dir) Closed();
	printf("dir ok\n");

	struct dirent *entery;
	struct stat fileStatus;
	char fileName[256];
	while ((entery = readdir(dir)) != NULL)
	{
		printf("while\n");
		printf("%s\n", entery->d_name);
		sprintf(fileName,"%s/%s", path, entery->d_name);
		if (checkMapFile(fileName)) selectMapScreenMapsList->addItem(fileName);
	}

	closedir(dir);
	printf("ok\n");
}

void startGame(std::string mapFileName)
{}

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
