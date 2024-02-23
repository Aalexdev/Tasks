#include "Tasks/TimeConstraint.hpp"

namespace Tasks{
	TimeConstraint::TimeConstraint(const Duration& duration) noexcept : _duration{duration} {}
	TimeConstraint::TimeConstraint(const TimeConstraint& other) noexcept : _duration{other._duration}{}
	TimeConstraint::~TimeConstraint() noexcept {}
	
	TimeConstraint& TimeConstraint::operator=(const TimeConstraint& other) noexcept{
		_duration = other._duration;
		return *this;
	}

	TimeConstraint& TimeConstraint::operator=(const Duration& duration) noexcept{
		_duration = duration;
		return *this;
	}

	const TimeConstraint::Duration& TimeConstraint::get() const noexcept{
		return _duration;
	}

	TimeConstraint::Duration& TimeConstraint::get() noexcept{
		return _duration;
	}
	
	bool TimeConstraint::hasConstraints() const noexcept{
		return _duration != NONE;
	}
}