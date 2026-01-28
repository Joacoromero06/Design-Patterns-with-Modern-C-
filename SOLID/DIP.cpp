// Dependency Inversion Principle
#include <iostream>
#include <memory>
struct ILogger{ virtual void log(const std::string& s)= 0; };
struct ISensor{ virtual float readTemperature()=0;};

struct WeatherStation{
    std::shared_ptr<ILogger> logger;
    std::unique_ptr<ISensor> sensor; // would be usefull has vector<InterfacesClasses>
    WeatherStation(std::shared_ptr<ILogger> l, std::unique_ptr<ISensor> s): 
        logger{l}, sensor{std::move(s)} { logger->log("WeatherStation set-up"); }
    void report(){ logger->log("Temperature report: " + std::to_string(sensor->readTemperature())); }
};
struct ConsoleLogger: ILogger{ void log (const std::string& s) override{ std::cout << s << std::endl; }};
struct TermalSensor: ISensor{ float readTemperature() override { return 24.; } };

#include "di.hpp"

int main(){
    return 0;
}
