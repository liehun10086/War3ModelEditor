//+-----------------------------------------------------------------------------
//| Included files
//+-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "EncryptWindow.h"


//+-----------------------------------------------------------------------------
//| Global objects
//+-----------------------------------------------------------------------------
ENC_WINDOW EncryptWindow;


//+-----------------------------------------------------------------------------
//| Constructor
//+-----------------------------------------------------------------------------
ENC_WINDOW::ENC_WINDOW()
{

}


//+-----------------------------------------------------------------------------
//| Destructor
//+-----------------------------------------------------------------------------
ENC_WINDOW::~ENC_WINDOW()
{
	//Empty
}


//+-----------------------------------------------------------------------------
//| Creates a new window
//+-----------------------------------------------------------------------------
BOOL ENC_WINDOW::Create()
{

	FrameInfo.Title = "加密";
	FrameInfo.Width = 500;
	FrameInfo.Height = 400;
	FrameInfo.Menu = ::LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(EncMenu));
	FrameInfo.Style &= (~WS_VISIBLE);
	FrameInfo.Style |= (WS_MAXIMIZEBOX | WS_SIZEBOX);

	if (!WINDOW_FRAME::Create()) return FALSE;
	/*
	WINDOW_BUTTON_INFO ButtonInfo;

	ButtonInfo.Parent = Window;
	ButtonInfo.Text = "选择文件夹";
	ButtonInfo.X = 10;
	ButtonInfo.Y = 46;
	ButtonInfo.Width = 150;
	ButtonInfo.Height = 26;
	ButtonInfo.ButtonType = BUTTON_TYPE_PUSHBUTTON;
	*/
	RegisterHotKey(Window, 1, MOD_NOREPEAT, 'S');

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Destroys the window
//+-----------------------------------------------------------------------------
VOID ENC_WINDOW::Destroy()
{
	WINDOW_FRAME::Destroy();
}


//+-----------------------------------------------------------------------------
//| Handles the window messages
//+-----------------------------------------------------------------------------
LRESULT ENC_WINDOW::MessageHandler(UINT Message, WPARAM W, LPARAM L)
{
	switch (Message)
	{
	case WM_SIZE:
	case WM_SIZING:
	{
		return 0;
	}

	case WM_CLOSE:
	{
		Hide();
		return 0;
	}

	case WM_DESTROY:
	{
		return 0;
	}

		case WM_HOTKEY:
		{
			switch (W)
			{
			case 1:
				//MessageBoxEx(Window, "test", "test", MB_ICONINFORMATION, CURRENT_LANGUAGE);
				break;
			}
			return 0;
		}
	}

	return DefWindowProc(Window, Message, W, L);
}


//+-----------------------------------------------------------------------------
//| Handles the window menu messages
//+-----------------------------------------------------------------------------
LRESULT ENC_WINDOW::MenuHandler(WORD MenuItem)
{
	return 0;
}


//+-----------------------------------------------------------------------------
//| Handles the window control messages
//+-----------------------------------------------------------------------------
LRESULT ENC_WINDOW::ControlHandler(HWND Control, WORD Code)
{
	PROPERTIES_INFO PropertiesInfo;

	if (Control == SelectButton.GetWindow())
	{
		MessageBoxEx(Window, "test", "test", MB_ICONINFORMATION, CURRENT_LANGUAGE);
	}

	return 0;
}


//+-----------------------------------------------------------------------------
//| Handles the window notify messages
//+-----------------------------------------------------------------------------
LRESULT ENC_WINDOW::NotifyHandler(HWND Control, UINT Code, NMHDR* Header)
{
	return 0;
}