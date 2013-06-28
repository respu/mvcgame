
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Time.hpp>

#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>
#include <stdexcept>

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

    Point& Point::operator*=(const Transform& t)
    {
        Point p = t*(*this);
        x = p.x;
        y = p.y;
        return *this;
    }

    Point Point::operator*(const Transform& t) const
    {
        Point p = t*(*this);
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

    bool Size::contains(const Point& p) const
    {
        return p.x >= 0 && p.y >=0 && p.x <= width && p.y <= height;
    }

#pragma mark - Rect
    
    Rect::Rect()
    {
    }

    Rect::Rect(const Size& s) : size(s)
    {
    }

    Rect::Rect(const Point& p, const Point& o) : origin(p), size(o-p)
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

    Rect& Rect::operator+=(const Point& p)
    {
        Point p1a = origin;
        Point p1b = getOuter();
        origin.x = std::min(p1a.x, p.x);
        origin.y = std::min(p1a.y, p.y);
        size.width = std::max(p1b.x, p.x) - origin.x;
        size.height = std::max(p1b.y, p.y) - origin.y;
        return *this;
    }

    Rect Rect::operator+(const Point& p) const
    {
        Point p1a = origin;
        Point p1b = getOuter();
        p1a.x = std::min(p1a.x, p.x);
        p1a.y = std::min(p1a.y, p.y);
        p1b.x = std::max(p1b.x, p.x);
        p1b.y = std::max(p1b.y, p.y);
        return Rect(p1a, p1b);
    }

    Rect& Rect::operator+=(const Rect& r)
    {
        Point p1a = origin;
        Point p1b = getOuter();
        Point p2a = r.origin;
        Point p2b = r.getOuter();
        origin.x = std::min(p1a.x, p2a.x);
        origin.y = std::min(p1a.y, p2a.y);
        size.width = std::max(p1b.x, p2b.x) - origin.x;
        size.height = std::max(p1b.y, p2b.y) - origin.y;
        return *this;
    }

    Rect Rect::operator+(const Rect& r) const
    {
        Point p1a = origin;
        Point p1b = getOuter();
        Point p2a = r.origin;
        Point p2b = r.getOuter();
        p1a.x = std::min(p1a.x, p2a.x);
        p1a.y = std::min(p1a.y, p2a.y);
        p1b.x = std::max(p1b.x, p2b.x);
        p1b.y = std::max(p1b.y, p2b.y);
        return Rect(p1a, p1b);
    }    

    Point Rect::getOuter() const
    {
        return Point(origin.x + size.width, origin.y + size.height);
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

#pragma mark - RectBorder

    RectBorder::RectBorder() :
    top(0), right(0), bottom(0), left(0)
    {
    }

    RectBorder::RectBorder(gunit_t t, gunit_t r, gunit_t b, gunit_t l) :
    top(t), right(r), bottom(b), left(l)
    {
    }

    bool RectBorder::operator==(const RectBorder& r) const
    {
        return top == r.top && right == r.right && bottom == r.bottom && left == r.left;
    }

    bool RectBorder::operator!=(const RectBorder& r) const
    {
        return !(*this==r);
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
        return Scale(x*r, y*r);
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

    const Transform Transform::Identity = Transform();

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

    bool Transform::update(const Rect& frame, const Anchor& anchor, const Rotation& rot, const Scale& scale)
    {
        return update(frame.origin, anchor*frame.size, rot, scale);
    }

    bool Transform::update(const Point& point, const Anchor& anchor, const Size& size, const Rotation& rot, const Scale& scale)
    {
        return update(point, anchor*size, rot, scale);
    }

    bool Transform::update(const Point& point, const Point& anchor, const Rotation& rot, const Scale& scale)
    {
        ScaleTransform st = scale*rot;
        Point tp = point-(anchor*st);
        bool same = guniteq(a, st.a) && guniteq(b, st.b) &&
        guniteq(c, st.c) && guniteq(d, st.d) &&
        guniteq(tx, tp.x) && guniteq(ty, tp.y);
        a = st.a;
        b = st.b;
        c = st.c;
        d = st.d;
        tx = tp.x;
        ty = tp.y;
        return !same;
    }

    bool Transform::operator==(const Transform& t) const
    {
        return guniteq(a, t.a) && guniteq(b, t.b) &&
        guniteq(c, t.c) && guniteq(d, t.d) &&
        guniteq(tx, t.tx) && guniteq(ty, t.ty);
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

    Transform Transform::operator+(const Point& p) const
    {
        return Transform(a, b, c, d, tx+p.x, ty+p.y);
    }

    Transform& Transform::operator+=(const Point& p)
    {
        tx += p.x;
        ty += p.y;
        return *this;
    }

    Transform Transform::operator-(const Point& p) const
    {
        return Transform(a, b, c, d, tx-p.x, ty-p.y);
    }

    Transform& Transform::operator-=(const Point& p)
    {
        tx -= p.x;
        ty -= p.y;
        return *this;
    }

    Point Transform::operator*(const Point& p) const
    {
        return Point(p.x*a+p.y*c+tx, p.y*d+p.x*b+ty);
    }    

    Transform Transform::operator*(const Transform& t) const
    {
        return Transform(
            a * t.a + c * t.b,
            a * t.c + c * t.d,
            b * t.a + d * t.b,
            b * t.c + d * t.d,
            tx * t.a + ty * t.b + t.tx,
            tx * t.c + ty * t.d + t.ty
        );
    }

    Transform& Transform::operator*=(const Transform& t)
    {
        Transform r = *this * t;
        a = r.a;
        b = r.b;
        c = r.c;
        d = r.d;
        tx = r.tx;
        ty = r.ty;
        return *this;
    }

    Transform Transform::operator/(const Transform& t) const
    {
        if(t == *this)
        {
            return Identity;
        }
        return *this * t.invert();
    }

    Transform& Transform::operator/=(const Transform& t)
    {
        return *this *= t.invert();
    }

    Transform Transform::invert() const
    {
        gunit_t det = a * d - b * c;

        if(det == 0)
        {
            throw std::runtime_error("Could not invert transform");
        }

        det = 1 / det;
        return Transform(det * d, -det * b, -det * c, det * a,
                            det * (b * ty - d * tx), det * (c * tx - a * ty) );
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

    std::ostream& operator<<(std::ostream& os, const Rect& r)
    {
        os << "Rect(origin=" << r.origin << " size=" << r.size << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const RectBorder& r)
    {
        os << "RectBorder(";
        os << " top=" << r.top << " right=" << r.right;
        os << " bottom=" << r.bottom << " left=" << r.left;
        os << ")";
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
        os.setf( std::ios::fixed, std::ios::floatfield );
        os << std::showpos;
        os << "ScaleTransform" << std::endl;
        os << "[ " << st.a << " " << st.b << " " << 0.0f << " ]" << std::endl;
        os << "[ " << st.c << " " << st.d << " " << 0.0f << " ]" << std::endl;
        os << "[ " << 0.0f << " " << 0.0f << " " << 1.0f << " ]" << std::endl;
        std::cout.unsetf( std::ios::floatfield ); 
        os << std::noshowpos;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Transform& t)
    {
        os.setf( std::ios::fixed, std::ios::floatfield );
        os << std::showpos;        
        os << "Transform" << std::endl;
        os << "[ " << t.a << " " << t.b << " " << t.tx << " ]" << std::endl;
        os << "[ " << t.c << " " << t.d << " " << t.ty << " ]" << std::endl;
        os << "[ " << 0.0f << " " << 0.0f << " " << 1.0f << " ]" << std::endl;
        std::cout.unsetf( std::ios::floatfield ); 
        os << std::noshowpos;        
        return os;
    }
    
              
}
