#pragma once
#include "../../../settings/CteManageSettings.hpp"
#include "roleSettings.hpp"
namespace cte {
	class CteRole2D
	{
	public:
		std::vector<RoleSettings2D> roleSettings;
		std::vector<Position2D> position;
		std::vector<Physics2D> physics;
		std::vector<CollisionBox2D> collisionBox;
		void move(std::string direction, int distance, int speed);

		int setRoleSettings(
			std::string ID,
			std::string name,
			std::string modelPath,
			std::string texturePath,
			std::string submitter
		);
		int setPosition(
			float x,
			float y
		);
		int setPhysics(
			float impactLight,
			float impactSound,
			float weight
		);
		int setCollisionBox(
			float x,
			float y
		);
	};
}

