#ifndef HTTPS_H
#define HTTPS_H
#include <wx/string.h>
#include <curl.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h>
#include <wx/filename.h>

size_t curl_easy_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
CURLcode Https(wxString strUrl,wxString& strResponse,wxFontEncoding enumCharSet=wxFONTENCODING_UTF8);
CURLcode DownloadFile(wxString strUrl,wxString& strSavePath);
wxString GetExeDir();
wxString GetHost(wxString url);
#endif // HTTPS_H
