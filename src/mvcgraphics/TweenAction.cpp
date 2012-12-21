//
//  TweenAction.cpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgraphics/TweenAction.hpp>
#include <mvcgraphics/View.hpp>
#include <functional>

namespace mvcgraphics {

	TweenAction::TweenAction(const Function& animate, Function complete, Easing::Function easing) :
	_animate(animate), _complete(complete), _easing(easing), _start(NULL), _end(NULL)
	{
		if(_easing == NULL)
		{
			_easing = std::bind(&Easing::linear, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		}
	}
    
    TweenAction::~TweenAction()
    {
        if(_start != NULL)
        {
            delete _start;
        }
        if(_end != NULL)
        {
            delete _end;
        }
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

	void TweenAction::update(IView& view, float p)
	{
		if(p == 0)
		{
			// obtain the end view properties
			_start = new View(view);
			_end = new View(view);
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

		view.setFrame(rect);
		view.setRotation(rot);
		view.setScale(scale);
	}

}