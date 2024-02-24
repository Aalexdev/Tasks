#include "Tasks/ThreadPool.hpp"
#include "Tasks/Context.hpp"
#include <iostream>

namespace Tasks{
	ThreadPool::ThreadPool(Context& context) : _context{context}{}
	ThreadPool::~ThreadPool(){
		waitIdle();
	}

	void ThreadPool::start(){
		std::unique_lock lock(_mutex);
		_stop = false;

		static const std::size_t threadCount = std::thread::hardware_concurrency() - 1;
		for (std::size_t i=0; i<threadCount; i++){
			_threads.push_back(std::thread(threadFnc, std::ref(*this)));
		}
	}

	void ThreadPool::stop(){
		_stop = true;
		_CV.notify_all();
	}

	void ThreadPool::waitIdle(){
		for (auto& thread : _threads){
			thread.join();
		}
		_threads.clear();
	}

	TaskID ThreadPool::nextTask(){
		auto& queue = _context.queue;

		std::unique_lock lock(_mutex);
		_CV.wait(
			lock, 
			[&]{
				return !queue.empty() || _stop;
			}
		);

		if (_stop) return INVALID_TASK_ID;

		Task task = queue.top();

		queue.pop();

		if (!queue.empty()){
			_CV.notify_one();
		}

		return task.id();
	}

	void ThreadPool::updateCurrentTask(TaskID id){
		std::unique_lock lock(_mutex);
		_currentTasks[std::this_thread::get_id()] = id;
	}

	void ThreadPool::threadFnc(ThreadPool& pool){
		while (pool.shouldContinue()){
			TaskID task = pool.nextTask();
			if (task == INVALID_TASK_ID) continue;

			auto executionStart = std::chrono::steady_clock::now();
			const auto& operation = pool._context.registry.data(task).operation;

			pool.updateCurrentTask(task);

			try{
				operation.execute();
			} catch (const std::exception& e){
				std::cerr << e.what() << std::endl;
			}

			auto executionDuration = std::chrono::steady_clock::now() - executionStart;
			pool.updateTaskData(task, executionDuration, executionStart);
		}
	}

	bool ThreadPool::shouldContinue(){
		return !_stop;
	}

	void ThreadPool::updateTaskData(const TaskID& id, const std::chrono::steady_clock::duration& executionDuration, const std::chrono::steady_clock::time_point& lastExecution){
		std::unique_lock lock(_context.registry.mutex());
		auto& data = _context.registry.data(id);

		data.lastExecution = lastExecution;
		data.lastDuration = executionDuration;
	}

	void ThreadPool::trigger(){
		_CV.notify_one();
	}
}