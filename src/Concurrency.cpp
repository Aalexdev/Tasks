#include "Tasks/Concurrency.hpp"

namespace Tasks{
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
	
	const TaskID& Concurrency::id() const noexcept{
		return _id;
	}

	TaskID& Concurrency::id() noexcept{
		return _id;
	}

	bool Concurrency::operator==(const Concurrency& other) const noexcept{
		return _id == other._id;
	}
}