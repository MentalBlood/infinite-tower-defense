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
			  x, y, width, height,
			  relativeTextIndent;

		void press()
		{
			pressed = true;
			for (unsigned int i = 0; i < fill.getVertexCount(); i++) fill[i].color = bordersColor;
			functionOnPress();
		}

	public:
		TwoConditionButton(	void (*functionOnPress)(), void (*functionOnUnpress)(), sf::String textString,
							sf::String textFontFileName, sf::Color textColor, sf::Color fillColor, sf::Color bordersColor, 
							float relativeX, float relativeY, float relativeWidth, float relativeHeight,
							float relativeTextIndent):
			pressed(false), functionOnPress(functionOnPress), functionOnUnpress(functionOnUnpress),
			textString(textString), fillColor(fillColor), bordersColor(bordersColor),
			relativeX(relativeX), relativeY(relativeY), relativeWidth(relativeWidth), relativeHeight(relativeHeight),
			relativeTextIndent(relativeTextIndent)
		{
			font = new sf::Font;
			if (!font->loadFromFile(textFontFileName)) Closed();
			text.setFont(*font);
			text.setString(textString);
			text.setFillColor(textColor);
			updatePositionAndSize();
		}

		void updatePositionAndSize()
		{
			x = windowSize.x * relativeX;
			y = windowSize.y * relativeY;
			width = windowSize.x * relativeWidth;
			height = windowSize.y * relativeHeight;
			float bordersThickness = sqrt(width * height) / 64;

			fitTextIntoRectangle(&text, x + bordersThickness * relativeTextIndent, y + bordersThickness * relativeTextIndent,
								width - 2 * bordersThickness * relativeTextIndent,
								height - 2 * bordersThickness * relativeTextIndent);

			makeVertexArrayFrame(&borders, x, y, width, height, bordersThickness, bordersColor);
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2 * bordersThickness, height - 2 * bordersThickness, fillColor);
		}

		void unpress()
		{
			if (!pressed) return;
			pressed = false;
			for (unsigned int i = 0; i < fill.getVertexCount(); i++) fill[i].color = fillColor;
			functionOnUnpress();
		}

		bool tryToPress(float mouseX, float mouseY)
		{
			if (pressed) return true;
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
