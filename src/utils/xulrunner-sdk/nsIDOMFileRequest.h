/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/file/nsIDOMFileRequest.idl
 */

#ifndef __gen_nsIDOMFileRequest_h__
#define __gen_nsIDOMFileRequest_h__


#ifndef __gen_nsIDOMDOMRequest_h__
#include "nsIDOMDOMRequest.h"
#endif

#include "jspubtd.h"

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMEventListener; /* forward declaration */

class nsIDOMLockedFile; /* forward declaration */


/* starting interface:    nsIDOMFileRequest */
#define NS_IDOMFILEREQUEST_IID_STR "6733d649-0acb-487d-8a7d-f102ac4419e9"

#define NS_IDOMFILEREQUEST_IID \
  {0x6733d649, 0x0acb, 0x487d, \
    { 0x8a, 0x7d, 0xf1, 0x02, 0xac, 0x44, 0x19, 0xe9 }}

class NS_NO_VTABLE nsIDOMFileRequest : public nsIDOMDOMRequest {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMFILEREQUEST_IID)

  /* readonly attribute nsIDOMLockedFile lockedFile; */
  NS_IMETHOD GetLockedFile(nsIDOMLockedFile * *aLockedFile) = 0;

  /* [implicit_jscontext] attribute jsval onprogress; */
  NS_IMETHOD GetOnprogress(JSContext* cx, JS::Value *aOnprogress) = 0;
  NS_IMETHOD SetOnprogress(JSContext* cx, const JS::Value & aOnprogress) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMFileRequest, NS_IDOMFILEREQUEST_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMFILEREQUEST \
  NS_IMETHOD GetLockedFile(nsIDOMLockedFile * *aLockedFile); \
  NS_IMETHOD GetOnprogress(JSContext* cx, JS::Value *aOnprogress); \
  NS_IMETHOD SetOnprogress(JSContext* cx, const JS::Value & aOnprogress); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMFILEREQUEST(_to) \
  NS_IMETHOD GetLockedFile(nsIDOMLockedFile * *aLockedFile) { return _to GetLockedFile(aLockedFile); } \
  NS_IMETHOD GetOnprogress(JSContext* cx, JS::Value *aOnprogress) { return _to GetOnprogress(cx, aOnprogress); } \
  NS_IMETHOD SetOnprogress(JSContext* cx, const JS::Value & aOnprogress) { return _to SetOnprogress(cx, aOnprogress); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMFILEREQUEST(_to) \
  NS_IMETHOD GetLockedFile(nsIDOMLockedFile * *aLockedFile) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLockedFile(aLockedFile); } \
  NS_IMETHOD GetOnprogress(JSContext* cx, JS::Value *aOnprogress) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOnprogress(cx, aOnprogress); } \
  NS_IMETHOD SetOnprogress(JSContext* cx, const JS::Value & aOnprogress) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOnprogress(cx, aOnprogress); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMFileRequest : public nsIDOMFileRequest
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMFILEREQUEST

  nsDOMFileRequest();

private:
  ~nsDOMFileRequest();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMFileRequest, nsIDOMFileRequest)

nsDOMFileRequest::nsDOMFileRequest()
{
  /* member initializers and constructor code */
}

nsDOMFileRequest::~nsDOMFileRequest()
{
  /* destructor code */
}

/* readonly attribute nsIDOMLockedFile lockedFile; */
NS_IMETHODIMP nsDOMFileRequest::GetLockedFile(nsIDOMLockedFile * *aLockedFile)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [implicit_jscontext] attribute jsval onprogress; */
NS_IMETHODIMP nsDOMFileRequest::GetOnprogress(JSContext* cx, JS::Value *aOnprogress)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMFileRequest::SetOnprogress(JSContext* cx, const JS::Value & aOnprogress)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMFileRequest_h__ */
