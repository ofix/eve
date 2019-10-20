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
        std::vector<wxString> GetCache(uint8_t depth); //��ȡ�����ļ��б�����б�Ŀ¼�е�����
        bool SaveCache(std::vector<wxString> data, uint8_t depth); //��������
        uint32_t GetTotalImageCount(); //��ȡ����ͼƬ����
        bool SaveAccessLog(wxString url); //������ʵ���־
    private:
        wxString _url; //���ʵ�URL
        uint8_t _depth; //�б�㼶�����
        wxString _destDir; //����ͼƬ��Ŀ¼
        wxString _cacheDir; //�����ļ���Ŀ¼
        wxString _accessDir; //���������־
        bool _bCache; //�Ƿ񻺴�����
        std::vector<wxString> _regexRules; //������ʽ
        std::vector<wxString> _failUrl; //����ʧ�ܵ�URL
        //������ͳ������
        uint32_t _totalImageCount; //���ص�����ͼƬ����
        bool _allowRepeat; //�Ƿ���ҪͼƬȥ��
};

#endif // PAGERSPIDER_H
