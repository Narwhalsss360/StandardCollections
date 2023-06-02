#pragma once

#include "CStyleArrayTest.h"
add_test(c_style_general_iterate);
add_test(c_style_enumerate);
add_test(c_style_zip);

#include "ArrayTest.h"
add_test(array_instantiation);
add_test(array_General_iterator);

#include "CollectionToolsTest.h"
add_test(finding_elements);
#ifndef LightCollection_h
add_test(for_each);
#endif // !LightCollection_h
add_test(comparators);
#ifndef LightCollection_h
add_test(slice);
#endif // !LightCollection_h
add_test(collection_casts);

#include "DynamicArrayTest.h"
add_test(dynamic_array);
add_test(dynamic_array_join);

#include "IteratorTests.h"
add_test(general_iteration);