#include <iostream>
#include "CStyleArrayTest.h"
#include "ArrayTest.h"

using std::cout;

int main()
{
	for (auto& test : tests)
	{
		cout << "Testing " << test.functionName << "()... \n";
		test();
	}

	test_standard_output_write("Tests done.");
}