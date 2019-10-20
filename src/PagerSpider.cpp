#include "../include/PagerSpider.h"
#include <wx/regex.h>

PagerSpider::PagerSpider(wxString url,
                         uint8_t depth,
                         wxString destDir,
                         bool bCache):
                             _url(url),
                             _depth(depth),
                             _destDir(destDir),
                             _bCache(bCache)

{
    //ctor
}

PagerSpider::~PagerSpider()
{
    //dtor
}

bool PagerSpider::Run()
{
    return false;
}

bool PagerSpider::IsCacheExists()
{
    return false;
}

void PagerSpider::SetRegexRules(wxString regexString,uint8_t type,uint8_t depth)
{
    _regexRules.push_back(regexString);
}

std::vector<wxString> PagerSpider::GetCache(uint8_t depth) //��ȡ�����ļ��б�����б�Ŀ¼�е�����
{
    std::vector<wxString> data;
    return data;
}

bool PagerSpider::SaveCache(std::vector<wxString> data, uint8_t depth) //��������
{
    return false;
}

uint32_t PagerSpider::GetTotalImageCount() //��ȡ����ͼƬ����
{
    return _totalImageCount;
}

bool PagerSpider::SaveAccessLog(wxString url) //������ʵ���־
{
    return false;
}
