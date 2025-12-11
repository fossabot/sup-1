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
    if(_parent) erase(_parent->_children, this);
    for (auto c : _children) {
        delete c;
    }

    for (auto cb : _managed) {
        cb();
    }
}

void Sup::manage(std::function<void()> freeCb) {
    _managed.push_back(freeCb);
}

void Sup::addChild(Sup *c) {
    _children.push_back(c);
}
