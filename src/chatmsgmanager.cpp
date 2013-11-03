#include "chatmsgmanager.h"
#include "d3dx_class.h"
#include "stringconvert.h"

#include <list>
#include <thread>
#include <mutex>

using namespace std;

namespace ChatMsg_Manager
{
	struct chat_t
	{
		string	text;
		int		tick;

		chat_t(void) : text(), tick(0)
		{
		}

		chat_t(const string & text_, int tick_) : text(text_), tick(tick_)
		{
		}
	};

	int LEFT_SPACE = 0;
	int BOTTOM_OFFSET = 0;

	mutex msg_list_mutex;
	list<chat_t> msg_list;

	int tickcount = 0;

	void CreateInstance()
	{
		Direct_Manager * direct = Direct_Manager::GetInstance();
		LEFT_SPACE = 50;
		BOTTOM_OFFSET = static_cast<int>(direct->GetHeight() * 0.3f);
	}

	void DestroyInstance()
	{

	}

	void PushMessage(const char * msg)
	{
		unique_lock<mutex> lock(msg_list_mutex);
		msg_list.push_back(chat_t(msg, tickcount));
	}

	void PushMessage(const wchar_t * wmsg)
	{
		string dest;
		uni2multi(wmsg, &dest);
		PushMessage(dest.c_str());
	}

	void PushMessage(const string & str)
	{
		PushMessage(str.c_str());
	}

	void PushMessage(const wstring & wstr)
	{
		PushMessage(wstr.c_str());
	}

	void UpdateLoop()
	{
		// 오래된 메시지는 지웁니다.
		unique_lock<mutex> lock(msg_list_mutex);
		for(auto it = msg_list.begin(); it != msg_list.end();)
		{
			if(it->tick + 200 < tickcount)
			{
				it = msg_list.erase(it);
			}
			else break;
		}

		tickcount++;
	}

	bool DrawLoop()
	{
		Direct_Manager * direct = Direct_Manager::GetInstance();
		RECT rc={LEFT_SPACE, 0, direct->GetWidth(), direct->GetHeight() - BOTTOM_OFFSET};
		unique_lock<mutex> lock(msg_list_mutex);
		for (auto it = msg_list.begin(); it != msg_list.end(); ++it)
		{
			int height = direct->GetFont()->DrawTextA(NULL, it->text.c_str(), -1, NULL, DT_CALCRECT, 0xffaaaaaa);

			direct->GetFont()->DrawTextA(NULL, it->text.c_str(), -1, &rc, DT_LEFT | DT_BOTTOM, 0xffaaaaaa);
			rc.bottom -= height;
		}
		return true;
	}
}