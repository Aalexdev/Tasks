#ifndef __TASKS_TIME_CONSTRAINT_HPP__
#define __TASKS_TIME_CONSTRAINT_HPP__

#include "Tasks/common.hpp"

namespace Tasks{
	class TimeConstraint{
		public:
			using Duration = ::std::chrono::steady_clock::duration;
			static constexpr Duration NONE = std::chrono::hours(100'000);

			TimeConstraint(const Duration& duration = NONE) noexcept;
			TimeConstraint(const TimeConstraint& other) noexcept;
			~TimeConstraint() noexcept;

			TimeConstraint& operator=(const TimeConstraint& other) noexcept;
			TimeConstraint& operator=(const Duration& duration) noexcept;

			const Duration& get() const noexcept;
			Duration& get() noexcept;

			bool hasConstraints() const noexcept;

		private:
			Duration _duration;
			
	};
}

#endif