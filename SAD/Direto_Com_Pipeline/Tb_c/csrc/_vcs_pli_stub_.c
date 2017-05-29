#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <dlfcn.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void* VCS_dlsymLookup(const char *);
extern void vcsMsgReportNoSource1(const char *, const char*);

/* PLI routine: $sad_monitor:call */
#ifndef __VCS_PLI_STUB_sad_monitor
#define __VCS_PLI_STUB_sad_monitor
extern void sad_monitor(int data, int reason);
#pragma weak sad_monitor
void sad_monitor(int data, int reason)
{
    static int _vcs_pli_stub_initialized_ = 0;
    static void (*_vcs_pli_fp_)(int data, int reason) = NULL;
    if (!_vcs_pli_stub_initialized_) {
        _vcs_pli_stub_initialized_ = 1;
        _vcs_pli_fp_ = (void (*)(int data, int reason)) dlsym(RTLD_NEXT, "sad_monitor");
        if (_vcs_pli_fp_ == NULL) {
            _vcs_pli_fp_ = (void (*)(int data, int reason)) VCS_dlsymLookup("sad_monitor");
        }
    }
    if (_vcs_pli_fp_) {
        _vcs_pli_fp_(data, reason);
    } else {
        vcsMsgReportNoSource1("PLI-DIFNF", "sad_monitor");
    }
}
void (*__vcs_pli_dummy_reference_sad_monitor)(int data, int reason) = sad_monitor;
#endif /* __VCS_PLI_STUB_sad_monitor */

#ifdef __cplusplus
}
#endif
