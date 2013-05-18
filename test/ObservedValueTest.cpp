
#include <mvcgame/base/ObservedValue.hpp>
#include <math.h>
#include <gtest/gtest.h>

using namespace mvcgame;

TEST(ObservedValue, basic) {

    ObservedValue<int> v(0);

    ASSERT_EQ(0, v);

    v = -5;

    ASSERT_EQ(-5, v);

    v += 10;

    ASSERT_EQ(5, v);

    v *= 4;

    ASSERT_EQ(20, v);

    v /= 2;

    ASSERT_EQ(10, v);    

    v -= 5;

    ASSERT_EQ(5, v);        
}

TEST(ObservedValue, observe) {

    ObservedValue<bool> v(true);    

    bool changed = false;
    ObservedValue<bool>::Callback cb = [&changed](bool b){
        changed = true;
    };

    v.addObserver(cb);

    v = true;

    ASSERT_EQ(false, changed);

    v = false;

    ASSERT_EQ(true, changed);
}

TEST(ObservedValue, removeObserver) {

    ObservedValue<int> v(5);    

    int changed = 0;
    ObservedValue<int>::Callback cb = [&changed](int v){
        changed = v;
    };

    void* ref;
    v.addObserver(cb, ref);

    v = 10;

    ASSERT_EQ(10, changed);

    v.removeObserver(ref);

    v = 20;

    ASSERT_EQ(10, changed);
}