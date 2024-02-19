#ifndef __TASKS_PRIORITY_HPP__
#define __TASKS_PRIORITY_HPP__

#include "common.hpp"

namespace Tasks{
	class Priority{
		public:
			static constexpr float LOW = 0.1f;
			static constexpr float MEDIUM = 0.5f;
			static constexpr float HIGH = 0.7f;
			static constexpr float URGENT = 1.f;

			Priority(float priority = MEDIUM) noexcept;
			Priority(const Priority& priority) noexcept;
			~Priority() noexcept;

			float& get() noexcept;
			const float& get() const noexcept;

			void set(const float& priority) noexcept;

			bool operator>(const Priority& other) const noexcept;
			bool operator<(const Priority& other) const noexcept;
			bool operator>=(const Priority& other) const noexcept;
			bool operator<=(const Priority& other) const noexcept;

			Priority& operator+=(const Priority& other) noexcept;
			Priority& operator-=(const Priority& other) noexcept;
			Priority& operator+=(const float& b) noexcept;
			Priority& operator-=(const float& b) noexcept;
			Priority& operator*=(const float& factor) noexcept;
			Priority& operator/=(const float& factor) noexcept;

			Priority operator+(const Priority& other) const noexcept;
			Priority operator-(const Priority& other) const noexcept;
			Priority operator+(const float& a) const noexcept;
			Priority operator-(const float& a) const noexcept;
			Priority operator*(const float& factor) const noexcept;
			Priority operator/(const float& factor) const noexcept;

		private:
			float _priority;
	};
}

#endif