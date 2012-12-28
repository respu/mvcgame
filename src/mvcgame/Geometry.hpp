//
//  Geometry.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_Geometry_hpp
#define mvcgame_Geometry_hpp

namespace mvcgame {
    
    typedef float gunit_t;

    class Distance;
    class Scale;
    class Anchor;
    class Size;
    class Duration;
    class Speed;
  
    /**
     * Represents a point in 2d space
     */
    class Point final {
    public:   
        gunit_t x = 0.0f;
        gunit_t y = 0.0f;
    
        Point();
        Point(gunit_t px, gunit_t py);

        bool operator==(const Point& p) const;
        bool operator!=(const Point& p) const;

        Point& operator+=(const gunit_t& p);
        const Point operator+(const gunit_t& p) const;
        Point& operator+=(const Distance& d);
        const Point operator+(const Distance& d) const;

        Point& operator-=(const Distance& d);
        const Distance operator-(const Point& p) const;
        Point& operator-=(const gunit_t& p);
        const Point operator-(const gunit_t& p) const;

        Point& operator*=(const gunit_t& s);
        const Point operator*(const gunit_t& s) const;
        Point& operator*=(const Scale& s);
        const Point operator*(const Scale& s) const;

        Point& operator/=(const gunit_t& s);
        const Point operator/(const gunit_t& s) const;
        const Scale operator/(const Point& p) const;
        const Anchor operator/(const Size& s) const;
        const Size operator/(const Anchor& a) const;

    };

    /**
     * Represents the difference between two points
     */
    class Distance final {
    private:
        mutable gunit_t _value;
        mutable bool _hasValue;
    public:
        gunit_t x = 0.0f;
        gunit_t y = 0.0f;

        Distance();
        Distance(gunit_t px, gunit_t py);
        operator gunit_t() const;

        bool operator==(const Distance& d) const;
        bool operator!=(const Distance& d) const;        

        const Point operator+(const Point& p);
        const Speed operator/(const Duration& d);
        const Distance operator/(const gunit_t& v);

        Distance& operator+=(const Distance& d);
        const Distance operator+(const Distance& d) const;
        Distance& operator+=(const gunit_t& d);
        const Distance operator+(const gunit_t& d) const;     

        Distance& operator-=(const Distance& d);
        const Distance operator-(const Distance& d) const;
        Distance& operator-=(const gunit_t& d);
        const Distance operator-(const gunit_t& d) const;     

    };    

    /**
     * Anchor point should be a value pair between 0 and 1
     * 0 being bottom or left
     * 1 being top or right
     */
    class Anchor final {
    public:
        gunit_t x = 0.5f;
        gunit_t y = 0.5f;
    
        Anchor();
        Anchor(gunit_t px, gunit_t py);

        bool operator==(const Anchor& a) const;
        bool operator!=(const Anchor& a) const;
        
        Anchor& operator+=(const Anchor& a);
        const Anchor operator+(const Anchor& a) const;
        Anchor& operator+=(const gunit_t& a); 
        const Anchor operator+(const gunit_t& a) const;

        Anchor& operator-=(const Anchor& a);
        const Anchor operator-(const Anchor& a) const;
        Anchor& operator-=(const gunit_t& a);
        const Anchor operator-(const gunit_t& a) const;

        Anchor& operator*=(const gunit_t& s);
        const Anchor operator*(const gunit_t& s) const;
        const Point operator*(const Size& s) const;

        Anchor& operator/=(const gunit_t& s);
        const Anchor operator/(const gunit_t& s) const;
    };    
    
    class Size final {
    public:
        gunit_t width = 0.0f;
        gunit_t height = 0.0f;
        
        Size();
        Size(gunit_t w, gunit_t h);

        bool operator==(const Size& s) const;
        bool operator!=(const Size& s) const;
        
        Size& operator+=(const gunit_t& s);
        const Size operator+(const gunit_t& s) const;
        
        Size& operator-=(const gunit_t& s);
        const Size operator-(const gunit_t& s) const;
        
        Size& operator*=(const gunit_t& s);
        const Size operator*(const gunit_t& s) const;
        const Point operator*(const Anchor& a) const;
        Size& operator*=(const Scale& s);
        const Size operator*(const Scale& s) const;

        const Anchor operator/(const Point& p) const;
        Size& operator/=(const gunit_t& s);
        const Size operator/(const gunit_t& s) const;
        const Scale operator/(const Size& s) const;

        gunit_t area() const;
    };
    
    /**
     * Represents a rectangle
     */
    class Rect final {
    public:        
        Point origin;
        Size size;
        
        Rect();
        Rect(const Point& p, const Size& s);
        Rect(gunit_t x, gunit_t y, gunit_t w, gunit_t h);
        Rect(const Point& bl, const Point& tr);

        bool operator==(const Rect& r) const;
        bool operator!=(const Rect& r) const;     

        Rect& operator/=(const gunit_t& s);
        const Rect operator/(const gunit_t& s) const;

        Rect& operator*=(const gunit_t& s);
        const Rect operator*(const gunit_t& s) const;
        Rect& operator*=(const Scale& s);
        const Rect operator*(const Scale& s) const;

        bool contains(const Point& p) const;
    };
    
    /**
     * Rotation should be in radians
     * both values will be mod(2*PI)
     */
    class Rotation final {
    private:
        void correct();
    public:
        gunit_t x = 0.0f;
        gunit_t y = 0.0f;

        static const gunit_t Pi;
        
        Rotation();
        Rotation(gunit_t px);
        Rotation(gunit_t px, gunit_t py);

        bool operator==(const Rotation& r) const;
        bool operator!=(const Rotation& r) const;        

        Rotation& operator+=(const gunit_t& a);
        const Rotation operator+(const gunit_t& a) const;

        Rotation& operator-=(const gunit_t& a);
        const Rotation operator-(const gunit_t& a) const;
    };
    
    class Scale final {
    public:        
        gunit_t x = 1.0f;
        gunit_t y = 1.0f;

        Scale();
        Scale(gunit_t px);
        Scale(gunit_t px, gunit_t py);

        bool operator==(const Scale& s) const;
        bool operator!=(const Scale& s) const;

        const Rect operator*(const Rect& r) const;
        const Point operator*(const Point& p) const;
        const Size operator*(const Size& s) const;
        const Scale operator*(const Scale& s) const;
        Scale& operator*=(const Scale& s);

        const Scale operator/(const Scale& s) const;
        Scale& operator/=(const Scale& s);       
    };
}

#endif
