#include "../include/PagerSpider.h"
#include <exception>
#include <wx/regex.h>
#include <wx/textfile.h>
#include <wx/log.h>
#include "../lib/Https.h"
#include <iostream>

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
    _totalImageCount = 0;
    _downloadedImageCount = 0;
    if(_destDir == ""){
        _destDir = GetExeDir()+"images/";
    }
}

PagerSpider::~PagerSpider()
{
    //dtor
}

void PagerSpider::SetGirl(wxString girl){
    _girl = girl;
}

/*****************************************
 *@brief 宽度优先遍历列表数据网页,解析出当前
 *层级所有的网页再进入下一级层级进行遍历解析
 *@param void
 *@return bool
 *****************************************/
bool PagerSpider::BfsVisist()
{
    std::vector<wxString> links;
    std::vector<wxString> next_links;
    links.push_back(_url);
    wxString host = GetHost(_url);
    for(uint8_t i=0;i<=_depth;i++){
        for(size_t nLinks=0; nLinks <links.size(); nLinks++){
            wxString response;
            Https(links[nLinks],response,wxFONTENCODING_UTF8);
            wxString rule = GetRegexRule(RULE_PAGER,(uint8_t)i);//检查是否有分页
            //访问links所有的网页，用对应的规则匹配出下一层级的所有链接
            if(rule == ""){ // 列表数据，内容少，没有分页
                wxString rule = GetRegexRule(RULE_LIST_DATA,i);
                std::vector<wxString> tmp_links = GetMatches(response,rule);
                next_links.insert(next_links.end(),tmp_links.begin(),tmp_links.end());
            }else{ // 列表数据，内容多，有分页
                std::vector<wxString> pageMaxUrl = GetMatches(response,rule); //只匹配了最大分页，其余分页由程序生成
                std::vector<wxString> pages;
                size_t nPages;
                pages = GetAllPages(pageMaxUrl[0],host,nPages);
                wxString rule = GetRegexRule(RULE_LIST_DATA,i);
                for(size_t j=0; j<nPages; j++){
                    //std::cout<<pages[j].char_str()<<std::endl;
                    Https(pages[j],response,wxFONTENCODING_UTF8);
                    std::vector<wxString> tmp_links = GetMatches(response,rule);
                    next_links.insert(next_links.end(),tmp_links.begin(),tmp_links.end());
                }
                if(i==_depth){
                    _totalImageCount  += next_links.size();
                }
            }
        }
        links.clear();
        links.insert(links.end(),next_links.begin(),next_links.end());
        next_links.clear();
    }
    _totalImageCount = links.size();
    DownloadAllImages(links);
    //下面是图片的链接
    return true;
}

/*****************************************
 *@brief 深度优先遍历列表数据网页,解析出当前
 *层级所有的网页再进入下一级层级进行遍历解析
 *@param void
 *@return bool
 *****************************************/
bool PagerSpider::DfsVisit()
{
    return false;
}

bool PagerSpider::Run()
{
    _totalImageCount = 0;
    _downloadedImageCount = 0;
    return BfsVisist();
}

bool PagerSpider::DownloadSingleImage(wxString& image_url,wxString savePath)
{
   std::cout<<image_url<<std::endl;
   CURLcode ret = DownloadFile(image_url,savePath);
   if(ret == CURLE_OK){
        return true;
   }
   return false;
}

bool PagerSpider::DownloadAllImages(std::vector<wxString>& images_url)
{
    for(size_t i = 0; i< images_url.size(); ++i){
        DownloadSingleImage(images_url[i], _destDir+_girl+"_"+wxString::Format("%04d",(int)i)+".jpg");
        _downloadedImageCount = i;
    }
    return true;
}

std::vector<wxString> PagerSpider::GetAllPages(wxString maxPageUrl,wxString host,size_t& nPages)
{
    wxString rule = "[^_]+_(\\d+).html";
    wxString pages = GetMatch(maxPageUrl,rule);
    long xPages;
    pages.ToLong(&xPages);
    nPages = (size_t)xPages; //最大的页数
    rule = "([^_]+)_\\d+.html";
    wxString prefix = GetMatch(maxPageUrl,rule);
    std::vector<wxString> all_pages;
    all_pages.push_back(host+prefix+".html");
    for(size_t i= 2; i<=nPages; ++i){
        all_pages.push_back(host+prefix+"_"+wxString::Format("%d",(int)i)+".html");
    }
    return all_pages;
}

