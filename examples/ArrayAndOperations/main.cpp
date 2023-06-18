#define EXAMPLE_NAME "ArrayAndOperations"

//#include "src/LightCollection.h" //Include this to remove some functionality, reduces program size.
#include "src/StandardCollections.h"
#include <iostream>

//const is applied to unsigned int as well.
const Array<unsigned int, 5> someDigitsOfPi = { 3, 1, 4, 1, 5 }; //<- Initializer list supported.

using std::cout;
using std::endl;

void showSomeDigitsOfPi()
{
	cout << "The digits of pi are ";
	for (const unsigned int& digit : someDigitsOfPi) //Alternatively -> for (const unsigned int& digit : Iterate(someDigitsOfPi))
		cout << digit;
	cout << '\n';

	index_t countOf1s = someDigitsOfPi.Count(1);
	cout << "There are " << countOf1s << " 1s in Pi\n";
}

unsigned int nextInFib(unsigned int previous, unsigned int current)
{
	return previous + current;
}

//Use type index_t for accessing elements in array, if signed version is required, use find_index_t
constexpr index_t sequenceIterations = 13;
Array<unsigned int, sequenceIterations + 2> fib; //+ 2 because first 2 is just a setup.
void calculateAndShowFib()
{
	fib[0] = 1;
	fib[1] = 1;

	//CollectionLength(fib); //<- Another way to get the length, function also work with c arrays (not pointers to arrays).
	for (index_t iPrevious = 0, iCurrent = 1, iNext = 2; iNext < fib.Length(); iPrevious++, iCurrent++, iNext++)
		fib[iNext] = nextInFib(fib[iPrevious], fib[iCurrent]);

	cout << "Fib sequence:\n";
	for (const Enumeration<unsigned int&>& e : Enumerate(fib))
		cout << "Iteration " << e.index + 1 << ": " << e.value << '\n';
}

void findPattern()
{
	cout << "Is there a pattern? you tell me.\n";
	for (const Zipping<const unsigned int&, const unsigned int&>& z : Zip(someDigitsOfPi, fib)) //Iterates through the smallest collection.
		cout << "Index " << z.index << " Pi:" << z.value1 << ", Fib:" << z.value2 << '\n';
}

unsigned int userDefinedCaster(double& real)
{
	return (unsigned int)real;
}

void castingArrays()
{
	Array<double, 2> real = { 3.1415, 1.414 };
	Array<unsigned int, 2> natural;

	CastCollection<double, unsigned int>(real, natural);
	//CastCollection<double, unsigned int>(real, natural, userDefinedCaster); //<- Use this to define how the types are casted.

	cout << "Real | Natural\n";

	for (const auto& z : ZipIterable<Collection<double>, double, unsigned int, Collection<unsigned int>>(&real, &natural, 0, 2)) //Zip() doesnt currently work on differing types
	//                               ^                   ^       ^             ^                         ^      ^         ^  ^
	//                       Type of collection 1   col 1 type col 2 type  Type of collection         col1ptr col2ptr  start end
	{
		cout << z.value1 << " | " << z.value2 << '\n';
	}
	cout << '\n';
}

void safelyIndexing()
{
	index_t index = 3360; //Clearly out of bounds...
	cout << "index: " << index << '\n';
	index = SafeIndex(index, CollectionLength(fib)); //With the length, the index is ran through modulo operator to make sure index is not out of bounds.
	cout << "index: " << index << '\n';
}

//Linear function
double f(double x)
{
	return sqrt(2 * x);
}

//Linear function, output is just a reference parameter.
void f_out(const index_t x, double& y)
{
	y = f(x);
}

//Prints number with index. const to promise not to change it, for compatability with non-const or const Array.
void printWithIndex(const index_t x, const double& y)
{
	cout << '[' << x << "]:" << y << '\n';
}

void forEachIteration()
{
	Array<double, 10> functionValues;
	functionValues.ForEach(f_out);
	cout << "Function values:\n";
	functionValues.ForEach(printWithIndex);
}

//Prints number with index. const to promise not to change it, for compatability with non-const or const Array.
void printWithIndex(const index_t x, const char& y)
{
	//Prints character, else ascii number
	if (y > '0')
		cout << '[' << x << "]:" << y << '\n';
	else
		cout << '[' << x << "]: ASCII " << (int)y << '\n';
}

void finding()
{
	char cstr[36] = "My null terminated(szType) c string";
	Array<char, 36> stringBuffer = Array<char, 36>(cstr);
	cout << "stringBuffer contains:\n";
	stringBuffer.ForEach(printWithIndex);

	IndexValuePair<const char> found = stringBuffer.Find('e');
	if (found.valid)
		cout << "found '" << *found.value << "' at index " << found.index;
	else
		cout << "Did not find.";

	auto foundLast = stringBuffer.FindLast('e');
}

int main()
{
	cout << EXAMPLE_NAME << " Example.\n";
	showSomeDigitsOfPi();
	calculateAndShowFib();
	findPattern();
	castingArrays();
	safelyIndexing();
	forEachIteration();
	finding();
	cout << endl;
}