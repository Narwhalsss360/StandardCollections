#include <iostream>
#include "TestProvider.h"
#include "OrderedTests.h"

using std::cout;

void RunTests()
{
	for (auto& test : tests)
	{
		cout << "Testing " << test.functionName << "()... \n";
		test();
	}

	test_standard_output_write("Tests done.");
}

int main()
{
	RunTests();
}