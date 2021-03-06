// Copyright 2016 Keybase Inc. All rights reserved.
// Use of this source code is governed by a BSD
// license that can be found in the LICENSE file.

#ifndef KBFS_DOKAN_BRIDGE_H__
#define KBFS_DOKAN_BRIDGE_H__

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)

#define UNICODE 1
#define _UNICODE 1

#include <stdint.h>
#include <windows.h>
#include <ntdef.h>
#include <ntstatus.h>

/* Compatibility for older toolchains */
#define PWIN32_FIND_DATAW LPWIN32_FIND_DATAW
typedef struct kbfs_WIN32_FIND_STREAM_DATA_ {
    LARGE_INTEGER StreamSize;
    WCHAR cStreamName[MAX_PATH + 36];
} kbfs_WIN32_FIND_STREAM_DATA,*kbfs_PWIN32_FIND_STREAM_DATA;
#define PWIN32_FIND_STREAM_DATA kbfs_PWIN32_FIND_STREAM_DATA


#include "dokan_header/dokan.h"

typedef int32_t error_t;
typedef uint32_t go_fs_id;

struct kbfsLibdokanCtx {
  DOKAN_OPERATIONS dokan_operations;
  DOKAN_OPTIONS dokan_options;
};

struct kbfsLibdokanCtx* kbfsLibdokanAllocCtx(ULONG64 fsslot);
error_t kbfsLibdokanFree(struct kbfsLibdokanCtx* ctx);
error_t kbfsLibdokanRun(struct kbfsLibdokanCtx* ctx);
void kbfsLibdokanSet_path(struct kbfsLibdokanCtx* ctx, void*);

int kbfsLibdokanFill_find(PFillFindData, PWIN32_FIND_DATAW, PDOKAN_FILE_INFO);

enum {
  kbfsLibdokanDebug = DOKAN_OPTION_DEBUG|DOKAN_OPTION_STDERR,
};

#endif /* windows check */

#endif /* KBFS_DOKAN_BRIDGE_H__ */
