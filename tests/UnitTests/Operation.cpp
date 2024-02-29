#include <gtest/gtest.h>
#include <Tasks/Operation.hpp>

void fnc(){}

void stdExceptionFnc(){
	throw std::runtime_error("exception");
}

void nonstdExceptionFnc(){
	throw "non standard exception";
}

TEST(Operation, default_constructor){
	Tasks::Operation operation;

	EXPECT_EQ(operation.get(), nullptr);
	EXPECT_FALSE(operation.isSet());
	EXPECT_FALSE(operation);
}

TEST(Operation, fnc_construction){
	Tasks::Operation operation(fnc);

	EXPECT_TRUE(operation.isSet());
	EXPECT_TRUE(operation);
}

TEST(Operation, operator_constructor){
	Tasks::Operation base(fnc);
	Tasks::Operation operation(base);

	EXPECT_EQ(operation, base);
	EXPECT_TRUE(operation.isSet());
	EXPECT_TRUE(operation);
}

TEST(Operation, no_throw_execute){
	Tasks::Operation operation(fnc);

	EXPECT_NO_THROW(operation.execute());
}

TEST(Operation, std_throw_execute){
	Tasks::Operation operation(stdExceptionFnc);
	
	EXPECT_THROW(operation.execute(), std::exception);
}

TEST(Operation, nonstd_throw_execute){
	Tasks::Operation operation(nonstdExceptionFnc);

	EXPECT_ANY_THROW(operation.execute());
}