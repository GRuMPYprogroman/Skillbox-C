#include <iostream>
#include </home/stepan/hw_5.7/include/Car.h>

int main() {
    // Создание объекта класса Car с использованием конструктора по умолчанию
    Car car1;
    std::cout << "Car 1 (default constructor):" << std::endl;
    std::cout << car1 << std::endl;

    // Создание объекта класса Car с использованием пользовательского конструктора
    Car car2("Toyota", 150, 4);
    std::cout << "\nCar 2 (custom constructor):" << std::endl;
    std::cout << car2 << std::endl;

    // Использование конструктора копирования
    Car car3 = car2;
    std::cout << "\nCar 3 (copy constructor):" << std::endl;
    std::cout << car3 << std::endl;

    // Перегрузка оператора присваивания
    car1 = car3;
    std::cout << "\nCar 1 (after assignment from Car 3):" << std::endl;
    std::cout << car1 << std::endl;

    // Использование перегруженного оператора ввода
    Car car4;
    std::cout << "\nВведите данные для Car 4 (в формате: <trademark> <power> <number_of_cylinders>): ";
    std::cin >> car4;
    std::cout << "Car 4 (after input):" << std::endl;
    std::cout << car4 << std::endl;

    // Демонстрация работы статического метода count()
    std::cout << "\nCurrent number of Car objects: " << Car::count() << std::endl;

    // Создание объекта класса Lorry
    Lorry lorry1("Volvo", 300, 6, 10000);
    std::cout << "\nLorry 1 (custom constructor):" << std::endl;
    std::cout << lorry1 << std::endl;

    // Использование конструктора копирования для Lorry
    Lorry lorry2 = lorry1;
    std::cout << "\nLorry 2 (copy constructor):" << std::endl;
    std::cout << lorry2 << std::endl;

    // Перегрузка оператора присваивания для Lorry
    lorry2 = Lorry("MAN", 320, 8, 12000);
    std::cout << "\nLorry 2 (after assignment):" << std::endl;
    std::cout << lorry2 << std::endl;

    // Вывод информации о количестве объектов класса Car и Lorry
    std::cout << "\nCurrent number of Car objects: " << Car::count() << std::endl;

    return 0;
}