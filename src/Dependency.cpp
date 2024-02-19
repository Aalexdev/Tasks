#include "Tasks/Dependency.hpp"

namespace Tasks{
	Dependency::Dependency(const TaskID& id) noexcept : _id{id}{}
	Dependency::Dependency(const Dependency& other) noexcept : _id{other._id}{}
	Dependency::~Dependency() noexcept{}


	Dependency& Dependency::operator=(const Dependency& other) noexcept{
		_id = other._id;
		return *this;
	}

	Dependency& Dependency::operator=(const TaskID& id) noexcept{
		_id = id;
		return *this;
	}
	
	const TaskID& Dependency::id() const noexcept{
		return _id;
	}

	TaskID& Dependency::id() noexcept{
		return _id;
	}
}