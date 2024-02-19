#ifndef __TASKS_TASK_MANAGER_HPP__
#define __TASKS_TASK_MANAGER_HPP__

#include "common.hpp"
#include "Context.hpp"

namespace Tasks{
	class Manager{
		public:
			Manager();
			~Manager();

			Task create(const std::string& name);
			void destroy(const Task& task);

			void start();
			void stop();
			
		private:
			Context _context;
	};
}

#endif