#include "Tasks/Dependency.hpp"
#include "Tasks/Task.hpp"

namespace Tasks{
	Dependency::Dependency(const TaskID& id) noexcept : _id{id}{}
	Dependency::Dependency(const Dependency& other) noexcept : _id{other._id}{}
	Dependency::Dependency(const Task& task) noexcept : _id{task.id()}{}
	Dependency::~Dependency() noexcept{}

	Dependency& Dependency::operator=(const Dependency& other) noexcept{
		_id = other._id;
		return *this;
	}

	Dependency& Dependency::operator=(const TaskID& id) noexcept{
		_id = id;
		return *this;
	}
	
	Dependency& Dependency::operator=(const Task& task) noexcept{
		_id = task.id();
		return *this;
	}
	
	const TaskID& Dependency::id() const noexcept{
		return _id;
	}

	TaskID& Dependency::id() noexcept{
		return _id;
	}
	
	bool Dependency::operator==(const Dependency& other) const noexcept{
		return _id == other.id();
	}

	bool Dependency::operator==(const TaskID& id) const noexcept{
		return _id == id;
	}

	bool Dependency::operator==(const Task& task) const noexcept{
		return _id == task.id();
	}
}