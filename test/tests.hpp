//
//  tests.hpp
//  mvcgraphics
//
//  Created by Miguel Ibero on 21/12/12.
//  Copyright (c) 2012 Social Point. All rights reserved.
//

#ifndef mvcgraphics_tests_hpp
#define mvcgraphics_tests_hpp

#include <gtest/gtest.h>

int runAllTests()
{
    int i = 0;
    ::testing::InitGoogleTest(&i,(char **)&i);
    return RUN_ALL_TESTS();
}

#endif