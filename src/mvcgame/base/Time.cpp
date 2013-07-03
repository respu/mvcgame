
#include <mvcgame/base/Time.hpp>
#include <cmath>
#include <chrono>
#include <cstdio>
#include <cassert>

#define FLOATTIME_EQ_ULP 4
#define FIXED_TIME_FACTOR (duration_t)1000000

namespace mvcgame {

#pragma mark - Duration
    
    const Duration Duration::years(duration_part_t y)
    {
        return Duration(FIXED_TIME_FACTOR*365*24*60*60*y);
    }
    
    const Duration Duration::months(duration_part_t m)
    {
        return Duration(FIXED_TIME_FACTOR*12*24*60*60*m);
    }
    
    const Duration Duration::days(duration_part_t d)
    {
        return Duration(FIXED_TIME_FACTOR*24*60*60*d);
    }
    
    const Duration Duration::hours(duration_part_t h)
    {
        return Duration(FIXED_TIME_FACTOR*60*60*h);
    }
    
    const Duration Duration::mins(duration_part_t m)
    {
        return Duration(FIXED_TIME_FACTOR*60*m);
    }
    
    const Duration Duration::secs(float s)
    {
        return Duration(FIXED_TIME_FACTOR*s);
    }
    
    const Duration Duration::usecs(duration_t u)
    {
        return Duration(u);
    }
    
    Duration::Duration() : _value(0.0f)
    {
    }
    
	Duration::Duration(duration_t pt) : _value(pt)
	{
	}
    
    Duration::operator bool() const
    {
        return _value != 0;
    }

    bool Duration::operator==(bool b) const
    {
        return (_value != 0) == b;
    }

    bool Duration::operator!=(bool b) const
    {
        return !((*this) == b);
    }

    bool Duration::operator==(const Duration& i) const
    {
        return _value == i._value;
    }

    bool Duration::operator!=(const Duration& i) const
    {
        return _value != i._value;
    }
    
    bool Duration::operator>(const Duration& i) const
    {
        return _value > i._value;
    }
    
    bool Duration::operator<(const Duration& i) const
    {
        return _value < i._value;
    }
    
    bool Duration::operator>=(const Duration& i) const
    {
        return _value >= i._value;
    }
    
    bool Duration::operator<=(const Duration& i) const
    {
        return _value <= i._value;
    }

    Duration Duration::operator+(const Duration& i) const
    {
        return Duration(_value+i._value);
    }

    Duration& Duration::operator+=(const Duration& i)
    {
    	_value += i._value;
        return *this;
    }

    Duration Duration::operator-(const Duration& i) const
    {
        return Duration(_value+i._value);
    }

    Duration& Duration::operator-=(const Duration& i)
    {
    	_value -= i._value;
        return *this;
    }

	Time Duration::operator+(const Time& s) const
    {
        return Time(_value+(fixedtime_t)s);
    }

    duration_part_t Duration::years() const
    {
        return _value/(365*24*60*60*FIXED_TIME_FACTOR);
    }
    
    duration_part_t Duration::months() const
    {
        return _value/(12*24*60*60*FIXED_TIME_FACTOR);
    }
    
    duration_part_t Duration::days() const
    {
        return _value/(24*60*60*FIXED_TIME_FACTOR);
    }
    
    duration_part_t Duration::hours() const
    {
        return _value/(60*60*FIXED_TIME_FACTOR);
    }
    
    duration_part_t Duration::mins() const
    {
        return _value/(60*FIXED_TIME_FACTOR);
    }
    
    duration_part_t Duration::secs() const
    {
        return _value/(FIXED_TIME_FACTOR);
    }
    
    duration_t Duration::usecs() const
    {
        return _value;
    }
    
    float Duration::fsecs() const
    {
        return (float)_value/(FIXED_TIME_FACTOR);
    }
    
    float Duration::operator/(const Duration& d) const
    {
        if(d._value)
        {
            return (double)_value/(double)d._value;
        }
        else
        {
            return 0;
        }
    }

#pragma mark - Time

    const Time Time::now()
    {
		auto time = std::chrono::system_clock::now();
		auto epoch = time.time_since_epoch();
		auto micros = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
		return Time(micros.count());
    }
    
    Time::Time() : _value(0)
    {
    }

	Time::Time(fixedtime_t pt) : _value(pt)
	{
	}
    
    Time::operator bool() const
    {
        return _value != 0;
    }

    bool Time::operator==(const Time& s) const
    {
        return _value == s._value;
    }

    bool Time::operator!=(const Time& s) const
    {
        return _value != s._value;
    }
    
    bool Time::operator>(const Time& s) const
    {
        return _value > s._value;
    }
    
    bool Time::operator<(const Time& s) const
    {
        return _value < s._value;
    }
    
    bool Time::operator>=(const Time& s) const
    {
        return _value >= s._value;
    }
    
    bool Time::operator<=(const Time& s) const
    {
        return _value <= s._value;
    }

    Time& Time::operator+=(const Duration& i)
    {
    	_value += (fixedtime_t)i;
        return *this;
    }

    Time& Time::operator-=(const Duration& i)
    {
    	_value -= (fixedtime_t)i;
        return *this;
    }

