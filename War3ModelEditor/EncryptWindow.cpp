//+-----------------------------------------------------------------------------
//| Included files
//+-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "EncryptWindow.h"
//#include <sys/types.h>
//#include <dirent.h>


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
	
	WINDOW_BUTTON_INFO ButtonInfo;

	ButtonInfo.Parent = Window;
	ButtonInfo.Text = "选择文件夹";
	ButtonInfo.X = 10;
	ButtonInfo.Y = 10;
	ButtonInfo.Width = 80;
	ButtonInfo.Height = 26;
	ButtonInfo.ButtonType = BUTTON_TYPE_PUSHBUTTON;

	if (!SelectButton.Create(ButtonInfo)) return FALSE;

	WINDOW_EDIT_INFO EditInfo;

	EditInfo.Parent = Window;
	EditInfo.Text = "C:\\";
	EditInfo.X = 100;
	EditInfo.Y = 10;
	EditInfo.Width = 390;
	EditInfo.Height = 26;
	//EditInfo.ReadOnly = TRUE;

	if (!PathEdit.Create(EditInfo)) return FALSE;

	WINDOW_TREEVIEW_INFO TreeInfo;

	TreeInfo.Parent = Window;
	TreeInfo.X = 10;
	TreeInfo.Y = 46;
	TreeInfo.Width = 200;
	TreeInfo.Height = 300;

	if (!FolderTree.Create(TreeInfo)) return FALSE;
	
	Icon.AssignIconListToTreeView(FolderTree.GetWindow());
	//FolderTree.SetDimension(GetWidth(), GetHeight());

	//RegisterHotKey(Window, 1, MOD_NOREPEAT, 'S');

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
		CHAR Buffer[MAX_PATH];
		BROWSEINFO bi;
		ZeroMemory(&bi, sizeof(BROWSEINFO));
		bi.hwndOwner = NULL;
		bi.pszDisplayName = Buffer;
		bi.lpszTitle = "选择文件夹目录:";
		bi.ulFlags = BIF_RETURNFSANCESTORS;
		LPITEMIDLIST idl = SHBrowseForFolder(&bi);

		if (idl == NULL) return 0;

		SHGetPathFromIDList(idl, Buffer);
		FolderPath = Buffer;
		SetText("当前路径：" + FolderPath);
		OpenFolder(FolderPath);
		//PathEdit.SetText(Buffer);
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

BOOL ENC_WINDOW::OpenFolder(CONST std::string& path)
{
	CloseFolder();

	using namespace std;
	HANDLE hFind;
	WIN32_FIND_DATA findData;
	LARGE_INTEGER size;
	hFind = FindFirstFile((path+"\\*.*").c_str(), &findData);
	CHAR Buffer[MAX_PATH];

	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to find first file!\n";
		return FALSE;
	}
	do
	{
		// 忽略"."和".."两个结果 
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;
		//过滤不支持的文件名
		_splitpath(findData.cFileName, NULL, NULL, NULL, Buffer);
		strlwr(Buffer);
		if (Buffer != "mdx" && Buffer != "blp" && Buffer != "tga")
			continue;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
		{
			cout << findData.cFileName << "\t<dir>\n";
		}
		else
		{
			size.LowPart = findData.nFileSizeLow;
			size.HighPart = findData.nFileSizeHigh;
			cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";
		}
	} while (FindNextFile(hFind, &findData));
	cout << "Done!\n";

	//if (!LoadListFile(path)) return FALSE;
	return TRUE;
}

VOID ENC_WINDOW::CloseFolder()
{

}

VOID ENC_WINDOW::UpdateTreeView()
{

}

BOOL ENC_WINDOW::LoadListFile(CONST std::string& path)
{
	std::string Name;
	std::ifstream File;
	std::string ListFileName;
	BOOL UseCustomListFile = TRUE;
	std::list<std::string> FileList;
	std::list<std::string>::iterator i;

	Filter.BuildFilter(RootNode.FilterData, "");
	ListFileName = Common.GetProgramDirectory() + "\\" + PATH_LIST_FILES + Common.GetName(path) + ".txt";

	File.open(ListFileName.c_str(), std::ios::in);
	if (File.fail()) UseCustomListFile = FALSE;

	if (UseCustomListFile)
	{
		while (!File.eof())
		{
			Name = "";
			std::getline(File, Name);

			Common.RemoveWhiteSpace(Name);
			if (Name != "")
			{
				//if (!AddFileToFileTree(Name)) return FALSE;
			}
		}
	}/*
	else
	{
		Mpq.GetFileList(FileList);

		i = FileList.begin();
		while (i != FileList.end())
		{
			Name = (*i);

			Common.RemoveWhiteSpace(Name);
			if (Name != "")
			{
				if (!AddFileToFileTree(Name)) return FALSE;
			}

			i++;
		}
	}*/

	return TRUE;
}

BOOL ENC_WINDOW::AddFileToFileTree(CONST std::string& FileName)
{
	std::string Name;
	std::list<std::string> PathList;
	std::list<std::string>::iterator i;
	FILE_NODE* NewNode;
	FILE_NODE* CurrentNode;

	MPQ_WINDOW::SplitPath(FileName, Name, PathList);

	CurrentNode = &RootNode;

	i = PathList.begin();
	while (i != PathList.end())
	{
		//CurrentNode = CreateFolder(CurrentNode, (*i));
		if (CurrentNode == NULL)
		{
			Error.SetMessage("Unable to add \"" + FileName + "\" to the treeview!");
			return FALSE;
		}

		i++;
	}

	NewNode = new FILE_NODE();
	if (NewNode == NULL)
	{
		Error.SetMessage("Unable to add \"" + FileName + "\" to the treeview, memory allocation failed!");
		return FALSE;
	}

	NewNode->FileNameAndPath = FileName;
	NewNode->FileName = Name;
	NewNode->Extention = Common.LowerCase(Common.GetExtention(Name));

	if (NewNode->FileName == PATH_LISTFILE) NewNode->Extention = "txt";

	//AddChild(CurrentNode, &CurrentNode->FileConnection, NewNode);

	Filter.BuildFilter(NewNode->FilterData, NewNode->Extention);
	//UpdateFilterData(NewNode, NewNode->FilterData);

	return TRUE;
}