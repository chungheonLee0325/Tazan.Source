// Fill out your copyright notice in the Description page of Project Settings.


#include "TazanGameInstance.h"

#include "GameplayTagsManager.h"
#include "TazanGameMode.h"
#include "K2Node_GetDataTableRow.h"

void UTazanGameInstance::Init()
{
	Super::Init();

	// AreaObject Data
	UDataTable* AreaObjectTable = LoadObject<UDataTable>(
		nullptr, TEXT("/Script/Engine.DataTable'/Game/_BluePrints/ResourceManager/db_AreaObject.db_AreaObject'"));
	if (nullptr != AreaObjectTable)
	{
		TArray<FName> RowNames = AreaObjectTable->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FAreaObjectData* Row = AreaObjectTable->FindRow<FAreaObjectData>(RowName, TEXT(""));
			if (nullptr != Row)
			{
				dt_AreaObject.Add(Row->AreaObjectID, *Row);
			}
		}
	}
	// Skill Data
	UDataTable* SkillTable = LoadObject<UDataTable>(
		nullptr, TEXT("/Script/Engine.DataTable'/Game/_BluePrints/ResourceManager/db_Skill.db_Skill'"));
	if (nullptr != SkillTable)
	{
		TArray<FName> RowNames = SkillTable->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FSkillData* Row = SkillTable->FindRow<FSkillData>(RowName, TEXT(""));
			if (nullptr != Row)
			{
				dt_Skill.Add(Row->SkillID, *Row);
			}
		}
	}
	// SkillBag Data
	UDataTable* SkillBagTable = LoadObject<UDataTable>(
		nullptr, TEXT("/Game/_BluePrints/ResourceManager/db_Skillbag.db_Skillbag"));
	if (nullptr != SkillTable)
	{
		TArray<FName> RowNames = SkillBagTable->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FSkillBagData* Row = SkillBagTable->FindRow<FSkillBagData>(RowName, TEXT(""));
			if (nullptr != Row)
			{
				dt_SkillBag.Add(Row->SkillBagID, *Row);
			}
		}
	}

	// Sound Data
	UDataTable* SoundTable = LoadObject<UDataTable>(
		nullptr, TEXT("/Script/Engine.DataTable'/Game/_BluePrints/ResourceManager/db_Sound.db_Sound'"));
	if (nullptr != SoundTable)
	{
		TArray<FName> RowNames = SoundTable->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FSoundData* Row = SoundTable->FindRow<FSoundData>(RowName, TEXT(""));
			if (nullptr != Row)
			{
				SoundDataMap.Add(Row->SoundID, Row->Sound);
			}
		}
	}
}

FAreaObjectData* UTazanGameInstance::GetDataAreaObject(const int AreaObjectID)
{
	if (FAreaObjectData* data = dt_AreaObject.Find(AreaObjectID))
	{
		return data;
	}

	return nullptr;
}

FSkillData* UTazanGameInstance::GetDataSkill(int SkillID)
{
	if (FSkillData* data = dt_Skill.Find(SkillID))
	{
		return data;
	}
	
	return nullptr;
}

FSkillBagData* UTazanGameInstance::GetDataSkillBag(int SkillBagID)
{
	if (FSkillBagData* data = dt_SkillBag.Find(SkillBagID))
	{
		return data;
	}
	
	return nullptr;
}
