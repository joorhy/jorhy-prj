/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/file/nsIDOMArchiveRequest.idl
 */

#ifndef __gen_nsIDOMArchiveRequest_h__
#define __gen_nsIDOMArchiveRequest_h__


#ifndef __gen_nsIDOMDOMRequest_h__
#include "nsIDOMDOMRequest.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMArchiveReader; /* forward declaration */


/* starting interface:    nsIDOMArchiveRequest */
#define NS_IDOMARCHIVEREQUEST_IID_STR "6e59f1be-24bc-43ee-810a-8abb21599f29"

#define NS_IDOMARCHIVEREQUEST_IID \
  {0x6e59f1be, 0x24bc, 0x43ee, \
    { 0x81, 0x0a, 0x8a, 0xbb, 0x21, 0x59, 0x9f, 0x29 }}

class NS_NO_VTABLE nsIDOMArchiveRequest : public nsIDOMDOMRequest {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMARCHIVEREQUEST_IID)

  /* readonly attribute nsIDOMArchiveReader reader; */
  NS_IMETHOD GetReader(nsIDOMArchiveReader * *aReader) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMArchiveRequest, NS_IDOMARCHIVEREQUEST_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMARCHIVEREQUEST \
  NS_IMETHOD GetReader(nsIDOMArchiveReader * *aReader); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMARCHIVEREQUEST(_to) \
  NS_IMETHOD GetReader(nsIDOMArchiveReader * *aReader) { return _to GetReader(aReader); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMARCHIVEREQUEST(_to) \
  NS_IMETHOD GetReader(nsIDOMArchiveReader * *aReader) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetReader(aReader); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMArchiveRequest : public nsIDOMArchiveRequest
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMARCHIVEREQUEST

  nsDOMArchiveRequest();

private:
  ~nsDOMArchiveRequest();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMArchiveRequest, nsIDOMArchiveRequest)

nsDOMArchiveRequest::nsDOMArchiveRequest()
{
  /* member initializers and constructor code */
}

nsDOMArchiveRequest::~nsDOMArchiveRequest()
{
  /* destructor code */
}

/* readonly attribute nsIDOMArchiveReader reader; */
NS_IMETHODIMP nsDOMArchiveRequest::GetReader(nsIDOMArchiveReader * *aReader)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMArchiveRequest_h__ */
