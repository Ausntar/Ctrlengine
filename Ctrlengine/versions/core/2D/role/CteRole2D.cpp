#include "CteRole2D.hpp"
namespace cte{
    void CteRole2D::move(std::string direction, int distance, int speed) {
        if (direction == "up") {
            position.back().x += distance * speed;
        } else if (direction == "down") {
            position.back().x -= distance * speed;
        } else if (direction == "left") {
            position.back().y -= distance * speed;
        } else if (direction == "right") {
            position.back().y += distance * speed;
        }
    }
	int CteRole2D::setRoleSettings(
		std::string ID,
		std::string name,
		std::string modelPath,
		std::string texturePath,
		std::string submitter
	) {
		roleSettings.push_back({ ID,name,modelPath,texturePath,submitter });
		return roleSettings.size();
	}
	int CteRole2D::setPosition(
		float x,
		float y
	) {
        position.push_back({ x,y});
        return position.size();
	}
	int CteRole2D::setPhysics(
		float impactLight,
		float impactSound,
		float weight
	) {
        physics.push_back({ impactLight,impactSound,weight });
        return physics.size();
	}
	int CteRole2D::setCollisionBox(
		float x,
		float y
	) {
		collisionBox.push_back({ x,y});
        return collisionBox.size();
	}
}
