class Parameter
{
	private:
		float currentValue,
			  adder,
			  multiplier;

	public:
		Parameter(FILE *file)
		{
			fscanf(file, "%f%f%f", &currentValue, &adder, &multiplier);
			printf("currentValue = %f\nadder = %f\nmultiplier = %f\n",
					currentValue, adder, multiplier);
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

		void calculateNextValue()
		{ currentValue = (currentValue + adder) * multiplier; }
};
