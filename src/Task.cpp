#include "Tasks/Task.hpp"

namespace Tasks{
	Task::Task() : _id{INVALID_TASK_ID}{}
	Task::Task(const TaskID& id) : _id{id}{}
	Task::Task(const Task& other) : _id{other._id}{}
	Task::~Task(){}

	const TaskID& Task::id() const{
		return _id;
	}

	const Priority& Task::priority() const{
		// return 
	}

}