#include <iostream>
#include <memory>
#include <vector>

class Shape{
public:
    virtual void draw() const = 0;
    ~Shape() = default;
};

class CompositeShape: public Shape{
private:
    std::vector<const Shape&> shapes;

public:
    virtual void draw() const override{
        std::cout<<"Drawing composite shapes..."<<std::endl;
        for(const auto &shape: shapes){
            shape->draw();
        }
    }
    void add_shape(const Shape& shape){
        shapes.push_back(shape);
    }
};

class Triangle: public Shape{

};

class Rectangle: public Shape{
private:
    int length;
    int breadth;
public:

};

class Circle: public Shape{
private:
    int radius;
public:
    Circle(int& r){
        radius = r;
    }
    
    virtual void draw() const override{
        std::cout<<"Drawing circle with radius "<<radius<<std::endl;
    }
};