    Duration Time::operator-(const Time& s) const
    {
        return Duration(_value-s._value);
    }
    
    Time Time::operator+(const Duration& i) const
    {
        return Time(_value+i.usecs());
    }

    Time Time::operator-(const Duration& i) const
    {
        return Time(_value-i.usecs());
    }
    
    fixedtime_t Time::year() const
    {
        return 1970 + years();
    }
    
    fixedtime_t Time::month() const
    {
        return months() - years()*12;
    }
    
    fixedtime_t Time::day() const
    {
        return days() - months()*30;
    }
    
    fixedtime_t Time::hour() const
    {
        return hours() - days()*24;
    }
    
    fixedtime_t Time::minu() const
    {
        return mins() - hours()*60;
    }
    
    fixedtime_t Time::sec() const
    {
        return secs() - mins()*60;
    }
    
    fixedtime_t Time::usec() const
    {
        return _value % FIXED_TIME_FACTOR;
    }
    
    fixedtime_t Time::stamp() const
    {
        return _value / FIXED_TIME_FACTOR;
    }
    
    fixedtime_t Time::years() const
    {
        return _value/(365*24*60*60*FIXED_TIME_FACTOR);
    }
    
    fixedtime_t Time::months() const
    {
        return _value/(30*24*60*60*FIXED_TIME_FACTOR);
    }
    
    fixedtime_t Time::days() const
    {
        return _value/(24*60*60*FIXED_TIME_FACTOR);
    }
    
    fixedtime_t Time::hours() const
    {
        return _value/(60*60*FIXED_TIME_FACTOR);
    }
    
    fixedtime_t Time::mins() const
    {
        return _value/(60*FIXED_TIME_FACTOR);
    }
    
    fixedtime_t Time::secs() const
    {
        return _value/(60*FIXED_TIME_FACTOR);
    }
    
    fixedtime_t Time::usecs() const
    {
        return _value;
    }

#pragma mark - Speed
    
    Speed::Speed() : x(0.0f), y(0.0f), d(1)
    {
    }

    Speed::Speed(gunit_t px, gunit_t py) : x(px), y(py), d(1)
    {
    }
    
    Speed::Speed(gunit_t px, gunit_t py, int pd) : x(px), y(py), d(pd)
    {
        
    }
    
    Speed& Speed::operator*=(const Duration& dur)
    {
        gunit_t dt = dur.fsecs();
        x *= dt;
        y *= dt;
        d++;
        return *this;
    }
    
    Speed& Speed::operator/=(const Duration& dur)
    {
        gunit_t dt = dur.fsecs();
        x /= dt;
        y /= dt;
        d--;
        return *this;
    }

    Speed Speed::operator*(const Duration& dur) const
    {
        gunit_t dt = dur.fsecs();
        return Speed(x*dt, y*dt, d-1);
    }

    Speed Speed::operator/(const Duration& dur) const
    {
        gunit_t dt = dur.fsecs();
        return Speed(x/dt, y/dt, d+1);
    }

    Speed& Speed::operator*=(gunit_t v)
    {
        x *= v;
        y *= v;
        return *this;        
    }

    Speed& Speed::operator/=(gunit_t v)
    {
        x /= v;
        y /= v;
        return *this;
    }

    Speed Speed::operator*(gunit_t v) const
    {
        return Speed(x*v, y*v, d);
    }

    Speed Speed::operator/(gunit_t v)const
    {
        return Speed(x/v, y/v, d);
    }


    Speed& Speed::operator+=(const Speed& s)
    {
        assert(d == s.d);        
        x += s.x;
        y += s.y;
        return *this;
    }

    Speed& Speed::operator-=(const Speed& s)
    {
        assert(d == s.d);
        x -= s.x;
        y -= s.y;
        return *this;
    }

    Speed Speed::operator+(const Speed& s) const
    {
        assert(d == s.d);
        return Speed(x+s.x, y+s.y, d);
    }

    Speed Speed::operator-(const Speed& s) const
    {
        assert(d == s.d);        
        return Speed(x-s.x, y-s.y, d);
    }


#pragma mark - stream functions

    std::ostream& operator<<(std::ostream& os, const Time& t)
    {
        os << "Time(";
        os << t.day() << "/" << t.month() << "/" << t.year() << " ";
        os << t.hour() << ":" << t.minu() << ":" << t.sec() << ":" << t.usec();
        os << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Duration& d)
    {
        os << "Duration(";
        int p;
        p = d.years();
        if(p)
        {
            os << " " << p << " years";
        }
        p = d.months();
        if(p)
        {
            os << " " << p << " months";
        }        
        p = d.days();
        if(p)
        {
            os << " " << p << " days";
        }        
        p = d.hours();
        if(p)
        {
            os << " " << p << " hours";
        }        
        p = d.mins();
        if(p)
        {
            os << " " << p << " mins";
        }        
        p = d.secs();
        if(p)
        {
            os << " " << p << " secs";
        }
        p = d.usecs();
        if(p)
        {
            os << " " << p << " usecs";   
        }
        os << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Speed& s)
    {
        os << "Speed(" << s.x << ", " << s.y << ", " << s.d <<")";
        return os;
    }

}