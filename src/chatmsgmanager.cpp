#include "chatmsgmanager.h"
#include "d3dx_class.h"

#include <list>

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
		msg_list.push_back(chat_t(msg, tickcount));
	}

	void PushMessage(const wchar_t * wmsg)
	{
		// convert to multi-byte string
		wstring wstr(wmsg);
		string str(wstr.begin(), wstr.end());
		PushMessage(str.c_str());
	}

	void UpdateLoop()
	{
		// ������ �޽����� ����ϴ�.
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
		for (auto it = msg_list.begin(); it != msg_list.end(); ++it)
		{
			int height = direct->GetFont()->DrawTextA(NULL, it->text.c_str(), -1, NULL, DT_CALCRECT, 0xffaaaaaa);

			direct->GetFont()->DrawTextA(NULL, it->text.c_str(), -1, &rc, DT_LEFT | DT_BOTTOM, 0xffaaaaaa);
			rc.bottom -= height;
		}
		return true;
	}
}