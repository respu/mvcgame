//
//  TimeTest.cpp
//  hydra
//
//  Created by Miguel Ibero on 19/12/12.
//
//

#include <mvcgame/Time.hpp>
#include <mvcgame/Geometry.hpp>
#include <math.h>
#include <gtest/gtest.h>

using namespace mvcgame;

TEST(Time, timestamp) {

    Time t;
    
    ASSERT_FALSE(t);
    
    t = Time::now();
    
    ASSERT_TRUE(t);
    
    Time t2 = t + Duration::mins(1);
    Duration d = t2-t;
    
    ASSERT_EQ(60, d.secs());
}

TEST(Time, speed) {
    Duration t = Duration::secs(1) + Duration::usecs(250000);
    Distance d = Distance(4, 5);
    Speed s = d/t;
    
    ASSERT_EQ(1, s.d);
    ASSERT_FLOAT_EQ(3.2, s.x);
    ASSERT_FLOAT_EQ(4, s.y);
    
    Speed a = s/t;
    
    ASSERT_EQ(2, a.d);
    ASSERT_FLOAT_EQ(2.56, a.x);
    ASSERT_FLOAT_EQ(3.2, a.y);
    
    s = a*t;
    
    ASSERT_EQ(1, s.d);
    ASSERT_FLOAT_EQ(3.2, s.x);
    ASSERT_FLOAT_EQ(4, s.y);
}