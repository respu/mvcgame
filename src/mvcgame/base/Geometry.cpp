
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Time.hpp>

#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>

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

    Point::Point() : x(0), y(0)
    {
    }

    Point::Point(gunit_t px, gunit_t py) : x(px), y(py)
    {
    }

    Point::Point(const Size& size) : x(size.width), y(size.height)
    {
    }

    gunit_t Point::distance() const
    {
        return sqrt(x*x+y*y);
    }

    bool Point::operator==(const Point& p) const
    {
        return guniteq(x, p.x) && guniteq(y, p.y);
    }

    bool Point::operator!=(const Point& p) const
    {
        return !guniteq(x, p.x) || !guniteq(y, p.y);
    }

    Point& Point::operator=(const Size& s)
    {
        x = s.width;
        y = s.height;
        return *this;
    }

    Point& Point::operator+=(const gunit_t& p)
    {
        x += p;
        y += p;
        return *this;
    }

    Point Point::operator+(const gunit_t& p) const
    {
        return Point(x+p, y+p);
    }

    Point& Point::operator+=(const Point& p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point Point::operator+(const Point& p) const
    {
        return Point(x+p.x, y+p.y);
    }

    Point& Point::operator-=(const Point& p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point Point::operator-(const Point& p) const
    {
        return Point(x-p.x, y-p.y);
    }

    Point& Point::operator-=(const gunit_t& p)
    {
        x -= p;
        y -= p;
        return *this;
    }

    Point Point::operator-(const gunit_t& p) const
    {
        return Point(x-p, y-p);
    }        

    Point& Point::operator*=(const gunit_t& s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    Point Point::operator*(const gunit_t& s) const
    {
        return Point(x*s, y*s);
    }

    Point& Point::operator*=(const Scale& s)
    {
        return operator*=(ScaleTransform(s));
    }

    Point Point::operator*(const Scale& s) const
    {
        return operator*(ScaleTransform(s));
    }

    Point& Point::operator*=(const Rotation& r)
    {
        return operator*=(ScaleTransform(r));
    }

    Point Point::operator*(const Rotation& r) const
    {
        return operator*(ScaleTransform(r));
    }

    Point& Point::operator*=(const ScaleTransform& s)
    {
        Point p = s*(*this);
        x = p.x;
        y = p.y;
        return *this;
    }

    Point Point::operator*(const ScaleTransform& s) const
    {
        Point p = s*(*this);
        return Point(p.x, p.y);
    }

    Size Point::operator*(const Anchor& a) const
    {
        return Size(x*a.x, y*a.y);
    }

    Point& Point::operator/=(const gunit_t& s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    Point Point::operator/(const gunit_t& s) const
    {
        return Point(x/s, y/s);
    }

    Scale Point::operator/(const Point& p) const
    {
        return Scale(x/p.x, y/p.y);
    }

    Anchor Point::operator/(const Size& s) const
    {
        return Anchor(x/s.width, y/s.height);
    }

    Size Point::operator/(const Anchor& a) const
    {
        return Size(x/a.x, y/a.y);
    }

    Speed Point::operator/(const Duration& d) const
    {
        float dt = d.fsecs();
        return Speed(x/dt, y/dt);
    }

#pragma mark - Anchor
    
    Anchor::Anchor() : x(0.5f), y(0.5f)
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

    Anchor Anchor::operator+(const Anchor& a) const
    {
        return Anchor(x+a.x, y+a.y);
    }

    Anchor& Anchor::operator+=(const gunit_t& a)
    {
        x += a;
        y += a;
        return *this;
    }

    Anchor Anchor::operator+(const gunit_t& a) const
    {
        return Anchor(x+a, y+a);
    }

    Anchor& Anchor::operator-=(const Anchor& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    Anchor Anchor::operator-(const Anchor& a) const
    {
        return Anchor(x-a.x, y-a.y);
    }

    Anchor& Anchor::operator-=(const gunit_t& a)
    {
        x -= a;
        y -= a;
        return *this;
    }

    Anchor Anchor::operator-(const gunit_t& a) const
    {
        return Anchor(x-a, y-a);
    }        

    Anchor& Anchor::operator*=(const gunit_t& s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    Anchor Anchor::operator*(const gunit_t& s) const
    {
        return Anchor(x*s, y*s);
    }

    Anchor& Anchor::operator/=(const gunit_t& s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    Anchor Anchor::operator/(const gunit_t& s) const
    {
        return Anchor(x/s, y/s);
    }

    Point Anchor::operator*(const Size& s) const
    {
        return Point(x*s.width, y*s.height);
    }

#pragma mark - Size
    
    Size::Size() : width(0), height(0)
    {
    }

    Size::Size(const Point& p) : width(p.x), height(p.y)
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

    Size& Size::operator=(const Point& p)
    {
        width = p.x;
        height = p.y;
        return *this;        
    }
    
    Size& Size::operator+=(const gunit_t& s)
    {
        width += s;
        height += s;
        return *this;
    }
    
    Size Size::operator+(const gunit_t& s) const
    {
        return Size(width+s, height+s);
    }
    
    Size& Size::operator-=(const gunit_t& s)
    {
        width -= s;
        height -= s;
        return *this;
    }
    
    Size Size::operator-(const gunit_t& s) const
    {
        return Size(width-s, height-s);
    }

    Point Size::operator*(const Anchor& a) const
    {
        return Point(width*a.x, height*a.y);
    }

    Anchor Size::operator/(const Point& p) const
    {
        return Anchor(width/p.x, height/p.y);
    }

    Size& Size::operator/=(const gunit_t& s)
    {
        width /= s;
        height /= s;
        return *this;
    }

    Size Size::operator/(const gunit_t& s) const
    {
        return Size(width/s, height/s);
    }

    Size& Size::operator*=(const gunit_t& s)
    {
        width *= s;
        height *= s;
        return *this;
    }

    Size Size::operator*(const gunit_t& s) const
    {
        return Size(width*s, width*s);
    }

    Scale Size::operator/(const Size& s) const
    {
        return Scale(width/s.width, height/s.height);
    }

    Size& Size::operator*=(const Scale& s)
    {
        width *= s.x;
        height *= s.y;
        return *this;
    }

    Size Size::operator*(const Scale& s) const
    {
        return Size(width*s.x, height*s.y);
    }

    gunit_t Size::area() const
    {
        return width*height;
    }

    Points Size::getVertices() const
    {
        Points vertices;
        vertices.push_back(Point(0, 0));
        vertices.push_back(Point(width, 0));
        vertices.push_back(Point(width, height));
        vertices.push_back(Point(0, height));        
        return vertices;
    }

#pragma mark - Rect
    
    Rect::Rect()
    {
    }

    Rect::Rect(const Size& s) : size(s)
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

    Rect Rect::operator/(const gunit_t& s) const
    {
        return Rect(origin/s, size/s);
    }

    Rect& Rect::operator*=(const gunit_t& s)
    {
        origin *= s;
        size *= s;
        return *this;
    }

    Rect Rect::operator*(const gunit_t& s) const
    {
        return Rect(origin*s, size*s);
    }

    Rect& Rect::operator*=(const Scale& s)
    {
        origin *= s;
        origin *= s;
        return *this;
    }

    Rect Rect::operator*(const Scale& s) const
    {
        return Rect(origin*s, size*s);
    }

    Points Rect::getVertices() const
    {
        Points vertices;
        vertices.push_back(Point(origin.x, origin.y));
        vertices.push_back(Point(origin.x+size.width, origin.y));
        vertices.push_back(Point(origin.x+size.width, origin.y+size.height));
        vertices.push_back(Point(origin.x, origin.y+size.height));        
        return vertices;
    }

    bool Rect::contains(const Point& p) const
    {
        return origin.x <= p.x && origin.x+size.width >= p.x &&
        origin.y <= p.y && origin.y+size.height >= p.y;
    }

#pragma mark - Rotation

	const gunit_t Rotation::Pi = 3.1415926535897932384626433832795028841971693993751;
    
    Rotation::Rotation() : x(0), y(0)
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

    Rotation Rotation::operator+(const gunit_t& a) const
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

    Rotation Rotation::operator-(const gunit_t& a) const
    {
        return Rotation(x-a, y-a);
    }

    Point Rotation::operator*(const Point& p) const
    {
        return p*(*this);
    }

    ScaleTransform Rotation::operator*(const Scale& s) const
    {
        return ScaleTransform(s, *this);
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
    
    Scale::Scale() : x(1), y(1)
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

    Scale& Scale::operator*=(gunit_t r)
    {
        x *= r;
        y *= r;
        return *this;
    }

    Scale Scale::operator*(gunit_t r) const
    {
        return Scale(*this)*r;
    }

    Rect Scale::operator*(const Rect& r) const
    {
        return Rect(r.origin.x*x, r.origin.y*y,
            r.size.width*x, r.size.height*y);
    }

    Point Scale::operator*(const Point& p) const
    {
        return Point(p.x*x, p.y*y);
    }

    Size Scale::operator*(const Size& s) const
    {
        return Size(s.width*x, s.height*y);
    }

    Scale Scale::operator/(const Scale& s) const
    {
        return Scale(x/s.x, y/s.y);
    }

    Scale& Scale::operator/=(const Scale& s)
    {
        x /= s.x;
        y /= s.y;
        return *this;
    }

    Scale Scale::operator*(const Scale& s) const
    {
        return Scale(x*s.x, y*s.y);
    }

    Scale& Scale::operator*=(const Scale& s)
    {
        x *= s.x;
        y *= s.y;
        return *this;
    }

    ScaleTransform Scale::operator*(const Rotation& r) const
    {
        return ScaleTransform(*this, r);
    }

#pragma mark - ScaleTransform

    ScaleTransform::ScaleTransform() :
    a(0),
    b(0),
    c(0),
    d(0)
    {

    }

    ScaleTransform::ScaleTransform(gunit_t pa, gunit_t pb, gunit_t pc, gunit_t pd) :
    a(pa),
    b(pb),
    c(pc),
    d(pd)   
    {
    }

    ScaleTransform::ScaleTransform(const Scale& s, const Rotation& r)
    {
        gunit_t cx = cosf(r.x);
        gunit_t cy = cosf(r.y);
        gunit_t sx = sinf(r.x);
        gunit_t sy = sinf(r.y);
        a = cy*s.x;
        b = sy*s.x;
        c = -sx*s.y;
        d = cx*s.y;
    }

    ScaleTransform::ScaleTransform(const Scale& s)
    {
        *this = s;
    }

    ScaleTransform::ScaleTransform(const Rotation& r)
    {
        *this = r;
    }

    ScaleTransform& ScaleTransform::operator=(const Rotation& r)
    {
        a = cosf(r.y);
        b = sinf(r.y);
        c = -sinf(r.x);
        d = cosf(r.x);
        return *this;
    }

    ScaleTransform& ScaleTransform::operator=(const Scale& s)
    {
        a = s.x;
        b = 0;
        c = 0;
        d = s.y;
        return *this;
    }

    Point ScaleTransform::operator*(const Point& p) const
    {
        return Point(p.x*a+p.y*c, p.y*d+p.x*b);
    }

#pragma mark - Transform

    Transform::Transform() :
    a(1),
    b(0),
    c(0),
    d(1),
    tx(0),
    ty(0)
    {
    }

    Transform::Transform(gunit_t pa, gunit_t pb, gunit_t pc,
        gunit_t pd, gunit_t ptx, gunit_t pty) :
    a(pa),
    b(pb),
    c(pc),
    d(pd),
    tx(ptx),
    ty(pty)
    {
    }

    Transform::Transform(const ScaleTransform& st)
    {
        *this = st;
    }

    Transform::Transform(const Point& p)
    {
        *this = p;
    }

    Transform::Transform(const Scale& s)
    {
        *this = ScaleTransform(s);
    }

    Transform::Transform(const Rotation& r)
    {
        *this = ScaleTransform(r);
    }

    void Transform::update(const Rect& frame, const Anchor& anchor, const Rotation& rot, const Scale& scale)
    {
        update(frame.origin, anchor*frame.size, rot, scale);
    }

    void Transform::update(const Point& point, const Anchor& anchor, const Size& size, const Rotation& rot, const Scale& scale)
    {
        update(point, anchor*size, rot, scale);
    }

    void Transform::update(const Point& point, const Point& anchor, const Rotation& rot, const Scale& scale)
    {
        ScaleTransform st = scale*rot;
        Point tp = point-(anchor*st);
        a = st.a;
        b = st.b;
        c = st.c;
        d = st.d;
        tx = tp.x;
        ty = tp.y;
    }

    Transform& Transform::operator=(const ScaleTransform& st)
    {
        a = st.a;
        b = st.b;
        c = st.c;
        d = st.d;
        tx = 0;
        ty = 0;
        return *this;
    }

    Transform& Transform::operator=(const Point& p)
    {
        a = 1;
        b = 0;
        c = 0;
        d = 1;
        tx = p.x;
        ty = p.y;
        return *this;
    }

    Transform Transform::operator+(const Point& p)
    {
        return Transform(a, b, c, d, tx+p.x, ty+p.y);
    }

    Transform& Transform::operator+=(const Point& p)
    {
        tx += p.x;
        ty += p.y;
        return *this;
    }

    Transform Transform::operator-(const Point& p)
    {
        return Transform(a, b, c, d, tx-p.x, ty-p.y);
    }

    Transform& Transform::operator-=(const Point& p)
    {
        tx -= p.x;
        ty -= p.y;
        return *this;
    }

    Transform Transform::invert() const
    {
        float det = 1 / (a * d - b * c);

        return Transform(det * d, -det * b, -det * c, det * a,
                            det * (c * ty - d * tx), det * (b * tx - a * ty) );
    }

#pragma mark - stream functions

    std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "Point(" << p.x << ", " << p.y << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Scale& s)
    {
        os << "Scale(" << s.x << ", " << s.y << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Anchor& a)
    {
        os << "Anchor(" << a.x << ", " << a.y << ")";
        return os;
    }


    std::ostream& operator<<(std::ostream& os, const Size& s)
    {
        os << "Size(" << s.width << ", " << s.height << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Rotation& r)
    {
        gunit_t dx = 180/Rotation::Pi*r.x;
        gunit_t dy = 180/Rotation::Pi*r.y;
        os << "Rotation(" << dx;
        if(!guniteq(dx, dy))
        {
            os << ", " << dy;
        }
        os << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const ScaleTransform& st)
    {
        os << "Transform(";
        os << " a=" << st.a << " b=" << st.b;
        os << " c=" << st.c << " d=" << st.d;
        os << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Transform& t)
    {
        os << "Transform(";
        os << " a=" << t.a << " b=" << t.b;
        os << " c=" << t.c << " d=" << t.d;
        os << " tx=" << t.tx << " ty=" << t.ty;
        os << ")";
        return os;
    }
    
              
}
