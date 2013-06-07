/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/indexedDB/nsIIndexedDatabaseManager.idl
 */

#ifndef __gen_nsIIndexedDatabaseManager_h__
#define __gen_nsIIndexedDatabaseManager_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#include "jspubtd.h"

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIURI; /* forward declaration */


/* starting interface:    nsIIndexedDatabaseUsageCallback */
#define NS_IINDEXEDDATABASEUSAGECALLBACK_IID_STR "38f15cc7-2df0-4a90-8b7f-1606b2243522"

#define NS_IINDEXEDDATABASEUSAGECALLBACK_IID \
  {0x38f15cc7, 0x2df0, 0x4a90, \
    { 0x8b, 0x7f, 0x16, 0x06, 0xb2, 0x24, 0x35, 0x22 }}

class NS_NO_VTABLE nsIIndexedDatabaseUsageCallback : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IINDEXEDDATABASEUSAGECALLBACK_IID)

  /* void onUsageResult (in nsIURI aURI, in unsigned long long aUsage, in unsigned long long aFileUsage, in unsigned long aAppId, in boolean aInMozBrowserOnly); */
  NS_IMETHOD OnUsageResult(nsIURI *aURI, uint64_t aUsage, uint64_t aFileUsage, uint32_t aAppId, bool aInMozBrowserOnly) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIIndexedDatabaseUsageCallback, NS_IINDEXEDDATABASEUSAGECALLBACK_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIINDEXEDDATABASEUSAGECALLBACK \
  NS_IMETHOD OnUsageResult(nsIURI *aURI, uint64_t aUsage, uint64_t aFileUsage, uint32_t aAppId, bool aInMozBrowserOnly); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIINDEXEDDATABASEUSAGECALLBACK(_to) \
  NS_IMETHOD OnUsageResult(nsIURI *aURI, uint64_t aUsage, uint64_t aFileUsage, uint32_t aAppId, bool aInMozBrowserOnly) { return _to OnUsageResult(aURI, aUsage, aFileUsage, aAppId, aInMozBrowserOnly); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIINDEXEDDATABASEUSAGECALLBACK(_to) \
  NS_IMETHOD OnUsageResult(nsIURI *aURI, uint64_t aUsage, uint64_t aFileUsage, uint32_t aAppId, bool aInMozBrowserOnly) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnUsageResult(aURI, aUsage, aFileUsage, aAppId, aInMozBrowserOnly); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsIndexedDatabaseUsageCallback : public nsIIndexedDatabaseUsageCallback
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIINDEXEDDATABASEUSAGECALLBACK

  nsIndexedDatabaseUsageCallback();

private:
  ~nsIndexedDatabaseUsageCallback();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsIndexedDatabaseUsageCallback, nsIIndexedDatabaseUsageCallback)

nsIndexedDatabaseUsageCallback::nsIndexedDatabaseUsageCallback()
{
  /* member initializers and constructor code */
}

nsIndexedDatabaseUsageCallback::~nsIndexedDatabaseUsageCallback()
{
  /* destructor code */
}

/* void onUsageResult (in nsIURI aURI, in unsigned long long aUsage, in unsigned long long aFileUsage, in unsigned long aAppId, in boolean aInMozBrowserOnly); */
NS_IMETHODIMP nsIndexedDatabaseUsageCallback::OnUsageResult(nsIURI *aURI, uint64_t aUsage, uint64_t aFileUsage, uint32_t aAppId, bool aInMozBrowserOnly)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIIndexedDatabaseManager */
#define NS_IINDEXEDDATABASEMANAGER_IID_STR "e5168115-baff-4559-887e-7c0405cc9e63"

#define NS_IINDEXEDDATABASEMANAGER_IID \
  {0xe5168115, 0xbaff, 0x4559, \
    { 0x88, 0x7e, 0x7c, 0x04, 0x05, 0xcc, 0x9e, 0x63 }}

