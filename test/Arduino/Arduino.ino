//#define SizingTest

#ifdef SizingTest
/*
    Empty sketch:
        1424 bytes of program storage
        376 bytes of dynamic memory

    Using most API functions\Data types:
        14922 bytes of program storage
        690 bytes of dynamic memory
*/

#include <StandardCollections.h>

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    DynamicJaggedDynamic<int> DJD;
    DynamicJaggedDynamic<int> DJD1;

    for (auto i : Iterate(DJD))
    {
    }

    for (auto i : Enumerate(DJD))
    {
    }

    for (auto i : Zip(DJD, DJD1))
    {
    }
}

void loop()
{
}
#else
#include "Commons.h"
#include "OrderedTests.h"

#define TEST_GROUP 3

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

#if TEST_GROUP == 0
    c_style_general_iterate();
    c_style_enumerate();
    c_style_zip();
#endif

#if TEST_GROUP == 1
    array_instantiation();
    array_General_iterator();
#endif

#if TEST_GROUP == 2
    finding_elements();
    for_each();
    comparators();
#endif
#if TEST_GROUP == 3
    slice();
    collection_casts();
#endif

#if TEST_GROUP == 4
    dynamic_array();
    dynamic_array_join();

    general_iteration();
#endif

    test_standard_output_write("Done testing group ");
    test_standard_output_write(TEST_GROUP);
    digitalWrite(LED_BUILTIN, LOW);
}


void loop()
{
}
#endif