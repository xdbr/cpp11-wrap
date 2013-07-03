/*
 *  test_wrap.cpp
 *
 */

#define BOOST_TEST_MODULE wrap_functions_test

#ifdef HEADER_ONLY
#   include <boost/test/included/unit_test.hpp>
#else
#   include <boost/test/unit_test.hpp>
#endif

#include <string>
#include <vector>
#include "wrap.hpp"


/*****************************************************************************/
/*      global test stuff                                                    */
/*****************************************************************************/
std::vector<std::string> messages_recieved;
std::vector<std::string> messages_expected;

void foo_function()  { messages_recieved.push_back(std::string("foo"));         }
void bar_function()  { messages_recieved.push_back(std::string("before foo"));  }
void baz_function()  { messages_recieved.push_back(std::string("after foo"));   }
void quux_function() { messages_recieved.push_back(std::string("yet another")); }


/*****************************************************************************/
/*      test_wrap_before                                                     */
/*****************************************************************************/
BOOST_AUTO_TEST_SUITE( test_wrap_before )

BOOST_AUTO_TEST_CASE(test_wrap_before_basics_1)
{
    // clean
    messages_recieved.clear();
    messages_expected.clear();

    /* messages_expected will be empty */

    auto wrapped_1 = before(foo_function, bar_function);

    BOOST_REQUIRE_EQUAL_COLLECTIONS( /* test both still empty. */
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)

    );
}


BOOST_AUTO_TEST_CASE(test_wrap_before_basics_2)
{
    // clean
    messages_recieved.clear();
    messages_expected.clear();

    // set exptected values
    messages_expected = {"before foo", "foo"};

    // wrap
    auto wrapped = before(foo_function, bar_function);

    // call
    wrapped();

    // check.
    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)
    );
}


BOOST_AUTO_TEST_CASE(test_wrap_before_basics_3)
{
    // clean
    messages_recieved.clear();
    messages_expected.clear();

    // set exptected values
    messages_expected = {"before foo", "foo", "another before foo", "foo"};

    // wrap
    auto wrapped_1 = before(foo_function, bar_function);
    auto wrapped_2 = before(foo_function, [&]{
        messages_recieved.push_back(std::string("another before foo"));
    });

    // call
    wrapped_1();
    wrapped_2();
    
    // check.
    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)
    );

}

BOOST_AUTO_TEST_CASE(test_wrap_before_basics_4)
{
    // clean
    messages_recieved.clear();
    messages_expected.clear();

    // set exptected values
    messages_expected = {"another before foo", "foo"};

    // wrap
    auto wrapped_1 = before(foo_function, [&]{
        messages_recieved.push_back(std::string("another before foo"));
    });

    // call
    wrapped_1();
    
    // check.
    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)
    );

}

// TODO
// BOOST_AUTO_TEST_CASE(test_wrap_before_basics_5)
// {
//     // clean
//     messages_recieved.clear();
//     messages_expected.clear();
// 
//     // set exptected values
//     messages_expected = {"yet another before", "before foo", "foo"};
// 
//     // wrap
//     auto wrapped_1 = before(foo_function, bar_function);
//     auto wrapped_2 = before(wrapped_1, quux_function);
//     // [&]{
//     //     messages_recieved.push_back(std::string("another before foo"));
//     // });
// 
//     // call
//     // wrapped_1();
//     wrapped_2();
//     
//     // check.
//     BOOST_REQUIRE_EQUAL_COLLECTIONS(
//         std::begin(messages_recieved), std::end(messages_recieved),
//         std::begin(messages_expected), std::end(messages_expected)
//     );
// 
// }

BOOST_AUTO_TEST_SUITE_END()



/*****************************************************************************/
/*      test_wrap_after                                                      */
/*****************************************************************************/
BOOST_AUTO_TEST_SUITE(test_wrap_after)

BOOST_AUTO_TEST_CASE(test_wrap_after_basics_1)
{
    // clean
    messages_recieved.clear();
    messages_expected.clear();

    // set exptected values
    messages_expected = {"foo", "after foo"};

    // wrap
    auto wrapped = after(foo_function, baz_function);

    // call
    wrapped();
    
    // check.
    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)
    );
    
}

BOOST_AUTO_TEST_CASE(test_wrap_after_basics_2)
{
    // clean
    messages_recieved.clear();
    messages_expected.clear();

    // set exptected values
    messages_expected = {"foo", "after foo"};

    // wrap
    auto wrapped = after<decltype(foo_function), decltype(baz_function)>(
        foo_function, baz_function
    );

    // call
    wrapped();
    
    // check.
    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)
    );
    
}

BOOST_AUTO_TEST_SUITE_END()
