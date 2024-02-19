#include "Tasks/TaskRef.hpp"
#include "Tasks/Context.hpp"
#include "Tasks/TaskData.hpp"
#include "Tasks/Task.hpp"

namespace Tasks{
	TaskRef::TaskRef(const TaskID& id, Context& context) : _id{id}, _context{&context}{
		auto& data = _context->registry.data(id);
		_priority = data.basePriority;
	}

	TaskRef::TaskRef(const TaskRef& other) : 
		_context{other._context},
		_id{other._id},
		_priority{other._priority}
	{}

	TaskRef::TaskRef(const Task& base) : 
		_context{base._context},
		_id{base.id()},
		_priority{base.priority()}{}

	TaskRef::~TaskRef() noexcept{}

	const Priority& TaskRef::priority() const noexcept{
		return _priority;
	}

	Priority& TaskRef::priority() noexcept{
		return _priority;
	}

	const TaskID& TaskRef::id() const noexcept{
		return _id;
	}

	TaskID& TaskRef::id() noexcept{
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
		_context = other._context;
		return *this;
	}
}

void ::std::swap(Tasks::TaskRef& first, Tasks::TaskRef& second){
	using std::swap;
	swap(first._id, second._id);
	swap(first._priority, second._priority);
	swap(first._context, second._context);
}
