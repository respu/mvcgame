
#ifndef mvcgame_Time_hpp
#define mvcgame_Time_hpp

#include <mvcgame/base/Geometry.hpp>
#include <cstdint>
#include <iostream>

namespace mvcgame {

    /**
     * timestamp in microseconds without more precision
     */
    typedef uint64_t fixedtime_t;
    typedef int8_t duration_part_t;
    typedef int64_t duration_t;    
    
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
        static const Duration secs(float s);
        static const Duration usecs(duration_t u);
        
        Duration();
    	Duration(duration_t pt);

		operator bool() const;
        bool operator==(bool b) const;
        bool operator!=(bool b) const;

        bool operator==(const Duration& i) const;
        bool operator!=(const Duration& i) const;
        bool operator>(const Duration& i) const;
        bool operator<(const Duration& i) const;
        bool operator>=(const Duration& i) const;
        bool operator<=(const Duration& i) const;
        
        Duration& operator+=(const Duration& i);
        Duration& operator-=(const Duration& i);
        
        Duration operator+(const Duration& i) const;
        Duration operator-(const Duration& i) const;
		Time operator+(const Time& s) const;
        
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
        fixedtime_t minu() const;
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

        Time operator+(const Duration& i) const;
        Time operator-(const Duration& i) const;
        Duration operator-(const Time& s) const;
    };

    class Speed {
    public:
        gunit_t x;
        gunit_t y;
        unsigned d;

        Speed();
        Speed(gunit_t px, gunit_t py);
        Speed(gunit_t px, gunit_t py, int pd);

        bool operator==(const Speed& s) const;
        bool operator!=(const Speed& s) const;        

        Speed& operator*=(const Duration& d);
        Speed& operator/=(const Duration& d);
        Speed operator*(const Duration& d) const;
        Speed operator/(const Duration& d) const;

        Speed& operator*=(gunit_t v);
        Speed& operator/=(gunit_t v);
        Speed operator*(gunit_t v) const;
        Speed operator/(gunit_t v)const;

        Speed& operator+=(const Speed& s);
        Speed& operator-=(const Speed& s);
        Speed operator+(const Speed& s) const;
        Speed operator-(const Speed& s) const;     
    };

    class Accel final : public Speed {
    public:
        Accel();
        Accel(gunit_t px, gunit_t py);
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const Time& t);
    std::ostream& operator<<(std::ostream& os, const Duration& d);
    std::ostream& operator<<(std::ostream& os, const Speed& s);
    std::ostream& operator<<(std::ostream& os, const Accel& a);

}

#endif