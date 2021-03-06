class Message
{
	private:
		void (*functionOnUnpress)();

		sf::String textString;

		float relativeX,
			  relativeY,
			  relativeWidth,
			  relativeHeight,
			  relativeTextIndent;

		sf::Color	textColor,
					fillColor,
					bordersColor;

		sf::Text text;

		TwoConditionButton *button;

		float x, y,
			  width, height;

		sf::VertexArray fill,
						borders;

	public:
		Message(void (*functionOnUnpress)(), sf::String textString, sf::String buttonTextString, enum fontType fontIndex,
				float relativeX, float relativeY, float relativeWidth, float relativeHeight, float relativeTextIndent,
				sf::Color textColor, sf::Color fillColor, sf::Color bordersColor):
			functionOnUnpress(functionOnUnpress), textString(textString),
			relativeX(relativeX), relativeY(relativeY), relativeWidth(relativeWidth), relativeHeight(relativeHeight),
			relativeTextIndent(relativeTextIndent),
			textColor(textColor), fillColor(fillColor), bordersColor(bordersColor)
		{
			text.setFont(fonts[fontIndex]);
			text.setString(textString);
			text.setFillColor(textColor);
			if (buttonTextString.getSize())
				button = new TwoConditionButton(nothing, functionOnUnpress, buttonTextString, fontIndex,
												textColor, fillColor, bordersColor,
												relativeX + relativeWidth/4, relativeY + relativeHeight*3/4,
												relativeWidth/2, relativeHeight/8, relativeTextIndent);
			else button = NULL;
			updatePositionAndSize();
		}

		~Message()
		{ delete button; }

		void updatePositionAndSize()
		{
			x = windowSize.x * relativeX;
			y = windowSize.y * relativeY;
			width = windowSize.x * relativeWidth;
			height = windowSize.y * relativeHeight;
			float bordersThickness = sqrt(width * height) / 64;

			fitTextIntoRectangle(&text, x + 2 * bordersThickness, y + 2 * bordersThickness,
								width - 4 * bordersThickness, height*3/4 - bordersThickness);

			makeVertexArrayFrame(&borders, x, y, width, height, bordersThickness, bordersColor);
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2*bordersThickness, height - 2*bordersThickness, fillColor);

			if (button) button->updatePositionAndSize();
		}

		void unpress()
		{ if (button) button->unpress(); }

		bool tryToPress(float mouseX, float mouseY)
		{
			if (button)
				return button->tryToPress(mouseX, mouseY);
			else
				return false;
		}

		void draw()
		{
			window.draw(borders);
			window.draw(fill);
			window.draw(text);
			if (button) button->draw();
		}
};
