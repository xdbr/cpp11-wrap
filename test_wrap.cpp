// /*
//
//     test_wrap.cpp
//
//
// */
//
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <functional>
// #include "wrap.hpp"
//
// using namespace std;
//
// void foo_function() {
//     std::cout << "foo_function" << std::endl;
// }
//
// void bar_function() {
//     // []{
//         std::cout << "before foo_function"<<std::endl;
//     // }
// }
//
// void baz_function() {
//     std::cout << "after foo_function" << std::endl;
// }
// int main() {
//
//     // auto wrapped_1 = before<decltype(foo_function), decltype(bar_function)>(foo_function, bar_function);
//     auto wrapped_1 = before(foo_function, bar_function);
//     auto wrapped_3 = before(foo_function, [&]{
//         std::cout << "Another before function" << std::endl;
//     });
//
//     auto wrapped_4 = before(wrapped_3, [&]{
//         std::cout << "Yet another before function" << std::endl;
//     });
//     auto wrapped_2 = after<decltype(foo_function), decltype(baz_function)>(foo_function, baz_function);
//
//     wrapped_2();
//
//     wrapped_1();
//     wrapped_3();
//     // wrapped_4();
//
//     return 0;
// }



#define BOOST_TEST_MODULE wrap_functions_test

#ifdef HEADER_ONLY
#   include <boost/test/included/unit_test.hpp>
#else
#   include <boost/test/unit_test.hpp>
#endif

#include <string>
#include <vector>
#include "wrap.hpp"

BOOST_AUTO_TEST_SUITE( test_suite1 )

// globals for reuse.
std::vector<std::string> messages_recieved;
std::vector<std::string> messages_expected;

void foo_function() {
    messages_recieved.push_back(std::string("foo"));
}

void bar_function() {
    // []{
    messages_recieved.push_back(std::string("before foo"));
    // }
}

void baz_function() {
    std::cout << "after foo_function" << std::endl;
}



/*****************************************************************************/
BOOST_AUTO_TEST_CASE(test_basics_1)
{

    auto wrapped_1 = before(foo_function, bar_function);

    BOOST_REQUIRE_EQUAL_COLLECTIONS( // both still empty.
        std::begin(messages_recieved), std::end(messages_recieved),
        // std::begin(messages_empty),    std::end(messages_empty)
        std::begin(messages_expected), std::end(messages_expected)

    );
}



/*****************************************************************************/
BOOST_AUTO_TEST_CASE(test_basics_2)
{
    // clean
    messages_recieved.clear();
    messages_expected.clear();

    // set exptected values
    messages_expected = {"before foo", "foo"};

    // wrap
    auto wrapped_1 = before(foo_function, bar_function);

    // call
    wrapped_1();

    // check.
    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)
    );
}



/*****************************************************************************/
BOOST_AUTO_TEST_CASE(test_basics_3)
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

    // for (auto x : messages_recieved) std::cout << x << std::endl;
    
    // check.
    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(messages_recieved), std::end(messages_recieved),
        std::begin(messages_expected), std::end(messages_expected)
    );


}

BOOST_AUTO_TEST_SUITE_END()
