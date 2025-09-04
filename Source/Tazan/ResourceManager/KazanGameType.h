﻿#pragma once

#include <Engine/DataTable.h>
#include "CoreMinimal.h"
#include "Engine/DamageEvents.h"
#include "UObject/ObjectMacros.h"
#include "KazanGameType.generated.h"


// Enum
// 언리얼 리플렉션 시스템과 통합하기 위해 UENUM() 매크로를 사용

class UBaseSkill;
// ConditionBits - 비트마스크를 활용한 죽음, 무적 
UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EConditionBitsType : uint32
{
	None = 0 UMETA(DisplayName = "None"),
	// 0b0001
	Dead = 1 << 0 UMETA(DisplayName = "Dead"),
	// 0b0010
	Invincible = 1 << 1 UMETA(DisplayName = "Invincible"),
	// 0b0100
	Guard = 1 << 2 UMETA(DisplayName = "Guard"),
	// 0b1000
	PerfectGuardWindow = 1 << 3 UMETA(DisplayName = "PerfectGuardWindow"),
	// 0b 1 0000
	DodgeWindow = 1 << 4 UMETA(DisplayName = "DodgeWindow"),
	// 0b 10 0000
	PerfectDodgeWindow = 1 << 5 UMETA(DisplayName = "PerfectDodgeWindow"),
};

ENUM_CLASS_FLAGS(EConditionBitsType);

// 체력Bar, 공격 및 피격 판정 확인 등 다양한 상황에서 사용
UENUM(BlueprintType)
enum class EAreaObjectType : uint8
{
	None UMETA(DisplayName = "None"), // 블루프린트에서 표시될 이름
	Player UMETA(DisplayName = "Player"),
	Enemy UMETA(DisplayName = "Enemy"),
};

// 몬스터 종류 구별용 Type - 체력Bar 등 다양한 상황에서 사용 가능
UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	None UMETA(DisplayName = "None"), // 블루프린트에서 표시될 이름
	Monster UMETA(DisplayName = "Monster"),
	NamedMonster UMETA(DisplayName = "NamedMonster"),
	Boss UMETA(DisplayName = "Boss"),
};

