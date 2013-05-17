
#ifndef mvcgame_tests_hpp
#define mvcgame_tests_hpp

#include <gtest/gtest.h>

int runAllTests()
{
    int i = 0;
    ::testing::InitGoogleTest(&i,(char **)&i);
    return RUN_ALL_TESTS();
}

#endif