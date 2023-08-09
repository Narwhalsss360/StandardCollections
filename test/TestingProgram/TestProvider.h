#pragma once
#include <vector>
#include <string>

#define test_function(name) void name()
#define add_test(name) TestAdder test_adder__##name = TestAdder(name, #name);
#define test_standard_output_write(msg) std::cout << msg
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

#ifdef TOP_LVL
#define test_expect(expression, expected) { \
											test_standard_output_write("Testing "); \
											test_standard_output_write(#expression); \
											test_standard_output_write("->"); \
											test_standard_output_write(#expected); \
											test_standard_output_write('\n'); \
											if ((expression) != (expected))  { test_standard_output_write("test_expected failed at line "); test_standard_output_write(__LINE__); \
											test_standard_output_write(" of file: "); \
											test_standard_output_write(__FILE__); \
											test_standard_output_write(" expression: "); \
											test_standard_output_write(#expression); \
											test_standard_output_write(" expected: "); \
											test_standard_output_write(#expected); \
											test_standard_output_write('\n'); \
											__debugbreak(); \
											} \
											}

#endif

using std::vector;
using std::string;

typedef void (*TestFunctionPointer)(void);
struct TestContainer
{
	TestContainer(TestFunctionPointer function, const char* functionName)
		: function(function), functionName(functionName)
	{
	}

	void operator()()
	{
		function();
	}

	TestFunctionPointer function;
	const string functionName;
};

vector<TestContainer> tests = vector<TestContainer>();

struct TestAdder
{
	TestAdder(TestFunctionPointer function, const char* functionName)
	{
		tests.emplace_back(function, functionName);
	}
};