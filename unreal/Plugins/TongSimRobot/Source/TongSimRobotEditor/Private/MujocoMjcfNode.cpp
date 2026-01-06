// Copyright Epic Games, Inc. All Rights Reserved.

#include "MujocoMjcfNode.h"


const FString& FMjcfAttribute::GetTag() const
{
	return Tag;
}

const FString& FMjcfAttribute::GetValue() const
{
	return Value;
}

void FMjcfAttribute::SetTag(const FString& InTag)
{
	Tag = InTag;
}

void FMjcfAttribute::SetValue(const FString& InValue)
{
	Value = InValue;
}

void FMjcfNode::Delete()
{
	TArray<FMjcfNode*> ToDelete = MoveTemp(Children);
	check(Children.IsEmpty());

	for (int32 Index = 0; Index != ToDelete.Num(); ++Index)
	{
		FMjcfNode* NodeToDelete = ToDelete[Index];
		ToDelete.Append(MoveTemp(NodeToDelete->Children));
		check(NodeToDelete->Children.IsEmpty());
	}

	for (FMjcfNode* Node : ToDelete)
	{
		delete Node;
	}
}

const FMjcfNode* FMjcfNode::GetNextNode() const
{
	return NextNode;
}

const TArray<FMjcfNode*>& FMjcfNode::GetChildrenNodes() const
{
	return Children;
}

const FMjcfNode* FMjcfNode::GetFirstChildNode() const
{
	if(Children.Num() > 0)
	{
		return Children[0];
	}
	else
	{
		return nullptr;
	}
}

const FMjcfNode* FMjcfNode::FindChildNode(const FString& InTag) const
{
	const int32 ChildCount = Children.Num();
	for(int32 ChildIndex = 0; ChildIndex < ChildCount; ++ChildIndex)
	{
		if(Children[ChildIndex] != nullptr && Children[ChildIndex]->GetTag() == InTag)
		{
			return Children[ChildIndex];
		}
	}

	return nullptr;
}

FMjcfNode* FMjcfNode::FindChildNode(const FString& InTag)
{
	return const_cast<FMjcfNode*>(AsConst(*this).FindChildNode(InTag));
}

const FString& FMjcfNode::GetTag() const
{
	return Tag;
}

const FString& FMjcfNode::GetContent() const
{
	return Content;
}

void FMjcfNode::SetContent( const FString& InContent )
{
	Content = InContent;
}

void FMjcfNode::SetAttributes(const TArray<FMjcfAttribute>& InAttributes)
{
	Attributes = InAttributes;
}

FString FMjcfNode::GetAttribute(const FString& InTag) const
{
	for(auto Iter(Attributes.CreateConstIterator()); Iter; Iter++)
	{
		if(Iter->GetTag() == InTag)
		{
			return Iter->GetValue();
		}
	}
	return FString();
}

void FMjcfNode::ModifyAttribute(const FString& InTag, const FString& InValue)
{
	for (auto Iter(Attributes.CreateIterator()); Iter; Iter++)
	{
		if (Iter->GetTag() == InTag)
		{
			Iter->SetValue(InValue);
		}
	}
}

FMjcfNode* FMjcfNode::AppendChildNode(const FString& InTag, const FString& InContent, const TArray<FMjcfAttribute>& InAttributes)
{
	auto NewNode = new FMjcfNode;
	NewNode->Tag = InTag;
	NewNode->Content = InContent;
	NewNode->Attributes = InAttributes;

	auto NumChildren = Children.Num();
	if (NumChildren != 0)
	{
		Children[NumChildren - 1]->NextNode = NewNode;
	}
	Children.Push(NewNode);

	return NewNode;
}

FMjcfNode* FMjcfNode::AppendChildNode(FMjcfNode* InNode)
{
	auto NumChildren = Children.Num();
	if (NumChildren != 0)
	{
		Children[NumChildren - 1]->NextNode = InNode;
	}
	Children.Push(InNode);

	return InNode;
}
