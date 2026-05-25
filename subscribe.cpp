#include <iostream>

class Observer {
public:
    virtual void update(float temp) = 0;
    virtual ~Observer() = default;
};

class TemperatureSensor {
    std::vector<Observer*> obs;
    float current {0.0};
public:
    void attach(Observer* o) { obs.push_back(o); }
    void detach(Observer* o) { obs.erase(std::remove(obs.begin(),obs.end(),o),obs.end()); }

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
    void detachAlexa() {sensor.detach(&alexa);}
    void detachAlice() {sensor.detach(&alice);}
    void attachAlexa() {sensor.attach(&alexa); }
    void attachAlca() {sensor.attach(&alice); }
};

int main()
{
    SmartHome home;
    home.changeTemp(22.5);
    home.detachAlexa();
    home.changeTemp(26.6);
    home.attachAlexa();
    home.changeTemp(43.3);
    return 0;
}
