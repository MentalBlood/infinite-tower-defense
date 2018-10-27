float minf(float a, float b)
{
	if (a < b) return a;
	return b;
}

class TwoConditionButton
{
	private:
		bool pressed;
		void (*functionOnPress)(),
			 (*functionOnUnpress)();

		sf::String textString;
		sf::Font *font;
		sf::Text text;
		sf::Color	fillColor,
					bordersColor;
		sf::VertexArray borders,
						fill;

		float relativeX,
			  relativeY,
			  relativeWidth,
			  relativeHeight,
			  x, y, width, height;

	public:
		TwoConditionButton(void (*functionOnPress)(), void (*functionOnUnpress)(), sf::String textStringArg, sf::String textFontFileName,
					sf::Color textColor, sf::Color fillColor, sf::Color bordersColor, 
					float relativeXArg, float relativeYArg, float relativeWidthArg, float relativeHeightArg):
			functionOnPress(functionOnPress), functionOnUnpress(functionOnUnpress),
			pressed(false), textString(textStringArg), fillColor(fillColor), bordersColor(bordersColor)
		{
			font = new sf::Font();
			if (!font->loadFromFile(textFontFileName)) Closed();
			text.setFont(*font);
			text.setString(textString);
			text.setFillColor(textColor);

			relativeX = relativeXArg;
			relativeY = relativeYArg;
			relativeWidth = relativeWidthArg;
			relativeHeight = relativeHeightArg;
		}

		void updatePositionAndSize()
		{
			x = windowSize.x * relativeX;
			y = windowSize.y * relativeY;
			width = windowSize.x * relativeWidth;
			height = windowSize.y * relativeHeight;

			float bordersThickness = sqrt(width * height) / 64;

			//find out how many pixels is font grow up with every character size unit
			//(supposed that font grows linear)
			text.setCharacterSize(10);
			float fontSizeCoefficientY = text.getLocalBounds().height / 10,
				  fontSizeCoefficientX = text.getLocalBounds().width / 10;

			//set the font size so that the text is placed in the button
			float fontSize = minf((width-4*bordersThickness)*3/4 / fontSizeCoefficientX, (height - 4*bordersThickness)*3/4 / fontSizeCoefficientY);
			text.setCharacterSize(fontSize);

			//set font position so that the text is placed in the center of the button
			text.setPosition(	x + width/2 - text.getLocalBounds().width/2,
								y + height/2 - text.getLocalBounds().height/2 - 2*bordersThickness);

			makeVertexArrayFrame(&borders, x, y, width, height, bordersThickness, bordersColor);
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2*bordersThickness, height - 2*bordersThickness, fillColor);
		}

		void press()
		{
			pressed = true;
			for (int i = 0; i < 4; i++) fill[i].color = bordersColor;
			functionOnPress();
		}

		void unpress()
		{
			pressed = false;
			for (int i = 0; i < 4; i++) fill[i].color = fillColor;
			functionOnUnpress();
		}

		bool tryToPress(float mouseX, float mouseY)
		{
			if ((mouseX > x) && (mouseX < x + width) &&
				(mouseY > y) && (mouseY < y + height))
			{
				press();
				return true;
			}
			return false;
		}

		void draw()
		{
			window.draw(borders);
			window.draw(fill);
			window.draw(text);
		}
};
