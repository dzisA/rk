#include <iostream>

class Observer {
public:
    virtual void update(float temp) = 0;
    virtual ~Observer() = default;
};

class TemperatureSensor {
    std::vector<Observer*> obs;
    float current;
public:
    void attach(Observer* o) { obs.push_back(o); }
    void detach(Observer* o) { /* удаление */ }

    void setTemperature(float t) {
        current = t;
        notify();
    }

    void notify() {
        for (auto o : obs)
            o->update(current);
    }
};

class Alice : public Observer {
public:
    void update(float t) override { std::cout << "Alice: current temperature is " << t << "\n";}
};

class Alexa : public Observer {
public:
    void update(float t) override { std::cout << "Alexa: current temperature is " << t << "\n"; }
};

class SmartHome {
    Alice alice;
    Alexa alexa;
    TemperatureSensor sensor;
public:
    SmartHome() {
        sensor.attach(&alice);
        sensor.attach(&alexa);
    }
    void changeTemp(float t) { sensor.setTemperature(t); }
};

int main()
{
    SmartHome home;
    home.changeTemp(22.5);
    return 0;
}
