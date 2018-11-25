template <class Type>
class Parameter
{
	private:
		Type currentValue;

		Type adder;
		float multiplier;

		bool typeIsFloat;

	public:
		Parameter(FILE *file, bool typeIsFloat, bool raw = false):
		typeIsFloat(typeIsFloat)
		{
			if (raw)
			{
				fread(&currentValue, sizeof(Type), 1, file);
				fread(&adder, sizeof(Type), 1, file);
				fread(&multiplier, sizeof(float), 1, file);
			}
			else
			{
				if (typeIsFloat)
					fscanf(file, "%f%f%f", &currentValue, &adder, &multiplier);
				else
					fscanf(file, "%u%u%f", &currentValue, &adder, &multiplier);
			}
		}

		static void rawWrite(FILE *file, Type currentValueArg, Type adderArg, float multiplierArg)
		{
			fwrite(&currentValueArg, sizeof(Type), 1, file);
			fwrite(&adderArg, sizeof(Type), 1, file);
			fwrite(&multiplierArg, sizeof(float), 1, file);
		}

		static void write(	FILE *file, Type currentValueArg, Type adderArg, float multiplierArg,
							bool typeIsFloat, bool firstWrite = false)
		{
			if (!firstWrite)
				fprintf(file, " ");
			if (typeIsFloat)
				fprintf(file, "%f %f %f", currentValueArg, adderArg, multiplierArg);
			else
				fprintf(file, "%u %u %f", currentValueArg, adderArg, multiplierArg);
		}

		Type getValue()
		{ return currentValue; }

		void calculateNextValue()
		{ currentValue = (currentValue + adder) * multiplier; }
};
