#ifndef BOSSTHREAD_H
#define BOSSTHREAD_H
#include <wx/thread.h>

class BossThread:wxThread
{
    public:
        BossThread();
        virtual ~BossThread();

};

#endif // BOSSTHREAD_H
