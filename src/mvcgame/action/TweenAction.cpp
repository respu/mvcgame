//
//  TweenAction.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/action/TweenAction.hpp>
#include <mvcgame/view/View.hpp>
#include <functional>

namespace mvcgame {

	TweenAction::TweenAction(const Function& animate, Function complete, Easing::Function easing) :
	_animate(animate), _complete(complete), _easing(easing), _start(nullptr), _end(nullptr)
	{
		if(_easing == nullptr)
		{
			_easing = std::bind(&Easing::linear, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		}
	}
    
    TweenAction::~TweenAction()
    {
    }

	void TweenAction::setEasing(const Easing::Function& easing)
	{
		_easing = easing;
	}

	void TweenAction::setComplete(const Function& complete)
	{
		_complete = complete;
	}

	float TweenAction::ease(float p, float b, float c)
	{
		return _easing(p, b, c);
	}

	void TweenAction::update(View& view, float p)
	{
		if(p == 0 || !_start || !_end)
		{
			// obtain the end view properties
			_start = std::unique_ptr<View>(new View(view));
			_end = std::unique_ptr<View>(new View(view));
			_animate(*_end);
		}

		const Rect& srect = _start->getFrame();
		const Rotation& srot = _start->getRotation();
		const Scale& sscale = _start->getScale();
		const Rect& erect = _end->getFrame();
		const Rotation& erot = _end->getRotation();
		const Scale& escale = _end->getScale();

		Rect rect(
			ease(p, srect.origin.x, erect.origin.x-srect.origin.x),
			ease(p, srect.origin.y, erect.origin.y-srect.origin.y),
			ease(p, srect.size.width, erect.size.width-srect.size.width),
			ease(p, srect.size.height, erect.size.height-srect.size.height)
		);
		Rotation rot(
			ease(p, srot.x, erot.x-srot.x),
			ease(p, srot.y, erot.y-srot.y)
		);
		Scale scale(
			ease(p, sscale.x, escale.x-sscale.x),
			ease(p, sscale.y, escale.y-sscale.y)
		);

#ifdef MVCGAME_DEBUG_TWEENACTION
		std::cout << ">>>>" << std::endl;        
        std::cout << "TweenAction::update " << p << std::endl;
        std::cout << "frame " << rect << std::endl;
        std::cout << "rotation " << rot << std::endl;
        std::cout << "scale " << scale << std::endl;        
        std::cout << "<<<<" << std::endl;
#endif		

		view.setFrame(rect);
		view.setRotation(rot);
		view.setScale(scale);
	}

}