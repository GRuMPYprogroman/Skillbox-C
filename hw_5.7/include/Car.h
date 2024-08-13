#pragma once
#include <string>
#include <iostream>
#include <algorithm>
using str = std::string;

class Car
{
private:
    str trademark;
    int power;
    int number_of_cylinders;
    static int objects_counter;
public:
    void set_trademark(str string){ trademark = string;};
    void set_power(int integer){power = integer;};
    void set_number_of_cylinders(int integer){number_of_cylinders = integer;};
    static int count() { return objects_counter;}
    int get_power()const{return power;};
    int get_number_of_cylinders()const{return number_of_cylinders;};
    str get_trademark()const{return trademark;};
    void set_objects_counter(char operation)
    {
        switch(operation)
        {   
            case '+':
                ++objects_counter;
                break;
            case '-':
                --objects_counter;
                break;

        }
    }

    // Перегрузка оператора присваивания

    Car& operator=(const Car& other) 
    {
        if (this == &other) {
            return *this;  // Защита от самоприсваивания
        }

        // Копировать данные от другого объекта
        trademark = other.trademark;
        power = other.power;
        number_of_cylinders = other.number_of_cylinders;

        // Вернуть ссылку на текущий объект
        return *this;
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Car& car_) {
        os << "Марка: " << car_.trademark << "\nМощность: " << car_.power << "\nЧисло цилиндров: " << car_.number_of_cylinders;
        return os;
    }

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& is, Car& car_) {
        is >> car_.trademark >> car_.power >> car_.number_of_cylinders;
        return is;
    }

    Car(/* args */);
    Car(str trademark_,int power_,int number_of_cylinders_);
    virtual ~Car();
    Car(const Car& other);
};

int Car::objects_counter = 0;  // Инициализация счётчика автомобилей

Car::Car(str trademark_, int power_, int number_of_cylinders_)
    : trademark(trademark_), power(power_), number_of_cylinders(number_of_cylinders_) {
    ++objects_counter;
}

Car::Car()
    : trademark("undefined"), power(0), number_of_cylinders(0) {
    ++objects_counter;
}

Car::~Car()
{
    --objects_counter;
    std::cout << "Уничтожен: " << trademark << std::endl;
}

Car::Car(const Car& other)
    : trademark(other.trademark), power(other.power), number_of_cylinders(other.number_of_cylinders) {}

class Lorry : public Car 
{
private:
    int lifting_capacity;
public:
    void set_lifting_capacity(int& integer){lifting_capacity = integer;};
    int get_lifting_capacity()const{return lifting_capacity;};
    Lorry(/* args */);
    Lorry(str trademark_,int power_,int number_of_cylinders_, int lifting_capacity_);
    ~Lorry();
    Lorry(const Lorry& other);
    Lorry& operator=(const Lorry& other) 
    {
        if (this == &other) {
            return *this;  // Защита от самоприсваивания
        }

        // Копировать данные от другого объекта
        Car::operator=(other);
        lifting_capacity = other.lifting_capacity;

        // Вернуть ссылку на текущий объект
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Lorry& lorry_) {
        os << static_cast<const Car&>(lorry_);
        os << "\nГрузоподъемность: " << lorry_.lifting_capacity;
        return os;
    }

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& is, Lorry& lorry_) {
        is >> static_cast<Car&>(lorry_);
        is >> lorry_.lifting_capacity;
        return is;
    }
};

Lorry::Lorry(str trademark_, int power_, int number_of_cylinders_, int lifting_capacity_)
    : Car(trademark_, power_, number_of_cylinders_), lifting_capacity(lifting_capacity_) {}


Lorry::Lorry()
    : Car("undefined", 0, 0), lifting_capacity(0) {}

Lorry::Lorry(const Lorry& other)
    : Car(other), lifting_capacity(other.lifting_capacity) {}

Lorry::~Lorry()
{
    std::cout << "Уничтожен: " << get_trademark() << std::endl;
}
