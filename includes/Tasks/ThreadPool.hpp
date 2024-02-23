#ifndef __TASKS_THREAD_POOL_HPP__
#define __TASKS_THREAD_POOL_HPP__

#include "common.hpp"
#include "TaskID.hpp"
#include "Operation.hpp"

namespace Tasks{
	class ThreadPool{
		public:
			ThreadPool(Context& context);
			~ThreadPool();

			void start();
			void stop();
			void waitIdle();

		private:
			Context& _context;
			std::list<std::thread> _threads;
			std::unordered_map<std::thread::id, TaskID> _currentTasks;
			std::mutex _taskMutex;
			std::atomic<bool> _stop;

			static void threadFnc(ThreadPool& pool);

			bool shouldContinue();
			TaskID nextTask();
			void updateCurrentTask(TaskID id);
			void updateTaskData(const TaskID& id, const std::chrono::steady_clock::duration& executionDuration, const std::chrono::steady_clock::time_point& lastExecution);
			bool checkConcurrencies(const std::list<Concurrency>& concurrencies);


	};
}

#endif