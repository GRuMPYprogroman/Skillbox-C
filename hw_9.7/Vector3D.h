#pragma once
#include <memory>


class Vector3D
{
    private:
        std::unique_ptr<double[]> coords;
    public:
        Vector3D();

        Vector3D(double x, double y, double z);

        ~Vector3D() = default;

        Vector3D(const Vector3D& other);

        Vector3D& operator=(const Vector3D& other);

        Vector3D(Vector3D&& other) noexcept : coords(std::move(other.coords)){};

        Vector3D& operator=(Vector3D&& other) noexcept; 

        void print() const;

        void normalize();


};

// Функция для работы с std::shared_ptr<Vector3D>
void processVector(std::shared_ptr<Vector3D> vec);
