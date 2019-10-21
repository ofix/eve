#include "../include/PagerSpider.h"
#include <wx/regex.h>
#include <wx/textfile.h>
#include <wx/filefn.h>

PagerSpider::PagerSpider(wxString url,
                         uint8_t depth,
                         wxString destDir,
                         bool bCache):
                             _url(url),
                             _depth(depth),
                             _destDir(destDir),
                             _bCache(bCache)

{
    _cacheDir = GetExeDir()+"cache/";
    _accessDir = GetExeDir();

}

PagerSpider::~PagerSpider()
{
    //dtor
}

bool PagerSpider::Run()
{
    return false;
}

bool PagerSpider::SaveCache(std::vector<wxString> data, uint8_t depth) //都是链接
{
    wxTextFile file(GetCacheFile());
    if(!file.Exists()){
        file.Create(GetCacheFile());
    }
    if(data.size() == 0){
        return false;
    }
    if(depth<0 || depth > 3){
        return false;
    }
    std::vector<wxString>::const_iterator it;
    for(it=data.begin(); it!=data.end(); ++it){
        wxString strDepth = wxString::Format("%d",depth);
        file.AddLine(strDepth+","+(*it));
    }
    file.Write();
    file.Close();
    return true;
}

bool PagerSpider::IsCacheExists()
{
    return wxFileExists(GetCacheFile());
}


wxString PagerSpider::GetCacheFile()
{
    return GetCacheDir()+"cache."+CACHE_SUFFIX;
}

wxString PagerSpider::GetCacheDir()
{
    return _cacheDir;
}

void PagerSpider::SetCacheDir(wxString cacheDir)
{
    _cacheDir = cacheDir;
}

bool PagerSpider::ClearCache()
{
   wxRemoveFile(GetCacheFile());
   return true;
}

//日志操作
wxString PagerSpider::GetLogDir()
{
    return _accessDir;
}

void PagerSpider::SetLogDir(wxString accessDir)
{
    _accessDir = accessDir;
}

wxString PagerSpider::GetLogFile()
{
    return _accessDir +"access."+ACCESS_SUFFIX;
}

wxString PagerSpider::GetExeDir()
{
    wxString strExePath ;
    wxStandardPathsBase& stdp = wxStandardPaths::Get();
    wxFileName exeFile(stdp.GetExecutablePath());
    strExePath = exeFile.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
    return strExePath;
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


uint32_t PagerSpider::GetTotalImageCount() //获取所有图片总数
{
    return _totalImageCount;
}

bool PagerSpider::SaveAccessLog(wxString url) //爬虫访问的日志
{
    return false;
}
