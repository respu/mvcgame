//
//  IViewMask.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

namespace mvcgraphics {

	class IViewMask
	{
	public:
		virtual contains(const Point& point) = 0;
	};
}