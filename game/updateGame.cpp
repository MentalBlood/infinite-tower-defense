void updateGame()
{
	elapsed *= gameSpeed;
	if (developerMode)
		tryToMakeNextAction();

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
	bool thereWereSomeMonsters = (monsters.size() > 0);
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
			money += 4 * (*i)->getDamage() * (*i)->getSpeed() * (*i)->getInitialHealth();
			delete *i;
			monsters.erase(i);
			gotSomeMoney = true;
			i--;
		}
	}
	if (thereWereSomeMonsters && (!monsters.size()) && (!Timer<Monster*>::first))
		abandonTimers<char>();
	if (gotSomeMoney) updateMoneyText();

	processTimers<Tower*>(); //towers shooting

	processTimers<Monster*>(); //monsters spawning
	processTimers<char>(); //waves starting
	updateCurrentSecondsToNextWaveText();

	moveSplinters(); //splinters moving
}
