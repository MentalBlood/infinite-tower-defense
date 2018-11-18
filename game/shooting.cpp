#include "shots/Shot.cpp"
#include "shots/ShotTypeA.cpp"
#include "shots/ShotTypeB.cpp"
#include "shots/ShotTypeC.cpp"
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
				shots.push_back(new ShotTypeA(tower, (*i), sf::Color(30, 130, 30), sf::Color(130, 255, 130)));
			else
			if (tower->getShotType() == TYPE_B)
				shots.push_back(new ShotTypeB(tower, (*i), sf::Color::Blue, 16));
			if (tower->getShotType() == TYPE_C)
				shots.push_back(new ShotTypeC(tower, (*i), sf::Color(180, 0, 0), sf::Color(255, 40, 40)));
			new Timer<Tower*>(tower->getShotsDelay(), tryToShoot, tower);
			return;
		}
	}
	new Timer<Tower*>(0, tryToShoot, tower);
}
