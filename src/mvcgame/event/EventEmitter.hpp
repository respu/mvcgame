
#ifndef mvcgame_EventEmitter_hpp
#define mvcgame_EventEmitter_hpp

#include <map>
#include <functional>

namespace mvcgame {

	class BaseViewController;
	class BaseView;	
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
		
		BaseViewController& _rootController;
		BaseView& _rootView;

		void emitUpdate(const UpdateEvent& event, BaseView& view);
		void emitUpdate(const UpdateEvent& event, BaseViewController& controller);
		void emitTouch(const TouchEvent& event, TouchResponderCallback callback);

        void findTouchResponders(const Point& p, const TouchEvent& event, BaseViewController& controller, TouchResponders& responders);
        void findTouchResponders(const TouchEvent& event, BaseViewController& controller, TouchResponders& responders);
		void findTouchResponders(const Point& p, const TouchEvent& event, BaseView& view, TouchResponders& responders);        
		void findTouchResponders(const TouchEvent& event, BaseView& view, TouchResponders& responders);
	public:
		EventEmitter(BaseViewController& root, BaseView& rootView);
		~EventEmitter();

		void emitUpdate(const UpdateEvent& event);
		void emitTouchStart(const TouchEvent& event);
		void emitTouchUpdate(const TouchEvent& event);
		void emitTouchEnd(const TouchEvent& event);
	};

};

#endif