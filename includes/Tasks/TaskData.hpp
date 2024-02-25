#ifndef __TASKS_TASK_DATA_HPP__
#define __TASKS_TASK_DATA_HPP__

#include "common.hpp"
#include "Operation.hpp"
#include "Priority.hpp"
#include "TaskID.hpp"
#include "TaskName.hpp"
#include "Importance.hpp"
#include "TimeConstraint.hpp"
#include "TaskCycle.hpp"
#include "Concurrency.hpp"

namespace Tasks{
	struct TaskData{
		TaskData();
		~TaskData();

		Operation operation;
		Priority basePriority;
		Importance importance;
		TimeConstraint timeConstraint;
		TaskCycle cycle;
		std::list<Concurrency> concurrencies;
		std::list<Operation> callbacks;

		std::chrono::steady_clock::time_point lastExecution;
		std::chrono::steady_clock::duration lastDuration;
	};
}

#endif