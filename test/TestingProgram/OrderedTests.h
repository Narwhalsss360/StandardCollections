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

#include "AlgorithmTest.h"
add_test(reverse);
add_test(unique);
add_test(bubble_sort);
add_test(collection_min);
add_test(collection_max);
add_test(collection_product);
add_test(collection_sum);
add_test(collection_average);
add_test(collection_median);
add_test(collection_factors);
add_test(collection_prime_factors);
add_test(collection_lcm);
add_test(collection_gcd);
add_test(collection_stdev);
add_test(insertion_sort);
add_test(selection_sort);
add_test(collection_union);
add_test(collection_intersect);

#include "CustomAllocatorArrayTest.h"
add_test(alloch_ctor_test);
add_test(freeh_dtor_test);
add_test(custom_allocator_array);