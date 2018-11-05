class EnterFileNameDialog
{
	private:
		sf::String promptString;
		void (*functionOnComplete)(std::string);

		float relativeX,
			  relativeY,
			  relativeWidth,
			  relativeHeight;

		sf::Color	promptColor,
					enteredTextColor,
					fillColor,
					bordersColor;

		sf::Text prompt, enteredText;
		sf::Font font;

		sf::VertexArray promptFrame,
						enteredTextFrame,
						fill;

		float bordersThickness,
			  separatorY,
			  x, y, width, height;

	public:
		EnterFileNameDialog(sf::String promptString, void (*functionOnComplete)(std::string), float relativeX, float relativeY, float relativeWidth, float relativeHeight,
							sf::String textFontFileName,
							sf::Color promptColor, sf::Color enteredTextColor, sf::Color fillColor, sf::Color bordersColor):
			promptString(promptString), functionOnComplete(functionOnComplete),
			relativeX(relativeX), relativeY(relativeY), relativeWidth(relativeWidth), relativeHeight(relativeHeight),
			promptColor(promptColor), enteredTextColor(enteredTextColor), fillColor(fillColor), bordersColor(bordersColor)
		{
			if (!font.loadFromFile(textFontFileName)) Closed();
			prompt.setFont(font);
			prompt.setString(promptString);
			prompt.setFillColor(promptColor);
			enteredText.setFont(font);
			enteredText.setString("unnamed.tdm");
			enteredText.setFillColor(enteredTextColor);
		}

		void updateEnteredTextSize()
		{
			fitTextIntoRectangle(&enteredText, x + 2*bordersThickness, separatorY + 2*bordersThickness,
								width - 4*bordersThickness, y + height - separatorY - 6*bordersThickness);
		}

		void updatePositionAndSize()
		{
			x = windowSize.x * relativeX;
			y = windowSize.y * relativeY;
			width = windowSize.x * relativeWidth;
			height = windowSize.y * relativeHeight;
			bordersThickness = sqrt(width * height) / 64;
			separatorY = y + height/1.618;

			fitTextIntoRectangle(&prompt, x + 2*bordersThickness, y + 2*bordersThickness,
								width - 4*bordersThickness, separatorY - y - 6*bordersThickness);
			updateEnteredTextSize();

			makeVertexArrayFrame(&promptFrame, x, y, width, separatorY - y, bordersThickness, bordersColor);
			makeVertexArrayFrame(&enteredTextFrame, x, separatorY - bordersThickness, width, y + height - separatorY + bordersThickness, bordersThickness, bordersColor);
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2*bordersThickness, height - 2*bordersThickness, fillColor);
		}

		bool processCharacter(sf::Uint32 character)
		{
			if (character == '\t') return true;
			if (character == 13) //"Enter"
			{
				functionOnComplete(enteredText.getString());
				return false;
			}

			sf::String enteredTextString = enteredText.getString();
			int enteredTextStringLength = enteredTextString.getSize();

			if (character == 8)
			{
				if (!enteredTextStringLength) return true;
				enteredTextString.erase(enteredTextStringLength - 1);
			}
			else
			{
				if (enteredTextStringLength == 32) return true;
				enteredTextString += character;
			}

			enteredText.setString(enteredTextString);
			updateEnteredTextSize();

			return true;
		}

		void draw()
		{
			window.draw(fill);
			window.draw(promptFrame);
			window.draw(enteredTextFrame);
			window.draw(prompt);
			window.draw(enteredText);
		}
};
