#include "main.h"
#include <cstdint>
 

struct STRUCT_POSITION
{
	uint16_t X;
	uint16_t Y;
};
struct STRUCT_SCORE_7556
{
	uint16_t Level;
	uint16_t Defense;
	uint16_t Attack;

	struct
	{
		uint8_t Merchant;
	} Merchant;
	struct
	{
		uint8_t Speed;
	} Move;//AttackRun

	uint16_t maxHP, maxMP;
	uint16_t curHP, curMP;

	uint16_t STR, INT;
	uint16_t DEX, CON;

	uint8_t Masteries[4];//Special
};

struct STRUCT_MOB_7556
{

	char Name[16];
	uint8_t CapeInfo;

	struct
	{
		uint8_t Merchant : 6;
		uint8_t CityID : 2;
	} Info;

	uint16_t GuildIndex;
	uint8_t ClassInfo;

	uint8_t AffectInfo;

	uint16_t QuestInfo;

	int32_t Gold;
	uint32_t Exp;

	STRUCT_POSITION LastPosition;

	STRUCT_SCORE_7556 BaseStatus;
	STRUCT_SCORE_7556 CurrentStatus;

	STRUCT_ITEM Equip[16];
	STRUCT_ITEM Inventory[64];

	uint32_t Learn;

	uint16_t
		StatusPoint,
		MasterPoint,
		SkillPoint;

	uint8_t Critical;
	uint8_t SaveMana;

	char SkillBar[4];

	char GuildMemberType;
	uint8_t MagicIncrement;

	uint8_t
		RegenHP,
		RegenMP;

	uint8_t
		Resists[4];
 
 
};

struct STRUCT_SCORE_759
{
	int Level;	 // The mob's level
	int Ac;		 // The mob's defense
	int Damage;   // The mob's damage force

	unsigned char  Merchant; // UNK
	unsigned char  AttackRun; // The mob's speed
	unsigned char  Direction;
	unsigned char  ChaosRate;

	int MaxHp;     // The max HP the mob can have
	int MaxMp;	  // The max MP the mob can have
	int Hp;		  // The current HP of the mob
	int Mp;		  // The current MP of the mob





	short		   Str;		  // The mob's strength points, affects it's attack power
	short		   Int;		  // The mob's intelligence points, affects it's skill attack powers and MP
	short		   Dex;		  // The mob's dexterity points, affects it's attack speed
	short		   Con;       // The mob's constitution points, affects it's HP

	short  Special[4]; // The mob's special points, affects it's skill tiers
};

struct STRUCT_MOB_759
{
	char		   MobName[NAME_LENGTH];	  // The name of the mob
	char		   Clan;		  // The clan the mob belongs to
	unsigned char  Merchant;	  // The mob's merchant ID
	unsigned short Guild;		  // The ID of the guild the mob belongs to
	unsigned char  Class;		  // The mobs class
	unsigned short  Rsv;
	unsigned char Quest;

	int			   Coin;		  // The ammount of coins the mob has

	long long   Exp;			  // The ammount of experience the mob has to level up

	short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll
	short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll

	STRUCT_SCORE   BaseScore;    // The base score of the mob 
	STRUCT_SCORE   CurrentScore; // The score the mob actually has

	STRUCT_ITEM    Equip[MAX_EQUIP];	 // The items the mob is wearing

	STRUCT_ITEM	   Carry[MAX_CARRY];	 // The items the mob is carrying


	long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)

	unsigned int Magic;

	unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
	unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
	unsigned short SkillBonus;	 // The points the mob can use to buy skills

	unsigned char  Critical;	 // The chance the mob has to deliver critical hits
	unsigned char  SaveMana;	 // Uknown use, nomenclature of variable is correct to all current standards

	unsigned char  SkillBar[4];  // The skills saved on the first 4 slots of the skill bar

	unsigned char  GuildLevel;   // The mob's guuld level, used to define if it's a guild member or leader

	unsigned short  RegenHP;		 // UNK
	unsigned short  RegenMP;		 // UNK

	char  Resist[4];	 // The mob's resistencies, to fire / ice / thunder / magic


};
 
char*  StringFormat(const char* str, ...)
{
	static char buffer[2048] = { 0, };
	va_list va;
	va_start(va, str);
	vsprintf_s(buffer, str, va);
	va_end(va);
	return buffer;
}

