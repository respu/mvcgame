//
//  EventEmitter.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_EventEmitter_hpp
#define mvcgame_EventEmitter_hpp

#include <vector>

namespace mvcgame {

	class IViewController;
	class IResponder;
	class UpdateEvent;
	class TouchEvent;
	class EndTouchEvent;
	class Point;

	/**
	 * This class can be used to emit events to a tree of ViewControllers and views.
	 */
	class EventEmitter
	{
	private:
		IViewController& _root;

		void emitUpdate(UpdateEvent& event, IViewController& controller);
		void emitTouchStart(TouchEvent& event, IViewController& controller);
        void emitTouchEnd(EndTouchEvent& event, IViewController& controller);
        void findTouchResponders(const Point& p, TouchEvent& event, IViewController& controller);
        void findTouchResponders(TouchEvent& event, IViewController& controller);
	public:
		EventEmitter(IViewController& root);
		~EventEmitter();

		void emitUpdate(UpdateEvent& event);
		void emitTouchStart(TouchEvent& event);
		void emitTouchEnd(EndTouchEvent& event);
	};

};

#endif