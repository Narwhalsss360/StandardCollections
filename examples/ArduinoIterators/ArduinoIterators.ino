#include <StandardCollections.h>

#define SERIAL_BAUDRATE 115200

/*
	How range based for loops work.
*/

int mysteriousSequence[] = { 0, 1, 1, 2, 3, 5, 13, 21, 34 };

void setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	while (!Serial); //Waiting for serial port to open.

	//pointer style:
	int* startPointerW = mysteriousSequence;
	int* endPointerW = &mysteriousSequence[CollectionLength(mysteriousSequence)]; //last pointer must be one greater than last, getting that pointer.

	while (startPointerW != endPointerW)
	{
		Serial.print("Old Way Number:");
		Serial.println(*startPointerW);
		startPointerW++;
	}

	//OR

	for (int* startPointer = mysteriousSequence, endPointer = &(mysteriousSequence[CollectionLength(mysteriousSequence)]);
		startPointer != endPointer;
		startPointer++)
	{
		Serial.print("Old Way for Number:");
		Serial.println(*startPointer);
		startPointer++;
	}



	//Using library



	//Wrapper around array
	auto start = GeneralIterator<int[CollectionLength(mysteriousSequence)], int&>(mysteriousSequence, 0);
	auto end = GeneralIterator<int[CollectionLength(mysteriousSequence)], int&>(mysteriousSequence, CollectionLength(mysteriousSequence));

	for (/*Already defined start and end above*/;
		start != end;
		++start)
	{
		Serial.print("Iterator for Number:");
		Serial.println(*start);
	}

	//Wrapper around iterators
	auto iterable = GeneralIterable<int[CollectionLength(mysteriousSequence)], GeneralIterator<int[CollectionLength(mysteriousSequence)], int&>>(mysteriousSequence, 0, CollectionLength(mysteriousSequence));
	for (auto istart = iterable.begin(), iend = iterable.end();
		istart != iend;
		++istart)
	{
		Serial.print("Iteratable for Number:");
		Serial.println(*istart);
	}

	//Wrapper for already existing begin and end. Does line 53 for you.
	auto iterable2 = Iterate(start, end);
	for (auto istart = iterable2.begin(), iend = iterable2.end();
		istart != iend;
		++istart)
	{
		auto value = *istart;
		{
			Serial.print("Begin end iteratable wrapper for Number:");
			Serial.println(value);
		}
	}

	//Same as:
	for (auto value : iterable2)
	{
		Serial.print("Begin end iteratable wrapper range-for Number:");
		Serial.println(value);
	}





	//Enumeration changes the template argument of te iterable to EnumerationIterator
	auto enumerationStart = EnumerationIterator<int[CollectionLength(mysteriousSequence)], int&>(mysteriousSequence, 0);
	auto enumerationEnd = EnumerationIterator<int[CollectionLength(mysteriousSequence)], int&>(mysteriousSequence, CollectionLength(mysteriousSequence));

	for (/*Already defined enumerationEtart and enumerationEnd above*/;
		enumerationStart != enumerationEnd;
		++enumerationStart)
	{
		Serial.print("Iterator for Number:");
		Serial.println((*enumerationStart).value);
	}

	auto enumerable = GeneralIterable<int[CollectionLength(mysteriousSequence)], EnumerationIterator<int[CollectionLength(mysteriousSequence)], int&>>(mysteriousSequence, 0, CollectionLength(mysteriousSequence));
	for (auto begin = enumerable.begin(), end = enumerable.end();
		begin != end;
		++begin)
	{
		auto enumeration = *begin;
		{
			Serial.print("index ");
			Serial.print(enumeration.index);
			Serial.print(" value ");
			Serial.println(enumeration.value);
		}
	}

	//Same as:

	for (auto enumeration : enumerable)
	{
		Serial.print("index ");
		Serial.print(enumeration.index);
		Serial.print(" value ");
		Serial.println(enumeration.value);
	}
}

void loop()
{
}