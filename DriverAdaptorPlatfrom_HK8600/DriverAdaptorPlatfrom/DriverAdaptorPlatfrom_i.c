

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Dec 14 11:44:37 2016
 */
/* Compiler settings for DriverAdaptorPlatfrom.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_DriverAdaptorPlatfromLib,0xFB1B6B75,0xC008,0x42B2,0xAA,0x5B,0xE5,0xCE,0xE7,0xA1,0x1D,0xCC);


MIDL_DEFINE_GUID(IID, DIID__DDriverAdaptorPlatfrom,0x9BC3145A,0x8744,0x4ADC,0xBB,0x2F,0x02,0x89,0x01,0x70,0x6D,0xAC);


MIDL_DEFINE_GUID(IID, DIID__DDriverAdaptorPlatfromEvents,0x48EF2238,0x1E11,0x4157,0x81,0x28,0x1E,0x26,0xB3,0x3B,0xD1,0xB4);


MIDL_DEFINE_GUID(CLSID, CLSID_DriverAdaptorPlatfrom,0x3A6B1F54,0x0BFB,0x4ED1,0x95,0x04,0xB6,0x19,0x10,0x33,0x8B,0xAE);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



