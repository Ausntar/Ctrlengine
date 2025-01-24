#pragma once
#include "../../../settings/CteManageSettings.hpp"
#include "roleSettings.hpp"

namespace cte {
	class CteRole3D {
	public:
		std::vector<RoleSettings3D> roleSettings;
		std::vector<Position3D> position;
		std::vector<Physics3D> physics;
		std::vector<CollisionBox3D> collisionBox;

		void move(std::string direction, int distance, int speed);
		void rotate(std::string direction, int degree, int speed);

		int setRoleSettings(
			std::string ID,
			std::string name,
			std::string modelPath,
			std::string texturePath,
			std::string submitter
		);
		int setPosition(
			float x,
			float y,
			float z
		);
		int setPhysics(
			float impactLight,
			float impactSound,
			float weight
		);
		int setCollisionBox(
			float x,
			float y,
			float z
		);
	};
}