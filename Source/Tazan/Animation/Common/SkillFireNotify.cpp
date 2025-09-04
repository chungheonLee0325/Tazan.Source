﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillFireNotify.h"

#include "Tazan/AreaObject/Base/AreaObject.h"
#include "Tazan/AreaObject/Skill/Base/BaseSkill.h"

class AAreaObject;

void USkillFireNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AAreaObject* owner = Cast<AAreaObject>( MeshComp->GetOwner());
		if (owner != nullptr && owner->GetCurrentSkill() != nullptr)
		{
			owner->GetCurrentSkill()->OnCastFire();
		}
	}
}
