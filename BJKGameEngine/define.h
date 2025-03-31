#pragma once



#define SINGLETON(type) public:\
							static type* GetInst()\
							{\
								static type inst;\
								return &inst;\
							}\
							private:\
								type();\
								~type();

#define CLONE(type) type* Clone() {return new type(*this);}
#define KEY(key, state) CKeyManager::GetInst()->GetKeyState(key) == state
#define KEY_Triggered(key) KEY(key, EKEY_STATE::Triggered)
#define KEY_Started(key) KEY(key, EKEY_STATE::Started)
#define KEY_Completed(key) KEY(key, EKEY_STATE::Completed)

#define PI 3.1415926535f

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	PROJECTILE_PLAYER,
	PROJECTILE_MONSTER,


	END = 32,
};



enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,


	END,
};


enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,


	END,
};