

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Nov 14 11:01:16 2013
 */
/* Compiler settings for .\active_plugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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


#ifndef __active_pluginidl_h__
#define __active_pluginidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___Dactive_plugin_FWD_DEFINED__
#define ___Dactive_plugin_FWD_DEFINED__
typedef interface _Dactive_plugin _Dactive_plugin;
#endif 	/* ___Dactive_plugin_FWD_DEFINED__ */


#ifndef ___Dactive_pluginEvents_FWD_DEFINED__
#define ___Dactive_pluginEvents_FWD_DEFINED__
typedef interface _Dactive_pluginEvents _Dactive_pluginEvents;
#endif 	/* ___Dactive_pluginEvents_FWD_DEFINED__ */


#ifndef __active_plugin_FWD_DEFINED__
#define __active_plugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class active_plugin active_plugin;
#else
typedef struct active_plugin active_plugin;
#endif /* __cplusplus */

#endif 	/* __active_plugin_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __active_pluginLib_LIBRARY_DEFINED__
#define __active_pluginLib_LIBRARY_DEFINED__

/* library active_pluginLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_active_pluginLib;

#ifndef ___Dactive_plugin_DISPINTERFACE_DEFINED__
#define ___Dactive_plugin_DISPINTERFACE_DEFINED__

/* dispinterface _Dactive_plugin */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__Dactive_plugin;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EE693F3B-1B36-422B-A118-A64AC2FA0CF2")
    _Dactive_plugin : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _Dactive_pluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _Dactive_plugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _Dactive_plugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _Dactive_plugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _Dactive_plugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _Dactive_plugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _Dactive_plugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _Dactive_plugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _Dactive_pluginVtbl;

    interface _Dactive_plugin
    {
        CONST_VTBL struct _Dactive_pluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _Dactive_plugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _Dactive_plugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _Dactive_plugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _Dactive_plugin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _Dactive_plugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _Dactive_plugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _Dactive_plugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___Dactive_plugin_DISPINTERFACE_DEFINED__ */


#ifndef ___Dactive_pluginEvents_DISPINTERFACE_DEFINED__
#define ___Dactive_pluginEvents_DISPINTERFACE_DEFINED__

/* dispinterface _Dactive_pluginEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__Dactive_pluginEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("97F111A3-770F-4A79-A2B4-464988846AC3")
    _Dactive_pluginEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _Dactive_pluginEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _Dactive_pluginEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _Dactive_pluginEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _Dactive_pluginEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _Dactive_pluginEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _Dactive_pluginEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _Dactive_pluginEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _Dactive_pluginEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _Dactive_pluginEventsVtbl;

    interface _Dactive_pluginEvents
    {
        CONST_VTBL struct _Dactive_pluginEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _Dactive_pluginEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _Dactive_pluginEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _Dactive_pluginEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _Dactive_pluginEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _Dactive_pluginEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _Dactive_pluginEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _Dactive_pluginEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___Dactive_pluginEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_active_plugin;

#ifdef __cplusplus

class DECLSPEC_UUID("50D171AE-0536-4FB6-BB9D-6C7EDDF0206B")
active_plugin;
#endif
#endif /* __active_pluginLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


