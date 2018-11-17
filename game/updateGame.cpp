void updateGame()
{
	if (monstersMoving)
		for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		{
			(*i)->animate();
			(*i)->moveInCorrectDirection();
		}
	//shots flying & monsters dying
	if (shotsFlying)
	{
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

	if (shotsFlying)
		processTimers<Tower*>(); //towers shooting

	if (monstersMoving)
	{
		processTimers<Monster*>(); //monsters spawning
		processTimers<char*>(); //waves starting
		updateCurrentSecondsToNextWaveText();
	}
}
