#include <iostream>
#include "TestProvider.h"
#include "OrderedTests.h"
#include "DetachedTests.h"

using std::cout;
using std::cin;

void RunTests()
{
	for (auto& test : tests)
	{
		cout << "Testing " << test.functionName << "()... \n";
		test();
	}

	cout << "Tests done.\n";
	cout << "Press enter to exit.";
	cin.get();
}

int main()
{
	RunTests();
}