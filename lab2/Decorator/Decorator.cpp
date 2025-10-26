#include <iostream>
#include <string>
#include <cstdint>

class Delivery {
public:
  virtual ~Delivery() = default;
  virtual uint16_t GetCost() = 0;
  virtual std::string GetTime() = 0;
};

class CourierDelivery : public Delivery {
public:
  uint16_t GetCost() override {
    return 10;
  }

  std::string GetTime() override {
    return "10-14 дней";
  }
};

class PostDelivery : public Delivery {
public:
  uint16_t GetCost() override {
    return 7;
  }

  std::string GetTime() override {
    return "14-17 дней";
  }
};

class PickupDelivery : public Delivery {
public:
  uint16_t GetCost() override {
    return 5;
  }

  std::string GetTime() override {
    return "10-14 дней";
  }
};

class ExpressDelivery : public Delivery {
private:
  Delivery* delivery;

  uint16_t ApiCost() {
    return 15;
  }

  std::string ApiTracker() {
    return "Tracker";
  }
public:
  ExpressDelivery(Delivery* _delivery) : delivery(_delivery) {};

  uint16_t GetCost() override {
    return delivery->GetCost() + ApiCost();
  }

  std::string GetTime() override {
    return "1-2 дня";
  }

  std::string Track() {
    return ApiTracker();
  }
};

int main()
{
  setlocale(LC_ALL, "Russian");

  CourierDelivery courier;
  PostDelivery post;
  ExpressDelivery expressCourier(&courier);

  std::cout << "Курьер. Цена: " << courier.GetCost() << ", Время: " << courier.GetTime() << std::endl;
  std::cout << "Экспресс курьер. Цена: " << expressCourier.GetCost() << ", Время: " << expressCourier.GetTime() << std::endl;
}