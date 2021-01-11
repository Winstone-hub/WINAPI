#pragma once

#define WINSIZEX  1280
#define WINSIZEY  720


extern HWND g_hWnd;




const DWORD KEY_UP				= 0x00001;			// 00000001
const DWORD KEY_DOWN		= 0x00002;			// 00000010
const DWORD KEY_LEFT			= 0x00004;			// 00000100
const DWORD KEY_RIGHT		= 0x00008;			// 00001000
const DWORD KEY_SPACE		= 0x00010;			// 00010000
const DWORD KEY_RETURN	= 0x00020;			// 00100000
const DWORD KEY_MENU		= 0x00040;			// 01000000



//		 00000001
//	|	 00000100
//------------------
//       00000101
//	&	 00000001
//------------------
//		 00000001



//       00000101
//	&	 00000100
//------------------
//		 00000100


// 00000100
// 00001000
// 00010000
// 00100000
// 01000000









