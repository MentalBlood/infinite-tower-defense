void fitTextIntoRectangle(sf::Text *text, float x, float y, float width, float height)
{
	//find out how many pixels is font grow up with every character size unit
	//(supposed that font grows linear)
	text->setCharacterSize(1);

	sf::FloatRect textBounds = text->getLocalBounds();
	float fontSizeCoefficientY = textBounds.height,
		  fontSizeCoefficientX = textBounds.width;

	//set the font size so that the text is placed in the button
	float fontSize = fmin(width / fontSizeCoefficientX, height / fontSizeCoefficientY);
	text->setCharacterSize(fontSize);

	//set font position so that the text is placed in the center of the button
	text->setPosition(x, y);
	textBounds = text->getGlobalBounds();
	float correctX = x + (x - textBounds.left),
		  correctY = y + (y - textBounds.top);
	text->setPosition(correctX + width/2 - textBounds.width/2, correctY + height/2 - textBounds.height/2);
}
