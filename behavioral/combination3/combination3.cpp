/*
 * This program contains combination of design patterns, null object, iterator and memento 
 */

#include <iostream>
#include <vector>

class Canvas;
class ReplayCanvas;

class CanvasMemento {
    friend class Canvas;
    friend class ReplayCanvas;
    const std::vector<std::string> shapes;
public:
    CanvasMemento(std::vector<std::string> shapes) : shapes(shapes) {};
};

class CanvasIterator {
public:
    virtual ~CanvasIterator() {};
    virtual CanvasMemento *next() = 0;
    virtual bool isFinished() = 0;
};

class ForwardsIterator: public CanvasIterator {
    int currentPosition;
    std::vector<CanvasMemento*> &history;
public:
    ForwardsIterator(std::vector<CanvasMemento*> &history) : currentPosition(0), history(history) {};
    CanvasMemento *next() override {
        CanvasMemento *current = history.at(currentPosition);
        currentPosition += 1;
        return current;
    }
    bool isFinished() override {
        return currentPosition >= history.size();
    }
};

class History {
public:
    virtual void addState(CanvasMemento *newState) = 0;
    virtual CanvasMemento *undo() = 0;
};

class CanvasHistory : public History {
    std::vector<CanvasMemento*> oldStates;
public:
    ~CanvasHistory() {
        for (auto p : oldStates) {
            delete p;
        }
        oldStates.clear();
    }
    void addState(CanvasMemento *newState) override {
        oldStates.push_back(newState);
    }
    CanvasMemento *undo() override {
        oldStates.pop_back();
        CanvasMemento *previousState = oldStates.back();
        return previousState;
    }
    ForwardsIterator *getForwardsIterator() {
        return new ForwardsIterator(oldStates);
    }
};

class NullHistory : public History {
private:
    CanvasMemento *state;
public:
    NullHistory() {state = new CanvasMemento({}); };
    virtual void addState(CanvasMemento *newState) override {
        state = newState;
    };
    virtual CanvasMemento *undo() override {
        return state;
    };
};

class Canvas {
    std::vector<std::string> shapes;
    History *history;
public:
    Canvas(History *history) : history(history) {};
    void addShape(const std::string & newShape) {
        shapes.push_back(newShape);
        history->addState(new CanvasMemento(shapes));
    };
    void undo() {
        CanvasMemento *previousState = history->undo();
        shapes = previousState->shapes;
    }
    void clearAll() {
        shapes.clear();
        history->addState(new CanvasMemento(shapes));
    };
    std::vector<std::string> getShapes() { return shapes; };
};

class ReplayCanvas {
    std::vector<std::string> shapes;
    ForwardsIterator *historyIterator;
public:
    ReplayCanvas(CanvasHistory *history) { historyIterator = history->getForwardsIterator(); };
    void replay() {
        while (!historyIterator->isFinished()) {
            CanvasMemento *nextState = historyIterator->next();
            shapes = nextState->shapes;
            std::cout << "The shapes are now: ";
            for (auto shape : shapes) {
                std::cout << shape << ", ";
            }
            std::cout << "\n";
        }
    }
};

int main(int argc, const char * argv[]) {
    NullHistory *history = new NullHistory;
    Canvas *canvas = new Canvas(history);
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    
    /*
    std::cout << "Watching replay:\n";
    
    ReplayCanvas *replayCanvas = new ReplayCanvas(history);
    replayCanvas->replay();
    */
   std::cout << "Null canvas current shapes:\n";
   for(auto shape: canvas->getShapes()){
    std::cout<<shape<<", ";
   }

   std::cout << "\n";
    
    std::cout << "Trying to undo...\n";
    canvas->undo();
    canvas->undo();
    canvas->undo();
    
    std::cout << "Null canvas shapes after undo:\n";
    
    for (auto shape : canvas->getShapes()) {
        std::cout << shape << ", ";
    };
    
    std::cout << "\n";

    return 0;
}
