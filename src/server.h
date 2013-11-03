#ifndef __SERVER_H__
#define __SERVER_H__

#include "stages.h"
#include <functional>

namespace Server
{
	void Start(SPECIAL_STAGE * stages16, std::function<void()> callback);
	void End();
};

#endif