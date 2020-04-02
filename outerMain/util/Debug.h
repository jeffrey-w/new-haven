#pragma once

#ifndef _DEBUG
#define _DEBUG
#endif // _DEGUG


#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

