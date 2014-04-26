#include "core/lux.h"
#include "core/MTJD/worker_thread.h"

#include "core/MTJD/manager.h"
#include "core/MTJD/job.h"

#define PROFILE_START
#define PROFILE_STOP

namespace Lux
{
	namespace MTJD
	{
#if TYPE == MULTI_THREAD

		WorkerTask::WorkerTask()
		{
		}

		WorkerTask::~WorkerTask()
		{
		}

		bool WorkerTask::create(const char* name, Manager* manager)
		{
			ASSERT(NULL != manager);
			m_manager = manager;
			return Task::create(name);
		}

		int WorkerTask::task()
		{
			ASSERT(NULL != m_trans_queue);

			while (!m_trans_queue->isAborted())
			{
				Manager::JobTrans* tr = m_trans_queue->pop(true);
				if (tr == NULL)
					break;

				PROFILE_START("WorkerTask");
				PROFILE_START(tr->data->getJobName());
				tr->data->execute();
				tr->setCompleted();
				PROFILE_STOP(tr->data->getJobName());
				PROFILE_STOP("WorkerTask");

				m_manager->doScheduling();
			}

			return 0;
		}

#endif // TYPE == MULTI_THREAD
	} // ~namepsace MTJD
} // ~namepsace Lux