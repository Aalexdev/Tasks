#include "Tasks/Manager.hpp"

namespace Tasks{
	Manager::Manager() : _context{}{}
	Manager::~Manager(){}

	Task Manager::create(const std::string& name){
		_context.syncManager.registryWrite();
		return Task(_context.registry.createTask(name), _context);
	}

	void Manager::destroy(const Task& task){
		_context.syncManager.registryWrite();
		_context.registry.destroyTask(task.id());
	}

	void Manager::start(){
		_context.threadPool.start();
		_context.scheduler.start();
	}

	void Manager::stop(){
		_context.scheduler.stop();
		_context.threadPool.stop();
		_context.threadPool.waitIdle();
	}
}