#include "VectorManager.h"
#include "ParticalSystem.h"
#include "../BaseClass/BaseActionSprite.h"

USING_NS_CC;


#define AttributeCategory ParticalSys::AttributeCategory

VectorManager::VectorManager(void)
{
	_particalSystem = nullptr;
}

VectorManager::~VectorManager(void)
{
}

BaseActionSprite* VectorManager::createCPUByIndex(int index)
{
	if (index >= _cDataList.size())
	{
		CCLOG("index >= _cDataList.size(),the index over the Vector size in createCPU");
		return nullptr;
	}
	auto data = _cDataList.at(index);
	auto temp = BaseActionSprite::createWithIndex(index, data.getDataId(), data.getMoveSpeed(), data.getAttackSpeed(), data.getMaxHealth(), BaseActionSpriteKind::Enemy, this);
	if (!temp)
		CCLOG("BaseActionSprite create false in createCPU");
	else
		_cList.pushBack(temp);
	return temp;
}

BaseActionSprite* VectorManager::createPlayerByIndex(int index)
{
	if (index >= _pDataList.size())
	{
		CCLOG("index >= _pDataList.size(),the index over the Vector size in createPlayer");
		return nullptr;
	}
	auto data = _cDataList.at(index);
	BaseActionSprite* temp = nullptr;
	switch (data.getAttackStyle())
	{
	case ParticalSys::InfantryNormal:
	case ParticalSys::InfantryActive:
	case ParticalSys::InfantryCritical:
		temp = BaseActionSprite::createWithIndex(index, data.getDataId(), data.getMoveSpeed(), data.getAttackSpeed(), data.getMaxHealth(), BaseActionSpriteKind::Fighter, this);
		break;
	case ParticalSys::ArcherNormal:
	case ParticalSys::ArcherActive:
	case ParticalSys::WorlockNormal:
	case ParticalSys::WorlockSpecial1:
	case ParticalSys::WorlockSpecial2:
	case ParticalSys::WorlockSpecial3:
		temp = BaseActionSprite::createWithIndex(index, data.getDataId(), data.getMoveSpeed(), data.getAttackSpeed(), data.getMaxHealth(), BaseActionSpriteKind::Range, this);
		break;
	default:
		break;
	}
	if (!temp)
		CCLOG("BaseActionSprite create false in createPlayer");
	else
		_pList.pushBack(temp);
	return temp;
}

void VectorManager::setParicalSystem(ParticalSys* sys)
{
	if (_particalSystem)
		_particalSystem->release();
	_particalSystem = sys;
	_particalSystem->retain();
}

void VectorManager::pushToWaitList(BaseActionSprite* bs)
{
	if (!bs)
		CCLOG("error in pushToWaitList(VectorManager):bs is nullptr");
	else
		_waitList.pushBack(bs);
}

void VectorManager::pushToAttackList(BaseActionSprite* bs)
{
	if (!bs)
		CCLOG("error in pushToAttackList(VectorManager):bs is nullptr");
	else
		_attackList.pushBack(bs);
}

void VectorManager::onExit(void)
{
	_iList.reverse();
	_pList.reverse();
	_cList.reverse();
	if (_particalSystem)
		_particalSystem->release();
	_particalSystem = nullptr;
}

void VectorManager::_checkWaitList()
{
	auto itor = _waitList.begin();
	Vector<BaseActionSprite*>* checkList = nullptr;
	while (itor != _waitList.end())
	{
		Rect rect = (*itor)->getBoundingBox();

		if ((*itor)->getKind() & BaseActionSpriteKind::Soldier)
			checkList = &_cList;

		else if ((*itor)->getKind() & BaseActionSpriteKind::Enemy)
		{
			for (auto node : _iList)
			{
				if (rect.intersectsRect(node->getBoundingBox()))
				{
					(*itor)->setNowAction(BaseActionSpriteAction::Attack);
					itor = _waitList.erase(itor);
					continue;
				}//if rect.interesectsRect
			}//for node:_iList
		}//else if Enmy

		for (auto node : *checkList)
		{
			if (rect.intersectsRect(node->getBoundingBox()))
			{
				(*itor)->setNowAction(BaseActionSpriteAction::Attack);
				itor = _waitList.erase(itor);
				continue;
			}
		}

		++itor;

	}//while itor != end
}

void VectorManager::_attackCheckAndHit(int attack ,BaseActionSprite* attacker, Vector<BaseActionSprite*>*checkList)
{
	Rect rect = attacker->getBoundingBox();
	auto node = checkList->begin();
	while (node != checkList->end())
	{
		if (rect.intersectsRect((*node)->getBoundingBox()))
		{
			int nowHp = (*node)->getNowHp() - attack;
			if (nowHp <= 0)
			{
				(*node)->setNowAction(BaseActionSpriteAction::Death);
				node = checkList->erase(node);
			}//hp <= 0
			else
			{
				(*node)->setNowHp(nowHp);
				++node;
			}
			break;
		}//AABB return true
	}//
}

void VectorManager::_checkAttackList()
{
	BaseActionSprite* node = nullptr;
	while (!_attackList.empty())
	{
		node = _attackList.back();

		_attackList.popBack();
	}
}

void VectorManager::updata(float dt)
{
	_checkWaitList();
	_checkAttackList();
}