#include "Tasks/TaskScheduler.hpp"
#include "Tasks/Context.hpp"
#include <iostream>

namespace Tasks{
	TaskScheduler::TaskScheduler(Context& context) : _context{context}{}
	TaskScheduler::~TaskScheduler(){
		stop();
	}

	void TaskScheduler::start(){
		_stop = false;
		_thread = std::thread(threadFnc, std::ref(*this));
	}

	void TaskScheduler::stop(){
		{ 
			auto schedulerLock = _context.syncManager.schedulerLock();
			_stop = true;
		}
		if (_thread.joinable()) _thread.join();
	}

	bool TaskScheduler::shouldContinue(){
		auto schedulerLock = _context.syncManager.schedulerLock();
		return !_stop;
	}

	std::pair<TaskID, std::chrono::steady_clock::time_point> TaskScheduler::nextTask(){
		auto schedulerLock = _context.syncManager.schedulerLock();
		auto registryLock = _context.syncManager.registryRead();

		TaskID minId = INVALID_TASK_ID;
		std::chrono::steady_clock::duration minDuration = std::chrono::hours(100'000);
		const auto now = std::chrono::steady_clock::now();

		for (const auto& id : _cyclicTasks){
			const auto& data = _context.registry.data(id);
			std::chrono::steady_clock::duration duration = data.lastExecution - now + data.cycle.period();
			if (duration < minDuration){
				minDuration = duration;
				minId = id;
			}
		}

		return std::make_pair(minId, now + minDuration);
	}

	void TaskScheduler::requestExecution(const TaskID& id){
		auto schedulerLock = _context.syncManager.schedulerLock();
		auto queueLock = _context.syncManager.queueLock();

		_context.queue.push(Task(id, _context));
		_context.priorityUpdater.update();
		_context.registry.data(id).lastExecution = std::chrono::steady_clock::now();

		_context.syncManager.queueUpdated().notify_one();
	}

	void TaskScheduler::threadFnc(TaskScheduler& scheduler){
		while (scheduler.shouldContinue()){
			auto [id, timePoint] = scheduler.nextTask();

			std::this_thread::sleep_until(timePoint);
			scheduler.requestExecution(id);
		}
	}
	
	void TaskScheduler::push(const TaskID& id){
		auto lock = _context.syncManager.schedulerLock();
		_cyclicTasks.push_back(id);
	}

	void TaskScheduler::pop(const TaskID& id){
		auto lock = _context.syncManager.schedulerLock();
		_cyclicTasks.remove(id);
	}
}