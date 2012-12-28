//
//  Geometry.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/Geometry.hpp>
#include <mvcgame/Time.hpp>
#include <math.h>
#include <limits>
#include <algorithm>

#define GUNIT_EQ_ULP 4

namespace mvcgame {
    
    /**
     * Decide if two gunits are equal
     */
    inline bool guniteq(gunit_t a, gunit_t b)
    {
        gunit_t epsilon = std::numeric_limits<gunit_t>::epsilon()*GUNIT_EQ_ULP;
        return fabs(a - b) <= epsilon * std::max(fabs(a), fabs(b));
    }
    
#pragma mark - Point
    
    Point::Point()
    {
    }

    Point::Point(gunit_t px, gunit_t py) : x(px), y(py)
    {
    }

    bool Point::operator==(const Point& p) const
    {
        return guniteq(x, p.x) && guniteq(y, p.y);
    }

    bool Point::operator!=(const Point& p) const
    {
        return !guniteq(x, p.x) || !guniteq(y, p.y);
    }

    Point& Point::operator+=(const gunit_t& p)
    {
        x += p;
        y += p;
        return *this;
    }

    const Point Point::operator+(const gunit_t& p) const
    {
        return Point(x+p, y+p);
    }

    Point& Point::operator+=(const Distance& d)
    {
        x += d.x;
        y += d.y;
        return *this;
    }

    const Point Point::operator+(const Distance& d) const
    {
        return Point(x+d.x, y+d.y);
    }

    Point& Point::operator-=(const Distance& d)
    {
        x -= d.x;
        y -= d.y;
        return *this;
    }

    const Distance Point::operator-(const Point& p) const
    {
        return Distance(x-p.x, y-p.y);
    }

    Point& Point::operator-=(const gunit_t& p)
    {
        x -= p;
        y -= p;
        return *this;
    }

    const Point Point::operator-(const gunit_t& p) const
    {
        return Point(x-p, y-p);
    }        

