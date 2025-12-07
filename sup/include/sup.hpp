#pragma once
#include <vector>
#include <string>
#include <optional>

class Sup {
	Sup *_parent;
	std::vector<Sup *> _children;

	void addChild(Sup *c);
public:
	virtual std::optional<std::string> name() {return std::nullopt;}
	Sup(Sup *parent = nullptr);
	virtual ~Sup();

	inline Sup *parent() {return _parent;};
	template <typename T>
	auto findChild(std::optional<std::string> name = std::nullopt, bool recursive = true) -> T* {
		for (auto c : _children) {
			auto r = dynamic_cast<T*>(c);
			if(r && (!(name || c->name()) || name == c->name())) return r;
			if(recursive) {
				r = c->findChild<T>(name, recursive);
				if(r) return r;
			}
		}
		return nullptr;
	}
};