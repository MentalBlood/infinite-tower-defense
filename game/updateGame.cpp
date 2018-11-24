void updateGame()
{
	if (pause) return;
	//monsters are moving
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		(*i)->animate();
		(*i)->moveInCorrectDirection();
	}
	updateMonstersCoordinatesInGrid();
	//shots are flying & monsters are dying
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
	{
		(*i)->checkMonsterExistance();
		(*i)->refreshLastMonsterPosition();
	}
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
	{
		(*i)->checkMonsterExistance();
		(*i)->moveCorrectlyUsingGrid();
		(*i)->animate();

		if ((*i)->isFinished())
		{
			delete *i;
			shots.erase(i);
			i--;
		}
	}

	//corpses are removed
	bool gotSomeMoney = false;
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		if ((*i)->isCame())
		{
			if (damageTheBase((*i)->damage)) return;
			delete *i;
			monsters.erase(i);
			i--;
		}
		else
		if ((*i)->isDead())
		{
			delete *i;
			monsters.erase(i);
			money += (*i)->getDamage() * (*i)->getSpeed() * (*i)->getInitialHealth();
			gotSomeMoney = true;
			i--;
		}
	}
	if (gotSomeMoney)
		updateMoneyText();

	processTimers<Tower*>(); //towers shooting

	processTimers<Monster*>(); //monsters spawning
	processTimers<char*>(); //waves starting
	updateCurrentSecondsToNextWaveText();

	moveSplinters(); //splinters moving
}
