#ifndef __TASKS_TASK_HPP__
#define __TASKS_TASK_HPP__

#include "common.hpp"
#include "TaskID.hpp"
#include "Priority.hpp"

namespace Tasks{
	class Task{
		friend class TaskRef;
		public:
			Task(TaskRegistry& registry);
			Task(const TaskID& id, TaskRegistry& registry);
			Task(const Task& other, TaskRegistry& registry);
			~Task();
			
			const TaskID& id() const noexcept;
			const Priority& priority() const noexcept;


		private:
			TaskRegistry* _registry;
			TaskID _id;
	};
}

#endif