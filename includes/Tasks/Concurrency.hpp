#ifndef __TASKS_CONCURRENCY_HPP__
#define __TASKS_CONCURRENCY_HPP__

#include "common.hpp"
#include "TaskID.hpp"

namespace Tasks{
	class Concurrency{
		public:
			Concurrency(const TaskID& id = INVALID_TASK_ID) noexcept;
			Concurrency(const Concurrency& other) noexcept;
			~Concurrency() noexcept;
			
			Concurrency& operator=(const Concurrency& other) noexcept;
			Concurrency& operator=(const TaskID& id) noexcept;

			const TaskID& id() const noexcept;
			TaskID& id() noexcept;

		private:
			TaskID _id;
	};
}

#endif