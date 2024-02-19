#ifndef __TASKS_SYNC_MANAGER_HPP__
#define __TASKS_SYNC_MANAGER_HPP__

#include "common.hpp"

namespace Tasks{
	class SyncManager{
		public:
			SyncManager(Context& context);
			~SyncManager();

			std::shared_mutex& registryAccess();
			std::shared_mutex& threadPoolAccess();
			std::mutex& queueAccess();
			std::mutex& schedulerAccess();

			std::shared_lock<std::shared_mutex> registryRead();
			std::shared_lock<std::shared_mutex> threadPoolRead();

			std::unique_lock<std::shared_mutex> registryWrite();
			std::unique_lock<std::shared_mutex> threadPoolWrite();

			std::lock_guard<std::mutex> queueLock();
			std::lock_guard<std::mutex> schedulerLock();

			std::condition_variable& queueUpdated();

		private:
			Context& _context;
			std::shared_mutex _registryAccess;
			std::shared_mutex _threadPoolAccess;
			std::mutex _queueAccess;
			std::mutex _schedulerAccess;
			std::condition_variable _queueUpdated;
	};
}

#endif