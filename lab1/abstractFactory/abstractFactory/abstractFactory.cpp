#include <iostream>
#include <string>
#include <memory>

class Button {
public:
  virtual ~Button() = default;
  virtual void render() const = 0;
  virtual void onClick() const = 0;
};

class WindowsButton : public Button {
public:
  void render() const override {
    std::cout << "[Windows] Отрисована кнопка в стиле Windows" << std::endl;
  }

  void onClick() const override {
    std::cout << "[Windows] Выполнено действие при клике на кнопку Windows" << std::endl;
  }
};

class LinuxButton : public Button {
public:
  void render() const override {
    std::cout << "[Linux] Отрисована кнопка в стиле Linux" << std::endl;
  }

  void onClick() const override {
    std::cout << "[Linux] Выполнено действие при клике на кнопку Linux" << std::endl;
  }
};

class GUIFactory {
public:
  virtual ~GUIFactory() = default;

  virtual std::unique_ptr<Button> createButton() const = 0;
};

class WindowsFactory : public GUIFactory {
public:
  std::unique_ptr<Button> createButton() const override {
    return std::make_unique<WindowsButton>();
  }
};

class LinuxFactory : public GUIFactory {
public:
  std::unique_ptr<Button> createButton() const override {
    return std::make_unique<LinuxButton>();
  }
};

class Application {
private:
  std::unique_ptr<GUIFactory> factory;
  std::unique_ptr<Button> button;

public:
  Application(std::unique_ptr<GUIFactory> factory_)
    : factory(std::move(factory_)) {
  }

  void createUI() {
    std::cout << "=== Создание пользовательского интерфейса ===" << std::endl;
    button = factory->createButton();
  }

  void renderUI() const {
    std::cout << std::endl << "=== Отрисовка интерфейса ===" << std::endl;
    button->render();
  }

  void simulateUserInteraction() const {
    std::cout << std::endl << "=== Имитация пользовательского взаимодействия ===" << std::endl;
    button->onClick();
  }
};

std::unique_ptr<GUIFactory> createFactory(const std::string& osType) {
  if (osType == "Windows") {
    std::cout << "Создана фабрика для Windows" << std::endl;
    return std::make_unique<WindowsFactory>();
  }
  else if (osType == "Linux") {
    std::cout << "Создана фабрика для Linux" << std::endl;
    return std::make_unique<LinuxFactory>();
  }
  else {
    throw std::runtime_error("Неизвестный тип ОС: " + osType);
  }
}

int main() {
  setlocale(LC_ALL, "Russian");

  try {
    std::string operatingSystems[] = { "Windows", "Linux" };

    for (const auto& os : operatingSystems) {
      std::cout << std::endl << std::string(50, '=') << std::endl;
      std::cout << "Тестирование для " << os << std::endl;
      std::cout << std::string(50, '=') << std::endl;

      auto factory = createFactory(os);

      Application app(std::move(factory));
      app.createUI();
      app.renderUI();
      app.simulateUserInteraction();
    }

  }
  catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}