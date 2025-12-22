#include <sup.hpp>
#include <set>
#include <memory>
using namespace std;

static set<Sup *> __safe_ptrs;
class Yggdrasil : public Sup {
public:
    virtual optional<string> name() const {return "yggdrasil";}
    static Yggdrasil __;
};
Yggdrasil Yggdrasil::__;

Sup::Sup(Sup *parent)
    : _parent(parent)
{
    if(!_parent) _parent = &Yggdrasil::__;
    __safe_ptrs.insert(this);
    if(parent) {
        parent->addChild(this);
    }
}

Sup::~Sup() {
    __safe_ptrs.extract(this);
    if(_parent) _parent->remove(this);
    for (auto c : _children) {
        if(c && c != this && __safe_ptrs.contains(c)) {
            __safe_ptrs.extract(c);
            delete c;
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
