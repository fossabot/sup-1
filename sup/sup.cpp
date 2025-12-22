#include <sup.hpp>
#include <set>
using namespace std;

static set<Sup *> __safe_ptrs;

class _PtrCleanup {
    ~_PtrCleanup() {
        for (auto p : __safe_ptrs) {
            __safe_ptrs.erase(p);
            if(p) delete p;
        }
    }
    static _PtrCleanup _;
};

_PtrCleanup _PtrCleanup::_;

Sup::Sup(Sup *parent)
    : _parent(parent)
{
    __safe_ptrs.insert(this);
    if(parent) {
        parent->addChild(this);
    }
}

Sup::~Sup() {
    __safe_ptrs.erase(this);
    if(_parent) _parent->remove(this);
    for (auto c : _children) {
        if(c && c != this && __safe_ptrs.contains(c)) {
            delete c;
            __safe_ptrs.erase(c);
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
