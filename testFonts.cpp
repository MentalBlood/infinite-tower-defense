#include <SFML/Graphics.hpp>
#include <math.h>

sf::RenderWindow window;
sf::Vector2u windowSize(800, 600);

sf::VertexArray realQuad(sf::Quads, 4),
				quad(sf::Quads, 4);
sf::Text text;
float rectangleWidth = 100,
	  rectangleHeight = 50;

void fitTextIntoRectangle(float x, float y, float width, float height)
{
	//find out how many pixels is font grow up with every character size unit
	//(supposed that font grows linear)
	text.setCharacterSize(1);

	sf::FloatRect textBounds = text.getLocalBounds();
	float fontSizeCoefficientY = textBounds.height,
		  fontSizeCoefficientX = textBounds.width;

	//set the font size so that the text is placed in the button
	float fontSize = fmin(width / fontSizeCoefficientX, height / fontSizeCoefficientY);
	text.setCharacterSize(trunc(fontSize));

	//set font position so that the text is placed in the center of the button
	text.setPosition(x, y);
	textBounds = text.getGlobalBounds();
	float correctX = x + (x - textBounds.left),
		  correctY = y + (y - textBounds.top);
	text.setPosition(correctX + width/2 - textBounds.width/2, correctY + height/2 - textBounds.height/2);
}

void refreshText()
{
	fitTextIntoRectangle(window.getSize().x/2, window.getSize().y/2, rectangleWidth, rectangleHeight);

	sf::FloatRect textGlobalBounds = text.getGlobalBounds();
	realQuad[0].position = sf::Vector2f(textGlobalBounds.left, textGlobalBounds.top);
	realQuad[1].position = sf::Vector2f(textGlobalBounds.left + textGlobalBounds.width, textGlobalBounds.top);
	realQuad[2].position = sf::Vector2f(textGlobalBounds.left + textGlobalBounds.width, textGlobalBounds.top + textGlobalBounds.height);
	realQuad[3].position = sf::Vector2f(textGlobalBounds.left, textGlobalBounds.top + textGlobalBounds.height);

	quad[0].position = sf::Vector2f(window.getSize().x/2, window.getSize().y/2);
	quad[1].position = sf::Vector2f(window.getSize().x/2 + rectangleWidth, window.getSize().y/2);
	quad[2].position = sf::Vector2f(window.getSize().x/2 + rectangleWidth, window.getSize().y/2 + rectangleHeight);
	quad[3].position = sf::Vector2f(window.getSize().x/2, window.getSize().y/2 + rectangleHeight);
}

int main(void)
{
	window.create(sf::VideoMode(800, 600), "Test fonts");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("fonts/Agitpropc.otf"))
	{
		window.close();
		return 0;
	}

	text.setFont(font);
	text.setString("some text");
	text.setFillColor(sf::Color::Blue);

	for (int i = 0; i < 4; i++)
		quad[i].color = sf::Color::Green;

	for (int i = 0; i < 4; i++)
		realQuad[i].color = sf::Color::Red;

	refreshText();

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
					rectangleHeight -= 1;
				else if (event.key.code == sf::Keyboard::Down)
					rectangleHeight += 1;
				else if (event.key.code == sf::Keyboard::Left)
					rectangleWidth -= 1;
				else if (event.key.code == sf::Keyboard::Right)
					rectangleWidth += 1;
				else continue;

				refreshText();

				printf("rectangle size size = (%f, %f)\n", rectangleWidth, rectangleHeight);
			}
		}

		window.clear(sf::Color::Black);
		window.draw(quad);
		window.draw(realQuad);
		window.draw(text);
		window.display();
	}

	return 0;
}
