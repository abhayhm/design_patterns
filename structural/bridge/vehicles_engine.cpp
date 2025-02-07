#include <iostream>
#include <memory>

class IEngine{
public:
    virtual void start() const = 0;
    virtual ~IEngine() = default;
};

class IVehicle{
public:
    explicit IVehicle(const IEngine &engine): m_engine(engine) {}
    void drive() const{
        m_engine.start();
        driveVehicle();
    }
    virtual ~IVehicle() = default;

protected:
    virtual void driveVehicle() const = 0;

private:
    const IEngine &m_engine;
};

// Asume we have hybrid, ice and ev engine.
class EvEngine: public IEngine{
public:
    virtual void start() const override{
        std::cout<<"Starting EvEngine"<<std::endl;
    }
};

class IceEngine: public IEngine{
public:
    virtual void start() const override{
        std::cout<<"Starting IceEngine"<<std::endl;
    }
};

class HybridEngine: public IEngine{
public:
    virtual void start() const override{
        std::cout<<"Starting HybridEngine"<<std::endl;
    }
};

// Assume we have car and truck
class car: public IVehicle{
public:
    car(const IEngine &engine): IVehicle(engine) {} 
    virtual void driveVehicle() const override{
        std::cout<<"Driving car"<<std::endl;
    }
};

class truck: public IVehicle{
public:
    truck(const IEngine &engine): IVehicle(engine) {} 
    virtual void driveVehicle() const override{
        std::cout<<"Driving truck"<<std::endl;
    }
};

int main(){
    auto ev = EvEngine();
    auto hybrid = HybridEngine();
    auto ice = IceEngine();

    const std::unique_ptr<IVehicle> vehicles[]{
        std::make_unique<car>(ev),
        std::make_unique<truck>(ice),
        std::make_unique<car>(hybrid)
    };

    for(const auto &vehicle : vehicles){
        vehicle->drive();
        std::cout<<std::endl;
    }
    return 0;
}