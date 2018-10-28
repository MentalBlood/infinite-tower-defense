void fitTextIntoRectangle(sf::Text *text, float x, float y, float width, float height)
{
	//find out how many pixels is font grow up with every character size unit
	//(supposed that font grows linear)
	text->setCharacterSize(10);
	sf::FloatRect textLocalBounds = text->getLocalBounds();
	float fontSizeCoefficientY = textLocalBounds.height / 10,
		  fontSizeCoefficientX = textLocalBounds.width / 10;

	//set the font size so that the text is placed in the button
	float fontSize = fmin(width*3/4 / fontSizeCoefficientX, height*3/4 / fontSizeCoefficientY);
	text->setCharacterSize(fontSize);

	//set font position so that the text is placed in the center of the button
	textLocalBounds = text->getLocalBounds();
	text->setPosition(	x + width/2 - textLocalBounds.width/2,
						y + height/2 - textLocalBounds.height/2);
}
