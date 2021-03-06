//==================================================================================================
//  File:
//      container_map_tests.h
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef CONTAINER_MAP_TESTS_H_DEFINED
#define CONTAINER_MAP_TESTS_H_DEFINED

#include "container_tests.h"

template<typename K, typename V, typename AS>
using test_map = map<K, V, less<K>, rhx_allocator<pair<const K, V>, AS>>;

template<typename T, typename AS>
using test_list = list<T, rhx_allocator<T,AS>>;

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_simple_umap_test<AS>
//
//  Summary:
//      This function template performs a very simple, sanity-checking test.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
do_simple_map_test()
{
    //- Various type aliases to aid readability.
    //
    using strategy    = AllocStrategy;
    using syn_string  = test_string<strategy>;
    using syn_str_map = test_map<syn_string, test_list<syn_string, strategy>, strategy>;

    auto    spmap = allocate<syn_str_map, strategy>();
    auto    spkey = allocate<syn_string, strategy>();
    auto    spval = allocate<syn_string, strategy>();

    char    key_str[128], val_str[128];

    for (int i = 961;  i <= 971;  ++i)
    {
        sprintf(key_str, "this is key string #%d", i);
        spkey->assign(key_str);

        for (int j = 101;  j <= 106;  ++j)
        {
            sprintf(val_str, "this is very long value string #%d created for map<string,list<string>>", j);
            spval->assign(val_str);
            (*spmap)[*spkey].push_back(*spval);
        }
    }

    cout << "***********************" << endl;
    cout << "*****  TEST MAP  ******" << endl;

    for (auto const& elem : *spmap)
    {
        cout << elem.first << endl;

        for (auto const& val : elem.second)
        {
            cout << "    " <<  val << endl;
        }
    }

    cout << endl;
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_normal_umap_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename KeyType, typename ValueType>
void
do_normal_map_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy       = AllocStrategy;

    using key_traits     = test_data_type_traits<KeyType, AllocStrategy>;
    using nat_key_type   = typename key_traits::nat_type;
    using syn_key_type   = typename key_traits::syn_type;

    using value_traits   = test_data_type_traits<ValueType, AllocStrategy>;
    using nat_value_type = typename value_traits::nat_type;
    using syn_value_type = typename value_traits::syn_type;

    using nat_map_type   = map<nat_key_type, nat_value_type>;
    using syn_map_type   = test_map<syn_key_type, syn_value_type, strategy>;

    //- Some maps.
    //
    nat_map_type    nat_map;
    syn_map_type    syn_map_1;
    auto            p_syn_map_A = allocate<syn_map_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_map, syn_map_1));
    CHECK(contents_match(nat_map, *p_syn_map_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_key_type    nat_key_data;
        syn_key_type    syn_key_data;

        key_traits::generate(nat_key_data, syn_key_data);

        nat_value_type  nat_value_data;
        syn_value_type  syn_value_data;

        value_traits::generate(nat_value_data, syn_value_data);

        nat_map[nat_key_data]        = nat_value_data;
        syn_map_1[syn_key_data]      = syn_value_data;
        (*p_syn_map_A)[syn_key_data] = syn_value_data;
    }

    CHECK(contents_match(nat_map, syn_map_1));
    CHECK(contents_match(nat_map, *p_syn_map_A));
    PRINT(nat_map, syn_map_1);
    PRINT(nat_map, *p_syn_map_A);

    nat_map.clear();
    syn_map_1.clear();
    p_syn_map_A->clear();

    CHECK(contents_match(nat_map, syn_map_1));
    CHECK(contents_match(nat_map, *p_syn_map_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_key_type    nat_key_data;
        syn_key_type    syn_key_data;

        key_traits::generate(nat_key_data, syn_key_data);

        nat_value_type  nat_value_data;
        syn_value_type  syn_value_data;

        value_traits::generate(nat_value_data, syn_value_data);

        nat_map[nat_key_data]        = nat_value_data;
        syn_map_1[syn_key_data]      = syn_value_data;
        (*p_syn_map_A)[syn_key_data] = syn_value_data;
    }

    CHECK(contents_match(nat_map, syn_map_1));
    CHECK(contents_match(nat_map, *p_syn_map_A));
    PRINT(nat_map, syn_map_1);
    PRINT(nat_map, *p_syn_map_A);


    nat_map.erase(nat_map.begin());
    syn_map_1.erase(syn_map_1.begin());
    p_syn_map_A->erase(p_syn_map_A->begin());

    CHECK(contents_match(nat_map, syn_map_1));
    CHECK(contents_match(nat_map, *p_syn_map_A));
    PRINT(nat_map, syn_map_1);
    PRINT(nat_map, *p_syn_map_A);

    //- Copy operations.
    //
    syn_map_type   syn_map_2(syn_map_1);
    syn_map_type   syn_map_3;

    syn_map_3 = syn_map_1;

    CHECK(contents_match(nat_map, syn_map_2));
    CHECK(contents_match(nat_map, syn_map_3));

    auto    p_syn_map_B = allocate<syn_map_type, strategy>(syn_map_1);
    auto    p_syn_map_C = allocate<syn_map_type, strategy>();

    *p_syn_map_C = syn_map_1;

    CHECK(contents_match(nat_map, *p_syn_map_B));
    CHECK(contents_match(nat_map, *p_syn_map_C));

    //- Move operations.
    //
    syn_map_type   syn_map_4(std::move(syn_map_2));
    syn_map_type   syn_map_5;

    CHECK(syn_map_2.size() == 0u);
    CHECK(contents_match(nat_map, syn_map_4));

    syn_map_5 = std::move(syn_map_3);

    CHECK(syn_map_3.size() == 0);
    CHECK(contents_match(nat_map, syn_map_5));

    auto    p_syn_map_D = allocate<syn_map_type, strategy>(std::move(*p_syn_map_B));
    auto    p_syn_map_E = allocate<syn_map_type, strategy>();

    CHECK(p_syn_map_B->size() == 0u);
    CHECK(contents_match(nat_map, *p_syn_map_D));

    *p_syn_map_E = std::move(*p_syn_map_C);

    CHECK(p_syn_map_C->size() == 0);
    CHECK(contents_match(nat_map, *p_syn_map_E));
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_map_normal_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual map test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_map_normal_tests(char const* stype)
{
    cout << "================================================================" << endl;
    cout << "Running basic operation tests for " << stype << endl;
    cout << "Using container std::map" << endl;

    do_simple_map_test<AllocStrategy>();

    do_normal_map_tests<AllocStrategy, string, test_struct>(5);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_normal_map_tests<AllocStrategy, string, string>(5);

    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_reloc_umap_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename KeyType, typename ValueType>
void
do_reloc_map_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy       = AllocStrategy;

    using key_traits     = test_data_type_traits<KeyType, AllocStrategy>;
    using nat_key_type   = typename key_traits::nat_type;
    using syn_key_type   = typename key_traits::syn_type;

    using value_traits   = test_data_type_traits<ValueType, AllocStrategy>;
    using nat_value_type = typename value_traits::nat_type;
    using syn_value_type = typename value_traits::syn_type;

    using nat_map_type   = map<nat_key_type, nat_value_type>;
    using syn_map_type   = test_map<syn_key_type, syn_value_type, strategy>;

    //- Some maps.
    //
    nat_map_type    nat_map;
    auto            p_syn_map_A = allocate<syn_map_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_map, *p_syn_map_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_key_type    nat_key_data;
        syn_key_type    syn_key_data;

        key_traits::generate(nat_key_data, syn_key_data);

        nat_value_type  nat_value_data;
        syn_value_type  syn_value_data;

        value_traits::generate(nat_value_data, syn_value_data);

        nat_map[nat_key_data]        = nat_value_data;
        (*p_syn_map_A)[syn_key_data] = syn_value_data;
    }

    CHECK(contents_match(nat_map, *p_syn_map_A));
    PRINT(nat_map, *p_syn_map_A);

    auto    pm_1 = addressof(*p_syn_map_A);
    auto    pe_1 = addressof(*p_syn_map_A->begin());

    strategy::swap_buffers();

    auto    pm_2 = addressof(*p_syn_map_A);
    auto    pe_2 = addressof(*p_syn_map_A->begin());

    CHECK(pm_1 != pm_2);
    CHECK(pe_1 != pe_2);
    CHECK(contents_match(nat_map, *p_syn_map_A));
    PRINT(nat_map, *p_syn_map_A);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_map_reloc_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual map test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_map_reloc_tests(char const* stype)
{
    cout << "================================================================" << endl;
    cout << "Running relocation tests for " << stype << endl;
    cout << "Using container std::map" << endl << endl;

    do_reloc_map_tests<AllocStrategy, string, test_struct>(5);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_reloc_map_tests<AllocStrategy, string, string>(10);

    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_map_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does simple map POC* testing, using natural pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_map_poc_tests()
{
    using test_alloc = poc_allocator<pair<const test_struct, test_struct>, POCCA, POCMA, POCS, EQ>;
    using test_map   = map<test_struct, test_struct, less<test_struct>, test_alloc>;

    test_map        m1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     key = generate_test_struct();
        test_struct     val = generate_test_struct();

        m1[key] = val;
    }

    test_map    m0(m1), m2(m1);
    test_map    m3(std::move(m1));
    test_map    m4(m1), m5(m1);

    CHECK(m1.size() == 0);
    CHECK(m2.size() == start_count);
    CHECK(m3.size() == start_count);
    CHECK(m2 == m3);

    m3.erase(m3.begin());
    m3.erase(m3.begin());
    CHECK(m3.size() == (start_count - 2));

    m4 = m3;
    m5 = std::move(m3);
    CHECK(m4 == m5);

    swap(m2, m5);
    CHECK(m2 == m4);
    CHECK(m5 == m0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_map_syn_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does simple map POC* testing, using synthetic pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_map_syn_poc_tests()
{
    using test_alloc = syn_poc_allocator<pair<const test_struct, test_struct>, POCCA, POCMA, POCS, EQ>;
    using test_map   = map<test_struct, test_struct, less<test_struct>, test_alloc>;

    test_map        m1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     key = generate_test_struct();
        test_struct     val = generate_test_struct();
        
        m1[key] = val;
    }

    test_map    m0(m1), m2(m1);
    test_map    m3(std::move(m1));
    test_map    m4(m1), m5(m1);

    CHECK(m1.size() == 0);
    CHECK(m2 == m3);

    m3.erase(m3.begin());
    m3.erase(m3.begin());

    m4 = m3;
    m5 = std::move(m3);
    CHECK(m4 == m5);

    swap(m2, m5);
    CHECK(m2 == m4);
    CHECK(m5 == m0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_map_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template manages the sequence of actual map POC* test function calls.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
run_map_poc_tests()
{
    cout << "Running POC tests for native pointer" << endl;
    do_map_poc_tests<POCCA,POCMA,POCS,EQ>();
 
#ifndef COMPILER_MS
    cout << "Running POC tests for synthetic pointer" << endl;
    do_map_syn_poc_tests<POCCA,POCMA,POCS,EQ>();
#endif

#if defined(COMPILER_MS) && (_MSC_VER > 1900)
    cout << "Running POC tests for synthetic pointer" << endl;
    do_map_syn_poc_tests<POCCA,POCMA,POCS,EQ>();
#endif
}

#endif  //- CONTAINER_MAP_TESTS_H_DEFINED
