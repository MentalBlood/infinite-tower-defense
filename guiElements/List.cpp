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
		enum fontType itemsFontIndex;

		std::vector<sf::Text> items;

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
			enum fontType nameFontIndex, enum fontType itemsFontIndex,
			float relativeX, float relativeY,
			float relativeWidth, float relativeHeight, int numberOfItemsShown,
			sf::Color nameColor, sf::Color itemsColor, sf::Color fillColor, sf::Color bordersColor, sf::Color selectorColor):
			numberOfItemsShown(numberOfItemsShown), firstItemShownNumber(0), lastItemShownNumber(-1), selectedItemNumber(0),
			nameString(nameString), relativeX(relativeX), relativeY(relativeY),
			relativeWidth(relativeWidth), relativeHeight(relativeHeight), functionOnSelect(functionOnSelect),
			itemsColor(itemsColor), fillColor(fillColor), bordersColor(bordersColor), selectorColor(selectorColor),
			itemsFontIndex(itemsFontIndex)
		{
			nameText.setFont(fonts[nameFontIndex]);
			nameText.setString(nameString);
			nameText.setFillColor(nameColor);
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
			selector.setPosition(x + bordersThickness, separatorY + itemHeight * (selectedItemNumber - firstItemShownNumber));
			selector.setFillColor(sf::Color(0, 0, 0, 0));
			selectorBordersThickness = sqrt(selector.getSize().x * selector.getSize().y)/64;
			selector.setOutlineThickness(-selectorBordersThickness);
			selector.setOutlineColor(selectorColor);
			makeVertexArrayQuad(&fill, x + bordersThickness, y + bordersThickness,
								width - 2*bordersThickness, height - 2*bordersThickness, fillColor);
		}

		void addItem(sf::String name)
		{
			sf::Text *newItem = new sf::Text(name, fonts[itemsFontIndex]);
			newItem->setFillColor(itemsColor);

			bool inserted = false;
			for (unsigned int i = 0; i < items.size(); i++)
				if (name < items[i].getString())
				{
					items.insert(items.begin() + i, *newItem);
					inserted = true;
					break;
				}

			if (!inserted)
				items.insert(items.end(), *newItem);

			if (items.size() < numberOfItemsShown)
				lastItemShownNumber = items.size() - 1;
			else
				lastItemShownNumber = numberOfItemsShown-1;
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
		{ functionOnSelect(items[selectedItemNumber].getString()); }

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

			selectedItemNumber = selectedNumber + firstItemShownNumber;
			selector.setPosition(x + bordersThickness, separatorY + itemHeight * selectedNumber);
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
