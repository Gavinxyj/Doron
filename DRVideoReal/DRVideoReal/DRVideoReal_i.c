

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Mar 23 11:39:47 2017
 */
/* Compiler settings for DRVideoReal.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_DRVideoRealLib,0xD20038C9,0x1AE7,0x44E0,0x9A,0x4D,0xD8,0x6B,0xE1,0x2E,0x3C,0x17);


MIDL_DEFINE_GUID(IID, DIID__DDRVideoReal,0x51131C17,0xF78B,0x4BB3,0x83,0xB6,0xEF,0xF0,0xFC,0xAC,0x2B,0x56);


MIDL_DEFINE_GUID(IID, DIID__DDRVideoRealEvents,0x565438E1,0x65B3,0x4F8E,0x8C,0x6E,0xA1,0x7B,0xD6,0xB9,0x70,0x26);


MIDL_DEFINE_GUID(CLSID, CLSID_DRVideoReal,0xE457FB87,0x4610,0x43D1,0xB9,0x9F,0x56,0xE1,0x08,0x61,0x48,0x80);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



