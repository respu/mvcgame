#ifndef mvcgame_Geometry_hpp
#define mvcgame_Geometry_hpp

#include <iostream>
#include <vector>

namespace mvcgame {
    
    class Point;
    class Scale;
    class Anchor;
    class Size;
    class Duration;
    class Speed;
    class Rotation;
    class ScaleTransform;
    class Transform;

    typedef float gunit_t;
    typedef std::vector<Point> Points;
  
    /**
     * Represents a point in 2d space
     */
    class Point final
    {
    public:
        gunit_t x;
        gunit_t y;

        Point();
        Point(gunit_t x, gunit_t y);
        Point(const Size& size);

        gunit_t distance() const;

        bool operator==(const Point& p) const;
        bool operator!=(const Point& p) const;

        Point& operator=(const Size& s);

        Point& operator+=(const gunit_t& p);
        Point operator+(const gunit_t& p) const;
        Point& operator+=(const Point& p);
        Point operator+(const Point& p) const;       

        Point& operator-=(const gunit_t& p);
        Point operator-(const gunit_t& p) const;
        Point& operator-=(const Point& p);
        Point operator-(const Point& p) const;

        Point& operator*=(const gunit_t& s);
        Point operator*(const gunit_t& s) const;
        Point& operator*=(const Scale& s);
        Point operator*(const Scale& s) const;
        Point& operator*=(const Rotation& r);
        Point operator*(const Rotation& r) const;
        Point& operator*=(const ScaleTransform& s);
        Point operator*(const ScaleTransform& s) const;
        Point& operator*=(const Transform& s);
        Point operator*(const Transform& s) const;        
        Size operator*(const Anchor& a) const;

        Point& operator/=(const gunit_t& s);
        Point operator/(const gunit_t& s) const;
        Scale operator/(const Point& p) const;
        Anchor operator/(const Size& s) const;
        Size operator/(const Anchor& a) const;
        Speed operator/(const Duration& d) const;
    };

    /**
     * Anchor point should be a value pair between 0 and 1
     * 0 being bottom or left
     * 1 being top or right
     */
    class Anchor final
    {
    public:
        gunit_t x;
        gunit_t y;
    
        Anchor();
        Anchor(gunit_t x, gunit_t y);

        bool operator==(const Anchor& a) const;
        bool operator!=(const Anchor& a) const;
        
        Anchor& operator+=(const Anchor& a);
        Anchor operator+(const Anchor& a) const;
        Anchor& operator+=(const gunit_t& a); 
        Anchor operator+(const gunit_t& a) const;

        Anchor& operator-=(const Anchor& a);
        Anchor operator-(const Anchor& a) const;
        Anchor& operator-=(const gunit_t& a);
        Anchor operator-(const gunit_t& a) const;

        Anchor& operator*=(const gunit_t& s);
        Anchor operator*(const gunit_t& s) const;
        Point operator*(const Size& s) const;

        Anchor& operator/=(const gunit_t& s);
        Anchor operator/(const gunit_t& s) const;
    };    
    
    class Size final
    {
    public:
        gunit_t width;
        gunit_t height;
        
        Size();
        Size(const Point& p);
        Size(gunit_t w, gunit_t h);

        bool operator==(const Size& s) const;
        bool operator!=(const Size& s) const;

        Size& operator=(const Point& p);
        
        Size& operator+=(const gunit_t& s);
        Size operator+(const gunit_t& s) const;
        
        Size& operator-=(const gunit_t& s);
        Size operator-(const gunit_t& s) const;
        
        Size& operator*=(const gunit_t& s);
        Size operator*(const gunit_t& s) const;
        Point operator*(const Anchor& a) const;
        Size& operator*=(const Scale& s);
        Size operator*(const Scale& s) const;

        Anchor operator/(const Point& p) const;
        Size& operator/=(const gunit_t& s);
        Size operator/(const gunit_t& s) const;
        Scale operator/(const Size& s) const;

        gunit_t area() const;

        Points getVertices() const;

        bool contains(const Point& p) const;
    };
    
    /**
     * Represents a rectangle
     */
    class Rect final
    {
    public:        
        Point origin;
        Size size;
        
        Rect();
        Rect(const Size& s);
        Rect(const Point& p, const Size& s);
        Rect(gunit_t x, gunit_t y, gunit_t w, gunit_t h);
        Rect(const Point& bl, const Point& tr);

        bool operator==(const Rect& r) const;
        bool operator!=(const Rect& r) const;     

        Rect& operator/=(const gunit_t& s);
        Rect operator/(const gunit_t& s) const;

        Rect& operator*=(const gunit_t& s);
        Rect operator*(const gunit_t& s) const;
        Rect& operator*=(const Scale& s);
        Rect operator*(const Scale& s) const;
        Rect& operator*=(const Rotation& r);
        Rect operator*(const Rotation& r) const;        

