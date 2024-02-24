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
		_stop = true;
		if (_thread.joinable()) _thread.join();
	}

	bool TaskScheduler::shouldContinue(){
		return !_stop;
	}

	std::pair<TaskID, std::chrono::steady_clock::time_point> TaskScheduler::nextTask(){
		std::unique_lock registryLock(_context.registry.mutex());
		std::unique_lock schedulerLock(_mutex);

		TaskID minId = INVALID_TASK_ID;
		std::chrono::nanoseconds minDuration = std::chrono::hours(100'000);
		const auto now = std::chrono::steady_clock::now();

		for (const auto& id : _cyclicTasks){
			const auto& data = _context.registry.data(id);
			std::chrono::nanoseconds duration = data.lastExecution - now + data.cycle.period();
			if (duration < minDuration){
				minDuration = duration;
				minId = id;
			}
		}

		return std::make_pair(minId, now + minDuration);
	}

	void TaskScheduler::requestExecution(const TaskID& id){
		_context.queue.push(Task(id, _context));
		_context.priorityUpdater.update();
		_context.registry.write(id, offsetof(TaskData, lastExecution), std::chrono::steady_clock::now());

		_context.threadPool.trigger();
	}

	void TaskScheduler::threadFnc(TaskScheduler& scheduler){
		while (scheduler.shouldContinue()){
			const auto [id, timePoint] = scheduler.nextTask();
			std::this_thread::sleep_until(timePoint);
			scheduler.requestExecution(id);
		}
	}
	
	void TaskScheduler::push(const TaskID& id){
		std::unique_lock lock(_mutex);
		_cyclicTasks.push_back(id);
	}

	void TaskScheduler::pop(const TaskID& id){
		std::unique_lock lock(_mutex);
		_cyclicTasks.remove(id);
	}
}