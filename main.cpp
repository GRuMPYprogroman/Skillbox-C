#include <iostream>

int fib(int n) //Функция, вычисляющая конкретное число Фиббоначи
{
    int a = 0, b = 1;
    int c;
    for(int i=2;i<=n;i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main()
{
    int fib_number;
    std::cout<<"Здравствуйте! Введите номер числа Фиббоначи: ";
    std::cin >> fib_number;
    std::cout << "Число Фиббоначи равно: " << fib(fib_number);
    return 0;
}