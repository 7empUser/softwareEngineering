#include <iostream>
#include <cstdint>
#include <string>

class DBA {
public:
  void Insert(uint32_t _id, std::string& _data) {
    std::cout << "A: Данные с id = " << _id << " вставлены: " << _data << std::endl;
  }

  std::string Select(uint32_t _id) {
    std::cout << "A: Данные с id = " << _id << " выбраны" << std::endl;
    return "1";
  }

  void Update(uint32_t _id, std::string& _data) {
    std::cout << "A: Данные с id = " << _id << " обновлены на " << _data << std::endl;
  }
};

class DBB {
public:
  void Save(uint32_t _id, float _data) {
    std::cout << "B: Данные с id = " << _id << " сохранены: " << _data << std::endl;
  }

  float Load(uint32_t _id) {
    std::cout << "B: Данные с id = " << _id << " выгружены" << std::endl;
    return 2.0f;
  }
  
  void Modify(uint32_t _id, float _data) {
    std::cout << "B: Данные с id = " << _id << " изменены на " << _data << std::endl;
  }
};

class DBFacade {
private:
  DBA dbA;
  DBB dbB;
public:
  void SaveData(uint32_t _id, std::string& _data, float _data2) {
    std::cout << "Facade: Сохраняем в 2 бд" << std::endl;
    dbA.Insert(_id, _data);
    dbB.Save(_id, _data2);
  }

  void UpdateDBA(uint32_t _id, std::string& _data) {
    std::cout << "Facade: Обновляем в бд A" << std::endl;
    dbA.Update(_id, _data);
  }

  void UpdateDBB(uint32_t _id, float _data2) {
    std::cout << "Facade: Обновляем в бд B" << std::endl;
    dbB.Modify(_id, _data2);
  }

  void SelectData(uint32_t _id) {
    std::cout << "Facade: Достаем данные" << std::endl;
    std::string data1 = dbA.Select(_id);
    float data2 = dbB.Load(_id);
    std::cout << "Id: " << _id << ", data1: " << data1 << ", data2: " << data2 << std::endl;
  }
};

int main()
{
  setlocale(LC_ALL, "Russian");

  DBFacade facade;

  std::string data1 = "123";
  float data2 = 6.0f;

  facade.SaveData(1, data1, data2);
  facade.SelectData(5);
}