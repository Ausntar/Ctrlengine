#include "CteRole3D.hpp"

namespace cte {
	void CteRole3D::move(std::string direction, int distance, int speed) {
		if (direction == "up") {
			position[0].z += distance * speed;
		}
		else if (direction == "down") {
			position[0].z -= distance * speed;
		}
		else if (direction == "left") {
			position[0].y -= distance * speed;
		}
		else if (direction == "right") {
			position[0].y += distance * speed;
		}
		else if (direction == "forward") {
			position[0].x += distance * speed;
		}
		else if (direction == "backward") {
			position[0].x -= distance * speed;
		}
	}

	void CteRole3D::rotate(std::string direction, int degree, int speed) {
		if (direction == "up") {
			position.back().x += degree * speed;
		}
		else if (direction == "down") {
			position.back().x -= degree * speed;
		}
		else if (direction == "left") {
			position.back().y -= degree * speed;
		}
		else if (direction == "right") {
			position.back().y += degree * speed;
		}
	}

	int CteRole3D::setRoleSettings(
		std::string ID,
		std::string name,
		std::string modelPath,
		std::string texturePath,
		std::string submitter
	) {
		roleSettings.push_back({ ID, name, modelPath, texturePath, submitter });
		return roleSettings.size();
	}

	int CteRole3D::setPosition(
		float x,
		float y,
		float z
	) {
		position.push_back({ x, y, z });
		return position.size();
	}

	int CteRole3D::setPhysics(
		float impactLight,
		float impactSound,
		float weight
	) {
		physics.push_back({ impactLight, impactSound, weight });
		return physics.size();
	}

	int CteRole3D::setCollisionBox(
		float x,
		float y,
		float z
	) {
		collisionBox.push_back({ x, y, z });
		return collisionBox.size();
	}
}
