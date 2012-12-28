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

	class ViewController;
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
		ViewController& _root;

		void emitUpdate(UpdateEvent& event, ViewController& controller);
		void emitTouchStart(TouchEvent& event, ViewController& controller);
        void emitTouchEnd(EndTouchEvent& event, ViewController& controller);
        void findTouchResponders(const Point& p, TouchEvent& event, ViewController& controller);
        void findTouchResponders(TouchEvent& event, ViewController& controller);
	public:
		EventEmitter(ViewController& root);
		~EventEmitter();

		void emitUpdate(UpdateEvent& event);
		void emitTouchStart(TouchEvent& event);
		void emitTouchEnd(EndTouchEvent& event);
	};

};

#endif