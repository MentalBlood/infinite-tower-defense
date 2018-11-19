void updateGame()
{
	if (pause) return;
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		(*i)->animate();
		(*i)->moveInCorrectDirection();
	}
	//shots flying & monsters dying
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
	{
		(*i)->checkMonsterExistance();
		(*i)->refreshLastMonsterPosition();
	}
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
	{
		(*i)->checkMonsterExistance();
		(*i)->moveCorrectly();
		(*i)->animate();

		if ((*i)->isFinished())
		{
			delete *i;
			shots.erase(i);
			i--;
		}
	}

	//corpses are removed
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
			i--;
		}
	}

	processTimers<Tower*>(); //towers shooting

	processTimers<Monster*>(); //monsters spawning
	processTimers<char*>(); //waves starting
	updateCurrentSecondsToNextWaveText();

	moveSplinters(); //splinters moving
}
