#pragma once

#define TO_UINT16 static_cast<unsigned short>

// request level -> give's context -> play!

enum sv2cl_t
{
	SV2CL_WELCOME,
	SV2CL_CONTEXT,
	SV2CL_REQUEST_STAGE,
	SV2CL_COMMANDS,
};

enum cl2sv_t
{
	CL2SV_REQUEST_LEVEL,
	CL2SV_STAGE_INFO,
	CL2SV_COMMANDS
};