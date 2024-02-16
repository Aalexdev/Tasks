#include "Tasks/TaskRef.hpp"
#include "Tasks/TaskRegistry.hpp"
#include "Tasks/TaskData.hpp"
#include "Tasks/Task.hpp"

namespace Tasks{
	TaskRef::TaskRef(const TaskID& id, TaskRegistry& registry) : _id{id}, _registry{&registry}{
		auto& data = _registry->data(id);
		_priority = data.basePriority;
	}

	TaskRef::TaskRef(const TaskRef& other) : 
		_registry{other._registry},
		_id{other._id},
		_priority{other._priority}
	{}

	TaskRef::TaskRef(const Task& base) : 
		_registry{base._registry},
		_id{base.id()},
		_priority{base.priority()}{}

	TaskRef::~TaskRef() noexcept{}

	const Priority& TaskRef::priority() const noexcept{
		return _priority;
	}

	const TaskID& TaskRef::id() const noexcept{
		return _id;
	}

	bool TaskRef::operator>(const TaskRef& other) const noexcept{
		return _priority > other._priority;
	}

	bool TaskRef::operator<(const TaskRef& other) const noexcept{
		return _priority < other._priority;
	}

	bool TaskRef::operator>=(const TaskRef& other) const noexcept{
		return _priority >= other._priority;
	}

	bool TaskRef::operator<=(const TaskRef& other) const noexcept{
		return _priority <= other._priority;
	}
	
	bool TaskRef::operator>(const Priority& priority) const noexcept{
		return _priority > priority;
	}

	bool TaskRef::operator<(const Priority& priority) const noexcept{
		return _priority < priority;
	}

	bool TaskRef::operator>=(const Priority& priority) const noexcept{
		return _priority >= priority;
	}

	bool TaskRef::operator<=(const Priority& priority) const noexcept{
		return _priority <= priority;
	}

	TaskRef& TaskRef::operator=(const TaskRef& other){
		_id = other._id;
		_priority = other._priority;
		_registry = other._registry;
		return *this;
	}
}

void ::std::swap(Tasks::TaskRef& first, Tasks::TaskRef& second){
	using std::swap;
	swap(first._id, second._id);
	swap(first._priority, second._priority);
	swap(first._registry, second._registry);
}
