/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/sms/interfaces/nsIDOMSmsRequest.idl
 */

#ifndef __gen_nsIDOMSmsRequest_h__
#define __gen_nsIDOMSmsRequest_h__


#ifndef __gen_nsIDOMDOMRequest_h__
#include "nsIDOMDOMRequest.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMMozSmsRequest */
#define NS_IDOMMOZSMSREQUEST_IID_STR "ae6acad4-3174-44d6-a491-9ff94ab847c2"

#define NS_IDOMMOZSMSREQUEST_IID \
  {0xae6acad4, 0x3174, 0x44d6, \
    { 0xa4, 0x91, 0x9f, 0xf9, 0x4a, 0xb8, 0x47, 0xc2 }}

class NS_NO_VTABLE nsIDOMMozSmsRequest : public nsIDOMDOMRequest {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMMOZSMSREQUEST_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMMozSmsRequest, NS_IDOMMOZSMSREQUEST_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMMOZSMSREQUEST \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMMOZSMSREQUEST(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMMOZSMSREQUEST(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMMozSmsRequest : public nsIDOMMozSmsRequest
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMMOZSMSREQUEST

  nsDOMMozSmsRequest();

private:
  ~nsDOMMozSmsRequest();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMMozSmsRequest, nsIDOMMozSmsRequest)

nsDOMMozSmsRequest::nsDOMMozSmsRequest()
{
  /* member initializers and constructor code */
}

nsDOMMozSmsRequest::~nsDOMMozSmsRequest()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMSmsRequest_h__ */