// Ai의 SkillBag에서 랜덤 확률로 사용될 스킬들 - 개시스킬들만 포함
UENUM(BlueprintType)
enum class EAiSkillType : uint8
{
	None UMETA(DisplayName = "None"),
	Main UMETA(DisplayName = "Main"),
	Weaving UMETA(DisplayName = "Weaving"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Back UMETA(DisplayName = "Back"),
	Short UMETA(DisplayName = "Short"),
	Middle UMETA(DisplayName = "Middle"),
	Long UMETA(DisplayName = "Long"),
	Grappling UMETA(DisplayName = "Grappling"),
};

// AiFSM을 위한 Enum Type
UENUM(BlueprintType)
enum class EAiStateType : uint8
{
	None UMETA(DisplayName = "None"),
	Idle UMETA(DisplayName = "Idle"),
	Wait UMETA(DisplayName = "Wait"),
	Attack UMETA(DisplayName = "Attack"),
	SelectSkill UMETA(DisplayName = "SelectSkill"),
	Chase UMETA(DisplayName = "Chase"),
	Return UMETA(DisplayName = "Return"),
	DoNothing UMETA(DisplayName = "DoNothing"),
};

// 공격시 Trace System에서 사용 - EnableCollisionNotifyState 참조
UENUM(BlueprintType)
enum class EHitDetectionType : uint8
{
	Line UMETA(DisplayName = "Line Trace"),
	Sphere UMETA(DisplayName = "Sphere Trace"),
	Capsule UMETA(DisplayName = "Capsule Trace"),
	Box UMETA(DisplayName = "Box Trace")
};

// 경직 타입 정의
UENUM(BlueprintType)
enum class EStaggerType : uint8
{
	None,
	// 약한 데미지 경직
	Weak UMETA(DisplayName = "Weak"),
	// 일반 데미지 경직
	Normal UMETA(DisplayName = "Normal"),
	// 강한 데미지 경직
	Strong UMETA(DisplayName = "Strong"),
	// 넘어짐
	AirBone UMETA(DisplayName = "AirBone"),
	// Parry 반동
	ParryReaction UMETA(DisplayName = "ParryReaction"),
	// Groggy
	Groggy UMETA(DisplayName = "Groggy"),
	// GuardBreak
	GuardBreak UMETA(DisplayName = "GuardBreak"),
};

UENUM(BlueprintType)
enum class EPMRotationMode : uint8
{
	Duration UMETA(DisplayName = "Duration"),
	Speed UMETA(DisplayName = "Speed")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None UMETA(DisplayName = "None"),
	Currency UMETA(DisplayName = "Currency"),
	Loot UMETA(DisplayName = "Loot"),
};

UENUM(BlueprintType)
enum class ECurrencyType : uint8
{
	None UMETA(DisplayName = "None"),
	Lachryma UMETA(DisplayName = "Lachryma"),
	Coin UMETA(DisplayName = "Coin"),
};

UENUM(BlueprintType)
enum class EAnimationPriority : uint8
{
	None = 0,
	Movement = 1,
	Action = 2,
	Skill = 3,
	Guard = 4,
	Dodge = 4,
	Groggy = 6,
	Stagger = 7,
	Death = 10
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	None UMETA(DisplayName = "None"),
	Idle UMETA(DisplayName = "Idle"),
	Move UMETA(DisplayName = "Move"),
	Fall UMETA(DisplayName = "Fall"),
	Attack UMETA(DisplayName = "Attack"),
	Guard UMETA(DisplayName = "Guard"),
	Dodge UMETA(DisplayName = "Dodge"),
	Stagger UMETA(DisplayName = "Stagger"),
	Dead UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EMovementInterpolationType : uint8
{
	// 선형
	Linear UMETA(DisplayName = "Linear"),
	// 시작에는 느리게 갈수록 빠르게
	EaseIn UMETA(DisplayName = "Ease In"),
	// 시작은 빠르게 갈수록 느리게
	EaseOut UMETA(DisplayName = "Ease Out"),
	EaseInOut UMETA(DisplayName = "Ease In Out"),
	EaseOutBounce UMETA(DisplayName = "Ease Out Bounce"),
	EaseOutElastic UMETA(DisplayName = "Ease Out Elastic"),
	ExpoIn UMETA(DisplayName = "Expo In"),
	ExpoOut UMETA(DisplayName = "Expo Out"),
	ExpoInOut UMETA(DisplayName = "Expo In Out"),
	ElasticIn UMETA(DisplayName = "Elastic In"),
	ElasticOut UMETA(DisplayName = "Elastic Out"),
	ElasticInOut UMETA(DisplayName = "Elastic In Out"),
};

UENUM(BlueprintType)
enum class EReactionDirection : uint8
{
	None UMETA(DisplayName = "None"), // 블루프린트에서 표시될 이름
	UP UMETA(DisplayName = "UP"),
	DOWN UMETA(DisplayName = "DOWN"),
	LEFT UMETA(DisplayName = "LEFT"),
	RIGHT UMETA(DisplayName = "RIGHT")
};

// Struct
// AreaObject 데이터 테이블용 구조체
USTRUCT(BlueprintType)
struct FAreaObjectData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int AreaObjectID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	FName Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	EAreaObjectType AreaObjectType = EAreaObjectType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	EEnemyType EnemyType = EEnemyType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data",
		meta=(EditCondition="AreaObjectType == EAreaObjectType::Enemy"))
	int SkillBagID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float HPMax = 1.0f;

	// 방어 기본 강인도 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int BasePoise = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	UAnimMontage* Die_AnimMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TMap<EStaggerType, UAnimMontage*> Stagger_AnimMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TSet<int> SkillList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float StaminaMax = 100.0f;

	// 스태미나 초당 회복량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float StaminaRecoveryRate = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float GroggyDuration = 5.f;

	// ToDo : 고도화되면 Skill로 이관 예정  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int HitSoundID = 0;
};

// HitBox 동적으로 생성하기 위한 구조체 정보, FAttackData 멤버 변수
USTRUCT(BlueprintType)
struct FHitBoxData
{
	GENERATED_BODY()

	// 히트 박스 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHitDetectionType DetectionType = EHitDetectionType::Line;

	// 소켓 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StartSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EndSocketName;

