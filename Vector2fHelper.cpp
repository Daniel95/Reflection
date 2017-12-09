#include "stdafx.h"
#include "Player.h"
#include "InputEvents.h"
#include <iostream>
#include <math.h>

// Normalizes the vector
static Vector2f Normalize(float x, float y) {


	float length = this->Length();

	if (length != 0) {
		vector.X = X / length;
		vector.Y = Y / length;
	}

	return vector;
}

static float Length(float x, float y) {
	return sqrt(x * x + y * y);
}





#pragma once

#include <math.h>

class Vector2 {
public:
	Vector2(void);
	Vector2(float X, float Y);
	~Vector2(void);
	float Length();
	Vector2 Normalize();
	float X, Y;
};




// Vector2.cpp

#include "StdAfx.h"
#include "Vector2.h"

Vector2::Vector2(void) {}

Vector2::Vector2(float X, float Y) {
	this->X = X;
	this->Y = Y;
}

// Returns the length of the vector
float Vector2::Length() {
	return sqrt(X * X + Y * Y);
}

// Normalizes the vector
Vector2 Vector2::Normalize() {
	Vector2 vector;
	float length = this->Length();

	if (length != 0) {
		vector.X = X / length;
		vector.Y = Y / length;
	}

	return vector;
}

Vector2::~Vector2(void) {}