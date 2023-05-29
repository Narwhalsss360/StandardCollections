#pragma once

void __debugbreak(String beginMessage = "")
{
	Serial.print(beginMessage);
	while (!Serial.available())
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
	}
	while (Serial.available()) Serial.read();
	digitalWrite(LED_BUILTIN, HIGH);
}

#define test_function(name) void name()
#define test_standard_output_write(msg) Serial.print(msg)
#define test_expect(expression, expected) if ((expression) != (expected))  { test_standard_output_write("test_expected failed at line "); test_standard_output_write(__LINE__); \
											test_standard_output_write(" of file: "); \
											test_standard_output_write(__FILE__); \
											test_standard_output_write(" expression: "); \
											test_standard_output_write(#expression); \
											test_standard_output_write(" expected: "); \
											test_standard_output_write(#expected); \
											test_standard_output_write('\n'); \
											__debugbreak(); \
											}