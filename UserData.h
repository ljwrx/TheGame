
#ifndef __USER__DATA__
#define __USER__DATA__

class UserData
{
public:
	~UserData();

	inline unsigned int getMapData(void){ return _mapData; }
	inline unsigned int getSSelData(void){ return _s_sel_data; }
	inline unsigned int getISelData(void){ return _i_sel_data; }
	inline unsigned int getLevelDataFromMapIndex(int mapIndex){ return *(_levelData + mapIndex) - 'a'; }

	static UserData* getInstance(void);

private:
	UserData(void);
	void init(void);

private:
	static UserData* _userData;

private:
	unsigned int _mapData;
	unsigned int _s_sel_data;
	unsigned int _i_sel_data;
	unsigned char* _levelData;
};

#endif