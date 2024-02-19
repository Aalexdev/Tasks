#include "Tasks/TaskCycle.hpp"

namespace Tasks{
	TaskCycle::TaskCycle() noexcept : _period{_period.zero()}{}
	TaskCycle::TaskCycle(const Frequency& frequency) noexcept : _period{std::chrono::duration_cast<Period>(std::chrono::seconds(1) / frequency)}{}
	TaskCycle::TaskCycle(const Period& period) noexcept : _period{period}{}
	TaskCycle::TaskCycle(const TaskCycle& other) noexcept : _period{other._period}{}
	TaskCycle::~TaskCycle() noexcept {}
	
	bool TaskCycle::isCyclic() const noexcept{
		return _period != _period.zero();
	}
	
	const TaskCycle::Period& TaskCycle::period() const noexcept{
		return _period;
	}

	TaskCycle::Period& TaskCycle::period() noexcept{
		return _period;
	}
}