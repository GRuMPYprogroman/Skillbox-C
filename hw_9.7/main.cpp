#include <iostream>
#include "Vector3D.h"

int main() {
    // Демонстрация конструктора перемещения
    Vector3D vec1(1.0, 2.0, 3.0);
    Vector3D vec2(std::move(vec1));
    vec2.print(); // Ожидается Vector3D(1.0, 2.0, 3.0)

    // Демонстрация оператора присваивания перемещением
    Vector3D vec3;
    vec3 = std::move(vec2);
    vec3.print(); // Ожидается Vector3D(1.0, 2.0, 3.0)

    // Работа с std::unique_ptr
    std::unique_ptr<Vector3D> uniqueVec = std::make_unique<Vector3D>(4.0, 5.0, 6.0);
    uniqueVec->print(); // Ожидается Vector3D(4.0, 5.0, 6.0)

    // Работа с std::shared_ptr
    std::shared_ptr<Vector3D> sharedVec = std::make_shared<Vector3D>(7.0, 8.0, 9.0);
    processVector(sharedVec); // Ожидается нормализованный вектор

    return 0;
}