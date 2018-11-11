template <class Type>
class Parameter
{
	private:
		Type currentValue;

		Type adder;
		float multiplier;

	public:
		Parameter(FILE *file)
		{
			fread(&currentValue, sizeof(Type), 1, file);
			fread(&adder, sizeof(Type), 1, file);
			fread(&multiplier, sizeof(float), 1, file);
		}

		static void write(FILE *file, Type currentValueArg, Type adderArg, float multiplierArg)
		{
			fwrite(&currentValueArg, sizeof(Type), 1, file);
			fwrite(&adderArg, sizeof(Type), 1, file);
			fwrite(&multiplierArg, sizeof(float), 1, file);
		}

		Type getValue()
		{ return currentValue; }

		void calculateNextValue()
		{ currentValue = (currentValue + adder) * multiplier; }
};

Parameter<unsigned int> *nextWaveNumberOfMonsters;
Parameter<float>		*nextWaveSecondsBetweenSpawns,
						*nextWaveMonstersSpeed,
						*nextWaveMonstersHealth;

void loadMonstersParameters()
{
	/*FILE *file = fopen("monstersParametres.txt", "wb");
	if (!file) Closed();

	Parameter<unsigned int>::write(file, 1, 1, 1);
	Parameter<float>::write(file, 1, 0.5, 0.5);
	Parameter<float>::write(file, 0.15, -0.01, 1.5);
	Parameter<float>::write(file, 5, -1, 1.5);

	fclose(file);*/

	FILE *file = fopen("monstersParametres.txt", "rb");
	if (!file) Closed();

	nextWaveNumberOfMonsters = new Parameter<unsigned int>(file);
	nextWaveSecondsBetweenSpawns = new Parameter<float>(file);
	nextWaveMonstersSpeed = new Parameter<float>(file);
	nextWaveMonstersHealth = new Parameter<float>(file);

	fclose(file);
}

void calculateNextWaveMonstersParametres()
{
	nextWaveNumberOfMonsters->calculateNextValue();
	nextWaveSecondsBetweenSpawns->calculateNextValue();
	nextWaveMonstersSpeed->calculateNextValue();
	nextWaveMonstersHealth->calculateNextValue();
}
