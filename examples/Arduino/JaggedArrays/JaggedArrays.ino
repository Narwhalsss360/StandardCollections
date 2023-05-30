#include <StandardCollections.h>

#define BAUDRATE 115200

//using 5 pins, each pin [0] is pin, [1] is mode.
int pinAndMode[5][2] =
{
    { LED_BUILTIN,  OUTPUT },
    { 2,            INPUT_PULLUP },
    { 3,            OUTPUT },
    { 7,            OUTPUT },
    { 8,            OUTPUT }
};

int pinAndModeAndInterrupt[5][3] =
{
    { LED_BUILTIN,  OUTPUT,                  -1 },
    { 2,            INPUT_PULLUP,       FALLING },
    { 3,            OUTPUT,                  -1 },
    { 7,            OUTPUT,                  -1 },
    { 8,            OUTPUT,                  -1 }
};

//Collection version:
Jagged<int, 5, 2> pinAndModeJagged; //Arduino does not support std::initializer_list, can't use braced-init list. 

void setup()
{
    Serial.begin(BAUDRATE);
    while (!Serial); //Waiting for serial port to open.

    for (auto pinModeGroup : Enumerate(pinAndMode))
    {
        pinAndModeJagged[pinModeGroup.index][0] = pinModeGroup[0];
        pinAndModeJagged[pinModeGroup.index][1] = pinModeGroup[1];
    }

    //if number of pins being used changes:
    DynamicJagged<int, 2> pinAndModeVariablePins;

    //if number of pins dont change but may want [pin][2] for true/false for interrupt
    JaggedDynamic<int, 5> pinAndModeVariableModes;

    //if both changes
    DynamicJaggedDynamic<int> pinAndModeBothVariable;

    //Multiply Jagged Arrays:
    Array<Array<Array<int, 2>, 3>, 5> mutiplyJagged;

    mutiplyJagged[4][2][1] = 3;

    /*
        Array of 5
        {
            Array of 3
            {
                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }
            }

            Array of 3
            {
                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }
            }

            Array of 3
            {
                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }
            }

            Array of 3
            {
                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }
            }

            Array of 3
            {
                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }
            }

            Array of 3
            {
                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }

                Array of 2
                {
                    int,
                    int
                }
            }
        }
    */
}

void loop()
{
}