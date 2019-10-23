#ifndef TASKITEM_H
#define TASKITEM_H

#include <wx/string.h>

class TaskItem
{
    public:
        TaskItem();
        virtual ~TaskItem();
    wxString rule_pager; //爬取分页数据的正则表达式
    wxString rule_list_data; //爬取列表数据的正则表达式
};

#endif // TASKITEM_H
