#ifndef mvcgame_ObservedValue_hpp
#define mvcgame_ObservedValue_hpp

#include <functional>
#include <algorithm>
#include <vector>

namespace mvcgame {

    template<typename Value>
    class ObservedValue
    {
    public:
        typedef std::function<void(const Value& v)> Callback;
        typedef std::pair<Callback, void*> Observer;
        typedef std::vector<Observer> ObserverList;
    private:
        Value _value;
        ObserverList _observers;
    protected:
        void notifyObservers(const Value& v)
        {
            for(Observer& observer: _observers)
            {
                observer.first(v);
            }
        }
    public:
        ObservedValue()
        {
        }

        ObservedValue(Value v) : _value(v)
        {
        }

        void addObserver(Callback callback, void* reference=nullptr)
        {
            _observers.push_back(Observer(callback, reference));
        }

        void removeObserver(void* reference)
        {
            _observers.erase(std::remove_if(_observers.begin(), _observers.end(), [reference](const Observer& observer){
                return observer.second == reference;
            }));
        }

        operator Value() const
        {
            return _value;
        }

        ObservedValue& operator=(const Value& v)
        {
            if(_value != v)
            {
                notifyObservers(v);
                _value = v;
            }
            return *this;
        }

        ObservedValue& operator+=(const Value& v)
        {
            return operator=(_value+v);
        }

        ObservedValue& operator-=(const Value& v)
        {
            return operator=(_value-v);
        }

        ObservedValue& operator*=(const Value& v)
        {
            return operator=(_value*v);
        }

        ObservedValue& operator/=(const Value& v)
        {
            return operator=(_value/v);
        }

    };
}

#endif