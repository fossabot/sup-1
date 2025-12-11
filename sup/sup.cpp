#include <sup.hpp>
#include <set>
using namespace std;

static set<Sup *> __unsafe_ptrs;

Sup::Sup(Sup *parent)
    : _parent(parent)
{
    if(__unsafe_ptrs.contains(this)) __unsafe_ptrs.erase(this);
    if(parent) {
        parent->addChild(this);
    }
}

Sup::~Sup() {
    if(_parent) _parent->remove(this);
    for (auto c : _children) {
        if(c && c != this && !(__unsafe_ptrs.contains(c))) {
            delete c;
            __unsafe_ptrs.insert(c);
        }
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
    c->_parent = this;
    _children.push_back(c);
}
