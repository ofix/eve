#include "WorkerThread.h"

WorkerThread::WorkerThread():wxThread(wxTHREAD_DETACHED)
{
    //ctor
}

WorkerThread::~WorkerThread()
{
    //dtor
}


//开始干活啦
wxThread::ExitCode WorkerThread::Entry()
{
     for(;;){

     }
     return NULL;
}
