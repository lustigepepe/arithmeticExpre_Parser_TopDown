//
//  mainTest.cpp
//  Parser Task
//
//  Created by soWhat on 20.02.18.
//  Copyright © 2018 soWhat. All rights reserved.
//

//
//  mainTest.hpp
//  Parser Task
//
//  Created by soWhat on 20.02.18.
//  Copyright © 2018 soWhat. All rights reserved.

#define BOOST_TEST_MODULE ParserBoostTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "testInterface.hpp"

string testExpression ("(4 + 5 * (7 - 3)) - 2");

BOOST_AUTO_TEST_CASE(testThreadAlloc)
{
    threadAlloc(testExpression);
    
    BOOST_TEST_MESSAGE("Test threadAlloc done");
    BOOST_TEST(input == "(4+5*(7-3))-2");
    BOOST_TEST_MESSAGE("-------------------");
    BOOST_TEST_MESSAGE("-------------------");
}

BOOST_AUTO_TEST_CASE( parseTdownTest )
{
    threadAlloc(testExpression);
    BOOST_TEST_MESSAGE("Test main parseDown down");
    BOOST_CHECK( parseTDown() == 22 );
}

