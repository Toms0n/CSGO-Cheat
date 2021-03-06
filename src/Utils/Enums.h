/// Enums.h
// This header defines different useful enums, structs and constants.

#pragma once
#include <cstdint>

// <code>#pragma region ...</code> only applies to VSC and some compilers might ignore it or give warnings about it
// so what this does depends on how the compiler treats it
#pragma region FLAGS 

#define IN_ATTACK					(1 << 0)
#define IN_JUMP						(1 << 1)
#define IN_DUCK						(1 << 2)
#define IN_FORWARD					(1 << 3)
#define IN_BACK						(1 << 4)
#define IN_USE						(1 << 5)
#define IN_CANCEL					(1 << 6)
#define IN_LEFT						(1 << 7)
#define IN_RIGHT					(1 << 8)
#define IN_MOVELEFT					(1 << 9)
#define IN_MOVERIGHT				(1 << 10)
#define IN_ATTACK2					(1 << 11)
#define IN_RUN						(1 << 12)
#define IN_RELOAD					(1 << 13)
#define IN_ALT1						(1 << 14)
#define IN_ALT2						(1 << 15)
#define IN_SCORE					(1 << 16)   
#define IN_SPEED					(1 << 17)	
#define IN_WALK						(1 << 18)	
#define IN_ZOOM						(1 << 19)	
#define IN_WEAPON1					(1 << 20)	
#define IN_WEAPON2					(1 << 21)
#define IN_BULLRUSH					(1 << 22)
#define IN_GRENADE1					(1 << 23)
#define IN_GRENADE2					(1 << 24)	
#define	IN_ATTACK3					(1 << 25)
#define	FL_ONGROUND					(1 << 0)	
#define FL_DUCKING					(1 << 1)	
#define	FL_WATERJUMP				(1 << 2)	
#define FL_ONTRAIN					(1 << 3)
#define FL_INRAIN					(1 << 4)	
#define FL_FROZEN					(1 << 5)
#define FL_ATCONTROLS				(1 << 6)
#define	FL_CLIENT					(1 << 7)	
#define FL_FAKECLIENT				(1 << 8)	
#define	FL_INWATER					(1 << 9)										
#define	FL_FLY						(1 << 10)	
#define	FL_SWIM						(1 << 11)
#define	FL_CONVEYOR					(1 << 12)
#define	FL_NPC						(1 << 13)
#define	FL_GODMODE					(1 << 14)
#define	FL_NOTARGET					(1 << 15)
#define	FL_AIMTARGET				(1 << 16)	
#define	FL_PARTIALGROUND			(1 << 17)	
#define FL_STATICPROP				(1 << 18)
#define FL_GRAPHED					(1 << 19) 
#define FL_GRENADE					(1 << 20)
#define FL_STEPMOVEMENT				(1 << 21)	
#define FL_DONTTOUCH				(1 << 22)
#define FL_BASEVELOCITY				(1 << 23)
#define FL_WORLDBRUSH				(1 << 24)	
#define FL_OBJECT					(1 << 25) 
#define FL_KILLME					(1 << 26)
#define FL_ONFIRE					(1 << 27)	
#define FL_DISSOLVING				(1 << 28)
#define FL_TRANSRAGDOLL				(1 << 29)
#define FL_UNBLOCKABLE_BY_PLAYER	(1 << 30) 
#define PLAYER_FLAG_BITS			10
#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)

#pragma endregion

// Different LifeStates for an entity
enum class LifeState : std::uint8_t
{
	LIFE_ALIVE = 0,	// alive
	LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
	LIFE_DEAD = 2	// dead. lying still.
};

