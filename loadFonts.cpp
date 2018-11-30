enum fontType
{
	chooseNewOrSavedMapToEditDialogFont,
	enterFileNameFont,
	gameInfoFont,
	helpButtonFont,
	helpTextFont,
	mapEditorButtonsFont,
	menuFont,
	messageFont,
	newMapSettingsFont,
	selectMapScreenFont,
	towerInfoFont,
	upgradeButtonFont,
	towerUpgradeInfoFont,
	fontsCount
};

const char *fontTypeFileName[fontsCount]
{
	"chooseNewOrSavedMapToEditDialogFont.otf",
	"enterFileNameFont.otf",
	"gameInfoFont.otf",
	"helpButtonFont.otf",
	"helpTextFont.ttf",
	"mapEditorButtonsFont.otf",
	"menuFont.otf",
	"messageFont.otf",
	"newMapSettingsFont.otf",
	"selectMapScreenFont.otf",
	"towerInfoFont.otf",
	"upgradeButtonFont.otf",
	"towerUpgradeInfoFont.otf"
};

std::vector<sf::Font> fonts;

void loadFonts()
{
	fonts.resize(fontsCount);
	for (unsigned int i = 0; i < fontsCount; i++)
		if (!fonts[i].loadFromFile("fonts/" + sf::String(fontTypeFileName[i])))
			Closed();
}
