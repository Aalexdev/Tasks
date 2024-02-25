#include "Tasks/Concurrency.hpp"
#include "Tasks/Task.hpp"

namespace Tasks{
	Concurrency::Concurrency(const Task& task) noexcept : _id{task.id()}{}
	Concurrency::Concurrency(const TaskID& id) noexcept : _id{id}{}
	Concurrency::Concurrency(const Concurrency& other) noexcept : _id{other._id}{}
	Concurrency::~Concurrency() noexcept{}

	Concurrency& Concurrency::operator=(const Concurrency& other) noexcept{
		_id = other._id;
		return *this;
	}

	Concurrency& Concurrency::operator=(const TaskID& id) noexcept{
		_id = id;
		return *this;
	}

	Concurrency& Concurrency::operator=(const Task& task) noexcept{
		_id = task.id();
		return *this;
	}
	
	const TaskID& Concurrency::id() const noexcept{
		return _id;
	}

	TaskID& Concurrency::id() noexcept{
		return _id;
	}

	bool Concurrency::operator==(const Concurrency& other) const noexcept{
		return _id == other._id;
	}
	
	bool Concurrency::operator==(const TaskID& id) const noexcept{
		return _id == id;
	}

	bool Concurrency::operator==(const Task& task) const noexcept{
		return _id == task.id();
	}
}