// Identifiers for classes (NOTE: might be outdated)
enum class ClassIDs : std::uint32_t
{
    AK47 = 1,
    BaseAnimating = 2,
    BaseDoor = 10,
    BaseEntity = 11,
    BaseTrigger = 20,
    C4 = 28,
    CSGameRulesProxy = 33,
    CSPlayer = 34,
    CSPlayerResource = 35,
    CSRagdoll = 36,
    CSTeam = 37,
    CascadeLight = 29,
    Chicken = 30,
    ColorCorrection = 31,
    DEagle = 38,
    DecoyGrenade = 39,
    DynamicProp = 42,
    EnvDetailController = 50,
    EnvTonemapController = 57,
    EnvWind = 58,
    Flashbang = 63,
    FogController = 64,
    FuncBrush = 69,
    FuncOccluder = 74,
    FuncRotating = 76,
    Func_Dust = 66,
    HEGrenade = 81,
    Hostage = 82,
    IncendiaryGrenade = 84,
    Inferno = 85,
    Knife = 88,
    KnifeGG = 88,
    LightGlow = 90,
    MolotovGrenade = 92,
    ParticleSystem = 97,
    PhysicsProp = 100,
    PhysicsPropMultiplayer = 101,
    PlantedC4 = 103,
    PostProcessController = 109,
    PredictedViewModel = 112,
    PropDoorRotating = 114,
    RopeKeyframe = 120,
    ShadowControl = 123,
    SmokeGrenade = 125,
    SmokeStack = 126,
    Sprite = 129,
    Sun = 134,
    VGuiScreen = 190,
    VoteController = 191,
    WeaponAUG = 194,
    WeaponAWP = 195,
    WeaponBizon = 196,
    WeaponElite = 200,
    WeaponFiveSeven = 202,
    WeaponG3SG1 = 203,
    WeaponGalilAR = 205,
    WeaponGlock = 206,
    WeaponHKP2000 = 207,
    WeaponM249 = 208,
    WeaponM4A1 = 210,
    WeaponMP7 = 214,
    WeaponMP9 = 215,
    WeaponMag7 = 212,
    WeaponNOVA = 217,
    WeaponNegev = 216,
    WeaponP250 = 219,
    WeaponP90 = 220,
    WeaponSCAR20 = 222,
    WeaponSG556 = 226,
    WeaponSSG08 = 227,
    WeaponTaser = 228,
    WeaponTec9 = 229,
    WeaponUMP45 = 231,
    WeaponXM1014 = 233,
    ParticleSmokeGrenade = 237,
    Weapon = 0xBEEF,
    Unknown = 0xDEAD
};

// Hardcoded hitboxes (NOTE: might be outdated by now)
enum class HitboxList : std::uint8_t
 {
    HITBOX_NONE,
    HITBOX_PELVIS,
	HITBOX_L_THIGH,
    HITBOX_L_CALF,
    HITBOX_L_FOOT,
    HITBOX_R_THIGH,
    HITBOX_R_CALF,
    HITBOX_R_FOOT,
    HITBOX_SPINE,
    HITBOX_SPINE1,
    HITBOX_SPINE2,
    HITBOX_SPINE3,
    HITBOX_NECK,
    HITBOX_HEAD,
    HITBOX_L_UPPERARM,
    HITBOX_L_FOREARM,
    HITBOX_L_HAND,
    HITBOX_R_UPPERARM,
    HITBOX_R_FOREARM,
    HITBOX_R_HAND,
    HITBOX_L_CLAVICLE,
    HITBOX_R_CLAVICLE,
    HITBOX_HELMET,
	HITBOX_SPINE4,
	HITBOX_MAX,
};

// Hardcoded bones (you can make this enum even more wide)
enum class BoneIDs : std::uint8_t
{
	PELVIS = 0,
	BONE_HEAD = 8,
	BONE_NECK = 7,
	BONE_BODY = 80,
};

// Identifiers for weapons (NOTE: might be outdated)
enum class WeaponIDs : std::uint16_t
{
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};

// Identifiers for teams
enum class TeamIDs : std::uint8_t
{
	NONE,
	SPEC,
	T,
	CT
};