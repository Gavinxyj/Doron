

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Mar 16 16:40:15 2017
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __DriverAdaptorPlatfromidl_h__
#define __DriverAdaptorPlatfromidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DDriverAdaptorPlatfrom_FWD_DEFINED__
#define ___DDriverAdaptorPlatfrom_FWD_DEFINED__
typedef interface _DDriverAdaptorPlatfrom _DDriverAdaptorPlatfrom;
#endif 	/* ___DDriverAdaptorPlatfrom_FWD_DEFINED__ */


#ifndef ___DDriverAdaptorPlatfromEvents_FWD_DEFINED__
#define ___DDriverAdaptorPlatfromEvents_FWD_DEFINED__
typedef interface _DDriverAdaptorPlatfromEvents _DDriverAdaptorPlatfromEvents;
#endif 	/* ___DDriverAdaptorPlatfromEvents_FWD_DEFINED__ */


#ifndef __DriverAdaptorPlatfrom_FWD_DEFINED__
#define __DriverAdaptorPlatfrom_FWD_DEFINED__

#ifdef __cplusplus
typedef class DriverAdaptorPlatfrom DriverAdaptorPlatfrom;
#else
typedef struct DriverAdaptorPlatfrom DriverAdaptorPlatfrom;
#endif /* __cplusplus */

#endif 	/* __DriverAdaptorPlatfrom_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __DriverAdaptorPlatfromLib_LIBRARY_DEFINED__
#define __DriverAdaptorPlatfromLib_LIBRARY_DEFINED__

/* library DriverAdaptorPlatfromLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_DriverAdaptorPlatfromLib;

#ifndef ___DDriverAdaptorPlatfrom_DISPINTERFACE_DEFINED__
#define ___DDriverAdaptorPlatfrom_DISPINTERFACE_DEFINED__

/* dispinterface _DDriverAdaptorPlatfrom */
/* [uuid] */ 


EXTERN_C const IID DIID__DDriverAdaptorPlatfrom;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9BC3145A-8744-4ADC-BB2F-028901706DAC")
    _DDriverAdaptorPlatfrom : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDriverAdaptorPlatfromVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDriverAdaptorPlatfrom * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDriverAdaptorPlatfrom * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDriverAdaptorPlatfrom * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDriverAdaptorPlatfrom * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDriverAdaptorPlatfrom * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDriverAdaptorPlatfrom * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDriverAdaptorPlatfrom * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDriverAdaptorPlatfromVtbl;

    interface _DDriverAdaptorPlatfrom
    {
        CONST_VTBL struct _DDriverAdaptorPlatfromVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDriverAdaptorPlatfrom_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DDriverAdaptorPlatfrom_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DDriverAdaptorPlatfrom_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DDriverAdaptorPlatfrom_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DDriverAdaptorPlatfrom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DDriverAdaptorPlatfrom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DDriverAdaptorPlatfrom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDriverAdaptorPlatfrom_DISPINTERFACE_DEFINED__ */


#ifndef ___DDriverAdaptorPlatfromEvents_DISPINTERFACE_DEFINED__
#define ___DDriverAdaptorPlatfromEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DDriverAdaptorPlatfromEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DDriverAdaptorPlatfromEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("48EF2238-1E11-4157-8128-1E26B33BD1B4")
    _DDriverAdaptorPlatfromEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDriverAdaptorPlatfromEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDriverAdaptorPlatfromEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDriverAdaptorPlatfromEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDriverAdaptorPlatfromEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDriverAdaptorPlatfromEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDriverAdaptorPlatfromEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDriverAdaptorPlatfromEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDriverAdaptorPlatfromEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDriverAdaptorPlatfromEventsVtbl;

    interface _DDriverAdaptorPlatfromEvents
    {
        CONST_VTBL struct _DDriverAdaptorPlatfromEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDriverAdaptorPlatfromEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DDriverAdaptorPlatfromEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DDriverAdaptorPlatfromEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DDriverAdaptorPlatfromEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DDriverAdaptorPlatfromEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DDriverAdaptorPlatfromEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DDriverAdaptorPlatfromEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDriverAdaptorPlatfromEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DriverAdaptorPlatfrom;

#ifdef __cplusplus

class DECLSPEC_UUID("3A6B1F54-0BFB-4ED1-9504-B61910338BAE")
DriverAdaptorPlatfrom;
#endif
#endif /* __DriverAdaptorPlatfromLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


