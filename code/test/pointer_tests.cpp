//==================================================================================================
//  File:
//      pointer_tests.cpp
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#include "pointer_tests.h"
#include "pointer_cast_tests.h"
#include "pointer_copy_tests.h"
#include "pointer_sort_tests.h"
#include "pointer_stable_sort_tests.h"

#define RUN_COPY_TESTS(ST, DT)          run_pointer_copy_tests<ST,DT>(#ST, #DT)
#define RUN_SORT_TESTS(ST, DT)          run_pointer_sort_tests<ST,DT>(#ST, #DT)
#define RUN_STABLE_SORT_TESTS(ST, DT)   run_pointer_stable_sort_tests<ST,DT>(#ST, #DT)

void
run_pointer_tests()
{
    run_pointer_cast_tests<wrapper_strategy>();
    run_pointer_cast_tests<based_2dxl_strategy>();
    run_pointer_cast_tests<based_2d_strategy>();
    run_pointer_cast_tests<based_1d_strategy>();
    run_pointer_cast_tests<offset_strategy>();

#if 0
    do_pointer_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_stable_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_stable_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_stable_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_stable_sort_test<offset_strategy, uint32_t>(17);
    do_pointer_sort_test<offset_strategy, uint64_t>(9);
    do_pointer_sort_test<offset_strategy, uint64_t>(9);
    do_pointer_sort_test<offset_strategy, uint64_t>(9);
    do_pointer_sort_test<offset_strategy, uint64_t>(9);
    do_pointer_sort_test<offset_strategy, test_struct>(10);
    do_pointer_sort_test<offset_strategy, test_struct>(10);
    do_pointer_sort_test<offset_strategy, test_struct>(17);
    do_pointer_sort_test<offset_strategy, test_struct>(17);
//    return;

    RUN_SORT_TESTS(offset_strategy, uint32_t);
    RUN_SORT_TESTS(offset_strategy, uint64_t);
    RUN_SORT_TESTS(offset_strategy, string);
    RUN_SORT_TESTS(offset_strategy, test_struct);

    RUN_STABLE_SORT_TESTS(offset_strategy, uint32_t);
    RUN_STABLE_SORT_TESTS(offset_strategy, uint64_t);
    RUN_STABLE_SORT_TESTS(offset_strategy, string);
    RUN_STABLE_SORT_TESTS(offset_strategy, test_struct);

    RUN_COPY_TESTS(offset_strategy, uint32_t);
    RUN_COPY_TESTS(offset_strategy, uint64_t);
    RUN_COPY_TESTS(offset_strategy, string);
    RUN_COPY_TESTS(offset_strategy, test_struct);
    return;
#endif
#if 1
    RUN_COPY_TESTS(wrapper_strategy, uint32_t);
    RUN_COPY_TESTS(wrapper_strategy, uint64_t);
    RUN_COPY_TESTS(wrapper_strategy, string);
    RUN_COPY_TESTS(wrapper_strategy, test_struct);

    RUN_COPY_TESTS(based_2dxl_strategy, uint32_t);
    RUN_COPY_TESTS(based_2dxl_strategy, uint64_t);
    RUN_COPY_TESTS(based_2dxl_strategy, string);
    RUN_COPY_TESTS(based_2dxl_strategy, test_struct);

    RUN_COPY_TESTS(based_2d_strategy, uint32_t);
    RUN_COPY_TESTS(based_2d_strategy, uint64_t);
    RUN_COPY_TESTS(based_2d_strategy, string);
    RUN_COPY_TESTS(based_2d_strategy, test_struct);

    RUN_COPY_TESTS(based_1d_strategy, uint32_t);
    RUN_COPY_TESTS(based_1d_strategy, uint64_t);
    RUN_COPY_TESTS(based_1d_strategy, string);
    RUN_COPY_TESTS(based_1d_strategy, test_struct);

    RUN_COPY_TESTS(offset_strategy, uint32_t);
    RUN_COPY_TESTS(offset_strategy, uint64_t);
    RUN_COPY_TESTS(offset_strategy, string);
    RUN_COPY_TESTS(offset_strategy, test_struct);
#endif

#if 1
    RUN_SORT_TESTS(wrapper_strategy, uint32_t);
    RUN_SORT_TESTS(wrapper_strategy, uint64_t);
    RUN_SORT_TESTS(wrapper_strategy, string);
    RUN_SORT_TESTS(wrapper_strategy, test_struct);

    RUN_SORT_TESTS(based_2dxl_strategy, uint32_t);
    RUN_SORT_TESTS(based_2dxl_strategy, uint64_t);
    RUN_SORT_TESTS(based_2dxl_strategy, string);
    RUN_SORT_TESTS(based_2dxl_strategy, test_struct);

    RUN_SORT_TESTS(based_2d_strategy, uint32_t);
    RUN_SORT_TESTS(based_2d_strategy, uint64_t);
    RUN_SORT_TESTS(based_2d_strategy, string);
    RUN_SORT_TESTS(based_2d_strategy, test_struct);

    RUN_SORT_TESTS(based_1d_strategy, uint32_t);
    RUN_SORT_TESTS(based_1d_strategy, uint64_t);
    RUN_SORT_TESTS(based_1d_strategy, string);
    RUN_SORT_TESTS(based_1d_strategy, test_struct);

#ifndef POSSIBLE_GCC6_CODEGEN_BUG
    RUN_SORT_TESTS(offset_strategy, uint32_t);
#endif
    RUN_SORT_TESTS(offset_strategy, uint64_t);
    RUN_SORT_TESTS(offset_strategy, string);
#ifndef POSSIBLE_GCC5_CODEGEN_BUG
    RUN_SORT_TESTS(offset_strategy, test_struct);
#endif
#endif

#if 1
    RUN_STABLE_SORT_TESTS(wrapper_strategy, uint32_t);
    RUN_STABLE_SORT_TESTS(wrapper_strategy, uint64_t);
    RUN_STABLE_SORT_TESTS(wrapper_strategy, string);
    RUN_STABLE_SORT_TESTS(wrapper_strategy, test_struct);

    RUN_STABLE_SORT_TESTS(based_2dxl_strategy, uint32_t);
    RUN_STABLE_SORT_TESTS(based_2dxl_strategy, uint64_t);
    RUN_STABLE_SORT_TESTS(based_2dxl_strategy, string);
    RUN_STABLE_SORT_TESTS(based_2dxl_strategy, test_struct);

    RUN_STABLE_SORT_TESTS(based_2d_strategy, uint32_t);
    RUN_STABLE_SORT_TESTS(based_2d_strategy, uint64_t);
    RUN_STABLE_SORT_TESTS(based_2d_strategy, string);
    RUN_STABLE_SORT_TESTS(based_2d_strategy, test_struct);

    RUN_STABLE_SORT_TESTS(based_1d_strategy, uint32_t);
    RUN_STABLE_SORT_TESTS(based_1d_strategy, uint64_t);
    RUN_STABLE_SORT_TESTS(based_1d_strategy, string);
    RUN_STABLE_SORT_TESTS(based_1d_strategy, test_struct);

    RUN_STABLE_SORT_TESTS(offset_strategy, uint32_t);
    RUN_STABLE_SORT_TESTS(offset_strategy, uint64_t);
    RUN_STABLE_SORT_TESTS(offset_strategy, string);
#ifndef POSSIBLE_GCC5_CODEGEN_BUG
    RUN_STABLE_SORT_TESTS(offset_strategy, test_struct);
#endif
#endif
}
