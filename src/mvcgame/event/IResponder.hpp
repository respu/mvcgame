
#ifndef mvcgame_IResponder_hpp
#define mvcgame_IResponder_hpp

namespace mvcgame {

    class UpdateEvent;
    class TouchEvent;
    class Point;

    /**
     * Base interface that represents an object that responds to events.
     */
    class IResponder
    {
    public:

        virtual void respondOnUpdate(const UpdateEvent& event)
        {
        }

        /**
         * Called before a touch event to decide if a responder
         * has the event inside. Return true if the touch point is inside
         * the responder.
         */
        virtual bool respondToTouchPoint(const Point& p, const TouchEvent& event)
        {
            return false;
        }

        virtual void respondOnTouchStart(const TouchEvent& event)
        {
        }

        virtual void respondOnTouchUpdate(const TouchEvent& event)
        {
        }        

        virtual void respondOnTouchEnd(const TouchEvent& event)
        {
        }
        
    };

}


#endif