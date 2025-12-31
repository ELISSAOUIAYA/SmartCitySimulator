#ifndef VEHICLES_H
#define VEHICLES_H

#include "raylib.h"
#include "raymath.h"
#include <vector>

class Vehicle {
public:
    Vector3 position;
    std::vector<Vector3> path;
    int currentPathIndex = 0;
    float speed, scale, rotation = 0.0f;
    Model modelRef;

    Vehicle(std::vector<Vector3> _p, Model _m, float _s, float _sc) : path(_p), modelRef(_m), speed(_s), scale(_sc) {
        if (!path.empty()) position = path[0];
    }

    void Update(bool isPaused) {
        if (isPaused || path.size() < 2 || currentPathIndex >= path.size() - 1) return;
        Vector3 target = path[currentPathIndex + 1];
        Vector3 dir = Vector3Subtract(target, position);
        if (Vector3Length(dir) < speed) {
            position = target;
            currentPathIndex++;
        } else {
            dir = Vector3Normalize(dir);
            position = Vector3Add(position, Vector3Scale(dir, speed));
            rotation = atan2(dir.x, dir.z) * RAD2DEG;
        }
    }

    void Draw() { DrawModelEx(modelRef, position, {0,1,0}, rotation, {scale, scale, scale}, WHITE); }

    bool IsClicked(Ray ray) {
        BoundingBox box = {(Vector3){position.x-2, 0, position.z-2}, (Vector3){position.x+2, 3, position.z+2}};
        return GetRayCollisionBox(ray, box).hit;
    }
};

class Taxi : public Vehicle { public: Taxi(std::vector<Vector3> p, Model m) : Vehicle(p, m, 0.06f, 0.35f) {} };
class Van : public Vehicle { public: Van(std::vector<Vector3> p, Model m) : Vehicle(p, m, 0.05f, 0.38f) {} };
class Truck : public Vehicle { public: Truck(std::vector<Vector3> p, Model m) : Vehicle(p, m, 0.04f, 0.41f) {} };

#endif