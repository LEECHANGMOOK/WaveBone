// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/TimelineComponent.h"
#include "Math/Rotator.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "CMWaveBonesAnimNode.generated.h"

class USkeletalMeshComponent;



USTRUCT()
struct FCMWaveBonesAnimNode : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = SkeletalControl)
		FBoneReference FirstBone;

	UPROPERTY(EditAnywhere, Category = SkeletalControl)
		FBoneReference EndBone;

	UPROPERTY()
		TArray<int> BoneIndices;
	UPROPERTY()
		TArray<FString> NameIndices;



	// Affect the X component of rotation on the target bone
	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Rotation X"))
		uint8 RotationX : 1;

	// Affect the Y component of rotation on the target bone
	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Rotation Y"))
		uint8 RotationY : 1;

	// Affect the Z component of rotation on the target bone
	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Rotation Z"))
		uint8 RotationZ : 1;

	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinShownByDefault))
		float GetTime;

	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinShownByDefault, DisplayName = "X Rotation"))
		float MyAngleX;
	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinHiddenByDefault, DisplayName = "X Speed"))
		float XSpeed;


	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinShownByDefault, DisplayName = "Y Rotation"))
		float MyAngleY;
	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinHiddenByDefault, DisplayName = "Y Speed"))
		float YSpeed;


	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinShownByDefault, DisplayName = "Z Rotation"))
		float MyAngleZ;
	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinHiddenByDefault, DisplayName = "Z Speed"))
		float ZSpeed;


	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinHiddenByDefault, DisplayName = "X Interval"))
		float MyIntervalX;
	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinHiddenByDefault, DisplayName = "Y Interval"))
		float MyIntervalY;
	UPROPERTY(EditAnywhere, Category = Condition, meta = (PinHiddenByDefault, DisplayName = "Z Interval"))
		float MyIntervalZ;





	UPROPERTY()
		int32 BoneLength;
	float XTime;
	float YTime;
	float ZTime;

	FCMWaveBonesAnimNode();

	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;







private:

	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;

};