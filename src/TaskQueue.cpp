#include "Tasks/TaskQueue.hpp"

namespace Tasks{
	TaskQueue::TaskQueue(TaskRegistry& registry) : _registry{registry}{
		
	}

	TaskQueue::~TaskQueue(){

	}

	void TaskQueue::pushTask(const Task& task){
		_tasks.insert(TaskRef(task.id(), _registry));
	}
}