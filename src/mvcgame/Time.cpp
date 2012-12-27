//
//  Time.cpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/Time.hpp>
#include <math.h>
#include <sys/time.h>

#define FLOATTIME_EQ_ULP 4
#define FIXED_TIME_FACTOR 1000000

namespace mvcgame {

#pragma mark - Duration
    
    const Duration Duration::years(duration_t y)
    {
        return Duration(365*24*60*60*FIXED_TIME_FACTOR*y);
    }
    
    const Duration Duration::months(duration_t m)
    {
        return Duration(12*24*60*60*FIXED_TIME_FACTOR*m);
    }
    
    const Duration Duration::days(duration_t d)
    {
        return Duration(24*60*60*FIXED_TIME_FACTOR*d);
    }
    
    const Duration Duration::hours(duration_t h)
    {
        return Duration(60*60*FIXED_TIME_FACTOR*h);
    }
    
    const Duration Duration::mins(duration_t m)
    {
        return Duration(60*FIXED_TIME_FACTOR*m);
    }
    
    const Duration Duration::secs(duration_t s)
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
        return _value == 0;
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

    const Duration Duration::operator+(const Duration& i) const
    {
        return Duration(_value+i._value);
    }

    Duration& Duration::operator+=(const Duration& i)
    {
    	_value += i._value;
        return *this;
    }

    const Duration Duration::operator-(const Duration& i) const
    {
        return Duration(_value+i._value);
    }

    Duration& Duration::operator-=(const Duration& i)
    {
    	_value -= i._value;
        return *this;
    }

	const Time Duration::operator+(const Time& s) const
    {
        return Time(_value+(fixedtime_t)s);
    }

    duration_t Duration::years() const
    {
        return _value/(365*24*60*60*FIXED_TIME_FACTOR);
    }
    
    duration_t Duration::months() const
    {
        return _value/(12*24*60*60*FIXED_TIME_FACTOR);
    }
    
    duration_t Duration::days() const
    {
        return _value/(24*60*60*FIXED_TIME_FACTOR);
    }
    
    duration_t Duration::hours() const
    {
        return _value/(60*60*FIXED_TIME_FACTOR);
    }
    
    duration_t Duration::mins() const
    {
        return _value/(60*FIXED_TIME_FACTOR);
    }
    
    duration_t Duration::secs() const
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
        return _value/d._value;
    }

#pragma mark - Time

    const Time Time::now()
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return Time(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);
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

    const Duration Time::operator-(const Time& s) const
    {
        return Duration(_value-s._value);
    }
    
    const Time Time::operator+(const Duration& i) const
    {
        return Time(_value+i.usecs());
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
    
    fixedtime_t Time::min() const
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
        return _value/(12*24*60*60*FIXED_TIME_FACTOR);
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

    const Speed Speed::operator*(const Duration& dur)
    {
        gunit_t dt = dur.fsecs();
        return Speed(x*dt, y*dt, d-1);
    }

    const Speed Speed::operator/(const Duration& dur)
    {
        gunit_t dt = dur.fsecs();
        return Speed(x/dt, y/dt, d+1);
    }

}