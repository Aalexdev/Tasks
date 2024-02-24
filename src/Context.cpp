#include "Tasks/Context.hpp"

namespace Tasks{
	Context::Context() : 
		registry{*this},
		queue{*this},
		priorityUpdater{*this},
		scheduler{*this},
		threadPool{*this}
	{}
}