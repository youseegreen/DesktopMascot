#pragma once
#include <iostream>
using namespace std;

struct Vector2f {
	float x;
	float y;

	Vector2f() { x = 0; y = 0; }
	Vector2f(const float tx, const float ty) { x = tx; y = ty; }
	~Vector2f() { }
	Vector2f(const Vector2f &other) { x = other.x; y = other.y; }
	Vector2f &operator=(const Vector2f &other) { 
		// ���g�̑���`�F�b�N
		if (this != &other) {
			x = other.x; y = other.y;
		}
		return *this;
	}

	//�����𐳋K��
	Vector2f &NormalizeSelf() {
		float s = sqrtf(x * x + y * y);
		x /= s;		y /= s;
		return *this;
	}
	//Vector2f��Ԃ�
	Vector2f Normalize() const {
		float s = sqrtf(x * x + y * y);
		return Vector2f(x / s, y / s);
	}

	// + - * 
	Vector2f operator+(const Vector2f &other)const {
		return Vector2f(x + other.x, y + other.y);
	}
	Vector2f operator-(const Vector2f &other)const {
		return Vector2f(x - other.x, y - other.y);
	}
	//����
	float operator*(const Vector2f &other)const {
		return (x * other.x + y * other.y);
	}

	//�X�J���[�Ƃ�+ - *
	Vector2f operator+(const float scalar)const {
		return Vector2f(x + scalar, y + scalar);
	}
	Vector2f operator-(const float scalar)const {
		return Vector2f(x - scalar, y - scalar);
	}
	Vector2f operator*(const float scalar)const {
		return Vector2f(x * scalar, y * scalar);
	}
	friend Vector2f operator+(const float scalar, const Vector2f vec) {
		return Vector2f(vec.x + scalar, vec.y + scalar);
	}
	friend Vector2f operator-(const float scalar, const Vector2f vec) {
		return Vector2f(vec.x - scalar, vec.y - scalar);
	}
	friend Vector2f operator*(const float scalar, const Vector2f vec) {
		return Vector2f(vec.x * scalar, vec.y * scalar);
	}

	//+= -=      *=�̓X�J���[�Ȃ̂Ł~
	Vector2f &operator+=(const Vector2f &other) {
		x += other.x; y += other.y;
		return *this;
	}
	Vector2f &operator-=(const Vector2f &other) {
		x -= other.x; y -= other.y;
		return *this;
	}
	Vector2f &operator+=(const float scalar) {
		x += scalar; y += scalar;
		return *this;
	}
	Vector2f &operator-=(const float scalar) {
		x -= scalar; y -= scalar;
		return *this;
	}

	//�P��
	Vector2f operator-()const {
		return Vector2f(-x, -y);
	}

	//��r���Z�q	�X�J���[��Vector2f
	bool operator==(const float scalar) const{
		if ((x == scalar) && (y == scalar))return true;
		return false;
	}
	bool operator==(const Vector2f other) const {
		if ((x == other.x) && (y == other.y))return true;
		return false;
	}
	bool operator!=(const float scalar) const {
		if ((x != scalar) && (y != scalar))return true;
		return false;
	}
	bool operator!=(const Vector2f other) const {
		if ((x != other.x) && (y != other.y))return true;
		return false;
	}

	void Disp(const char *name)const {
		cout << name << endl;
		cout << "(x,y) = ( " << x << " , " << y << " )" << endl;
	}
};