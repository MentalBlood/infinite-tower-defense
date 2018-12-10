class Parameter
{
	private:
		double currentValue,
			   nextValue,
			   adder,
			   multiplier;

		double calculateNextValue()
		{ return (currentValue + adder) * multiplier; }

	public:
		Parameter(FILE *file)
		{
			fscanf(file, "%lf%lf%lf", &currentValue, &adder, &multiplier);
			nextValue = calculateNextValue();
		}

		static void rawWrite(FILE *file, double currentValueArg, double adderArg, double multiplierArg)
		{
			size_t sizeOfFloat = sizeof(float);
			fwrite(&currentValueArg, sizeOfFloat, 1, file);
			fwrite(&adderArg, sizeOfFloat, 1, file);
			fwrite(&multiplierArg, sizeOfFloat, 1, file);
		}

		static void write(	FILE *file, double currentValueArg, double adderArg, double multiplierArg,
							bool firstWrite = false)
		{
			if (!firstWrite)
				fprintf(file, " ");
			fprintf(file, "%lf %lf %lf", currentValueArg, adderArg, multiplierArg);
		}

		double getAdder()
		{ return adder; }

		double getMultiplier()
		{ return multiplier; }

		double getValue()
		{ return currentValue; }

		double getNextValue()
		{ return nextValue; }

		void setNextValue()
		{
			currentValue = nextValue;
			nextValue = calculateNextValue();
		}
};

void setNextParametersValues(std::vector<Parameter*> & parameters)
{
	for (unsigned int i = 0; i < parameters.size(); i++)
		parameters[i]->setNextValue();
}
