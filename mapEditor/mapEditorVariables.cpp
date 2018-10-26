Map *mapEditorMap;
float mapEditorCellRelativeSize;

bool mapEditorMapDragging,
	 mapEditorAddingPathByMouse;
float mapEditorMapDraggingMouseX1,
	  mapEditorMapDraggingMouseY1;
sf::Vector2f mapEditorMapDraggingMapInitialCoordinates;

float minf(float a, float b)
{
	if (a < b) return a;
	return b;
}

class TwoConditionButton
{
	private:
		bool pressed;
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
			  relativeHeight;

	public:
		TwoConditionButton(sf::String textStringArg, sf::String textFontFileName,
					sf::Color textColor, sf::Color fillColor, sf::Color bordersColor, 
					float relativeXArg, float relativeYArg, float relativeWidthArg, float relativeHeightArg):
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
			float	x = windowSize.x * relativeX,
					y = windowSize.y * relativeY,
					width = windowSize.x * relativeWidth,
					height = windowSize.y * relativeHeight;

			float bordersThickness = sqrt(width * height) / 64;
			text.setCharacterSize(10);
			float fontSizeCoefficientY = text.getLocalBounds().height / 10,
				  fontSizeCoefficientX = text.getLocalBounds().width / 10;
			float fontSize = minf(width*7/8 / fontSizeCoefficientX, (height - bordersThickness*4) / fontSizeCoefficientY);
			text.setCharacterSize(fontSize);

			text.setPosition(x + width/16, y + height/2 - fontSize*fontSizeCoefficientY/2);

			makeVertexArrayFrame(&borders, x, y, width, height, bordersThickness, bordersColor);
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2*bordersThickness, height - 2*bordersThickness, fillColor);
		}

		void press()
		{
			pressed = true;
			for (int i = 0; i < 4; i++) fill[i].color = bordersColor;
		}

		void unpress()
		{
			pressed = false;
			for (int i = 0; i < 4; i++) fill[i].color = fillColor;
		}

		void draw()
		{
			window.draw(borders);
			window.draw(fill);
			window.draw(text);
		}
};

//std::vector<TwoConditionButton> mapEditorButtons;

void updateMapEditorVariables()
{
//	for (int i = 0; i < mapEditorButtons.size(); i++)
//		mapEditorButtons[i].updatePositionAndSize();
}

void setMapEditorVariables(int mapEditorMapWidth, int mapEditorMapHeight)
{
	mapEditorMap = new Map(	mapEditorMapWidth, mapEditorMapHeight,
							sf::Color(150, 150, 64, 196), sf::Color(0, 0, 196, 128), sf::Color(128, 0, 196));
	mapEditorCellRelativeSize = 0.9;
	mapEditorMap->setTextures(mapEditorCellRelativeSize);
	mapEditorMap->setPosition(0, 0);
	mapEditorMapDragging = false;

	windowSize = window.getSize();
//	mapEditorButtons.push_back(TwoConditionButton(	"change spawner", "fonts/mapEditorButtonsFont.otf",
//													sf::Color(255, 196, 64), sf::Color(0, 0, 64), sf::Color(64, 64, 128),
//													0.75, 0.05, 0.2, 0.08));

	updateMapEditorVariables();
}
