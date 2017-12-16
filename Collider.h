#pragma once

#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 

using namespace std;
using namespace sf;

class Collider {
private:
	RectangleShape& body;
public:
	Collider(RectangleShape &body);
	Collider(RectangleShape &body, float mass);
	~Collider();

	float Mass;
	vector<function<void(Collider&, float)>> CollisionEnterEvent;
	vector<function<void(Collider&, float)>> CollisionEvent;
	vector<function<void(Collider&, float)>> CollisionExitEvent;

	void Move(float dx, float dy) { body.move(dx, dy); }
	void Move(Vector2f move) { body.move(move); }

	bool CheckCollision(Collider& other);
	bool CheckCollision(Collider& other, Vector2f &thisPush, Vector2f &otherPush);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
};

