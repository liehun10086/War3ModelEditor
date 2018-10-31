//+-----------------------------------------------------------------------------
//| Included files
//+-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "ModelLight.h"


//+-----------------------------------------------------------------------------
//| Constructor
//+-----------------------------------------------------------------------------
MODEL_LIGHT::MODEL_LIGHT()
{
	ModelBaseData = &LightData;
	ModelBaseData->Type = NODE_TYPE_LIGHT;
}


//+-----------------------------------------------------------------------------
//| Destructor
//+-----------------------------------------------------------------------------
MODEL_LIGHT::~MODEL_LIGHT()
{
	Clear();
}


//+-----------------------------------------------------------------------------
//| Clears the light
//+-----------------------------------------------------------------------------
VOID MODEL_LIGHT::Clear()
{
	LightData = MODEL_LIGHT_DATA();
}


//+-----------------------------------------------------------------------------
//| Returns the mdx size of the light
//+-----------------------------------------------------------------------------
INT MODEL_LIGHT::GetSize()
{
	return GetBaseSize() + LightData.Visibility.GetSize() + LightData.Intensity.GetSize() + 48;
}


//+-----------------------------------------------------------------------------
//| Returns a reference to the data
//+-----------------------------------------------------------------------------
MODEL_LIGHT_DATA& MODEL_LIGHT::Data()
{
	return LightData;
}
