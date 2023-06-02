#include <StandardCollections.h>

#define SERIAL_BAUDRATE 115200 //delays are required wheen reading buffer if BAUDRATE is set to high values.

void setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	while (!Serial); //Waiting for serial port to open.
	Serial.println("Send something through the serial port");
}

void loop()
{
	//Uncomment on arduino leonardo/micro
	//if (Serial.available()) serialEvent();
}

void serialEvent()
{
	DynamicArray<char> inChars;

	/*
		There is Push/Pop
		as well as Unshift/Shift

		SetCapacity() Changes heap allocation.
		SetLength() Changes length, changes behavior but not allocation UNLESS length is set to something greater than capacity. Probably shouldn't use.
	*/

	inChars.SetCapacity(Serial.available()); //Reserving space for the bytes.

	while (Serial.available())
	{
		inChars.Push(Serial.read()); //Adding the read byte to array.
	}

	String message; //Printing at end of function, showing othe stuff first.
	message.reserve(inChars.Length()); //Reserving space for the string.

	for (auto character : Enumerate(inChars))
	{
		message += character.value;
	}

	Serial.print("Length of message ");
	Serial.println(inChars.Length());
	while (inChars.Length()) //While array not empty
	{
		Serial.print("Popped character:");
		Serial.println(inChars.Pop());
	}

	Serial.print("Echo:");
	Serial.println(message);
	Serial.println("Send something else through the serial port!\n");
}