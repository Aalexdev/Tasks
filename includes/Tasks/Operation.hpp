#ifndef __TASKS_OPERATION_HPP__
#define __TASKS_OPERATION_HPP__

#include "common.hpp"

namespace Tasks{
	class Operation{
		public:
			using FunctionPointer = void(*)(void);
			
			Operation();
			Operation(const Operation& other);
			Operation(const FunctionPointer& operation);
			~Operation();

			const FunctionPointer& get() const;
			FunctionPointer& get();

			void set(const FunctionPointer& function);
			
			void execute();

			bool isSet() const;
			operator bool() const;

			bool operator==(const FunctionPointer& other) const;
			bool operator==(const Operation& other) const;

		public:
			FunctionPointer _function;
			
	};
}

#endif