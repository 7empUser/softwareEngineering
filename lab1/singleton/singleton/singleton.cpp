#include <iostream>
#include <string>
#include <unordered_map>

class ConfigManager {
private:
  ConfigManager() {
    config["theme"] = "dark";
    config["language"] = "russian";
    config["volume"] = "75";
    config["resolution"] = "1920x1080";
    config["notifications"] = "enabled";
    std::cout << "ConfigManager инициализирован с настройками по умолчанию" << std::endl;
  }

  ConfigManager(const ConfigManager&) = delete;
  ConfigManager& operator=(const ConfigManager&) = delete;

  std::unordered_map<std::string, std::string> config;

public:
  static ConfigManager& getInstance() {
    static ConfigManager instance;
    return instance;
  }

  void setConfig(const std::string& key_, const std::string& value_) {
    config[key_] = value_;
    std::cout << "Настройка изменена: " << key_ << " = " << value_ << std::endl;
  }

  std::string getConfig(const std::string& key_) const {
    auto it = config.find(key_);
    if (it != config.end()) {
      return it->second;
    }
    return "Не найдено";
  }

  void printAllConfigs() const {
    std::cout << "=== Текущие настройки приложения ===" << std::endl;
    for (const auto& [key, value] : config) {
      std::cout << "  " << key << ": " << value << std::endl;
    }
    std::cout << "=====================================" << std::endl;
  }

  void resetToDefaults() {
    config.clear();
    config["theme"] = "dark";
    config["language"] = "russian";
    config["volume"] = "75";
    config["resolution"] = "1920x1080";
    config["notifications"] = "enabled";
    std::cout << "Настройки сброшены к значениям по умолчанию" << std::endl;
  }
};

int main() {
  setlocale(LC_ALL, "Russian");

  std::cout << "=========================================" << std::endl;
  std::cout << "ДЕМОНСТРАЦИЯ CONFIGMANAGER SINGLETON" << std::endl;
  std::cout << "=========================================" << std::endl << std::endl;

  std::cout << "1. Получение экземпляра ConfigManager:" << std::endl;
  ConfigManager& config = ConfigManager::getInstance();

  std::cout << std::endl << "2. Начальные настройки:" << std::endl;
  config.printAllConfigs();

  std::cout << "3. Изменение настроек:" << std::endl;
  config.setConfig("theme", "light");
  config.setConfig("language", "english");
  config.setConfig("volume", "90");
  config.setConfig("username", "JohnDoe");

  std::cout << std::endl << "4. Обновленные настройки:" << std::endl;
  config.printAllConfigs();

  std::cout << std::endl << "6. Проверка, что это singleton:" << std::endl;

  ConfigManager& anotherConfig = ConfigManager::getInstance();

  config.setConfig("resolution", "3840x2160");

  std::cout << "   Проверка изменения через другую ссылку: "
    << anotherConfig.getConfig("resolution") << std::endl;

  std::cout << "   Это один и тот же объект? "
    << (&config == &anotherConfig) << std::endl;

  std::cout << std::endl << "7. Сброс настроек:" << std::endl;
  config.resetToDefaults();
  config.printAllConfigs();

  std::cout << "8. Работа в разных областях видимости:" << std::endl;
  {
    ConfigManager& configInScope = ConfigManager::getInstance();
    configInScope.setConfig("autosave", "true");
    std::cout << "   Внутри scope: autosave = " << configInScope.getConfig("autosave") << std::endl;
  }

  std::cout << "   После выхода из scope: autosave = " << config.getConfig("autosave") << std::endl;

  std::cout << std::endl << "=========================================" << std::endl;
  std::cout << "Демонстрация завершена успешно!" << std::endl;
  std::cout << "=========================================" << std::endl;

  return 0;
}