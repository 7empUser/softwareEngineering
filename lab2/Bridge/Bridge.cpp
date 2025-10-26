#include <iostream>
#include <string>

class LoggerSource {
public:
  virtual ~LoggerSource() = default;
  virtual void Log(const std::string& _data) = 0;
};

class ConsoleLogger : public LoggerSource {
public:
  void Log(const std::string& _data) override {
    std::cout << "Вывод в консоль: " << _data << std::endl;
  }
};

class DatabaseLogger : public LoggerSource {
public:
  void Log(const std::string& _data) override {
    std::cout << "Вывод в бд: " << _data << std::endl;
  }
};

class Logger {
protected:
  LoggerSource* loggerSource;
public:
  Logger(LoggerSource* _loggerSource) : loggerSource(_loggerSource) {};

  virtual ~Logger() = default;
  virtual void Log(const std::string& _data) = 0;
};

class PriorityLogger : public Logger {
public:
  using Logger::Logger;

  void Log(const std::string& _data) override {
    loggerSource->Log("[INFO] " + _data);
  }

  void Warn(const std::string& _data) {
    loggerSource->Log("[WARNING] " + _data);
  }

  void Error(const std::string& _data) {
    loggerSource->Log("[ERROR] " + _data);
  }
};

class TimestampLogger : public Logger {
private:
  std::string CurrentTime() {
    return "[1761471999]";
  }
public:
  using Logger::Logger;

  void Log(const std::string& _data) {
    std::string time = CurrentTime();
    loggerSource->Log(time + " " + _data);
  }
};

int main()
{
  setlocale(LC_ALL, "Russian");

  ConsoleLogger consoleLogger;
  DatabaseLogger databaseLogger;

  PriorityLogger priorityConsoleLogger(&consoleLogger);
  TimestampLogger timestampDatabaseLogger(&databaseLogger);

  priorityConsoleLogger.Log("1");
  priorityConsoleLogger.Error("2");
  timestampDatabaseLogger.Log("3");
}