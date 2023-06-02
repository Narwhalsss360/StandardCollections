#include <StandardCollections.h>

#define SERIAL_BAUDRATE 115200

//Fictional pin array in order of priority.
byte priorityPinArray[] = { 2, 3, A4, A5, 0, 1 };
byte pinModeArray[] = { INPUT_PULLUP, INPUT_PULLUP, OUTPUT, OUTPUT, OUTPUT, OUTPUT };

//Converts INPUT, INPUT_PULLUP, OUTPUT to a String
String GetModeString(byte mode)
{
	switch (mode)
	{
	case INPUT:
		return "INPUT";
		break;
	case OUTPUT:
		return "OUTPUT";
	case INPUT_PULLUP:
		return "INPUT_PULLUP";
	default:
		return "INPUT";
	}
}

void setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	while (!Serial); //Waiting for serial port to open.

	int negative1Array[12];

	FillCStyleArray(negative1Array, -1); //Filling array with -1.

	int numberOfPinsUsed = CollectionLength(priorityPinArray);

	Serial.print("Using a total of ");
	Serial.print(numberOfPinsUsed);
	Serial.println(" pins");

	auto Converted = CStyleToArray(priorityPinArray); //Converts c array to the type of Array<typename CollectableType, index_t TemplateLength> (Arrays Example)

	//Safely enter any number for the index, and the length of the array and you wont access memory outside of the bounds of the array.
	byte pinAtIndex402 = priorityPinArray[SafeIndex(402, CollectionLength(priorityPinArray))];

	Serial.print("Using pins: ");
	for (byte pinNumber : Iterate(priorityPinArray))
	{
		Serial.print(pinNumber);
		Serial.print(" ");
	}
	Serial.println();

	Serial.print("Order of priority:\n");
	for (Enumeration<byte&> enumeration : Enumerate(priorityPinArray))
	{
		Serial.print("Position ");
		Serial.print(enumeration.index);
		Serial.print(" ");
		Serial.println(enumeration.value);
	}
	Serial.println();

	for (Zipping<byte, byte> zipped : Zip(priorityPinArray, pinModeArray))
	//verbose -> for (Zipping<byte, byte> zipped : Zip<byte[6], byte, byte, byte[6]>(priorityPinArray, pinModeArray))
	{
		/*
			value1 is the pin from priorityPinArray
			value2 is the mode from pinModeArray
		*/
		Serial.print("Setting pin ");
		Serial.print(zipped.value1);
		Serial.print(" as ");
		String modeString = GetModeString(zipped.value2);
		Serial.println(modeString);
		pinMode(zipped.value1, zipped.value2);
	}
}

void loop()
{
}