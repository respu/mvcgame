//
//  TweenAction.hpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef hydra_TweenAction_hpp
#define hydra_TweenAction_hpp

#include <mvcgraphics/Easing.hpp>
#include <mvcgraphics/IAction.hpp>
#include <mvcgraphics/Geometry.hpp>

namespace mvcgraphics {
 

 	/**
 	 * This action will tween a view from the current
 	 * state to a given one
 	 */
	class TweenAction : public IAction
	{
	public:
		typedef boost::function<void(IView& view)> Function;
	private:
		Function _complete;
		Function _animate;
		Easing::Function _easing;
		IView* _start;
		IView* _end;

		float ease(float p, float b, float c);
	public:
		TweenAction(const Function& animate, Function complete=NULL, Easing::Function easing=NULL);
        ~TweenAction();

		void setEasing(const Easing::Function& easing);
		void setComplete(const Function& complete);

		void update(IView& view, float proportion);
	};
}

#endif