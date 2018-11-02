//+-----------------------------------------------------------------------------
//| Inclusion guard
//+-----------------------------------------------------------------------------
#ifndef MAGOS_MAIN_WINDOW_H
#define MAGOS_MAIN_WINDOW_H


//+-----------------------------------------------------------------------------
//| Included files
//+-----------------------------------------------------------------------------
#include "Window.h"
#include "ResourceLoader.h"


//+-----------------------------------------------------------------------------
//| Pre-declared classes
//+-----------------------------------------------------------------------------
struct FILE_NODE;


//+-----------------------------------------------------------------------------
//| File node connection structure
//+-----------------------------------------------------------------------------
struct FILE_NODE_CONNECTION
{
	FILE_NODE_CONNECTION()
	{
		FirstChildNode = NULL;
		LastChildNode = NULL;
	}

	FILE_NODE* FirstChildNode;
	FILE_NODE* LastChildNode;
};


//+-----------------------------------------------------------------------------
//| File node structure
//+-----------------------------------------------------------------------------
struct FILE_NODE
{
	FILE_NODE()
	{
		IsFolder = FALSE;
		IconCollectionIndex = INVALID_INDEX;

		FileNameAndPath = "";
		FileName = "";
		Extention = "";

		FilterData.FilterList.resize(Filter.GetNrOfFilters(), FALSE);

		NextNode = NULL;
		PreviousNode = NULL;
		ParentNode = NULL;

		TreeViewItem = NULL;
	}

	BOOL IsFolder;
	INT IconCollectionIndex;

	std::string FileNameAndPath;
	std::string FileName;
	std::string Extention;

	FILTER_DATA FilterData;

	FILE_NODE* NextNode;
	FILE_NODE* PreviousNode;
	FILE_NODE* ParentNode;

	FILE_NODE_CONNECTION FileConnection;
	FILE_NODE_CONNECTION FolderConnection;

	HTREEITEM TreeViewItem;
};


//+-----------------------------------------------------------------------------
//| Main window class
//+-----------------------------------------------------------------------------
class MAIN_WINDOW : public WINDOW_FRAME
{
	public:
		CONSTRUCTOR MAIN_WINDOW();
		DESTRUCTOR ~MAIN_WINDOW();

		virtual BOOL Create();
		virtual VOID Destroy();

		virtual LRESULT MessageHandler(UINT Message, WPARAM W, LPARAM L);
		virtual LRESULT MenuHandler(WORD MenuItem);
		virtual LRESULT ControlHandler(HWND Control, WORD Code);
		virtual LRESULT NotifyHandler(HWND Control, UINT Code, NMHDR* Header);

		HMENU GetHistoryMenu();

		VOID UpdateAndRender(INT TimeDifference);

		BOOL ModelIsLoaded();
		VOID MakeModelUnsaved();
		VOID MakeModelNeverSaved();

		BOOL LoadByForce(CONST std::string& FileName);

		BOOL LoadFileFromBuffer(CONST std::string& FileName, BUFFER& Buffer, BOOL SkipSaveTest = FALSE);
		BOOL LoadModelFromBuffer(CONST std::string& FileName, BUFFER& Buffer);
		BOOL LoadTextureFromBuffer(CONST std::string& FileName, BUFFER& Buffer);

	protected:
		BOOL RegisterExtentions(REGISTER_INFO& RegisterInfo);

		BOOL NewFile();
		BOOL OpenFile();
		BOOL ImportFile();
		BOOL SaveFile(BOOL& Cancel, BOOL ForceNewName);
		BOOL SaveFileIfNeccessary(BOOL& Cancel);
		BOOL CloseFile(BOOL NoWindowHide = FALSE);
		BOOL NewLoadingScreen(CONST std::string& TextureFileName);

		BOOL DisplayHelp();
		BOOL CalculateExtents();
		VOID UpdateWindowStatus(BOOL NoWindowHide = FALSE);

		VOID Render(INT TimeDifference);

		GRAPHICS_WINDOW GraphicsWindow;

		BOOL ModelLoaded;
		BOOL ModelSaved;
		BOOL ModelNeverSaved;

		std::string ModelFileName;

		BOOL WindowActive;
};


//+-----------------------------------------------------------------------------
//| Global objects
//+-----------------------------------------------------------------------------
extern MAIN_WINDOW MainWindow;


//+-----------------------------------------------------------------------------
//| Post-included files
//+-----------------------------------------------------------------------------
#include "AnimationWindow.h"
#include "TextureWindow.h"
#include "ModelWindow.h"
#include "MpqWindow.h"
#include "EncryptWindow.h"
#include "NodeManagerWindow.h"
#include "CameraManagerWindow.h"
#include "GeosetManagerWindow.h"
#include "GeosetAnimationManagerWindow.h"
#include "TextureManagerWindow.h"
#include "TextureAnimationManagerWindow.h"
#include "MaterialManagerWindow.h"
#include "SequenceManagerWindow.h"
#include "GlobalSequenceManagerWindow.h"


//+-----------------------------------------------------------------------------
//| End of inclusion guard
//+-----------------------------------------------------------------------------
#endif