    Point& Point::operator*=(const gunit_t& s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    const Point Point::operator*(const gunit_t& s) const
    {
        return Point(x*s, y*s);
    }

    Point& Point::operator*=(const Scale& s)
    {
        x *= s.x;
        y *= s.y;
        return *this;
    }

    const Point Point::operator*(const Scale& s) const
    {
        return Point(x*s.x, y*s.y);
    }        

    Point& Point::operator/=(const gunit_t& s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    const Point Point::operator/(const gunit_t& s) const
    {
        return Point(x/s, y/s);
    }

    const Scale Point::operator/(const Point& p) const
    {
        return Scale(x/p.x, y/p.y);
    }        

    const Anchor Point::operator/(const Size& s) const
    {
        return Anchor(x/s.width, y/s.height);
    }

    const Size Point::operator/(const Anchor& a) const
    {
        return Size(x/a.x, y/a.y);
    }

#pragma mark - Distance
    
    Distance::Distance()
    {
    }

    Distance::Distance(gunit_t px, gunit_t py) : x(px), y(py)
    {
    }

    Distance::operator gunit_t() const
    {
        if(!_hasValue)
        {
            _value = sqrt(x*x+y*y);
            _hasValue = true;
        }
        return _value;
    }
    
    bool Distance::operator==(const Distance& d) const
    {
        return guniteq(x, d.x) && guniteq(y, d.y);
    }
    
    bool Distance::operator!=(const Distance& d) const
    {
        return !guniteq(x, d.x) || !guniteq(y, d.y);
    }

    const Point Distance::operator+(const Point& p)
    {
        return Point(x+p.x, y+p.y);
    }

    const Speed Distance::operator/(const Duration& d)
    {
        float dt = d.fsecs();
        return Speed(x/dt, y/dt);
    }

    Distance& Distance::operator+=(const Distance& d)
    {
        x += d.x;
        y += d.y;
        return *this;
    }

    const Distance Distance::operator+(const Distance& d) const
    {
        return Distance(x+d.x, y+d.y);
    }

    Distance& Distance::operator+=(const gunit_t& d)
    {
        x += d;
        y += d;
        return *this;
    }

    const Distance Distance::operator+(const gunit_t& d) const
    {
        return Distance(x+d, y+d);
    }

    Distance& Distance::operator-=(const Distance& d)
    {
        x -= d.x;
        y -= d.y;
        return *this;
    }

    const Distance Distance::operator-(const Distance& d) const
    {
        return Distance(x-d.x, y-d.y);
    }

    Distance& Distance::operator-=(const gunit_t& d)
    {
        x -= d;
        y -= d;
        return *this;
    }

    const Distance Distance::operator-(const gunit_t& d) const
    {
        return Distance(x-d, y-d);
    }

#pragma mark - Anchor
    
    Anchor::Anchor()
    {
    }
    
    Anchor::Anchor(gunit_t px, gunit_t py) : x(px), y(py)
    {
    }

    bool Anchor::operator==(const Anchor& a) const
    {
        return guniteq(x, a.x) && guniteq(y, a.y);
    }

    bool Anchor::operator!=(const Anchor& a) const
    {
        return !guniteq(x, a.x) || !guniteq(y, a.y);
    }
    
    Anchor& Anchor::operator+=(const Anchor& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    const Anchor Anchor::operator+(const Anchor& a) const
    {
        return Anchor(x+a.x, y+a.y);
    }

    Anchor& Anchor::operator+=(const gunit_t& a)
    {
        x += a;
        y += a;
        return *this;
    }

    const Anchor Anchor::operator+(const gunit_t& a) const
    {
        return Anchor(x+a, y+a);
    }

    Anchor& Anchor::operator-=(const Anchor& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    const Anchor Anchor::operator-(const Anchor& a) const
    {
        return Anchor(x-a.x, y-a.y);
    }

    Anchor& Anchor::operator-=(const gunit_t& a)
    {
        x -= a;
        y -= a;
        return *this;
    }

    const Anchor Anchor::operator-(const gunit_t& a) const
    {
        return Anchor(x-a, y-a);
    }        

    Anchor& Anchor::operator*=(const gunit_t& s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    const Anchor Anchor::operator*(const gunit_t& s) const
    {
        return Anchor(x*s, y*s);
    }

    Anchor& Anchor::operator/=(const gunit_t& s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    const Anchor Anchor::operator/(const gunit_t& s) const
    {
        return Anchor(x/s, y/s);
    }

    const Point Anchor::operator*(const Size& s) const
    {
        return Point(x*s.width, y*s.height);
    }

#pragma mark - Size
    
    Size::Size()
    {
    }

    Size::Size(gunit_t w, gunit_t h) : width(w), height(h)
    {
    }
    
    bool Size::operator==(const Size& s) const
    {
        return guniteq(width, s.width) && guniteq(height, s.height);
    }
    
    bool Size::operator!=(const Size& s) const
    {
        return !guniteq(width, s.width) || !guniteq(height, s.height);
    }
    
    Size& Size::operator+=(const gunit_t& s)
    {
        width += s;
        height += s;
        return *this;
    }
    
    const Size Size::operator+(const gunit_t& s) const
    {
        return Size(width+s, height+s);
    }
    
    Size& Size::operator-=(const gunit_t& s)
    {
        width -= s;
        height -= s;
        return *this;
    }
    
    const Size Size::operator-(const gunit_t& s) const
    {
        return Size(width-s, height-s);
    }

    const Point Size::operator*(const Anchor& a) const
    {
        return Point(width*a.x, height*a.y);
    }

    const Anchor Size::operator/(const Point& p) const
    {
        return Anchor(width/p.x, height/p.y);
    }

    Size& Size::operator/=(const gunit_t& s)
    {
        width /= s;
        height /= s;
        return *this;
    }

    const Size Size::operator/(const gunit_t& s) const
    {
        return Size(width/s, height/s);
    }

    Size& Size::operator*=(const gunit_t& s)
    {
        width *= s;
        height *= s;
        return *this;
    }

    const Size Size::operator*(const gunit_t& s) const
    {
        return Size(width*s, width*s);
    }

    const Scale Size::operator/(const Size& s) const
    {
        return Scale(width/s.width, height/s.height);
    }

    Size& Size::operator*=(const Scale& s)
    {
        width *= s.x;
        height *= s.y;
        return *this;
    }

    const Size Size::operator*(const Scale& s) const
    {
        return Size(width*s.x, height*s.y);
    }

    gunit_t Size::area() const
    {
        return width*height;
    }

#pragma mark - Rect
    
    Rect::Rect()
    {
    }
    
    Rect::Rect(const Point& p, const Size& s) : origin(p), size(s)
    {
    }
    
    Rect::Rect(gunit_t x, gunit_t y, gunit_t w, gunit_t h) : origin(x, y), size(w, h)
    {
    }

    bool Rect::operator==(const Rect& r) const
    {
        return origin == r.origin && size == r.size;
    }

    bool Rect::operator!=(const Rect& r) const
    {
        return origin != r.origin || size != r.size;
    }    

    Rect& Rect::operator/=(const gunit_t& s)
    {
        origin /= s;
        size /= s;
        return *this;
    }

    const Rect Rect::operator/(const gunit_t& s) const
    {
        return Rect(origin/s, size/s);
    }

    Rect& Rect::operator*=(const gunit_t& s)
    {
        origin *= s;
        size *= s;
        return *this;
    }

    const Rect Rect::operator*(const gunit_t& s) const
    {
        return Rect(origin*s, size*s);
    }

    Rect& Rect::operator*=(const Scale& s)
    {
        origin *= s;
        origin *= s;
        return *this;
    }

    const Rect Rect::operator*(const Scale& s) const
    {
        return Rect(origin*s, size*s);
    }

    bool Rect::contains(const Point& p) const
    {
        return origin.x <= p.x && origin.x+size.width >= p.x &&
        origin.y <= p.y && origin.y+size.height >= p.y;
    }

#pragma mark - Rotation
    
    Rotation::Rotation()
    {
    }

    Rotation::Rotation(gunit_t px) : x(px), y(px)
    {
        correct();
    }
    
    Rotation::Rotation(gunit_t px, gunit_t py) : x(px), y(py)
    {
        correct();
    }

    const gunit_t Rotation::Pi = 3.1415926535897932384626433832795028841971693993751;

    bool Rotation::operator==(const Rotation& r) const
    {
        return guniteq(x, r.x) && guniteq(y, r.y);
    }

    bool Rotation::operator!=(const Rotation& r) const
    {
        return !guniteq(x, r.x) || !guniteq(y, r.y);
    }

    Rotation& Rotation::operator+=(const gunit_t& a)
    {
        x += a;
        y += a;
        correct();
        return *this;
    }

    const Rotation Rotation::operator+(const gunit_t& a) const
    {
        return Rotation(x+a, y+a);
    }

    Rotation& Rotation::operator-=(const gunit_t& a)
    {
        x -= a;
        y -= a;
        correct();
        return *this;
    }

    const Rotation Rotation::operator-(const gunit_t& a) const
    {
        return Rotation(x-a, y-a);
    }

    void Rotation::correct()
    {
        gunit_t max = 2*Pi;
        while(x > max) {
            x -= max;
        }
        while(x < 0) {
            x += max;
        }
        while(y > max) {
            y -= max;
        }
        while(y < 0) {
            y += max;
        }
    }

#pragma mark - Scale
    
    Scale::Scale()
    {
    }
    
    Scale::Scale(gunit_t px) : x(px), y(px)
    {
    }
    
    Scale::Scale(gunit_t px, gunit_t py) : x(px), y(py)
    {
    }

    bool Scale::operator==(const Scale& s) const
    {
        return guniteq(x, s.x) && guniteq(y, s.y);
    }

    bool Scale::operator!=(const Scale& s) const
    {
        return !guniteq(x, s.x) || !guniteq(y, s.y);
    }

    const Rect Scale::operator*(const Rect& r) const
    {
        return Rect(r.origin.x*x, r.origin.y*y,
            r.size.width*x, r.size.height*y);
    }

    const Point Scale::operator*(const Point& p) const
    {
        return Point(p.x*x, p.y*y);
    }

    const Size Scale::operator*(const Size& s) const
    {
        return Size(s.width*x, s.height*y);
    }

    const Scale Scale::operator/(const Scale& s) const
    {
        return Scale(x/s.x, y/s.y);
    }

    Scale& Scale::operator/=(const Scale& s)
    {
        x /= s.x;
        y /= s.y;
        return *this;
    }

    const Scale Scale::operator*(const Scale& s) const
    {
        return Scale(x*s.x, y*s.y);
    }

    Scale& Scale::operator*=(const Scale& s)
    {
        x *= s.x;
        y *= s.y;
        return *this;
    }
              
}
