#include "Tasks/TaskRef.hpp"
#include "Tasks/TaskRegistry.hpp"
#include "Tasks/TaskData.hpp"

namespace Tasks{
	TaskRef::TaskRef(const TaskID& id, TaskRegistry& registry) : _id{id}, _registry{registry}{
		auto& data = _registry.data(id);
		_priority = data.basePriority;
	}

	TaskRef::~TaskRef() noexcept{

	}

	const Priority& TaskRef::priority() const noexcept{
		return _priority;
	}

	void TaskRef::updatePriority(){
		// TODO: change to custom increase
		// For now, a simple 50% increase
		_priority *= 1.5;
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
}