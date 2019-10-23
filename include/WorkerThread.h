#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <wx/thread.h>
#include <wx/string.h>

class WorkerThread:wxThread
{
    public:
        WorkerThread();
        virtual ~WorkerThread();
        virtual wxThread::ExitCode Entry();
    protected:
};

#endif // DOWNLOADTHREAD_H
