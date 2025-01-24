#pragma once
#include <string>
namespace cte {
    struct RoleSettings3D {
        std::string ID;
        std::string name;
        std::string modelPath;
        std::string texturePath;
        std::string submitter;
    };
    struct Position3D {
        float x;
        float y;
        float z;
    };
    struct Physics3D {
        float impactLight;
        float impactSound;

        float weight;
        float height;

        std::string type;
    };
    struct CollisionBox3D {
        float x;
        float y;
        float z;
    };
}