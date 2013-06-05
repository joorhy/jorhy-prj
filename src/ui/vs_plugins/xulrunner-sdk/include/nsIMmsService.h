/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/mms/interfaces/nsIMmsService.idl
 */

#ifndef __gen_nsIMmsService_h__
#define __gen_nsIMmsService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIMmsService */
#define NS_IMMSSERVICE_IID_STR "217ddd76-75db-4210-955d-8806cd8d87f9"

#define NS_IMMSSERVICE_IID \
  {0x217ddd76, 0x75db, 0x4210, \
    { 0x95, 0x5d, 0x88, 0x06, 0xcd, 0x8d, 0x87, 0xf9 }}

class NS_NO_VTABLE nsIMmsService : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IMMSSERVICE_IID)

  /* boolean hasSupport (); */
  NS_IMETHOD HasSupport(bool *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIMmsService, NS_IMMSSERVICE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIMMSSERVICE \
  NS_IMETHOD HasSupport(bool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIMMSSERVICE(_to) \
  NS_IMETHOD HasSupport(bool *_retval) { return _to HasSupport(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIMMSSERVICE(_to) \
  NS_IMETHOD HasSupport(bool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->HasSupport(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsMmsService : public nsIMmsService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIMMSSERVICE

  nsMmsService();

private:
  ~nsMmsService();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsMmsService, nsIMmsService)

nsMmsService::nsMmsService()
{
  /* member initializers and constructor code */
}

nsMmsService::~nsMmsService()
{
  /* destructor code */
}

/* boolean hasSupport (); */
NS_IMETHODIMP nsMmsService::HasSupport(bool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIMmsService_h__ */
