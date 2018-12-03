// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Book_Work, Log, All);
// __FUNCTION__ : ���� ȣ��Ǵ� �Լ� �̸�. __LINE__ : ���� ����
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(Book_Work, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(Book_Work, Verbosity, TEXT("%s, %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))