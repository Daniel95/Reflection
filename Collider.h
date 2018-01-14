#pragma once

#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include "GameObject.h"

using namespace std;
using namespace sf;

class Collider {
private:
	GameObject& gameObject;
	RectangleShape& body;
public:
	Collider(GameObject &gameObject);
	Collider(GameObject &gameObject, float mass);
	~Collider();

	float Mass = 0;
	vector<function<void(Collider&, Vector2f)>> CollisionEnterEvent;
	vector<function<void(Collider&, Vector2f)>> CollisionEvent;
	vector<function<void(Collider&)>> CollisionExitEvent;

	void DispatchCollisionEnterEvent(Collider&, Vector2f);
	void DispatchCollisionEvent(Collider&, Vector2f);
	void DispatchCollisionExitEvent(Collider&);
	bool CheckCollision(Collider& other, Vector2f &thisPush, Vector2f &otherPush);
	bool CheckCollision(Collider& other);
	void Move(float dx, float dy) { body.move(dx, dy); }
	void Move(Vector2f move) { body.move(move); }
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	GameObject GetGameObject() { return gameObject; }
};

