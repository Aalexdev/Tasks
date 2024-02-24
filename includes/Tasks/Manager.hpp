#ifndef __TASKS_TASK_MANAGER_HPP__
#define __TASKS_TASK_MANAGER_HPP__

#include "common.hpp"
#include "Task.hpp"

namespace Tasks{
	class Manager{
		public:
			Manager();
			~Manager();

			Task create();
			void destroy(const Task& task);

			void start();
			void stop();
			
		private:
			Context* _context;
	};
}

#endif
