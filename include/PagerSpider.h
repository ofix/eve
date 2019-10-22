#ifndef PAGERSPIDER_H
#define PAGERSPIDER_H
#include <wx/string.h>
#include <vector>
#include <unordered_set>
#include "CacheItem.h"

#define CACHE_SUFFIX "eve"
#define CACHE_META_SUFFIX "mta"
#define ACCESS_SUFFIX "log"

#define RULE_LIST_DATA 1
#define RULE_PAGER 2
#define RULE_IMAGE 3

#define DEPTH_LIMIT 2

class PagerSpider
{
    public:
        PagerSpider(wxString url, uint8_t depth, wxString destDir, bool bCache=true);
        virtual ~PagerSpider();
        bool Run();
        void SetGirl(wxString girl);
        void SetRegexRule(wxString regexString,uint8_t type,uint8_t depth);
        wxString GetRegexRule(uint8_t type,uint8_t depth);
        std::vector<wxString> GetMatches(wxString& response,wxString& rule);
        wxString GetMatch(wxString& response,wxString& rule);
        uint32_t GetTotalImageCount(); //获取所有图片总数
        std::vector<wxString> GetAllPages(wxString maxPageUrl,wxString host,size_t& nPages);
        bool DownloadSingleImage(wxString& image_url,wxString savePath);
        bool DownloadAllImages(std::vector<wxString>& images_url);

        bool BfsVisist(); //广度优先遍历
        bool DfsVisit();  //深度优先遍历

        //日志相关函数
        bool SaveLog(wxString url); //爬虫访问的日志
        wxString GetLogFile();
        void SetLogDir(wxString logDir);
        wxString GetLogDir();
        //缓存相关日志
        bool IsCacheExists();
        std::vector<wxString> GetCache(uint8_t depth); //获取缓存文件中保存的列表目录中的数据
        bool SaveCacheData(std::vector<wxString> data, uint8_t depth); //都是链接
        bool SaveCacheMeta();
        bool ClearCache();//清空缓存
        wxString GetCacheFile();
        wxString GetCacheMetaFile();
        wxString GetCacheDir();
        void SetCacheDir(wxString cacheDir); //设置缓存目录
        //Cache 解析相关
        bool RestoreCacheMeta();//解析Cache里面的数据
        wxString ParseItem(wxString itemLine);
        wxString ParseMetaLine(wxString line,wxString prefix);
        std::vector<wxString> Split(wxString line,wxString seperator=",");
        //deubg
        void console(wxString data,bool bUtf8 = true);
    private:
        wxString _url; //访问的URL
        uint8_t _depth; //列表层级的深度
        wxString _destDir; //保存图片的目录
        wxString _cacheDir; //缓存文件的目录
        wxString _accessDir; //爬虫访问日志
        bool _bCache; //是否缓存数据
        std::vector<RegexRule> _regexRules; //正则表达式
        std::vector<wxString> _failedUrl; //访问失败的URL

        wxString _girl; //当前女孩的名字
        std::vector<wxString> _girls; //所有女孩的名字
        std::vector<CacheItem> _cache_items; //缓存数据

        CacheItem _cache_meta; //当前缓存的meta数据
        //下面是统计数据
        size_t _totalImageCount; //下载的所有图片总数
        bool _allowRepeat; //是否需要图片去重
        // 统计相关变量
        uint32_t _elapsed; //消逝的时间，单位秒
};

#endif // PAGERSPIDER_H
