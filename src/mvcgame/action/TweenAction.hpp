//
//  TweenAction.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_TweenAction_hpp
#define mvcgame_TweenAction_hpp

#include <mvcgame/Easing.hpp>
#include <mvcgame/action/IAction.hpp>
#include <mvcgame/Geometry.hpp>

#include <functional>

namespace mvcgame {
 
 	/**
 	 * This action will tween a view from the current
 	 * state to a given one
 	 */
	class TweenAction : public IAction
	{
	public:
		typedef std::function<void(IView& view)> Function;
	private:
		Function _animate;		
		Function _complete;
		Easing::Function _easing;
		IView* _start;
		IView* _end;

		float ease(float p, float b, float c);
	public:
		TweenAction(const Function& animate, Function complete=nullptr, Easing::Function easing=nullptr);
        ~TweenAction();

		void setEasing(const Easing::Function& easing);
		void setComplete(const Function& complete);

		void update(IView& view, float proportion);
	};
}

#endif