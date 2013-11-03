#ifndef  __CHATMSGMANAGER_H__
#define  __CHATMSGMANAGER_H__

#include <string>

class Direct_Manager;

namespace ChatMsg_Manager
{
	void CreateInstance();
	void DestroyInstance();
	
	void PushMessage(const char * msg);
	void PushMessage(const wchar_t * wmsg);
	void PushMessage(const std::string & str);
	void PushMessage(const std::wstring & wstr);

	void UpdateLoop();
	bool DrawLoop();
};

#endif