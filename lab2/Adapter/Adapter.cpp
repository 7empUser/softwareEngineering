#include <iostream>

class Road {
public:
  void roadOutput() {
    std::cout << "Дорога что-то делает" << std::endl;
  }
};

class Donkey {
  void Eat() {
    std::cout << "Осел ест" << std::endl;
  }
};

class Transport {
public:
  virtual ~Transport() = default;
  virtual void Move(Road* _road) = 0;
};

class Car : Transport {
public:
  void Move(Road* _road) override {
    std::cout << "Машина едет" << std::endl;
    _road->roadOutput();
  }
};

class Saddle : Transport {
private:
  Donkey* donkey;
public:
  Saddle(Donkey* _donkey) : donkey(_donkey) {}

  void Move(Road* _road) override {
    std::cout << "Осел идет" << std::endl;
    _road->roadOutput();
  }
};

int main()
{
  setlocale(LC_ALL, "Russian");

  Road road;

  Car car;
  car.Move(&road);

  Donkey donkey;
  Saddle saddle(&donkey);
  saddle.Move(&road);
}