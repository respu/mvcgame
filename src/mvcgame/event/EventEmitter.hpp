
#ifndef mvcgame_EventEmitter_hpp
#define mvcgame_EventEmitter_hpp

#include <vector>

namespace mvcgame {

	class BaseViewController;
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
		BaseViewController& _root;

		void emitUpdate(UpdateEvent& event, BaseViewController& controller);
		void emitTouchStart(TouchEvent& event, BaseViewController& controller);
        void emitTouchEnd(EndTouchEvent& event, BaseViewController& controller);
        void findTouchResponders(const Point& p, TouchEvent& event, BaseViewController& controller);
        void findTouchResponders(TouchEvent& event, BaseViewController& controller);
	public:
		EventEmitter(BaseViewController& root);
		~EventEmitter();

		void emitUpdate(UpdateEvent& event);
		void emitTouchStart(TouchEvent& event);
		void emitTouchEnd(EndTouchEvent& event);
	};

};

#endif