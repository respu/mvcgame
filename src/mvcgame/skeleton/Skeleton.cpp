
#include <mvcgame/skeleton/Skeleton.hpp>

namespace mvcgame {
    
    std::ostream& operator<<(std::ostream& os, const Skeleton& s)
    {
        os << "Skeleton(";
        os << ")";
        return os;
    }
}