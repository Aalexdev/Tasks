#include "Tasks/Operation.hpp"

namespace Tasks{
	Operation::Operation() : _function{nullptr}{}
	Operation::Operation(const Operation& other) : _function{other._function}{}
	Operation::Operation(const FunctionPointer& operation) : _function{operation}{}

	Operation::~Operation(){}

	const Operation::FunctionPointer& Operation::get() const{
		return _function;
	}

	Operation::FunctionPointer& Operation::get(){
		return _function;
	}

	void Operation::set(const FunctionPointer& function){
		_function = function;
	}

	void Operation::execute(){
		if (isSet()) _function();
	}

	bool Operation::isSet() const{
		return _function != nullptr;
	}

	Operation::operator bool() const{
		return isSet();
	}
	
	bool Operation::operator==(const FunctionPointer& other) const{
		return _function == other;
	}

	bool Operation::operator==(const Operation& other) const{
		return _function == other._function;
	}
}