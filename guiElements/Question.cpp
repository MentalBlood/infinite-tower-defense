class Question
{
	private:
		void (*leftButtonFunction)(),
			 (*rightButtonFunction)();

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

		TwoConditionButton *leftButton,
						   *rightButton;

		float x, y,
			  width, height;

		sf::VertexArray fill,
						borders;

	public:
		Question(void (*leftButtonFunction)(), void (*rightButtonFunction)(),
				sf::String textString, sf::String leftButtonString, sf::String rightButtonString,
				enum fontType fontIndex,
				float relativeX, float relativeY, float relativeWidth, float relativeHeight, float relativeTextIndent,
				sf::Color textColor, sf::Color fillColor, sf::Color bordersColor, float buttonsRelativeBordersThickness):
			leftButtonFunction(leftButtonFunction), rightButtonFunction(rightButtonFunction),
			textString(textString),
			relativeX(relativeX), relativeY(relativeY), relativeWidth(relativeWidth), relativeHeight(relativeHeight),
			relativeTextIndent(relativeTextIndent),
			textColor(textColor), fillColor(fillColor), bordersColor(bordersColor)
		{
			text.setFont(fonts[fontIndex]);
			text.setString(textString);
			text.setFillColor(textColor);
			leftButton = new TwoConditionButton(nothing, leftButtonFunction, leftButtonString, fontIndex,
												textColor, fillColor, bordersColor,
												relativeX + relativeWidth/5, relativeY + relativeHeight*3/4,
												relativeWidth/5, relativeHeight/8, relativeTextIndent,
												buttonsRelativeBordersThickness);
			rightButton = new TwoConditionButton(nothing, rightButtonFunction, rightButtonString, fontIndex,
												textColor, fillColor, bordersColor,
												relativeX + 3 * relativeWidth/5, relativeY + relativeHeight*3/4,
												relativeWidth/5, relativeHeight/8, relativeTextIndent,
												buttonsRelativeBordersThickness);
			updatePositionAndSize();
		}

		~Question()
		{
			delete leftButton;
			delete rightButton;
		}

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

			leftButton->updatePositionAndSize();
			rightButton->updatePositionAndSize();
		}

		void unpress()
		{
			leftButton->unpress();
			rightButton->unpress();
		}

		bool tryToPress(float mouseX, float mouseY)
		{ return (leftButton->tryToPress(mouseX, mouseY) || rightButton->tryToPress(mouseX, mouseY)); }

		void draw()
		{
			window.draw(borders);
			window.draw(fill);
			window.draw(text);
			leftButton->draw();
			rightButton->draw();
		}
};
