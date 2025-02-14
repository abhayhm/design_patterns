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
    std::vector<Shape*> shapes;

public:
    virtual void draw() const override{
        std::cout<<"Drawing composite shapes..."<<std::endl;
        for(const auto &shape: shapes){
            shape->draw();
        }
    }
    void add_shape(Shape& shape){
        shapes.push_back(&shape);
    }
};

class Rectangle: public Shape{
private:
    int length;
    int breadth;
public:
    Rectangle(int l, int b): length(l), breadth(b) {}

    virtual void draw() const override{
        std::cout<<"Drawing rectangle with length "<<length<<" breadth "<<breadth<<std::endl;
    }
};

class Circle: public Shape{
private:
    int radius;
public:
    Circle(int r): radius(r){}
    
    virtual void draw() const override{
        std::cout<<"Drawing circle with radius "<<radius<<std::endl;
    }
};

int main(){
    Circle c(5);
    Rectangle r(10, 15);

    CompositeShape cs;
    cs.add_shape(c);
    cs.add_shape(r);
    cs.draw();

    return 0;
}