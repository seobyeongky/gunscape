#ifndef __STRINGCONVERT__H__
#define __STRINGCONVERT__H__

#include <string>

void multi2uni(const std::string & src, std::wstring * dest);
void uni2multi(const std::wstring & src, std::string * dest);

#endif