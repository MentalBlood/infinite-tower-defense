#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
	int i;
	char c;
	bool b;
	unsigned int u;
	float f;
	
	printf("int\t%lu\nchar\t%lu\nbool\t%lu\nuint\t%lu\nfloat\t%lu\n",
			typeid(int).hash_code(),
			typeid(c).hash_code(),
			typeid(b).hash_code(),
			typeid(u).hash_code(),
			typeid(f).hash_code());
}
