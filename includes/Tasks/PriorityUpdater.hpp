#ifndef __TASKS_PRIORITY_UPDATER_HPP__
#define __TASKS_PRIORITY_UPDATER_HPP__

#include "common.hpp"

namespace Tasks{
	class PriorityUpdater{
		public:
			PriorityUpdater(Context& context);
			~PriorityUpdater();

			void update();

		private:
			Context& _context;

	};
}

#endif