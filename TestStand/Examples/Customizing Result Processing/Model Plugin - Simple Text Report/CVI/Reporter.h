//==============================================================================
//
// Title:       Report.h
//
// Created on:  9/16/2011 at 7:32:33 PM by Jed Beach.
//
//==============================================================================

#ifndef __Report_H__
#define __Report_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdlib.h>
#include <cvidef.h>
#include <userint.h>

int AppendReportRow(
	CAObjHandle reportSection,
	CAObjHandle columns,
	BOOL padColumns,
	CAObjHandle stepResultErrorMsg);

int ProcessResultList(
	CAObjHandle reportSection,
	CAObjHandle resultList,
	CAObjHandle options,
	CAObjHandle runtimeVariables,
	const char * sequence,
	const char * sequenceFile,
	int threadId,
	CAObjHandle stepResultErrorMsg);

int ProcessResultListOtf(
	CAObjHandle reportSection,
	CAObjHandle resultList,
	int parentIds[],
	const char * callbackNames[],
	CAObjHandle options,
	CAObjHandle runtimeVariables,
	const char * sequence,
	const char * sequenceFile,
	int threadId,
	CAObjHandle stepResultErrorMsg);

int GenerateUniqueReportPath(
    CAObjHandle reportPath,
	const char * reportDirectory,
	const char * reportBaseName,
	const char * dotExtension,
	size_t maxTries,
	CAObjHandle stepResultErrorMsg);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Report_H__ */
