#include "Tasks/Task.hpp"
#include "Tasks/TaskRegistry.hpp"

namespace Tasks{
	Task::Task(TaskRegistry& registry) : _id{INVALID_TASK_ID}, _registry{&registry}{}
	Task::Task(const TaskID& id, TaskRegistry& registry) : _id{id}, _registry{&registry}{}
	Task::Task(const Task& other, TaskRegistry& registry) : _id{other._id}, _registry{&registry}{}
	Task::~Task(){}

	const TaskID& Task::id() const noexcept{
		return _id;
	}

	const Priority& Task::priority() const noexcept{
		return _registry->data(_id).basePriority;
	}
}