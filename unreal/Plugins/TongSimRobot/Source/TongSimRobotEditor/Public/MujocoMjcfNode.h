// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "CoreMinimal.h"

/** Forward Decl for implementation */
class FMjcfFile;

class TONGSIMROBOT_API FMjcfAttribute
{
public:
	FMjcfAttribute(const FString& InTag, const FString& InValue)
		: Tag(InTag)
		, Value(InValue)
	{
	}

	/** Gets the tag of the attribute */
	const FString& GetTag() const;

	/** Gets the value of the attribute */
	const FString& GetValue() const;

	/** Sets the tag of the attribute */
	void SetTag(const FString& InTag);

	/** Sets the value of the attribute */
	void SetValue(const FString& InValue);

private:
	/** The tag string */
	FString Tag;

	/** The value string */
	FString Value;
};

/** Xml Node representing a line in an xml file */
class FMjcfNode
{
	friend class FMjcfFile;

public:

	FMjcfNode(const FString& InTag, const FString& InContent = FString(), const TArray<FMjcfAttribute>& InAttributes = TArray<FMjcfAttribute>())
		: Tag(InTag)
		, Content(InContent)
		, Attributes(InAttributes)
		, NextNode(nullptr)
	{ }

	// Move Constructor
	FMjcfNode(FMjcfNode&& Other) noexcept
		: Children(MoveTemp(Other.Children))
		, Tag(MoveTemp(Other.Tag))
		, Content(MoveTemp(Other.Content))
		, Attributes(MoveTemp(Other.Attributes))
		, NextNode(MoveTemp(Other.NextNode))
	{ }


	/** Default ctor, private for FMjcfFile use only */
	FMjcfNode() : NextNode(nullptr) {}

	/** dtor */
	~FMjcfNode() { Delete(); }

	/** Recursively deletes the nodes for cleanup */
	void Delete();

	/** Gets the next node in a list of nodes */
	const FMjcfNode* GetNextNode() const;
	/** Gets a list of children nodes */
	const TArray<FMjcfNode*>& GetChildrenNodes() const;
	/** Gets the first child of this node which can be iterated into with GetNextNode */
	const FMjcfNode* GetFirstChildNode() const;
	/** Finds the first child node that contains the specified tag */
	const FMjcfNode* FindChildNode(const FString& InTag) const;
	/** Finds the first child node that contains the specified tag */
	FMjcfNode* FindChildNode(const FString& InTag);
	/** Gets the tag of the node */
	const FString& GetTag() const;
	/** Gets the value of the node */
	const FString& GetContent() const;
	/** Sets the new value of the node */
	void SetContent(const FString& InContent);
	/** Sets the attributes of the node */
	void SetAttributes(const TArray<FMjcfAttribute>& InAttributes);

	/**
	 * Gets all of the attributes in this node
	 *
	 * @return	List of attributes in this node
	 */
	const TArray<FMjcfAttribute>& GetAttributes() const
	{
		return Attributes;
	}

	/** Gets an attribute that corresponds with the passed-in tag */
	FString GetAttribute(const FString& InTag) const;

	/** Modify the value of the attribute */
	void ModifyAttribute(const FString& InTag, const FString& InValue);

	/**
	 *  Adds a child node to this node  
	 * @param	InTag				The tag of the child node
	 * @param	InContent			(optional) The content of the child node
	 * @param	InAttributes		(optional) An array of attributes of the child node
	 */
	FMjcfNode* AppendChildNode(const FString& InTag, const FString& InContent = FString(), const TArray<FMjcfAttribute>& InAttributes = TArray<FMjcfAttribute>());
	
	FMjcfNode* AppendChildNode(FMjcfNode* InNode);

public:

	/** The list of children nodes */
	TArray<FMjcfNode*> Children;
	/** Tag of the node */
	FString Tag;
	/** Content of the node */
	FString Content;
	/** Attributes of this node */
	TArray<FMjcfAttribute> Attributes;
	/** Next pointer */
	FMjcfNode* NextNode;

};
