#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "SFML_Include.hpp"
#include "General_Include.hpp"

class Vector2d : public sf::Vector2<double>
{
public:
    Vector2d() : sf::Vector2<double>(0.0, 0.0) { }
    Vector2d(sf::Vector2<double> t) : sf::Vector2<double>(t) { }
    Vector2d(double x, double y) : sf::Vector2<double>(x, y) { }

    double Dot(Vector2d t) { return ((this->x * t.x) + (this->y * t.y)); }
    double Magnitude() { return std::sqrt((this->x * this->x) + (this->y * this->y)); }
    
    Vector2d Normalize() { return Vector2d((*this) / this->Magnitude()); }
    Vector2d Rotate(double theta) 
    { 
        double xRot = (this->x * std::cos(theta)) - (this->y * std::sin(theta));
        double yRot = (this->x * std::sin(theta)) + (this->y * std::cos(theta));
        return Vector2d(xRot, yRot);
    }
};

class Vector3d : public sf::Vector3<double>
{
public:
    Vector3d() : sf::Vector3<double>(0.0, 0.0, 0.0) { }
    Vector3d(sf::Vector3<double> t) : sf::Vector3<double>(t) { }
    Vector3d(double x, double y, double z) : sf::Vector3<double>(x, y, z) { }

    double Dot(Vector3d t) { return ((this->x * t.x) + (this->y * t.y) + (this->z * t.z)); }
    double Magnitude() { return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z)); }

    Vector3d Normalize() { return Vector3d((*this) / this->Magnitude()); }
    Vector3d Cross(Vector3d t) 
    { 
        double x = (this->y * t.z) - (this->z * t.y);
        double y = (this->z * t.x) - (this->x * t.z);
        double z = (this->x * t.y) - (this->y * t.x);

        return Vector3d(x, y, z);
    }
};

#endif