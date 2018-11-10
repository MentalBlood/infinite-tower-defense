class Setting
{
	private:
		sf::String name;
		unsigned int minValue,
					 maxValue,
					 currentValue;
		bool type;
		sf::Text text;
		std::vector<sf::String> valuesNames;

	public:
		Setting(sf::String nameArg, sf::Font *font, sf::Color fontColor, bool type,
				unsigned int minValue, unsigned int maxValue):
			name(nameArg), minValue(minValue), maxValue(maxValue), currentValue((minValue + maxValue) / 2), type(type)
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
