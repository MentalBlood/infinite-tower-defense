char* intToString(int x)
{
	char **string = (char**)malloc(sizeof(char*));
	*string = (char*)malloc(sizeof(char)*11);
	for (char *c = *string; ; c++)
	{
		*c = '0' + x%10;
		x /= 10;
		if (!x)
		{
			*(c+1) = 0;
			for (char *c1 = *string; c1 <= c; c--, c1++) //inverting string
			{
				char temp = *c1;
				*c1 = *c;
				*c = temp;
			}
			return *string;
		}
	}
	return *string;
}

sf::Color	newMapSettingsFontColor(0, 175, 70),
			newMapSelectedSettingColor(215, 215, 60);

unsigned int	newMapSettingsFontSize,
				newMapSettingsSelectedSettingNumber = 0;

float newMapSettingsY1;

#define TEXT 0
#define INTEGER 1

#include "Setting.cpp"
std::vector<Setting> newMapSettings;

void updateNewMapSettingsVariables()
{
	newMapSettingsFontSize = sqrt(windowSize.x * windowSize.y) / 16;
	newMapSettingsY1 = float(windowSize.y) / 8;
	for (unsigned int i = 0; i < newMapSettings.size(); i++)
	{
		newMapSettings[i].setFontSize(newMapSettingsFontSize);
		newMapSettings[i].setPosition(float(windowSize.x) / 16, newMapSettingsY1 + i*newMapSettingsFontSize*1.5);
	}
}

void setNewMapSettingsVariables()
{
	newMapSettings.push_back(Setting(sf::String("width"), &fonts[newMapSettingsFont], newMapSettingsFontColor, 1, 8, 128));
	newMapSettings.push_back(Setting(sf::String("height"), &fonts[newMapSettingsFont], newMapSettingsFontColor, 1, 8, 128));

	updateNewMapSettingsVariables();
	newMapSettingsSelectedSettingNumber = 0;
	newMapSettings[0].select();
}
