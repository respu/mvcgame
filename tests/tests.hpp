//
//  tests.hpp
//  mvcgraphics
//
//  Created by Miguel Ibero on 21/12/12.
//  Copyright (c) 2012 Social Point. All rights reserved.
//

#ifndef mvcgraphics_tests_hpp
#define mvcgraphics_tests_hpp

#include "gtest/gtest.h"

void runAllTests()
{
    int i = 0;
    ::testing::InitGoogleTest(&i,(char **)&i);
    initGraphics();

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new tap::TapListener());

    return RUN_ALL_TESTS();
}

#endif
