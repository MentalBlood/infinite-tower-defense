std::vector<Parameter*> monstersParameters;

enum monstersParameter
{
	NUMBER,
	SECONDS_BETWEEN_SPAWNS,
	SPEED,
	HEALTH,
	monstersParametersCount
};

void loadMonstersParameters()
{
	FILE *file = fopen("monstersParametres.txt", "rb");
	if (!file) Closed();

	monstersParameters.resize(monstersParametersCount);
	for (unsigned int i = 0; i < monstersParameters.size(); i++)
		monstersParameters[i] = new Parameter(file);

	fclose(file);
}

void clearMonsterParameters()
{
	for (unsigned int i = 0; i < monstersParameters.size(); i++)
		delete monstersParameters[i];
}

void calculateNextWaveMonstersParametres()
{
	for (unsigned int i = 0; i < monstersParameters.size(); i++)
		monstersParameters[i]->setNextValue();
}
