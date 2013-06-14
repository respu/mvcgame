
#ifndef mvcgame_EventEmitter_hpp
#define mvcgame_EventEmitter_hpp

#include <map>
#include <functional>

namespace mvcgame {

	class BaseViewController;
	class UpdateEvent;
	class TouchEvent;
	class UpdateTouchEvent;
	class Point;
	class IResponder;

	/**
	 * This class can be used to emit events to a tree of ViewControllers and views.
	 */
	class EventEmitter
	{
	private:
		typedef std::map<IResponder*, TouchEvent> TouchResponders;
		typedef std::function<void(IResponder& resp, const TouchEvent& event)> TouchResponderCallback;
		
		BaseViewController& _root;

		void emitUpdate(const UpdateEvent& event, BaseViewController& controller);
		void emitTouch(const TouchEvent& event, BaseViewController& controller, TouchResponderCallback callback);

        void findTouchResponders(const Point& p, const TouchEvent& event, BaseViewController& controller, TouchResponders& responders);
        TouchResponders findTouchResponders(const TouchEvent& event, BaseViewController& controller);
	public:
		EventEmitter(BaseViewController& root);
		~EventEmitter();

		void emitUpdate(const UpdateEvent& event);
		void emitTouchStart(const TouchEvent& event);
		void emitTouchUpdate(const TouchEvent& event);
		void emitTouchEnd(const TouchEvent& event);
	};

};

#endif