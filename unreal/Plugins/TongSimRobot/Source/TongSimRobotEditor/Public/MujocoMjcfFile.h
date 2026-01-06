// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Containers/Array.h"
#include "Containers/StringFwd.h"
#include "Containers/UnrealString.h"
#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "MujocoMjcfNode.h"

class FMjcfAttribute;
class FMjcfNode;

namespace EMjcfConstructMethod
{
	enum Type
	{
		ConstructFromFile,
		ConstructFromBuffer,
	};
}

/** Class representing an XML file */
class TONGSIMROBOT_API FMjcfFile
{
public:

	/** Constructs the file without a path */
	FMjcfFile() : RootNode(nullptr), bFileLoaded(false) {}
	/** 
	 * Constructs the file with the passed path. InFile is either treated as a filename to open, or as a text
	 * buffer to load.
	 * @param	InFile				The path/text to use
	 * @param	ConstructMethod		Whether to load a file of use the string as a buffer of xml data
	 */
	FMjcfFile(const FString& InFile, EMjcfConstructMethod::Type ConstructMethod = EMjcfConstructMethod::ConstructFromFile);
	~FMjcfFile() { Clear(); };

	FMjcfFile(const FMjcfFile& rhs) = delete;
	FMjcfFile& operator=(const FMjcfFile& rhs) = delete;

	/** 
	 * Loads the file with the passed path. Path is either treated as a filename to open, or as a text
	 * buffer to load.
	 * @param	Path				The path/text to use
	 * @param	ConstructMethod		Whether to load a file of use the string as a buffer of xml data
	 */
	bool LoadFile(const FString& Path, EMjcfConstructMethod::Type ConstructMethod = EMjcfConstructMethod::ConstructFromFile);
	/** Gets the last error message from the class */
	FString GetLastError() const;
	/** Clears the file of all internals. Note: Makes any existing pointers to FMjcfNode's INVALID */
	void Clear();
	/** Checks to see if a file is loaded */
	bool IsValid() const;

	/** 
	 * Returns the root node of the loaded file. nullptr if no file loaded. 
	 * It is assumed that there will always be one and only one root node.
	 * @return						Pointer to root node
	 */
	const FMjcfNode* GetRootNode() const;

	/** 
	 * Returns the root node of the loaded file. nullptr if no file loaded. 
	 * It is assumed that there will always be one and only one root node.
	 * @return						Pointer to root node
	 */
	FMjcfNode* GetRootNode();

	/**
	 * Write to disk, UTF-16 format only at the moment
	 * @param	Path				File path to save to
	 * @return						Whether writing the XML to a file succeeded
	 */
	bool Save(const FString& Path);

private:

	/** Pre-processes the file doing anything necessary (such as removing comments) */
	void PreProcessInput(TArray<FString>& Input);
	/** Whites of the text at the specified locations in a passed-in array */
	void WhiteOut(TArray<FString>& Input, int32 LineStart, int32 LineEnd, int32 IndexStart, int32 IndexEnd);
	/** Converts the passed input into a list of tokens for parsing */
	void Tokenize(FStringView Input, TArray<FString>& Tokens);
	/** Converts the passed input into a list of tokens for parsing */
	TArray<FString> Tokenize(const TArray<FString>& Input);
	/** 
	 * Add an attribute to the passed-in array.
	 * This makes the assumption that an attribute comes in as one 'token' (i.e. no spaces between tag="value").
	 */
	static void AddAttribute(const FString& InToken, TArray<FMjcfAttribute>& OutAttributes);
	/** Recursively creates nodes from the list of tokens */
	FMjcfNode* CreateRootNode(TArrayView<const FString> Tokens);
	/** Hook next ptrs up recursively */
	void HookUpNextPtrs(FMjcfNode* Node);
	/** Creates the internal file representation as a bunch of FMjcfNode's */
	void CreateNodes(const TArray<FString>& Tokens);
	/** Writes a node hierarchy at the given root to a string */
	static void WriteNodeHierarchy(const FMjcfNode& Node, const FString& Indent, FString& Output);

public:

	/** The passed-in path of the loaded file (might be absolute or relative) */
	FString LoadedFile;
	/** An error message generated on errors to return to the client */
	FString ErrorMessage;
	/** A pointer to the root node */
	FMjcfNode* RootNode;
	/** Flag for whether a file is loaded or not */
	bool bFileLoaded;
	/** Flag for whether the node creation process failed or not */
	bool bCreationFailed;
};
