/*sf::Uint8 changeColorComponent(sf::Uint8 *colorComponent, sf::Uint8 delta)
{
	if ((255 - colorComponent) <= delta) colorComponent += delta;
	else
	{
		sf::Uint8 newDelta = delta - (255 - colorComponent);
		colorComponent = 255;
		return newDelta;
	}
}*/

void nextColor(sf::Color &color, sf::Uint8 delta, sf::Color min, sf::Color max)
{
	if ((color.r == max.r) && (color.g < max.g) && (color.b == min.b))
		color += sf::Color(0, delta, 0, 0);
	else
	if ((color.r > min.r) && (color.g == max.g) && (color.b == min.b))
		color -= sf::Color(delta, 0, 0, 0);
	else
	if ((color.r == min.r) && (color.g == max.g) && (color.b < max.b))
		color += sf::Color(0, 0, delta, 0);
	else
	if ((color.r == min.r) && (color.g > min.g) && (color.b == max.b))
		color -= sf::Color(0, delta, 0, 0);
	else
	if ((color.r < max.r) && (color.g == min.g) && (color.b == max.b))
		color += sf::Color(delta, 0, 0, 0);
	else
	if ((color.r == max.r) && (color.g == min.g) && (color.b > min.b))
		color -= sf::Color(0, 0, delta, 0);

	if (color.r < min.r) color.r = min.r;
	else
	if (color.r > max.r) color.r = max.r;

	if (color.g < min.g) color.g = min.g;
	else
	if (color.g > max.g) color.g = max.g;

	if (color.b < min.b) color.b = min.b;
	else
	if (color.b > max.b) color.b = max.b;
}
