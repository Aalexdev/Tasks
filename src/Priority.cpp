#include <Tasks/Priority.hpp>

namespace Tasks{
	Priority::Priority(float priority) noexcept : _priority{priority}{}
	Priority::Priority(const Priority& priority) noexcept : _priority{priority._priority}{}
	Priority::~Priority() noexcept {}

	float& Priority::get() noexcept{
		return _priority;
	}

	const float& Priority::get() const noexcept{
		return _priority;
	}

	void Priority::set(const float& priority) noexcept{
		_priority = priority;
	}

	bool Priority::operator>(const Priority& other) const noexcept{
		return _priority > other._priority;
	}

	bool Priority::operator<(const Priority& other) const noexcept{
		return _priority < other._priority;
	}

	bool Priority::operator>=(const Priority& other) const noexcept{
		return _priority >= other._priority;
	}

	bool Priority::operator<=(const Priority& other) const noexcept{
		return _priority <= other._priority;
	}
	
	Priority& Priority::operator+=(const Priority& other) noexcept{
		_priority += other._priority;
		return *this;
	}

	Priority& Priority::operator-=(const Priority& other) noexcept{
		_priority -= other._priority;
		return *this;
	}

	Priority& Priority::operator+=(const float& b) noexcept{
		_priority += b;
		return *this;
	}

	Priority& Priority::operator-=(const float& b) noexcept{
		_priority -= b;
		return *this;
	}

	Priority& Priority::operator*=(const float& factor) noexcept{
		_priority *= factor;
		return *this;
	}

	Priority& Priority::operator/=(const float& factor) noexcept{
		_priority /= factor;
		return *this;
	}
	
	Priority Priority::operator+(const Priority& other) const noexcept{
		return Priority(_priority + other._priority);
	}

	Priority Priority::operator-(const Priority& other) const noexcept{
		return Priority(_priority - other._priority);
	}

	Priority Priority::operator+(const float& a) const noexcept{
		return Priority(_priority - a);
	}

	Priority Priority::operator-(const float& a) const noexcept{
		return Priority(_priority - a);
	}

	Priority Priority::operator*(const float& factor) const noexcept{
		return Priority(_priority * factor);
	}

	Priority Priority::operator/(const float& factor) const noexcept{
		return Priority(_priority / factor);
	}
}