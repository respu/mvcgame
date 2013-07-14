
#ifndef mvcgame_PhysicsAtlas_hpp
#define mvcgame_PhysicsAtlas_hpp

#include <memory>
#include <map>
#include <iostream>

namespace mvcgame {

	class PhysicsShape;

	class PhysicsAtlas : public std::enable_shared_from_this<PhysicsAtlas>
	{
	public:
		typedef PhysicsShape Shape;
		typedef std::map<std::string, std::shared_ptr<Shape>> Shapes;
	private:		
		Shapes _shapes;
	public:
		PhysicsAtlas();
		void setShape(const std::string& name, std::shared_ptr<Shape> shape);
		std::shared_ptr<const Shape> getShape(const std::string& name) const;
		std::shared_ptr<Shape> getShape(const std::string& name);
		Shapes& getShapes();
		const Shapes& getShapes() const;
	};

    std::ostream& operator<<(std::ostream& os, const PhysicsAtlas& a);
}

#endif