#include "Tasks/Manager.hpp"
#include "Tasks/Context.hpp"

namespace Tasks{
	Manager::Manager() : _context{}{
		_context = new Context();
	}

	Manager::~Manager(){
		delete _context;
	}

	Task Manager::create(){
		return Task(_context->registry.createTask(), *_context);
	}

	void Manager::destroy(const Task& task){
		_context->registry.destroyTask(task.id());
	}

	void Manager::start(){
		_context->threadPool.start();
		_context->scheduler.start();
	}

	void Manager::stop(){
		_context->scheduler.stop();
		_context->threadPool.stop();
		_context->threadPool.waitIdle();
	}

	void Manager::trigger(const Task& task){
		_context->queue.push(task);
	}
}