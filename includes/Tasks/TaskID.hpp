#ifndef __TASKS_TASK_ID_HPP__
#define __TASKS_TASK_ID_HPP__

#include "common.hpp"

namespace Tasks{
	using TaskID = std::size_t;
	static constexpr TaskID INVALID_TASK_ID = TaskID(~0);
}

#endif