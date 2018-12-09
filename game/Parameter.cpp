class Parameter
{
	private:
		float currentValue,
			  nextValue,
			  adder,
			  multiplier;

		float calculateNextValue()
		{ return (currentValue + adder) * multiplier; }

	public:
		Parameter(FILE *file)
		{
			fscanf(file, "%f%f%f", &currentValue, &adder, &multiplier);
			nextValue = calculateNextValue();
		}

		static void rawWrite(FILE *file, float currentValueArg, float adderArg, float multiplierArg)
		{
			size_t sizeOfFloat = sizeof(float);
			fwrite(&currentValueArg, sizeOfFloat, 1, file);
			fwrite(&adderArg, sizeOfFloat, 1, file);
			fwrite(&multiplierArg, sizeOfFloat, 1, file);
		}

		static void write(	FILE *file, float currentValueArg, float adderArg, float multiplierArg,
							bool firstWrite = false)
		{
			if (!firstWrite)
				fprintf(file, " ");
			fprintf(file, "%f %f %f", currentValueArg, adderArg, multiplierArg);
		}

		float getValue()
		{ return currentValue; }

		float getNextValue()
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
