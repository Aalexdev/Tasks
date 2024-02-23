#include "Tasks/Importance.hpp"

namespace Tasks{
	Importance::Importance(const float& importance) noexcept : _importance{importance}{}
	Importance::Importance(const Importance& other) noexcept : _importance{other._importance}{}
	Importance::~Importance() noexcept{}

	Importance& Importance::operator=(const Importance& other) noexcept{
		_importance = other._importance;
		return *this;
	}

	bool Importance::operator>(const Importance& other) const noexcept{
		return _importance > other._importance;
	}

	bool Importance::operator>=(const Importance& other) const noexcept{
		return _importance >= other._importance;
	}

	bool Importance::operator<(const Importance& other) const noexcept{
		return _importance < other._importance;
	}

	bool Importance::operator<=(const Importance& other) const noexcept{
		return _importance <= other._importance;
	}

	const float Importance::get() const noexcept{
		return _importance;
	}

}