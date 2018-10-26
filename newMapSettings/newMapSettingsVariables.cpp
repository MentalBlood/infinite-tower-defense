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

sf::Font newMapSettingsFont;

sf::Color	newMapSettingsFontColor(0, 175, 70),
			newMapSelectedSettingColor(215, 215, 60);

int newMapSettingsFontSize,
	newMapSettingsSelectedSettingNumber = 0;

float newMapSettingsY1;

#define TEXT 0
#define INTEGER 1

class Setting
{
	private:
		bool type;
		sf::String name;
		sf::Text text;
		int currentValue,
			maxValue,
			minValue;
		std::vector<sf::String> valuesNames;

	public:
		Setting(sf::String nameArg, sf::Font *font, sf::Color fontColor, bool type, int minValueArg, int maxValueArg):
			name(nameArg), maxValue(maxValueArg), minValue(minValueArg), currentValue((minValueArg + maxValueArg) / 2)
		{
			text.setFont(*font);
			text.setFillColor(fontColor);
			if (type == TEXT)
				text.setString(name + sf::String("\tno values"));
			else //type == INTEGER
				text.setString(name + sf::String("\t") + sf::String(intToString(int((maxValue + minValue) / 2))));
		}

		void select()
		{ text.setFillColor(newMapSelectedSettingColor); }

		void unselect()
		{ text.setFillColor(newMapSettingsFontColor); }

		void setPosition(float x, float y)
		{ text.setPosition(x, y); }

		void setFontSize(int size)
		{ text.setCharacterSize(size); }

		void addValue(sf::String newValueName)
		{
			if (type) return;
			valuesNames.push_back(newValueName);
			maxValue = valuesNames.size()-1;
		}

		void refreshText()
		{
			if (type == TEXT)
				text.setString(name + sf::String("\t") + valuesNames[currentValue]);
			else //type == INTEGER
				text.setString(name + sf::String("\t") + sf::String(intToString(currentValue)));
		}

		void increaseValue()
		{
			if (currentValue < maxValue) ++currentValue;
			refreshText();
		}

		void decreaseValue()
		{
			if (currentValue > minValue) --currentValue;
			refreshText();
		}

		int getValue()
		{ return currentValue; }

		void draw()
		{ window.draw(text); }
};

std::vector<Setting> newMapSettings;

void updateNewMapSettingsVariables()
{
	newMapSettingsFontSize = sqrt(windowSize.x * windowSize.y) / 16;
	newMapSettingsY1 = float(windowSize.y) / 8;
	for (int i = 0; i < newMapSettings.size(); i++)
	{
		newMapSettings[i].setFontSize(newMapSettingsFontSize);
		newMapSettings[i].setPosition(float(windowSize.x) / 16, newMapSettingsY1 + i*newMapSettingsFontSize*1.5);
	}
}

void setNewMapSettingsVariables()
{
	if (!newMapSettingsFont.loadFromFile("fonts/newMapSettingsFont.otf")) Closed();

	newMapSettings.push_back(Setting(sf::String("width"), &newMapSettingsFont, newMapSettingsFontColor, 1, 8, 32));
	newMapSettings.push_back(Setting(sf::String("height"), &newMapSettingsFont, newMapSettingsFontColor, 1, 8, 32));

	updateNewMapSettingsVariables();
	newMapSettings[0].select();
}
