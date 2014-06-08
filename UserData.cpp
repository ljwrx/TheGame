#include "UserData.h"
#include "cocos2d.h"

#define USER_DATA_ORIGINAL	""
#define USER_DATA_FILE_NAME "save\\data.txt"

#define MAP_DATA_INDEX		0
#define S_SELECT_INDEX		1
#define I_SELECT_INDEX		2
#define LEVEL_DATA_INDEX	3

using cocos2d::Array;
using cocos2d::String;
using cocos2d::FileUtils;

UserData* UserData::_userData = nullptr;

UserData::UserData()
	:	_mapData(0),
	_s_sel_data(0),
	_i_sel_data(0)
{
	_levelData = nullptr;
}

UserData::~UserData()
{
}

UserData* UserData::getInstance(void)
{
	if (!_userData)
	{
		_userData = new UserData();
		_userData->init();
	}
	return _userData;
}

void UserData::init(void)
{
	String str = FileUtils::getInstance()->getStringFromFile(USER_DATA_FILE_NAME);
	auto arr = str.componentsSeparatedByString("-");
	_mapData = ((String*)arr->objectAtIndex(MAP_DATA_INDEX))->intValue();
	_s_sel_data = ((String*)arr->objectAtIndex(S_SELECT_INDEX))->intValue();
	_i_sel_data = ((String*)arr->objectAtIndex(I_SELECT_INDEX))->intValue();

	String* data  = ((String*)arr->objectAtIndex(LEVEL_DATA_INDEX));
	_levelData = (unsigned char*)malloc(data->length()*8);
	memcpy(_levelData, data->getCString(), data->length()*8);
}