class NS_NO_VTABLE nsIIndexedDatabaseManager : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IINDEXEDDATABASEMANAGER_IID)

  /* [optional_argc] void getUsageForURI (in nsIURI aURI, in nsIIndexedDatabaseUsageCallback aCallback, [optional] in unsigned long aAppId, [optional] in boolean aInMozBrowserOnly); */
  NS_IMETHOD GetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) = 0;

  /* [optional_argc] void cancelGetUsageForURI (in nsIURI aURI, in nsIIndexedDatabaseUsageCallback aCallback, [optional] in unsigned long aAppId, [optional] in boolean aInMozBrowserOnly); */
  NS_IMETHOD CancelGetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) = 0;

  /* [optional_argc] void clearDatabasesForURI (in nsIURI aURI, [optional] in unsigned long aAppId, [optional] in boolean aInMozBrowserOnly); */
  NS_IMETHOD ClearDatabasesForURI(nsIURI *aURI, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) = 0;

  /* [implicit_jscontext] void initWindowless (in jsval aObject); */
  NS_IMETHOD InitWindowless(const JS::Value & aObject, JSContext* cx) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIIndexedDatabaseManager, NS_IINDEXEDDATABASEMANAGER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIINDEXEDDATABASEMANAGER \
  NS_IMETHOD GetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc); \
  NS_IMETHOD CancelGetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc); \
  NS_IMETHOD ClearDatabasesForURI(nsIURI *aURI, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc); \
  NS_IMETHOD InitWindowless(const JS::Value & aObject, JSContext* cx); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIINDEXEDDATABASEMANAGER(_to) \
  NS_IMETHOD GetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) { return _to GetUsageForURI(aURI, aCallback, aAppId, aInMozBrowserOnly, _argc); } \
  NS_IMETHOD CancelGetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) { return _to CancelGetUsageForURI(aURI, aCallback, aAppId, aInMozBrowserOnly, _argc); } \
  NS_IMETHOD ClearDatabasesForURI(nsIURI *aURI, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) { return _to ClearDatabasesForURI(aURI, aAppId, aInMozBrowserOnly, _argc); } \
  NS_IMETHOD InitWindowless(const JS::Value & aObject, JSContext* cx) { return _to InitWindowless(aObject, cx); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIINDEXEDDATABASEMANAGER(_to) \
  NS_IMETHOD GetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUsageForURI(aURI, aCallback, aAppId, aInMozBrowserOnly, _argc); } \
  NS_IMETHOD CancelGetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) { return !_to ? NS_ERROR_NULL_POINTER : _to->CancelGetUsageForURI(aURI, aCallback, aAppId, aInMozBrowserOnly, _argc); } \
  NS_IMETHOD ClearDatabasesForURI(nsIURI *aURI, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearDatabasesForURI(aURI, aAppId, aInMozBrowserOnly, _argc); } \
  NS_IMETHOD InitWindowless(const JS::Value & aObject, JSContext* cx) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitWindowless(aObject, cx); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsIndexedDatabaseManager : public nsIIndexedDatabaseManager
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIINDEXEDDATABASEMANAGER

  nsIndexedDatabaseManager();

private:
  ~nsIndexedDatabaseManager();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsIndexedDatabaseManager, nsIIndexedDatabaseManager)

nsIndexedDatabaseManager::nsIndexedDatabaseManager()
{
  /* member initializers and constructor code */
}

nsIndexedDatabaseManager::~nsIndexedDatabaseManager()
{
  /* destructor code */
}

/* [optional_argc] void getUsageForURI (in nsIURI aURI, in nsIIndexedDatabaseUsageCallback aCallback, [optional] in unsigned long aAppId, [optional] in boolean aInMozBrowserOnly); */
NS_IMETHODIMP nsIndexedDatabaseManager::GetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [optional_argc] void cancelGetUsageForURI (in nsIURI aURI, in nsIIndexedDatabaseUsageCallback aCallback, [optional] in unsigned long aAppId, [optional] in boolean aInMozBrowserOnly); */
NS_IMETHODIMP nsIndexedDatabaseManager::CancelGetUsageForURI(nsIURI *aURI, nsIIndexedDatabaseUsageCallback *aCallback, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [optional_argc] void clearDatabasesForURI (in nsIURI aURI, [optional] in unsigned long aAppId, [optional] in boolean aInMozBrowserOnly); */
NS_IMETHODIMP nsIndexedDatabaseManager::ClearDatabasesForURI(nsIURI *aURI, uint32_t aAppId, bool aInMozBrowserOnly, uint8_t _argc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [implicit_jscontext] void initWindowless (in jsval aObject); */
NS_IMETHODIMP nsIndexedDatabaseManager::InitWindowless(const JS::Value & aObject, JSContext* cx)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIIndexedDatabaseManager_h__ */
