// Author: Lucas Vilas-Boas
// Year: 2023
// Repo: https://github.com/lucoiso/UEHttpGPT

#pragma once

#include <CoreMinimal.h>
#include <Dom/JsonValue.h>
#include "HttpGPTTypes.generated.h"

UENUM(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Model"))
enum class EHttpGPTModel : uint8
{
	gpt35turbo		UMETA(DisplayName = "gpt-3.5-turbo"),
	textdavinci003	UMETA(DisplayName = "text-davinci-003"),
	textdavinci002	UMETA(DisplayName = "text-davinci-002"),
	codedavinci002	UMETA(DisplayName = "code-davinci-002"),
};

UENUM(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Role"))
enum class EHttpGPTRole : uint8
{
	User,
	Assistant
};

USTRUCT(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Message"))
struct FHttpGPTMessage
{
	GENERATED_BODY()

	FHttpGPTMessage() = default;
	FHttpGPTMessage(const EHttpGPTRole& Role, const FString& Content) : Role(Role), Content(Content) {}
	FHttpGPTMessage(const FName& Role, const FString& Content) : Role(Role.ToString().ToLower() == "user" ? EHttpGPTRole::User : EHttpGPTRole::Assistant), Content(Content) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	EHttpGPTRole Role;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FString Content;

	TSharedPtr<FJsonValue> GetMessage() const;
};

USTRUCT(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Choice"))
struct FHttpGPTChoice
{
	GENERATED_BODY()

	FHttpGPTChoice() = default;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	int32 Index;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FHttpGPTMessage Message;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FName FinishReason;
};

USTRUCT(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Usage"))
struct FHttpGPTUsage
{
	GENERATED_BODY()

	FHttpGPTUsage() = default;
	FHttpGPTUsage(const int32& PromptTokens, const int32& CompletionTokens, const int32& TotalTokens) : PromptTokens(PromptTokens), CompletionTokens(CompletionTokens), TotalTokens(TotalTokens) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	int32 PromptTokens;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	int32 CompletionTokens;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	int32 TotalTokens;
};

USTRUCT(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Error"))
struct FHttpGPTError
{
	GENERATED_BODY()

	FHttpGPTError() = default;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FName Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FName Code;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FString Message;
};

USTRUCT(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Response"))
struct FHttpGPTResponse
{
	GENERATED_BODY()

	FHttpGPTResponse() = default;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FName ID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FName Object;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	int32 Created;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	TArray<FHttpGPTChoice> Choices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FHttpGPTUsage Usage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	bool bSuccess;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT")
	FHttpGPTError Error;
};

USTRUCT(BlueprintType, Category = "HttpGPT", Meta = (DisplayName = "HttpGPT Options"))
struct FHttpGPTOptions
{
	GENERATED_BODY()

	FHttpGPTOptions();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT", Meta = (DisplayName = "Model"))
	EHttpGPTModel Model;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT", Meta = (DisplayName = "Max Tokens", ClampMin = "1", UIMin = "1", ClampMax = "2048", UIMax = "2048"))
	int32 MaxTokens;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT", Meta = (DisplayName = "Temperature", ClampMin = "0.0", UIMin = "0.0", ClampMax = "2.0", UIMax = "2.0"))
	float Temperature;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT", Meta = (DisplayName = "Choices", ClampMin = "1", UIMin = "1"))
	int32 Choices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT", Meta = (DisplayName = "Presence Penalty", ClampMin = "-2.0", UIMin = "-2.0", ClampMax = "2.0", UIMax = "2.0"))
	float PresencePenalty;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HttpGPT", Meta = (DisplayName = "Frequency Penalty", ClampMin = "-2.0", UIMin = "-2.0", ClampMax = "2.0", UIMax = "2.0"))
	float FrequencyPenalty;
};