#include <pybind11/pybind11.h>
#include <iostream>
#include <cmath>
#include "Vector3D.h"

namespace py = pybind11;

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

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    Vector3D vector;
    for (int i = 0; i < 3; ++i)
    {
        vector.coords[i] = this->coords[i] + other.coords[i];
    }
    return vector;
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    Vector3D vector;
    for (int i = 0; i < 3; ++i)
    {
        vector.coords[i] = this->coords[i] - other.coords[i];
    }
    return vector;
}

double Vector3D::operator*(const Vector3D& other) const
{
    double sum = 0.0;
    for (int i = 0; i < 3; ++i)
    {
        sum += this->coords[i] * other.coords[i];
    }
    return sum;
}

double Vector3D::length()
{
    double len_sq = std::pow(this->coords[0],2) + std::pow(this->coords[1],2) + std::pow(this->coords[2],2);
    return std::sqrt(len_sq);
}

std::tuple<double, double, double> Vector3D::get_coords() const {
    return std::make_tuple(coords[0], coords[1], coords[2]);
}


PYBIND11_MODULE(SmartPtr_hw,m)
{
    py::class_<Vector3D>(m,"Vector3D")
        .def(py::init<>())
        .def(py::init<double,double,double>())
        .def("length",&Vector3D::length)
        .def("print", &Vector3D::print)
        .def("dot_product", &Vector3D::operator*)
        .def("plus_product", &Vector3D::operator+)
        .def("minus_product", &Vector3D::operator-)
        .def("normalize", &Vector3D::normalize)
        .def("get_coords", &Vector3D::get_coords)
        ;
}