        Rect& operator+=(const Point& p);
        Rect operator+(const Point& p) const;

        Rect& operator+=(const Rect& r);
        Rect operator+(const Rect& r) const;

        Points getVertices() const;

        bool contains(const Point& p) const;

        Point getOuter() const;
    };

    /**
     * Represents a rectangle border
     */
    class RectBorder final
    {
    public:
        gunit_t top;
        gunit_t right;        
        gunit_t bottom;
        gunit_t left;

        RectBorder();
        RectBorder(gunit_t t, gunit_t r, gunit_t b, gunit_t l);

        bool operator==(const RectBorder& r) const;
        bool operator!=(const RectBorder& r) const; 
    };
    
    /**
     * Rotation should be in radians
     * both values will be mod(2*PI)
     */
    class Rotation final
    {
    private:
        void correct();
    public:
        gunit_t x;
        gunit_t y;

        static const gunit_t Pi;
        
        Rotation();
        Rotation(gunit_t x);
        Rotation(gunit_t x, gunit_t y);

        bool operator==(const Rotation& r) const;
        bool operator!=(const Rotation& r) const;        

        Rotation& operator+=(const gunit_t& a);
        Rotation operator+(const gunit_t& a) const;

        Rotation& operator-=(const gunit_t& a);
        Rotation operator-(const gunit_t& a) const;

        Point operator*(const Point& p) const;
        ScaleTransform operator*(const Scale& s) const;
    };
    
    class Scale final
    {
    public:        
        gunit_t x;
        gunit_t y;

        Scale();
        Scale(gunit_t x);
        Scale(gunit_t x, gunit_t y);

        bool operator==(const Scale& s) const;
        bool operator!=(const Scale& s) const;

        Scale& operator*=(gunit_t r);
        Scale operator*(gunit_t r) const;

        Rect operator*(const Rect& r) const;
        Point operator*(const Point& p) const;
        Size operator*(const Size& s) const;
        Scale operator*(const Scale& s) const;
        Scale& operator*=(const Scale& s);

        Scale operator/(const Scale& s) const;
        Scale& operator/=(const Scale& s);

        ScaleTransform operator*(const Rotation& r) const;
    };

    /**
     * A scale transformation matrix
     */
    class ScaleTransform
    {
    public:
        gunit_t a;
        gunit_t b;
        gunit_t c;
        gunit_t d;

        ScaleTransform();
        ScaleTransform(gunit_t a, gunit_t b, gunit_t c, gunit_t d);
        ScaleTransform(const Scale& s, const Rotation& r);
        ScaleTransform(const Scale& s);
        ScaleTransform(const Rotation& r);

        ScaleTransform& operator=(const Rotation& r);
        ScaleTransform& operator=(const Scale& s);

        Point operator*(const Point& p) const;
    };

    /**
     * A transformation matrix
     * | a b tx |
     * | c d ty |
     * | 0 0  1 |
     */
    class Transform final {
    public:
        gunit_t a;
        gunit_t b;
        gunit_t c;
        gunit_t d;
        gunit_t tx;
        gunit_t ty;

        static const Transform Identity;

        Transform();        
        Transform(gunit_t a, gunit_t b, gunit_t c,
            gunit_t d, gunit_t tx, gunit_t ty);
        Transform(const ScaleTransform& st);
        Transform(const Scale& s);
        Transform(const Rotation& r);
        Transform(const Point& p);

        bool update(const Rect& f, const Anchor& a,
            const Rotation& r, const Scale& c);        

        bool update(const Point& p, const Anchor& a,
            const Size& s, const Rotation& r, const Scale& c);

        bool update(const Point& p, const Point& a,
            const Rotation& r, const Scale& c);

        bool operator==(const Transform& t) const;

        Transform& operator=(const ScaleTransform& st);
        Transform& operator=(const Point& p);

        Transform operator+(const Point& p) const;
        Transform& operator+=(const Point& p);
        Transform operator-(const Point& p) const;
        Transform& operator-=(const Point& p);

        Point operator*(const Point& p) const;

        Transform operator*(const Transform& t) const;
        Transform& operator*=(const Transform& t);

        Transform operator/(const Transform& t) const;
        Transform& operator/=(const Transform& t);

        Transform invert() const;
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const Point& p);
    std::ostream& operator<<(std::ostream& os, const Scale& s);
    std::ostream& operator<<(std::ostream& os, const Anchor& a);
    std::ostream& operator<<(std::ostream& os, const Size& s);
    std::ostream& operator<<(std::ostream& os, const Rect& r); 
    std::ostream& operator<<(std::ostream& os, const RectBorder& r);
    std::ostream& operator<<(std::ostream& os, const Rotation& r);
    std::ostream& operator<<(std::ostream& os, const ScaleTransform& st);
    std::ostream& operator<<(std::ostream& os, const Transform& t);
}

#endif