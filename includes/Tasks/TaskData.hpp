#ifndef __TASKS_TASK_DATA_HPP__
#define __TASKS_TASK_DATA_HPP__

#include "common.hpp"
#include "Operation.hpp"
#include "Priority.hpp"
#include "TaskID.hpp"
#include "TaskName.hpp"

namespace Tasks{
	struct TaskData{
		TaskData();
		~TaskData();

		Operation operation;
		Priority basePriority;
	};
}

#endif