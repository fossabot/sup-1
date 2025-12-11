#include <sup.hpp>
using namespace std;

Sup::Sup(Sup *parent)
    : _parent(parent)
{
    if(parent) {
        parent->addChild(this);
    }
}

Sup::~Sup() {
    if(_parent) _parent->remove(this);
    for (auto c : _children) {
        if(c != this) delete c;
    }

    for (auto cb : _managed) {
        cb();
    }
}

void Sup::manage(std::function<void()> freeCb) {
    _managed.push_back(freeCb);
}

void Sup::remove(Sup *c) {
    erase(_children, c);
}

void Sup::addChild(Sup *c) {
    _children.push_back(c);
}
