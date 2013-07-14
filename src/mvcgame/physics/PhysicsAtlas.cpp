
#include <mvcgame/physics/PhysicsAtlas.hpp>
#include <mvcgame/physics/PhysicsShape.hpp>

namespace mvcgame {

	PhysicsAtlas::PhysicsAtlas()
	{
	}


	void PhysicsAtlas::setShape(const std::string& name, std::shared_ptr<Shape> shape)
	{
		_shapes[name] = shape;
	}

	std::shared_ptr<const PhysicsShape> PhysicsAtlas::getShape(const std::string& name) const
	{
		return _shapes.at(name);
	}

	std::shared_ptr<PhysicsShape> PhysicsAtlas::getShape(const std::string& name)
	{
		return _shapes[name];
	}

	PhysicsAtlas::Shapes& PhysicsAtlas::getShapes()
	{
		return _shapes;
	}

	const PhysicsAtlas::Shapes& PhysicsAtlas::getShapes() const
	{
		return _shapes;
	}

	std::ostream& operator<<(std::ostream& os, const PhysicsAtlas& a)
	{
		os << "PhysicsAtlas(";
		PhysicsAtlas::Shapes::const_iterator itr;
		for(itr = a.getShapes().begin(); itr!=a.getShapes().end(); ++itr)
		{
			os << itr->first << ": " << *(itr->second) << std::endl;
		}
        os << ")";
        return os;
	}
}
