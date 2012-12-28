//
//  GeometryTest.cpp
//  hydra
//
//  Created by Miguel Ibero on 17/12/12.
//
//

#include <mvcgame/Geometry.hpp>
#include <math.h>
#include <gtest/gtest.h>

using namespace mvcgame;

TEST(Geometry, point) {
    
    Point p(2.3, 3.4);
    ASSERT_FLOAT_EQ(2.3, p.x);
    ASSERT_FLOAT_EQ(3.4, p.y);
    
    Point p2(2.3, 3.4);
    
    ASSERT_TRUE(p == p2);
    ASSERT_FALSE(p != p2);

    Point p3 = p + 5;
    
    ASSERT_FLOAT_EQ(7.3, p3.x);
    ASSERT_FLOAT_EQ(8.4, p3.y);
    
    ASSERT_FALSE(p == p3);
    p3 -= 5;
    ASSERT_TRUE(p == p3);
    
    p3 *= 2;

    ASSERT_FLOAT_EQ(4.6, p3.x);
    ASSERT_FLOAT_EQ(6.8, p3.y);
    
    p3 *= Scale(0.5);
    ASSERT_TRUE(p == p3);
    
    Scale s = p/p2;
    
    ASSERT_FLOAT_EQ(1, s.x);
    ASSERT_FLOAT_EQ(1, s.y);
    
    Size s1 = Size(4.6, 3.4);
    Anchor a = p/s1;
    
    ASSERT_FLOAT_EQ(0.5, a.x);
    ASSERT_FLOAT_EQ(1, a.y);
    
    Size s2 = p/a;
    
    ASSERT_TRUE(s1 == s2);
    
    Point p4;
    
    ASSERT_FLOAT_EQ(0, p4.x);
    ASSERT_FLOAT_EQ(0, p4.y);
}

TEST(Geometry, distance) {
    
    Point p1(4,4);
    Point p2(8,9);
    
    Distance d = p1-p2;
    
    ASSERT_FLOAT_EQ(-4, d.x);
    ASSERT_FLOAT_EQ(-5, d.y);
    ASSERT_FLOAT_EQ(sqrtf(5*5+4*4), d);
    
    ASSERT_TRUE(d+p2 == p1);
    
    d += 1;
    
    ASSERT_FLOAT_EQ(-3, d.x);
    ASSERT_FLOAT_EQ(-4, d.y);
    
    
    Distance d2 = d + Distance(2,3);
    
    ASSERT_FLOAT_EQ(-1, d2.x);
    ASSERT_FLOAT_EQ(-1, d2.y);
    
}

TEST(Geometry, anchor) {

    Anchor a;
    
    ASSERT_FLOAT_EQ(0.5, a.x);
    ASSERT_FLOAT_EQ(0.5, a.y);
    
    Point p = a*Size(10,20);
    
    ASSERT_FLOAT_EQ(5, p.x);
    ASSERT_FLOAT_EQ(10, p.y);
}



TEST(Geometry, size) {
    
    Size s;
    
    ASSERT_FLOAT_EQ(0, s.width);
    ASSERT_FLOAT_EQ(0, s.height);
    
    s += 10;
    
    ASSERT_FLOAT_EQ(10, s.width);
    ASSERT_FLOAT_EQ(10, s.height);
    
    s = s-10;
    
    ASSERT_FLOAT_EQ(0, s.width);
    ASSERT_FLOAT_EQ(0, s.height);
    
    
    s = Size(20, 20);
    Anchor a = s/Point(5, 10);
    
    ASSERT_FLOAT_EQ(4, a.x);
    ASSERT_FLOAT_EQ(2, a.y);
    
    s /= 2;
    
    ASSERT_FLOAT_EQ(10, s.width);
    ASSERT_FLOAT_EQ(10, s.height);
    
    s = s/2;
    
    ASSERT_FLOAT_EQ(5, s.width);
    ASSERT_FLOAT_EQ(5, s.height);

    Scale sc = s/Size(10, 20);
    
    ASSERT_FLOAT_EQ(0.5, sc.x);
    ASSERT_FLOAT_EQ(0.25, sc.y);
}

TEST(Geometry, rect) {
    
    Rect r;
    
    ASSERT_FLOAT_EQ(0, r.origin.x);
    ASSERT_FLOAT_EQ(0, r.origin.y);
    ASSERT_FLOAT_EQ(0, r.size.width);
    ASSERT_FLOAT_EQ(0, r.size.height);
    
    r.origin += 2;
    r.size += 10;
    
    Rect r2(2, 2, 10, 10);
    
    ASSERT_TRUE(r == r2);
    
    r2 = Rect(Point(2,2), Size(10,10));
    
    ASSERT_TRUE(r == r2);
    
    r2.size.width += 1;
    
    ASSERT_TRUE(r != r2);
    
    r2 /= 2;
    
    ASSERT_FLOAT_EQ(5.5, r2.size.width);
    
    r2 = r2*2;

    ASSERT_FLOAT_EQ(11, r2.size.width);
    
    Point p(2,2);
    
    ASSERT_TRUE(r2.contains(p));
    
    p = Point(1, 2);
    
    ASSERT_FALSE(r2.contains(p));
    
    p = Point(5, 5);
    
    ASSERT_TRUE(r2.contains(p));
    
    p = Point(13, 12);
    
    ASSERT_TRUE(r2.contains(p));
}

TEST(Geometry, rotation) {
    
    Rotation r;
    
    ASSERT_FLOAT_EQ(0, r.x);
    ASSERT_FLOAT_EQ(0, r.y);
    
    r = Rotation(Rotation::Pi);
    
    ASSERT_FLOAT_EQ(3.141592, r.x);
    ASSERT_FLOAT_EQ(3.141592, r.y);
    
    r += Rotation::Pi*2;
    
    ASSERT_FLOAT_EQ(3.141592, r.x);
    ASSERT_FLOAT_EQ(3.141592, r.y);
    
}

TEST(Geometry, scale) {
    
    Scale s;
    
    ASSERT_FLOAT_EQ(1, s.x);
    ASSERT_FLOAT_EQ(1, s.y);
    
    s *= 2;

    ASSERT_FLOAT_EQ(2, s.x);
    ASSERT_FLOAT_EQ(2, s.y);
    
    s = s*Scale(2, 4);

    ASSERT_FLOAT_EQ(4, s.x);
    ASSERT_FLOAT_EQ(8, s.y);
    
    s /= Scale(2, 4);
    
    ASSERT_FLOAT_EQ(2, s.x);
    ASSERT_FLOAT_EQ(2, s.y);


}