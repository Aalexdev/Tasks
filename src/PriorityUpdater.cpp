#include "Tasks/PriorityUpdater.hpp"
#include "Tasks/Context.hpp"
#include "Tasks/TaskRegistry.hpp"

namespace Tasks{
	PriorityUpdater::PriorityUpdater(Context& context) : _context{context}{}
	PriorityUpdater::~PriorityUpdater(){}

	void PriorityUpdater::update(){
		auto& queue = _context.queue;

		for (const auto& it : queue._taskIDToIndex){
			const std::size_t& ID = it.second;

			const Tasks::TaskRef& ref = queue.ref(ID);
			queue.update(ID, ref.priority() * 1.5);
		}
	}
}