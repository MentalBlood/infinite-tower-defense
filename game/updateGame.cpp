void updateGame()
{
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		if ((*i)->isCame())
		{
			damageTheBase((*i)->damage);
			delete *i;
			monsters.erase(i);
			i--;
			continue;
		}
		(*i)->animate();
		(*i)->moveInCorrectDirection();
	}

	processTimers();
	updateCurrentSecondsToNextWaveText();
}
