#ifndef PAGERSPIDER_H
#define PAGERSPIDER_H
#include <wx/string.h>
#include <vector>

#define CACHE_SUFFIX ".eve"
#define REGEX_URL_LIST 1
#define REGEX_URL_PAGER 2
#define REGEX_URL_IMAGE 3

#define DEPTH_LIMIT 2

class PagerSpider
{
    public:
        PagerSpider(wxString url, uint8_t depth, wxString destDir, bool bCache=false);
        virtual ~PagerSpider();
        bool Run();
        bool IsCacheExists();
        void SetRegexRules(wxString regexString,uint8_t type,uint8_t depth);
        std::vector<wxString> GetCache(uint8_t depth); //获取缓存文件中保存的列表目录中的数据
        bool SaveCache(std::vector<wxString> data, uint8_t depth); //都是链接
        uint32_t GetTotalImageCount(); //获取所有图片总数
        bool SaveAccessLog(wxString url); //爬虫访问的日志
    private:
        wxString _url; //访问的URL
        uint8_t _depth; //列表层级的深度
        wxString _destDir; //保存图片的目录
        wxString _cacheDir; //缓存文件的目录
        wxString _accessDir; //爬虫访问日志
        bool _bCache; //是否缓存数据
        std::vector<wxString> _regexRules; //正则表达式
        std::vector<wxString> _failUrl; //访问失败的URL
        //下面是统计数据
        uint32_t _totalImageCount; //下载的所有图片总数
        bool _allowRepeat; //是否需要图片去重
};

#endif // PAGERSPIDER_H