void ReadMobInDir( char* fileName)
{
	 
	
	STRUCT_MOB_7556 mob = STRUCT_MOB_7556();

	FILE* fp;
	fp = fopen(StringFormat("./npc/%s", fileName), "rb");
	int tsum;
	if (fp == NULL)
	{
		 
		return;
	}
	fread((char*)&mob, sizeof(STRUCT_MOB_7556), 1, fp);
	fclose(fp);



	STRUCT_MOB_759  MobToSave =   STRUCT_MOB_759();

	
	printf(StringFormat("./npc/%s\n", mob.Name));
 

	//MOBNAME
	strcpy(MobToSave.MobName, mob.Name);
	//OTHERINFOS
	MobToSave.Clan = mob.CapeInfo;
	MobToSave.Merchant = mob.Info.Merchant;
	MobToSave.Guild = mob.GuildIndex;
	MobToSave.Class = mob.ClassInfo;
	//MobToSave.Rsv = mob.Rsv;
	MobToSave.Quest = mob.QuestInfo;
	MobToSave.Coin = mob.Gold;
	MobToSave.Exp = mob.Exp;
	MobToSave.SPX = mob.LastPosition.X;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll
	MobToSave.SPY = mob.LastPosition.Y;		 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll

	MobToSave.LearnedSkill = mob.Learn;// The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)
	//MobToSave.LearnedSkill = 0; // The new skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)

	MobToSave.ScoreBonus = mob.StatusPoint;   // The points the mob can use to increase score (Str, Int, Dex, Con)
	MobToSave.SpecialBonus = mob.MasterPoint; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
	MobToSave.SkillBonus = mob.SkillPoint;	 // The points the mob can use to buy skills

	MobToSave.Critical = mob.Critical;	 // The chance the mob has to deliver critical hits
	MobToSave.SaveMana = mob.SaveMana;	 // Uknown use, nomenclature of variable is correct to all current standards

	  // The skills saved on the first 4 slots of the skill bar

	MobToSave.GuildLevel = mob.GuildMemberType;   // The mob's guuld level, used to define if it's a guild member or leader


	//MobToSave.UNK_1 = 0;

	MobToSave.RegenHP = mob.RegenHP;		 // UNK
	MobToSave.RegenMP = mob.RegenMP;		 // UNK


	//BASESCORE
	MobToSave.BaseScore.Level = mob.BaseStatus.Level;    // The mob's level
	MobToSave.BaseScore.Ac = mob.BaseStatus.Defense;     // The mob's defense
	MobToSave.BaseScore.Damage = mob.BaseStatus.Attack;  // The mob's damage force
	MobToSave.BaseScore.Merchant = mob.BaseStatus.Merchant.Merchant; // UNK
	MobToSave.BaseScore.AttackRun = mob.BaseStatus.Move.Speed;// The mob's speed
	MobToSave.BaseScore.RegenHP = 0;
	MobToSave.BaseScore.RegenMP = 0;
	MobToSave.BaseScore.MaxHp = mob.BaseStatus.maxHP;    // The max HP the mob can have
	MobToSave.BaseScore.MaxMp = mob.BaseStatus.maxMP;     // The max MP the mob can have
	MobToSave.BaseScore.Hp = mob.BaseStatus.curHP;    // The current HP of the mob
	MobToSave.BaseScore.Mp = mob.BaseStatus.curMP;       // The current MP of the mob
	MobToSave.BaseScore.Str = mob.BaseStatus.STR;     // The mob's strength points, affects it's attack power
	MobToSave.BaseScore.Int = mob.BaseStatus.INT;        // The mob's intelligence points, affects it's skill attack powers and MP
	MobToSave.BaseScore.Dex = mob.BaseStatus.DEX;      // The mob's dexterity points, affects it's attack speed
	MobToSave.BaseScore.Con = mob.BaseStatus.CON;   // The mob's constitution points, affects it's HP
	for (int i = 0; i < 4; i++)
		MobToSave.BaseScore.Special[i] = mob.BaseStatus.Masteries[i]; // The mob's special points, affects it's skill tiers
	//CURENT SCORE
	MobToSave.CurrentScore.Level = mob.CurrentStatus.Level;    // The mob's level
	MobToSave.CurrentScore.Ac = mob.CurrentStatus.Defense;     // The mob's defense
	MobToSave.CurrentScore.Damage = mob.CurrentStatus.Attack;  // The mob's damage force
	MobToSave.CurrentScore.Merchant = mob.CurrentStatus.Merchant.Merchant; // UNK
	MobToSave.CurrentScore.AttackRun = mob.CurrentStatus.Move.Speed;// The mob's speed
	MobToSave.CurrentScore.RegenHP = 0;
	MobToSave.CurrentScore.RegenMP = 0;
	MobToSave.CurrentScore.MaxHp = mob.CurrentStatus.maxHP;    // The max HP the mob can have
	MobToSave.CurrentScore.MaxMp = mob.CurrentStatus.maxMP;     // The max MP the mob can have
	MobToSave.CurrentScore.Hp = mob.CurrentStatus.curHP;    // The current HP of the mob
	MobToSave.CurrentScore.Mp = mob.CurrentStatus.curMP;       // The current MP of the mob
	MobToSave.CurrentScore.Str = mob.CurrentStatus.STR;     // The mob's strength points, affects it's attack power
	MobToSave.CurrentScore.Int = mob.CurrentStatus.INT;        // The mob's intelligence points, affects it's skill attack powers and MP
	MobToSave.CurrentScore.Dex = mob.CurrentStatus.DEX;      // The mob's dexterity points, affects it's attack speed
	MobToSave.CurrentScore.Con = mob.CurrentStatus.CON;   // The mob's constitution points, affects it's HP
	for (int i = 0; i < 4; i++)
	{
		MobToSave.CurrentScore.Special[i] = mob.CurrentStatus.Masteries[i]; // The mob's special points, affects it's skill tiers
		MobToSave.SkillBar[i] = mob.SkillBar[i];
	}
	//EQUIPAMENTS
	for (int i = 0; i < 16; i++)
		MobToSave.Equip[i] = mob.Equip[i];
	//CARRY
	for (int i = 0; i < 64; i++)
		MobToSave.Carry[i] = mob.Inventory[i];


	FILE* fs = nullptr;
	fopen_s(&fs, StringFormat("./convertidos/%s", fileName), "wb");
	if (fs == nullptr)
		return;



	fwrite((char*)&MobToSave, 1, sizeof(STRUCT_MOB_759), fs);
	fclose(fs);
	 
	 
}


void list_dir(const char* path) {
	struct dirent* entry;
	DIR* dir = opendir(path);

	if (dir == NULL) {
		return;
	}
	while ((entry = readdir(dir)) != NULL) {

		if (!strncmp(entry->d_name, ".", 1))
			continue;

		
		ReadMobInDir(entry->d_name);
	}
	closedir(dir);
}


int main()
{

	_wmkdir(L"./convertidos");
	list_dir("./npc/");

	return 1;
}