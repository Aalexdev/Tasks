#include "Tasks/SyncManager.hpp"

namespace Tasks{
	SyncManager::SyncManager(Context& context) : _context{context}{}
	SyncManager::~SyncManager(){}

	std::shared_mutex& SyncManager::registryAccess(){
		return _registryAccess;
	}

	std::shared_mutex& SyncManager::threadPoolAccess(){
		return _threadPoolAccess;
	}

	std::mutex& SyncManager::queueAccess(){
		return _queueAccess;
	}

	std::mutex& SyncManager::schedulerAccess(){
		return _schedulerAccess;
	}

	std::shared_lock<std::shared_mutex> SyncManager::registryRead(){
		return std::shared_lock<std::shared_mutex>(_registryAccess);
	}

	std::shared_lock<std::shared_mutex> SyncManager::threadPoolRead(){
		return std::shared_lock<std::shared_mutex>(_threadPoolAccess);
	}

	std::unique_lock<std::shared_mutex> SyncManager::registryWrite(){
		return std::unique_lock<std::shared_mutex>(_registryAccess);
	}

	std::unique_lock<std::shared_mutex> SyncManager::threadPoolWrite(){
		return std::unique_lock<std::shared_mutex>(_threadPoolAccess);
	}

	std::lock_guard<std::mutex> SyncManager::schedulerLock(){
		return std::lock_guard<std::mutex>(_schedulerAccess);
	}
	
	std::lock_guard<std::mutex> SyncManager::queueLock(){
		return std::lock_guard<std::mutex>(_queueAccess);
	}

	std::condition_variable& SyncManager::queueUpdated(){
		return _queueUpdated;
	}
}