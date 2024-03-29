#ifndef __TASKS_CONTEXT_HPP__
#define __TASKS_CONTEXT_HPP__

#include "common.hpp"
#include "TaskRegistry.hpp"
#include "TaskQueue.hpp"
#include "PriorityUpdater.hpp"
#include "TaskScheduler.hpp"
#include "ThreadPool.hpp"

namespace Tasks{
	struct Context{
		TaskRegistry registry;
		TaskQueue queue;
		PriorityUpdater priorityUpdater;
		TaskScheduler scheduler;
		ThreadPool threadPool;

		Context();
	};
}

#endif