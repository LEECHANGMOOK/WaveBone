// Copyright Epic Games, Inc. All Rights Reserved.


#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "CMWaveBonesAnimNode.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "CMWaveBonesED.generated.h"




class UCurveFloat;

UCLASS(Blueprintable)
class  UCMWaveBonesED : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()


		UPROPERTY(EditAnywhere, Category = Settings)
		FCMWaveBonesAnimNode Node;



public:
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;





protected:
	// UAnimGraphNode_Base interface
	virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;



	virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin) override;
	// End of UAnimGraphNode_Base interface



	virtual FText GetControllerDescription() const override;

	virtual const FAnimNode_SkeletalControlBase* GetNode() const override { return &Node; }
	//A



private:
	//A
	FNodeTitleTextTable CachedNodeTitles;
};