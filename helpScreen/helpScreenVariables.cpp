Message *helpScreenMessage;

void updateHelpScreenVariables()
{
	helpScreenMessage->updatePositionAndSize();
}

void helpScreenExit()
{
	delete helpScreenMessage;
	helpScreenMessage = NULL;
	startMenu();
}

void setHelpScreenVariables()
{
	char *helpTextData = (char*)malloc(sizeof(char)*1024);
	FILE *file = fopen("helpText.txt", "rb");
	if (!file) Closed();
	char *c = helpTextData;
	for (; !feof(file); c++)
		*c = fgetc(file);
	--c;
	*c = 0;
	helpTextData = (char*)realloc(helpTextData, sizeof(char)*(c - helpTextData + 1));

	helpScreenMessage = new Message(helpScreenExit, sf::String(helpTextData), "OK",
									"fonts/helpTextFont.otf",
									0, 0, 1, 1, 4,
									sf::Color(0, 0, 0), sf::Color(64, 128, 64), sf::Color(192, 192, 192));
}
