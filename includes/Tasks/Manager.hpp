#ifndef __TASKS_TASK_MANAGER_HPP__
#define __TASKS_TASK_MANAGER_HPP__

#include "common.hpp"
#include "TaskRegistry.hpp"
#include "TaskQueue.hpp"

namespace Tasks{
	class Manager{
		public:
			Manager();
			~Manager();

			
		private:
			TaskRegistry _registry;
			TaskQueue _queue;
			

	};
}

#endif