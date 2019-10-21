#include "../include/PagerSpider.h"
#include <wx/regex.h>
#include <wx/textfile.h>
#include <wx/filefn.h>
#include <exception>

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

bool PagerSpider::RestoreCache()
{
    wxTextFile file(GetCacheFile());
    wxString line = file.GetNextLine();
    do{
        if(line[0] == "%"&&line[1]=="%"){
            wxString global = line.Mid(2);
            if(global == "girls"){

            }else if(global == "dest_dir"){

            }
        }else if(line[0] =="+"&&line[1]=="+"){//
            CacheItem item;
            item.url = ParseItem(line);
            line = file.GetNextLine();
            wxString meta_name = ParseMetaLine(line,"::");
            if(meta_name=="girl"){
                item.girl = file.GetNextLine();
            }
            meta_name = ParseMetaLine(line,"::");
            if(meta_name=="regex_rules"){
                line=file.GetNextLine();
                do{
                    std::vector<wxString> parts = Split(line,",");
                    RegexRule rule;
                    rule.type = parts[0];
                    rule.depth = parts[1];
                    rule.rule = parts[2];
                    item.regex_rules.push_back(rule);
                }while(line[0]!=":"&&line[1]!=":")
            }
            meta_name = ParseMetaLine(line,"::");
            if(meta_name == "cache_data"){
                line = file.GetNextLine();
                std::vector<wxString> parts = Split(line,"|");
                std::vector<wxString>::const_iterator it;
                for(it=parts.begin(); it!=parts.end(); ++it){
                    std::vector<wxString> m = Split(*it,",");
                    Chunk chunk;
                    chunk.start = m[0];
                    chunk.end = m[1];
                    item.chunks.push_back(chunk);
                }
            }
            _cache_items.insert(item);
        }
        line = file.GetNextLine();
    }while(line!=""||line == file.Eof());
    return true;
}

std::vector<wxString> PagerSpider::Split(wxString line,wxString seperator=",")
{
    size_t nLine = line.length();
    std:vector<wxString> parts;
    wxString part="";
    for(size_t i=0; i<nLine; i++){
        if(line[i] == seperator){
            parts.push_back(part);
            part = "";
        }else{
            part.Append(line[i]);
        }
    }
    return parts;
}

wxString PagerSpider::ParseMetaLine(wxString line,wxString prefix)
{
    size_t nLine = line.length();
    size_t nPrefix = prefix.length();
    if(nLine < nPrefix){
        throw new exception("unrecognized meta line");
    }
    if(line.Mid(0,nPrefix) == prefix){
        return line.Mid(nPrefix).Trim();
    }else{
        throw new exception("meta line parse error.");
    }
}

wxString PagerSpider::ParseItem(wxString line){
    wxString ret;
    for(uint32_t i=0; i<line.length(); i++){
       if(line[i]!='+'&&line[i]!=' '){
           ret.Append(line[i]);
       }
    }
    return ret;
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
