

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Mar 31 13:38:20 2017
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __DRVideoRealidl_h__
#define __DRVideoRealidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DDRVideoReal_FWD_DEFINED__
#define ___DDRVideoReal_FWD_DEFINED__
typedef interface _DDRVideoReal _DDRVideoReal;
#endif 	/* ___DDRVideoReal_FWD_DEFINED__ */


#ifndef ___DDRVideoRealEvents_FWD_DEFINED__
#define ___DDRVideoRealEvents_FWD_DEFINED__
typedef interface _DDRVideoRealEvents _DDRVideoRealEvents;
#endif 	/* ___DDRVideoRealEvents_FWD_DEFINED__ */


#ifndef __DRVideoReal_FWD_DEFINED__
#define __DRVideoReal_FWD_DEFINED__

#ifdef __cplusplus
typedef class DRVideoReal DRVideoReal;
#else
typedef struct DRVideoReal DRVideoReal;
#endif /* __cplusplus */

#endif 	/* __DRVideoReal_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __DRVideoRealLib_LIBRARY_DEFINED__
#define __DRVideoRealLib_LIBRARY_DEFINED__

/* library DRVideoRealLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_DRVideoRealLib;

#ifndef ___DDRVideoReal_DISPINTERFACE_DEFINED__
#define ___DDRVideoReal_DISPINTERFACE_DEFINED__

/* dispinterface _DDRVideoReal */
/* [uuid] */ 


EXTERN_C const IID DIID__DDRVideoReal;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("51131C17-F78B-4BB3-83B6-EFF0FCAC2B56")
    _DDRVideoReal : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDRVideoRealVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDRVideoReal * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDRVideoReal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDRVideoReal * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDRVideoReal * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDRVideoReal * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDRVideoReal * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDRVideoReal * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDRVideoRealVtbl;

    interface _DDRVideoReal
    {
        CONST_VTBL struct _DDRVideoRealVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDRVideoReal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DDRVideoReal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DDRVideoReal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DDRVideoReal_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DDRVideoReal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DDRVideoReal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DDRVideoReal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDRVideoReal_DISPINTERFACE_DEFINED__ */


#ifndef ___DDRVideoRealEvents_DISPINTERFACE_DEFINED__
#define ___DDRVideoRealEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DDRVideoRealEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DDRVideoRealEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("565438E1-65B3-4F8E-8C6E-A17BD6B97026")
    _DDRVideoRealEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDRVideoRealEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDRVideoRealEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDRVideoRealEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDRVideoRealEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDRVideoRealEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDRVideoRealEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDRVideoRealEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDRVideoRealEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDRVideoRealEventsVtbl;

    interface _DDRVideoRealEvents
    {
        CONST_VTBL struct _DDRVideoRealEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDRVideoRealEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DDRVideoRealEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DDRVideoRealEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DDRVideoRealEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DDRVideoRealEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DDRVideoRealEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DDRVideoRealEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDRVideoRealEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DRVideoReal;

#ifdef __cplusplus

class DECLSPEC_UUID("E457FB87-4610-43D1-B99F-56E108614880")
DRVideoReal;
#endif
#endif /* __DRVideoRealLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