	// 크기 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (EditCondition = "DetectionType != EHitDetectionType::Line || DetectionType != EHitDetectionType::Box"))
	float Radius = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "DetectionType == EHitDetectionType::Capsule"))
	float HalfHeight = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "DetectionType == EHitDetectionType::Box"))
	FVector BoxExtent = FVector(15.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseInterpolation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bUseInterpolation"))
	int32 InterpolationSteps = 4;

	// 소켓이 있는 메시 컴포넌트 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MeshComponentTag = NAME_None;
};

// FSkill의 멤버 변수, 전투에서 공격에 관련된 데이터 담당
USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_USTRUCT_BODY()

	// 체력 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthDamageAmountMin = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthDamageAmountMax = 0.0f;

	// 스테미나 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaDamageAmount = 0.0f;

	// 강인도 공격 Level : 0 ~ 15 까지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PoiseAttackAmount = 1;

	// 강인도 비교에 의해 경직 적용시 Stagger(경직) 타입 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStaggerType StaggerType = EStaggerType::None;

	// 공격 히트 박스 정보 구조체
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitBoxData HitBoxData;

	// HitStop 관련 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableHitStop = false; // HitStop 적용 여부

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bEnableHitStop"))
	float HitStopDuration = 0.1f; // HitStop 지속 시간

	// 넉백 관련 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockBackForce = 0.0f; // 넉백 거리

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseCustomKnockBackDirection = false; // 커스텀 넉백 방향 사용 여부

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bUseCustomKnockbackDirection"))
	FVector KnockBackDirection = FVector::ForwardVector; // 커스텀 넉백 방향
};

// m_SkillData 테이블 정보, 데미지 정보등 관리
USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseSkill> SkillClass = nullptr;

	// 소모 자원(현재는 스태미너 고정 추후 체력등 확장시 enum 추가될듯)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost = 0;

	// 스킬 사정거리 (AI 용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CastRange = 0.0f;

	// 스킬 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 0.0f;

	// 사용 스킬의 애님 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage = nullptr;

	// 스킬 시전중 시전자의 방어 강인도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AnimationPoiseBonusValue = 1;

	// 데미지 관련 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAttackData> AttackData;

	// 다음 스킬 ID (플레이어 및 몬스터 콤보 어택)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NextSkillID = 0;
	// Todo : Sound & Cast/Hit FX 관련 항목 추가? -> Anim Notify로 처리할듯
};

// Item 데이터 테이블용 구조체
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	EItemType ItemType = EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data",
		meta = (EditCondition = "ItemType == EItemType::Currency"))
	ECurrencyType CurrencyType = ECurrencyType::None;
	// 획득시 사운드ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int SoundID = 0;

	// 획득시 FxID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int VfxID = 0;
};


// Unreal Damage 프레임워크 안에서 Attack 정보를 넘기기위한 구조체
USTRUCT(BlueprintType)
struct FCustomDamageEvent : public FPointDamageEvent
{
	GENERATED_BODY()

	UPROPERTY()
	FAttackData AttackData;

	// FDamageEvent 인터페이스 구현
	virtual bool IsOfType(int32 InID) const override;
	virtual int32 GetTypeID() const override;

	static const int32 ClassID = 0; // 유니크한 ID 할당
};

inline bool FCustomDamageEvent::IsOfType(int32 InID) const
{
	return InID == ClassID;
}

inline int32 FCustomDamageEvent::GetTypeID() const
{
	return ClassID;
}

// FXDataTable 데이터, GameMode에서 관리
USTRUCT(BlueprintType)
struct FVfxData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int VfxID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	UParticleSystem* Vfx = nullptr;
};

// SoundDataTable 데이터, GameMode에서 관리
// Why Not GameInstance? AudioComponent가질수없음 -> BGM 관리 불가
USTRUCT(BlueprintType)
struct FSoundData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int SoundID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	USoundBase* Sound = nullptr;
};

// 몬스터가 확률에의해 사용하는 Skill목록 - Weight는 가중치
USTRUCT(BlueprintType)
struct FSkillBag
{
	GENERATED_BODY()

	// <SkillID, Weight>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, float> SkillID_Weight;
};

USTRUCT(BlueprintType)
struct FSkillBagData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int SkillBagID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TMap<EAiSkillType, FSkillBag> TypeSkillBag;
};
