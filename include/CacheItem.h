#ifndef CACHEITEM_H
#define CACHEITEM_H

#include <vector>
#include <wx/string.h>

class RegexRule
{
public:
    uint8_t type;
    uint8_t depth;
    wxString rule;
};

class Chunk
{
public:
    uint32_t start;
    uint32_t end;
};

class CacheItem
{
    public:
    wxString url;
    wxString girl;
    std::vector<RegexRule> regex_rules;
    std::vector<Chunk> chunks;
};

#endif // CACHEITEM_H
