#include <iostream>
#include <cmath>
#include "Vector3D.h"


Vector3D::Vector3D() : coords(std::make_unique<double[]>(3))
{
    coords[0] = coords[1] = coords[2] = 0.0;
}

Vector3D::Vector3D(double x, double y, double z) : coords(std::make_unique<double[]>(3))
{
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
}

Vector3D::Vector3D(const Vector3D &other) : coords(std::make_unique<double[]>(3))
{
    coords[0] = other.coords[0];
    coords[1] = other.coords[1];
    coords[2] = other.coords[2];
}

Vector3D &Vector3D::operator=(const Vector3D &other)
{
    if (this == &other)
        return *this; // Защита от самоприсваивания
    coords = std::make_unique<double[]>(3);
    coords[0] = other.coords[0];
    coords[1] = other.coords[1];
    coords[2] = other.coords[2];
    return *this;
}

Vector3D& Vector3D::operator=(Vector3D &&other) noexcept
{
    if (this == &other)
        return *this;
    coords = std::move(other.coords);
    return *this;
}

void Vector3D::print() const
{
    std::cout << "Vector3D(" << coords[0] << ", " << coords[1] << ", " << coords[2] << ")" << std::endl;
}

void Vector3D::normalize(){
    double length = std::sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
    if (length > 0) {
            coords[0] /= length;
            coords[1] /= length;
            coords[2] /= length;
        }
}

// Функция для работы с std::shared_ptr<Vector3D>
void processVector(std::shared_ptr<Vector3D> vec) {
    vec->normalize();
    vec->print();
}