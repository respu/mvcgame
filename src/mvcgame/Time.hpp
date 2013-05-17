//
//  Time.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_Time_hpp
#define mvcgame_Time_hpp

#include <mvcgame/Geometry.hpp>
#include <stdint.h>

namespace mvcgame {

    /**
     * timestamp in microseconds without more precision
     */
    typedef uint64_t fixedtime_t;
    typedef int16_t duration_part_t;
    typedef int8_t duration_t;    
    
    class Time;
    class Accel;

    class Duration final {
    private:
    	duration_t _value;
    public:
        
        static const Duration years(duration_part_t m);
        static const Duration months(duration_part_t m);
        static const Duration days(duration_part_t d);
        static const Duration hours(duration_part_t h);
        static const Duration mins(duration_part_t m);
        static const Duration secs(duration_part_t s);
        static const Duration usecs(duration_t u);
        static const Duration fsecs(float s);
        
        Duration();
    	Duration(duration_t pt);
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
        
        duration_part_t years() const;
        duration_part_t months() const;
        duration_part_t days() const;
        duration_part_t hours() const;
        duration_part_t mins() const;
        duration_part_t secs() const;
        duration_t usecs() const;
        float fsecs() const;
    };

    class Time final {
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

    class Speed final {
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