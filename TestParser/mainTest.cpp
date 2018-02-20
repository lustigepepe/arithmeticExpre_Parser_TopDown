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

//#include <stdio.h>
#include "../ParserMain/main.hpp"

int add( int i, int j ) { return i+j; }

BOOST_AUTO_TEST_CASE( parseTdownTest )
{
    BOOST_CHECK( add( 2,2 ) == 4 );        // #1 continues on error
    BOOST_TEST_MESSAGE( "Testing update :" );
}


