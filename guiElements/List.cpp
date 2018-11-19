class List
{
	private:
		unsigned int	numberOfItemsShown,
						firstItemShownNumber;
		int lastItemShownNumber;
		unsigned int selectedItemNumber;

		sf::String nameString;

		float relativeX,
			  relativeY,
			  relativeWidth,
			  relativeHeight;

		void (*functionOnSelect)(std::string);

		sf::Color	itemsColor,
					fillColor,
					bordersColor,
					selectorColor;

		std::vector<sf::Text> items;
		std::vector<std::string> itemsStringsToReturn;

		sf::Font	nameFont,
					itemsFont;

		sf::Text nameText;

		sf::VertexArray nameFrame,
						itemsFrame,
						fill;
		sf::RectangleShape selector;
		
		float bordersThickness,
			  selectorBordersThickness,
			  separatorY,
			  itemHeight,
			  x, y, width, height;

	public:
		List(sf::String nameString, void (*functionOnSelect)(std::string),
			sf::String nameFontFileName, sf::String itemsFontFileName,
			float relativeX, float relativeY,
			float relativeWidth, float relativeHeight, int numberOfItemsShown,
			sf::Color nameColor, sf::Color itemsColor, sf::Color fillColor, sf::Color bordersColor, sf::Color selectorColor):
			numberOfItemsShown(numberOfItemsShown), firstItemShownNumber(0), lastItemShownNumber(-1), selectedItemNumber(0),
			nameString(nameString), relativeX(relativeX), relativeY(relativeY),
			relativeWidth(relativeWidth), relativeHeight(relativeHeight), functionOnSelect(functionOnSelect),
			itemsColor(itemsColor), fillColor(fillColor), bordersColor(bordersColor), selectorColor(selectorColor)
		{
			if (!nameFont.loadFromFile(nameFontFileName)) Closed();
			nameText.setFont(nameFont);
			nameText.setString(nameString);
			nameText.setFillColor(nameColor);
			if (!itemsFont.loadFromFile(itemsFontFileName)) Closed();
			updatePositionAndSize();
		}

		void updateItems()
		{
			if (!items.size()) return;
			float itemY = separatorY;
			for (int i = firstItemShownNumber; i <= lastItemShownNumber; i++, itemY += itemHeight)
				fitTextIntoRectangle(&items[i], x + selectorBordersThickness, itemY + selectorBordersThickness,
									width - 2*selectorBordersThickness, itemHeight - 2*selectorBordersThickness);
		}

		void updatePositionAndSize()
		{
			x = windowSize.x * relativeX;
			y = windowSize.y * relativeY;
			width = windowSize.x * relativeWidth;
			height = windowSize.y * relativeHeight;
			bordersThickness = sqrt(width * height) / 64;

			separatorY = y + height/8; //between name and elements
			itemHeight = (height - separatorY - bordersThickness) / numberOfItemsShown;

			fitTextIntoRectangle(&nameText, x + bordersThickness, y + bordersThickness,
								width - 2*bordersThickness, separatorY - y - 2*bordersThickness);
			updateItems();

			makeVertexArrayFrame(&nameFrame, x, y, width, separatorY - y, bordersThickness, bordersColor);
			makeVertexArrayFrame(&itemsFrame, x, separatorY - bordersThickness, width, y + height - separatorY + bordersThickness, bordersThickness, bordersColor);
			selector.setSize(sf::Vector2f(width - 2*bordersThickness, itemHeight));
			selector.setPosition(x + bordersThickness, separatorY);
			selector.setFillColor(sf::Color(0, 0, 0, 0));
			selectorBordersThickness = sqrt(selector.getSize().x * selector.getSize().y)/64;
			selector.setOutlineThickness(-selectorBordersThickness);
			selector.setOutlineColor(selectorColor);
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2*bordersThickness, height - 2*bordersThickness, fillColor);
		}

		void addItem(sf::String name, sf::String stringToReturn)
		{
			sf::Text *newItem = new sf::Text(name, itemsFont);
			newItem->setFillColor(itemsColor);
			items.push_back(*newItem);
			itemsStringsToReturn.push_back(stringToReturn);
			if ((lastItemShownNumber - int(firstItemShownNumber)) < int(numberOfItemsShown-1))
			{
				++lastItemShownNumber;
				updateItems();
			}
		}

		void selectNext()
		{
			if (selectedItemNumber == (items.size()-1)) return;

			if (int(selectedItemNumber) == lastItemShownNumber)
			{
				++firstItemShownNumber;
				++lastItemShownNumber;
				updateItems();
			}
			else
				selector.move(0, itemHeight);
			++selectedItemNumber;
		}

		void selectPrevious()
		{
			if (selectedItemNumber == 0) return;

			if (selectedItemNumber == firstItemShownNumber)
			{
				--firstItemShownNumber;
				--lastItemShownNumber;
				updateItems();
			}
			else
				selector.move(0, -itemHeight);
			--selectedItemNumber;
		}

		void selectThis()
		{ functionOnSelect(itemsStringsToReturn[selectedItemNumber]); }

		bool selectByMouse(float mouseY)
		{
			bool mouseOnItem = true;
			unsigned int selectedNumber;
			if (mouseY < separatorY)
			{
				selectedNumber = 0;
				mouseOnItem = false;
			}
			else
			{
				selectedNumber = (unsigned int)((mouseY - separatorY) / itemHeight);
				if (selectedNumber > (lastItemShownNumber-firstItemShownNumber))
				{
					selectedNumber = (lastItemShownNumber-firstItemShownNumber);
					mouseOnItem = false;
				}
			}

			selectedItemNumber = selectedNumber;
			selector.setPosition(x + bordersThickness, separatorY + itemHeight * selectedItemNumber);
			return mouseOnItem;
		}

		void draw()
		{
			window.draw(fill);
			window.draw(nameFrame);
			window.draw(itemsFrame);
			window.draw(nameText);
			if (!items.size()) return;
			for (int i = firstItemShownNumber; i <= lastItemShownNumber; i++)
				window.draw(items[i]);
			window.draw(selector);
		}
};
