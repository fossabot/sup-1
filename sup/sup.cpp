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
    for (auto c : _children) {
        delete c;
    }
}

void Sup::addChild(Sup *c) {
    _children.push_back(c);
}
