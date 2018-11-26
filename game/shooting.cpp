#include "shots/Shot.cpp"
#include "shots/ShotTypeA.cpp"
#include "shots/ShotTypeB.cpp"
#include "shots/ShotTypeC.cpp"
#include "shots/ShotTypeD.cpp"
#include "shots/ShotTypeE.cpp"
std::list<Shot*> shots;

void tryToShoot(Tower *tower)
{
	float minDistanceSquare = tower->getRangeSquare();
	Monster *nearestMonster = NULL;

	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		float distanceSquareToThisMonster =
			vectorLengthSquare(((*i)->getPosition() - tower->getPosition()) / gameMap->getScale());

		if (distanceSquareToThisMonster <= tower->getRangeSquare())
			if (distanceSquareToThisMonster <= minDistanceSquare)
			{
				nearestMonster = (*i);
				minDistanceSquare = distanceSquareToThisMonster;
			}
	}

	if (!nearestMonster)
	{		
		new Timer<Tower*>(0, tryToShoot, tower);
		return;
	}

	if (tower->getShotType() == TYPE_A)
		shots.push_back(new ShotTypeA(tower, nearestMonster, sf::Color(30, 130, 30), sf::Color(130, 255, 130)));
	else if (tower->getShotType() == TYPE_B)
		shots.push_back(new ShotTypeB(tower, nearestMonster, sf::Color::Blue, 16));
	else if (tower->getShotType() == TYPE_C)
		shots.push_back(new ShotTypeC(tower, nearestMonster, sf::Color::Red));
	else if (tower->getShotType() == TYPE_D)
		shots.push_back(new ShotTypeD(tower, nearestMonster));
	else if (tower->getShotType() == TYPE_E)
		shots.push_back(new ShotTypeE(tower, nearestMonster));

	new Timer<Tower*>(tower->getParameterValue(SHOTS_DELAY), tryToShoot, tower);
}
