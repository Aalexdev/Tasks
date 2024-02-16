#ifndef __TASKS_TASK_HPP__
#define __TASKS_TASK_HPP__

#include "common.hpp"
#include "TaskID.hpp"
#include "Priority.hpp"

namespace Tasks{
	class Task{
		public:
			Task();
			Task(const TaskID& id);
			Task(const Task& other);
			~Task();

			const TaskID& id() const;
			const Priority& priority() const;

		private:
			TaskID _id;
	};
}

#endif