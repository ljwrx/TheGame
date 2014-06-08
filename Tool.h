
#ifndef __GAME__TOOL__
#define __GAME__TOOL__

#include "cocos2d.h"


#define PI							3.1415926f
#define InRadians360				6.2831853f
#define InAngle360					360.0f
#define InAngleHalf360				180.0f

namespace TOOL
{
	///////////////////////////////////////////////////////////////////////////////
	//////////////		字节操作函数		//////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//对num中特定字节进行更改
	//num	元数据
	//index	需要获取的位置
	inline int GetBinNum(unsigned int num, int index)
	{
		return (num >> (index - 1)) & 1;
	}

	//获取num中特定字节的数据
	//num	元数据
	//index 需要更改的字节位置
	//flag	更改的数据
	inline void SetBinNum(unsigned int& num, int index, int flag)
	{
		--index;
		num = (num&~(1 << index)) | (flag << index);
	}

	
	//获取8位字节数据
	//num	元数据
	//index	需要获取的数据所在的组
	//num以8位为一组,即一组为一个0x000000FF
	inline int GetHexNum(unsigned int num, int index)
	{
		return (num >> (8 * (index - 1))) & 0x000000FF;
	}

	//设置8位字节数据
	//num	元数据
	//index 需要获取的数据所在的组
	//flag	更改的数据
	//num以8位为一组,即一组为一个0x000000FF
	inline void SetHexNum(unsigned int& num, int index, int flag)
	{
		--index;
		num = (num&~(0x000000FF << index)) | (flag << 8 * index);
	}


	//获取高16位数据
	inline int GetHigData(unsigned int num)
	{
		return num >> 16;
	}

	//num	需要更改的数据
	//data	修改的数据
	//设置高16位数据
	inline void SetHigData(unsigned int& num, int data)
	{
		num = (num & 0x0000FFFF) | (data << 16);
	}

	//num	需要更改的数据
	//data	修改的数据
	//设置低16位数据
	inline void SetLowData(unsigned int& num, int data)
	{
		num = (num & 0xFFFF0000) | (data & 0x0000FFFF);
	}

	//获取低16位数据
	inline int GetLowData(unsigned int num)
	{
		return num & 0x0000FFFF;
	}

	//获取任意位数字节数据
	inline unsigned int GetDataFromSize(unsigned int sor, int size, int begin = 0)
	{
		unsigned int mask = 0xFFFFFFFF;
		mask = ~(mask << size);
		mask = mask << begin;
		return (sor&mask) >> begin;
	}


	//设置任意位数字节数据
	inline void SetDataFromSize(unsigned int& sor, unsigned int data, int size, int begin = 0)
	{
		unsigned int mask = 0xFFFFFFFF;
		mask = ~(mask << size);
		mask = ~(mask << begin);
		sor = sor&mask | ((data << begin)&mask);
	}





	template <class T>
	inline T* GetDataFromFile(char* fileName, int *size)
	{
		return (T*)(cocos2d::FileUtils::getInstance()->getFileData(fileName, "rb", size));
	}

	template <class T>
	inline void GetDataFromFile(char* fileName, T* data, int size)
	{
		unsigned char* ch = (unsigned char*)data;
		FILE *f = fopen(fileName, "wb");
		if (!fp)
			break;
		fwrite(ch, sizeof(T), size / sizeof(T), fp);
	}


	//卡马克的开平方算法
	inline float kamake_sqr(float number)
	{
		long i;
		float x, y;
		const float f = 1.5F;
		x = number * 0.5F;
		y = number;
		i = *(long *)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float *)&i;
		y = y * (f - (x * y * y));
		y = y * (f - (x * y * y));
		return number * y;
	}

	//两点间距离
	inline float PointToPoint(cocos2d::Point p1, cocos2d::Point p2)
	{
		float dx = p1.x - p2.x;
		float dy = p1.y - p2.y;
		return kamake_sqr(dx*dx + dy*dy);
	}

	//两点间距离
	inline float PointToPoint(float x1, float y1, float x2, float y2)
	{
		float dx = x1 - x2;
		float dy = y1 - y2;
		return kamake_sqr(dx*dx + dy*dy);
	}


	//加密
	template<class T>
	T Lock(T data)
	{
		return data;
	}

	//解密
	template<class T>
	T Unlock(T data)
	{
		return data;
	}

	

};


#endif