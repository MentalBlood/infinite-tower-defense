void updateGame()
{
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		(*i)->animate();
		(*i)->moveInCorrectDirection();
	}
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
	{
		if ((*i)->isFinished())
		{
			delete *i;
			shots.erase(i);
			i--;
		}
		else
		{
			(*i)->move();
			(*i)->animate();
		}
	}
	
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

	processTimers<Tower*>();
	processTimers<Shot*>();
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
		(*i)->animate();

	processTimers<Monster*>();
	processTimers<char*>();
	updateCurrentSecondsToNextWaveText();
}
