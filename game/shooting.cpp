#include "shots/Shot.cpp"
#include "shots/ShotTypeA.cpp"
std::list<Shot*> shots;

void tryToShoot(Tower *tower)
{
	sf::Vector2f vectorDistance;
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		vectorDistance = ((*i)->getPosition() - tower->getPosition()) / gameMap->getScale();
		if ((vectorDistance.x * vectorDistance.x + vectorDistance.y * vectorDistance.y) <= tower->getRangeSquare())
		{
			if (tower->getShotType() == TYPE_A)
				shots.push_back(new ShotTypeA(tower, (*i), sf::Color(130, 30, 30), sf::Color(255, 130, 130)));
			new Timer<Tower*>(tower->getShotsDelay(), tryToShoot, tower);
			return;
		}
	}
	new Timer<Tower*>(0, tryToShoot, tower);
}
