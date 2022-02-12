// Copyright Epic Games, Inc. All Rights Reserved.

#include "CMWaveBonesAnimNode.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimTrace.h"


FCMWaveBonesAnimNode::FCMWaveBonesAnimNode()
	:RotationX(true)
	, RotationY(true)
	, RotationZ(true)
	, XSpeed(float(1.0f))
	, YSpeed(float(1.0f))
	, ZSpeed(float(1.0f))
	, MyIntervalX(float(0.0f))
	, MyIntervalY(float(0.0f))
	, MyIntervalZ(float(0.0f))
	, BoneLength(0)
	, XTime(float(0.0f))
	, YTime(float(0.0f))
	, ZTime(float(0.0f))




{}

void FCMWaveBonesAnimNode::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

}


void FCMWaveBonesAnimNode::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(EvaluateSkeletalControl_AnyThread)
	check(OutBoneTransforms.Num() == 0);
	// const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();
	// FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();


	int32 k = FirstBone.BoneIndex;
	int32 LastIndexNum = k + BoneLength;

	float j = 0.f;
	float intervalX = MyIntervalX / (BoneLength);
	float intervalY = MyIntervalY / (BoneLength);
	float intervalZ = MyIntervalZ / (BoneLength);

	float intervalXX = 0;
	float intervalYY = 0;
	float intervalZZ = 0;
	FRotator Rot(RotationY, RotationZ, RotationX);


	for (int32 i = k; i <= LastIndexNum; i++)
	{
		if (MyAngleX != 0)
		{

			intervalXX = intervalXX + intervalX;
		}
		else
		{
			intervalXX = 0;
		}
		if (MyAngleY != 0)
		{

			intervalYY = intervalYY + intervalY;
		}
		else
		{
			intervalYY = 0;
		}
		if (MyAngleZ != 0)
		{

			intervalZZ = intervalZZ + intervalZ;
		}
		else
		{
			intervalZZ = 0;
		}
		
		XTime += GetTime * 0.1;
		YTime += GetTime * 0.1;
		ZTime += GetTime * 0.1;

		float MySinTranX = FMath::InterpSinInOut((MyAngleX + intervalXX) * 0.5, ((MyAngleX + intervalXX) * -0.5), XTime * XSpeed - j);
		float MySinTranY = FMath::InterpSinInOut((MyAngleY + intervalYY) * 0.5, ((MyAngleY + intervalYY) * -0.5), YTime * YSpeed - j);
		float MySinTranZ = FMath::InterpSinInOut((MyAngleZ + intervalZZ) * 0.5, ((MyAngleZ + intervalZZ) * -0.5), ZTime * ZSpeed - j);

	

		FRotator FinalTran(RotationY * MySinTranY, RotationZ * MySinTranZ, RotationX * MySinTranX);


		const FQuat BoneQuatTran(FinalTran);
		FCompactPoseBoneIndex CurrentIndex = FCompactPoseBoneIndex(i);
		FTransform TransBoneTM = Output.Pose.GetComponentSpaceTransform(CurrentIndex);


		TransBoneTM.SetRotation(BoneQuatTran * TransBoneTM.GetRotation());
		
		if (i != k)
		{
			TransBoneTM.SetLocation(BoneQuatTran * TransBoneTM.GetLocation());

		}

		OutBoneTransforms.Add(FBoneTransform(CurrentIndex, TransBoneTM));


		j += 0.06;

	}
}

bool FCMWaveBonesAnimNode::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	return (FirstBone.IsValidToEvaluate(RequiredBones));
	return (EndBone.IsValidToEvaluate(RequiredBones));
}



void FCMWaveBonesAnimNode::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	FirstBone.Initialize(RequiredBones);
	EndBone.Initialize(RequiredBones);

	BoneLength = RequiredBones.GetDepthBetweenBones(EndBone.BoneIndex, FirstBone.BoneIndex);
}

