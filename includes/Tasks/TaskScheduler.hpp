#ifndef __TASKS_TASK_SCHEDULER_HPP__
#define __TASKS_TASK_SCHEDULER_HPP__

#include "common.hpp"
#include "TaskID.hpp"

namespace Tasks{
	class TaskScheduler{
		public:
			TaskScheduler(Context& context);
			~TaskScheduler();

			void start();
			void stop();

			void push(const TaskID& id);
			void pop(const TaskID& id);

		private:
			Context& _context;
			std::list<TaskID> _cyclicTasks;
			bool _stop;
			std::thread _thread;

			static void threadFnc(TaskScheduler& scheduler);

			bool shouldContinue();
			std::pair<TaskID, std::chrono::steady_clock::time_point> nextTask();
			void requestExecution(const TaskID& id);
	};
}

#endif