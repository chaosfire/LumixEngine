#include "core/lux.h"
#include "core/MTJD/job.h"

#include "core/MTJD/manager.h"

namespace Lux
{
	namespace MTJD
	{
		Job::Job(bool auto_destroy, Priority priority, bool sync_event, Manager* manager)
			: BaseEntry(1, sync_event)
			, m_manager(manager)
			, m_priority(priority)
			, m_auto_destroy(auto_destroy)
			, m_scheduled(false)
			, m_executed(false)
		{
			ASSERT(NULL != manager);
			setJobName("Unknown Job");
		}

		Job::~Job()
		{
		}

		void Job::incrementDependency()
		{
#if TYPE == MULTI_THREAD

			MT::atomicIncrement(&m_dependency_count);
			ASSERT(!m_scheduled);

#endif //TYPE == MULTI_THREAD
		}

		void Job::decrementDependency()
		{
#if TYPE == MULTI_THREAD

			uint32_t count = MT::atomicDecrement(&m_dependency_count);
			if (1 == count)
			{
				m_manager->schedule(this);
			}

#endif //TYPE == MULTI_THREAD
		}

		void Job::onExecuted()
		{
			BaseEntry::dependencyReady();

			if (m_auto_destroy)
			{
				LUX_DELETE(this);
			}

			m_executed = true;
		}
	} // ~namepsace MTJD
} // ~namepsace Lux