wxString PagerSpider::GetMatch(wxString& response,wxString& rule)
{
   std::vector<wxString> matches = GetMatches(response,rule);
   return matches[0];
}

std::vector<wxString> PagerSpider::GetMatches(wxString& response,wxString& rule)
{
    std::vector<wxString> matches;
    wxRegEx r(rule,wxRE_ADVANCED);
    wxString text = response;
    while(r.Matches(text)){
        size_t start, len;
        r.GetMatch(&start, &len, 0);
        wxString match = r.GetMatch(text,1); //只有一个匹配
        matches.push_back(match);
        text = text.Mid(start+len);
    }
    return matches;
}


void  PagerSpider::console(wxString data,bool bUtf8)
{
 wxCSConv gbkConv(wxFONTENCODING_CP936);
 std::string str_gbk(gbkConv.cWX2MB(data.wchar_str()));
 std::cout<<str_gbk<<std::endl;
}

//正则存取函数
wxString PagerSpider::GetRegexRule(uint8_t type,uint8_t depth)
{
    std::vector<RegexRule>::const_iterator it;
    //需要排序
    for(it=_regexRules.begin(); it!=_regexRules.end(); ++it){
        if((*it).depth == depth && (*it).type == type){
            return (*it).rule;
        }
    }
    return "";
}

void PagerSpider::SetRegexRule(wxString regexString,uint8_t type,uint8_t depth)
{
    RegexRule rule;
    rule.depth = depth;
    rule.type = type;
    rule.rule = regexString;
    _regexRules.push_back(rule);
    if(depth > _depth){
        _depth = depth;
    }
}

bool PagerSpider::SaveCacheMeta()
{
    if(!IsCacheExists()){ //没有就新建

    }else{ // 如果有的话，检查 _cache_meta
        if(_cache_meta.url == ""){
            RestoreCacheMeta(); //复原Meta对象
        }
    }
    return false;
}

bool PagerSpider::SaveCacheData(std::vector<wxString> data, uint8_t depth) //都是链接
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



bool PagerSpider::RestoreCacheMeta()
{
    wxTextFile file(GetCacheMetaFile());
    wxString line = file.GetNextLine();
    do{
        if(line[0] == '%'&&line[1]=='%'){
            wxString global = line.Mid(2);
            if(global == "girls"){

            }else if(global == "dest_dir"){

            }
        }else if(line[0] =='+'&&line[1]=='+'){//
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
                    std::vector<wxString> parts = Split(line,wxT(","));
                    RegexRule rule;
                    long type;
                    long depth;
                    parts[0].ToLong(&type);
                    parts[1].ToLong(&depth);
                    rule.type = (uint8_t)type;
                    rule.depth = (uint8_t)depth;
                    rule.rule = parts[2];
                    item.regex_rules.push_back(rule);
                }while(line[0]!=':'&&line[1]!=':');
            }
            meta_name = ParseMetaLine(line,"::");
            if(meta_name == "cache_data"){
                line = file.GetNextLine();
                std::vector<wxString> parts = Split(line,"|");
                std::vector<wxString>::const_iterator it;
                for(it=parts.begin(); it!=parts.end(); ++it){
                    std::vector<wxString> m = Split(*it,",");
                    Chunk chunk;
                    long start;long end;
                    m[0].ToLong(&start);
                    m[1].ToLong(&end);
                    chunk.start = (uint32_t)start;
                    chunk.end = (uint32_t)end;
                    item.chunks.push_back(chunk);
                }
            }
            _cache_items.push_back(item);
        }
        line = file.GetNextLine();
    }while(!file.Eof());
    return true;
}

std::vector<wxString> PagerSpider::Split(wxString line,wxString seperator)
{
    size_t nLine = line.length();
    std::vector<wxString> parts;
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
        throw "unrecognized meta line";
    }
    if(line.Mid(0,nPrefix) == prefix){
        return line.Mid(nPrefix).Trim();
    }else{
        throw "meta line parse error.";
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

wxString PagerSpider::GetCacheMetaFile()
{
    return GetCacheDir()+"cache.meta."+CACHE_SUFFIX;
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

std::vector<wxString> PagerSpider::GetCache(uint8_t depth) //获取缓存文件中保存的列表目录中的数据
{
    std::vector<wxString> data;
    return data;
}


size_t PagerSpider::GetTotalImageCount() //获取所有图片总数
{
    return _totalImageCount;
}

size_t PagerSpider::GetDownloadImageCount()
{
    return _downloadedImageCount;
}
