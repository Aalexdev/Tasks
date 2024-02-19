#ifndef __TASKS_IMPORTANCE_HPP__
#define __TASKS_IMPORTANCE_HPP__

#include "common.hpp"

namespace Tasks{
	class Importance{
		public:
			static constexpr float OPTIONAL = 0.f;
			static constexpr float LOW = 0.2f;
			static constexpr float MODERATE = 0.4f;
			static constexpr float HIGH = 0.6f;
			static constexpr float VERY_HIGH = 0.8f;
			static constexpr float CRITICAL = 1.f;

			Importance(const float& importance = MODERATE) noexcept;
			Importance(const Importance& other) noexcept;
			~Importance() noexcept;

			Importance& operator=(const Importance& other) noexcept;

			bool operator>(const Importance& other) const noexcept;
			bool operator>=(const Importance& other) const noexcept;
			bool operator<(const Importance& other) const noexcept;
			bool operator<=(const Importance& other) const noexcept;

		private:
			float _importance;

	};
}

#endif