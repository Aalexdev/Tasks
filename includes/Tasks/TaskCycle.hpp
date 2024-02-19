#ifndef __TASKS_TASK_CYCLE_HPP__
#define __TASKS_TASK_CYCLE_HPP__

#include "common.hpp"

namespace Tasks{
	class TaskCycle{
		public:
			using Period = ::std::chrono::steady_clock::duration;
			using Frequency = float;

			static constexpr Frequency SINGLE = 0.f;

			TaskCycle() noexcept;
			TaskCycle(const Frequency& ferquency) noexcept;
			TaskCycle(const Period& period) noexcept;
			TaskCycle(const TaskCycle& other) noexcept;
			~TaskCycle() noexcept;

			bool isCyclic() const noexcept;

			const Period& period() const noexcept;
			Period& period() noexcept;

		private:
			Period _period;
			
	};
}

#endif