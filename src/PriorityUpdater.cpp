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
			const TaskRef& ref = queue.cdata(queueID);

			Priority basePriority;
			Importance importance;
			TimeConstraint::Duration lastDuration;
			TimeConstraint timeConstraint;

			{
				auto& registry = _context.registry;

				std::shared_lock lock(registry.mutex());
				const TaskData& data = registry.cdata(ref.id());

				basePriority = data.basePriority;
				importance = data.importance;
				lastDuration = data.lastDuration;
				timeConstraint = data.timeConstraint;
			}

			float factor = 1.f;

			factor += basePriority.get();
			factor += importance.get();

			if (timeConstraint.hasConstraints()){
				const auto& wantedDuration = timeConstraint.get();
				const auto& realDurarion = lastDuration;

				const float effectiveness = wantedDuration / realDurarion;
				factor *= effectiveness;
			}

			const Priority newPriority = ref.priority() * factor;
			queue.updateID(queueID, newPriority);
		}
	}
}