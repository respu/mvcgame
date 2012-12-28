//
//  IViewMask.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_IViewMask_hpp
#define mvcgame_IViewMask_hpp

namespace mvcgame {

	class IViewMask
	{
	public:
		virtual contains(const Point& point) = 0;
	};
}

#endif