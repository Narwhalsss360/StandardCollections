#include <LightCollection.h> //

/*
	Include LightCollection.h instead StandardCollections.h to save some program memory space.
	this does remove some methods:
		Fill,
		First,
		Last,
		ForEach,
		Slice,
		CopyTo,
		MoveTo
*/

#define SERIAL_BAUDRATE 115200

Array<byte, 7> specialCode1; //Creating empty array of bytes of length 7.
Array_init(byte, specialCode, { 7, 3, 5, 5, 6, 0, 8 }); //Creating byte array containing items.
Array_init(byte, specialCodeReversed, { 8, 0, 6, 5, 5, 3, 7 }); //Creating byte array containing items.

//Function that tells us if a number is 6.
bool isSix(const byte& number)
{
	if (number == 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	while (!Serial); //Waiting for serial port to open.

	Serial.println("Showing the special code the old way...");
	for (size_t i = 0; i < specialCode.Length(); i++)
	{
		Serial.print(specialCode[i]); //Getting elements is the same as regular c arrays.
	}
	Serial.println();

	Serial.println("Showing the special code the new way...");
	for (int digit : specialCode)
		//OR -> for (int digit : Iterate(specialCode))
	{
		Serial.print(digit);
	}
	Serial.println();

	Serial.println("Showing the digits with its index...");
	for (Enumeration<byte&> enumeration : Enumerate(specialCode)) //Enumeration<T> contains a reference to the type.
	{
		if (enumeration.defaulted) //Sanity check, theoretically not required, but if it is defaulted, the value of enumeration.index is not defined.
		{
			continue;
		}

		Serial.print(enumeration.index);
		Serial.print(":");
		Serial.print(enumeration.value);
		//OR -> Serial.print(enumeration) <- Implicit cast operator overloaded.
		Serial.print("  ");
	}
	Serial.println();


	Serial.println("Showing the digits and its place.");
	for (auto enumeration : Enumerate(specialCodeReversed))
	{
		unsigned int place = enumeration.index + 1;

		Serial.print(place);
		switch (place)
		{
		case 1:
			Serial.print("st ");
			break;
		case 2:
			Serial.print("nd ");
			break;
		case 3:
			Serial.print("rd ");
			break;
		default:
			Serial.print("th ");
			break;
		}

		Serial.print("place is ");
		Serial.print(enumeration);

		Serial.print("  ");
	}

	Serial.println();

	Serial.print("The highest-place digit is ");
	Serial.println(specialCode.First());

	Serial.print("The lowest-place digit is ");
	Serial.println(specialCode.Last());

	Serial.print("There are ");
	Serial.print(specialCode.Count(5));
	Serial.println(" fives in the code");

	Serial.print("The index of 6 is ");
	IndexValuePair<const byte> pair = specialCode.Find(6);
	// OR -> IndexValuePair<const byte> pair = specialCode.Find(isSix); <- Create a function that returns true if given value is your find query.
	Serial.println((index_t)pair.index);
}

void loop()
{
}