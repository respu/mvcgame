//
//  Time.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_Time_hpp
#define hydra_Time_hpp

#include <mvcgraphics/Geometry.hpp>

namespace mvcgraphics {

    /**
     * timestamp in microseconds without more precision
     */
    typedef uint64_t fixedtime_t;
    
    struct Time;
    struct Accel;

    struct Duration {
    private:
    	fixedtime_t _value;
    public:
        
        static const Duration years(fixedtime_t m);
        static const Duration months(fixedtime_t m);
        static const Duration days(fixedtime_t d);
        static const Duration hours(fixedtime_t h);
        static const Duration mins(fixedtime_t m);
        static const Duration secs(fixedtime_t s);
        static const Duration usecs(fixedtime_t u);
        static const Duration fsecs(float s);
        
        Duration();
    	explicit Duration(fixedtime_t pt);
		operator bool() const;

        bool operator==(const Duration& i) const;
        bool operator!=(const Duration& i) const;
        bool operator>(const Duration& i) const;
        bool operator<(const Duration& i) const;
        bool operator>=(const Duration& i) const;
        bool operator<=(const Duration& i) const;
        
        Duration& operator+=(const Duration& i);
        Duration& operator-=(const Duration& i);
        
        const Duration operator+(const Duration& i) const;
        const Duration operator-(const Duration& i) const;
		const Time operator+(const Time& s) const;
        
        float operator/(const Duration& d) const;
        
        fixedtime_t years() const;
        fixedtime_t months() const;
        fixedtime_t days() const;
        fixedtime_t hours() const;
        fixedtime_t mins() const;
        fixedtime_t secs() const;
        fixedtime_t usecs() const;
        float fsecs() const;
    };

    struct Time {
    private:
    	fixedtime_t _value;
    public:

    	static const Time now();
        
        Time();
    	Time(fixedtime_t pt);
		operator bool() const;

        fixedtime_t year() const;
        fixedtime_t month() const;
        fixedtime_t day() const;
        fixedtime_t hour() const;
        fixedtime_t min() const;
        fixedtime_t sec() const;
        fixedtime_t usec() const;
        fixedtime_t stamp() const;
        
        fixedtime_t years() const;
        fixedtime_t months() const;
        fixedtime_t days() const;
        fixedtime_t hours() const;
        fixedtime_t mins() const;
        fixedtime_t secs() const;
        fixedtime_t usecs() const;
        
        bool operator==(const Time& s) const;
        bool operator!=(const Time& s) const;
        bool operator>(const Time& s) const;
        bool operator<(const Time& s) const;
        bool operator>=(const Time& s) const;
        bool operator<=(const Time& s) const;
        
        Time& operator+=(const Duration& i);
        Time& operator-=(const Duration& i);

        const Time operator+(const Duration& i) const;
        const Duration operator-(const Time& s) const;
    };

    struct Speed {
    public:
        gunit_t x;
        gunit_t y;
        unsigned d;

        Speed();
        Speed(gunit_t px, gunit_t py);
        Speed(gunit_t px, gunit_t py, int pd);

        Speed& operator*=(const Duration& d);
        Speed& operator/=(const Duration& d);
        const Speed operator*(const Duration& d);
        const Speed operator/(const Duration& d);
    };

}

#endif