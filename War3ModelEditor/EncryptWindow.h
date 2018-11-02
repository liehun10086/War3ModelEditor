//+-----------------------------------------------------------------------------
//| Inclusion guard
//+-----------------------------------------------------------------------------
#ifndef MAGOS_ENC_WINDOW_H
#define MAGOS_ENC_WINDOW_H


//+-----------------------------------------------------------------------------
//| Included files
//+-----------------------------------------------------------------------------
#include "MainWindow.h"
#include "MpqWindow.h"

//+-----------------------------------------------------------------------------
//| Mpq window class
//+-----------------------------------------------------------------------------
class ENC_WINDOW : public WINDOW_FRAME
{
public:
	CONSTRUCTOR ENC_WINDOW();
	DESTRUCTOR ~ENC_WINDOW();

	virtual BOOL Create();
	virtual VOID Destroy();

	virtual LRESULT MessageHandler(UINT Message, WPARAM W, LPARAM L);
	virtual LRESULT MenuHandler(WORD MenuItem);
	virtual LRESULT ControlHandler(HWND Control, WORD Code);
	virtual LRESULT NotifyHandler(HWND Control, UINT Code, NMHDR* Header);

	BOOL OpenFolder(const std::string & path);

protected:
	WINDOW_BUTTON SelectButton;
	WINDOW_EDIT PathEdit;
	WINDOW_TREEVIEW FolderTree;

	FILE_NODE RootNode;
	FILE_NODE* CurrentlySelectedFile;
	FILE_NODE* CurrentlySelectedPopupFile;

	BOOL FolderLoaded;
	std::string FolderPath;

	VOID CloseFolder();

	VOID UpdateTreeView();

	BOOL LoadListFile(const std::string & path);

	BOOL AddFileToFileTree(const std::string & FileName);

};

//+-----------------------------------------------------------------------------
//| Global objects
//+-----------------------------------------------------------------------------
extern ENC_WINDOW EncryptWindow;

//+-----------------------------------------------------------------------------
//| End of inclusion guard
//+-----------------------------------------------------------------------------
#endif
