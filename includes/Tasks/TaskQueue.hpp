#ifndef __TASKS_TASK_QUEUE_HPP__
#define __TASKS_TASK_QUEUE_HPP__

#include "common.hpp"
#include "TaskRef.hpp"
#include "Task.hpp"

namespace Tasks{
	class TaskQueue{
		public:
			TaskQueue(TaskRegistry& registry);
			~TaskQueue();

			void pushTask(const Task& task);

		private:
			TaskRegistry& _registry;
			std::set<TaskRef> _tasks;
	};
}

#endif