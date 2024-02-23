#include "Tasks/PriorityUpdater.hpp"
#include "Tasks/Context.hpp"
#include "Tasks/TaskRegistry.hpp"
#include <iostream>

namespace Tasks{
	PriorityUpdater::PriorityUpdater(Context& context) : _context{context}{}
	PriorityUpdater::~PriorityUpdater(){}

	void PriorityUpdater::update(){
		auto& queue = _context.queue;

		for (const auto& it : queue._taskIDToIndex){
			const std::size_t& queueID = it.second;
			const Tasks::TaskRef& ref = queue.ref(queueID);
			const Tasks::TaskData& data = _context.registry.data(ref.id());

			float factor = 1.f;

			factor += data.basePriority.get();
			factor += data.importance.get();

			if (data.timeConstraint.hasConstraints()){
				const auto& wantedDuration = data.timeConstraint.get();
				const auto& realDurarion = data.lastDuration;

				const float effectiveness = wantedDuration / realDurarion;
				factor *= effectiveness;
			}

			const Priority newPriority = ref.priority() * factor;

			queue.update(queueID, newPriority);
		}
	}
}