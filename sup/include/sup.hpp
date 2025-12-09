#pragma once
#include <vector>
#include <string>
#include <optional>
#include <algorithm>

class Sup {
	Sup *_parent;
	std::vector<Sup *> _children;

	void addChild(Sup *c);
public:
	virtual std::optional<std::string> name() {return std::nullopt;}
	Sup(Sup *parent = nullptr);
	virtual ~Sup();

	inline Sup *parent() {return _parent;};

	template <typename T = Sup>
	auto children(bool recursive = false) -> std::vector<T*> {
		std::vector<T*> result;
		for(auto c : _children) {
			auto r = dynamic_cast<T*>(c);
			if(r) result.push_back(r);
			if(recursive) {
				auto ch = c->children<T>(recursive);
				result.insert(result.end(), ch.begin(), ch.end());
			}
		}
		return result;
	}

	template <typename T>
	auto findChild(std::optional<std::string> name = std::nullopt, bool recursive = true) -> T* {
		auto ch = children<T>(recursive);
		auto el = std::find_if(ch.begin(), ch.end(), [name](auto c) {return !name || name == c->name();});
		if(el != ch.end()) return *el;
		return nullptr;
	}

	template <typename T>
	auto findParent(std::optional<std::string> name = std::nullopt) -> T* {
		auto p = _parent;
		while(p) {
			auto found = dynamic_cast<T*>(p);
			if(found && (!name || name == found->name())) return found;
			p = p->_parent;
		}
		return nullptr;
	}
};