#ifndef __TASKS_OPERATION_HPP__
#define __TASKS_OPERATION_HPP__

#include "common.hpp"

namespace Tasks{
	class Operation{
		public:
			using FunctionPointer = std::function<void(void)>;
			
			Operation();
			Operation(const Operation& other);
			Operation(const FunctionPointer& fnc);
			~Operation();

			Operation& operator=(const Operation& other);

			const FunctionPointer& get() const;
			FunctionPointer& get();

			void set(const FunctionPointer& function);
			
			void execute() const;

			bool isSet() const;
			operator bool() const;

			bool operator==(const FunctionPointer& other) const;
			bool operator==(const Operation& other) const;

		public:
			FunctionPointer _function;
			
	};
}



#endif