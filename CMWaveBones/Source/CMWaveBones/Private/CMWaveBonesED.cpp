// Copyright Epic Games, Inc. All Rights Reserved.

#include "CMWaveBonesED.h"
#include "UnrealWidget.h"
#include "AnimNodeEditModes.h"
#include "Kismet2/CompilerResultsLog.h"




#define LOCTEXT_NAMESPACE "A3Nodes"
//텍스트현지화
//A: 본 이름 표기
FLinearColor UCMWaveBonesED::GetNodeTitleColor() const
{
	return FLinearColor::Yellow;
}

FText UCMWaveBonesED::GetControllerDescription() const
{
	return LOCTEXT("SwimmingFish", "Swimming Fish");
}

void UCMWaveBonesED::ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog)
{

}





void UCMWaveBonesED::CopyPinDefaultsToNodeData(UEdGraphPin* InPin)
{
	/*if (InPin->GetName() == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_Swimming, Rotation))
	{
		GetDefaultValue(GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_Swimming, Rotation), Node.Rotation);
	}*/

	return;


}

//A
FText UCMWaveBonesED::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if ((TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle) && (Node.FirstBone.BoneName == NAME_None))
	{
		return GetControllerDescription();
	}
	else
	{

		FFormatNamedArguments Args;
		Args.Add(TEXT("ControllerDescription"), GetControllerDescription());
		Args.Add(TEXT("BoneName"), FText::FromName(Node.FirstBone.BoneName));


		if (TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle)
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_Swimming_ListTitle", "{ControllerDescription} - Bone: {BoneName}"), Args), this);
		}
		else
		{
			CachedNodeTitles.SetCachedTitle(TitleType, FText::Format(LOCTEXT("AnimGraphNode_Swimming_Title", "{ControllerDescription}\nBone: {BoneName}"), Args), this);
		}
	}
	return CachedNodeTitles[TitleType];
}

FText UCMWaveBonesED::GetTooltipText() const
{
	return LOCTEXT("My first CustomNode", "My first CustomNode");
}


#undef LOCTEXT_NAMESPACE
