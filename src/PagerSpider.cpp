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

std::vector<wxString> PagerSpider::GetCache(uint8_t depth) //获取缓存文件中保存的列表目录中的数据
{
    std::vector<wxString> data;
    return data;
}

bool PagerSpider::SaveCache(std::vector<wxString> data, uint8_t depth) //都是链接
{
    return false;
}

uint32_t PagerSpider::GetTotalImageCount() //获取所有图片总数
{
    return _totalImageCount;
}

bool PagerSpider::SaveAccessLog(wxString url) //爬虫访问的日志
{
    return false;
}
