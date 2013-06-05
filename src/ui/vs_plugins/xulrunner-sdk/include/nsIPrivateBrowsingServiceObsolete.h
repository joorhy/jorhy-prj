/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/netwerk/base/public/nsIPrivateBrowsingServiceObsolete.idl
 */

#ifndef __gen_nsIPrivateBrowsingServiceObsolete_h__
#define __gen_nsIPrivateBrowsingServiceObsolete_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIPrivateBrowsingService */
#define NS_IPRIVATEBROWSINGSERVICE_IID_STR "7ad4b7f1-5a88-41aa-9b40-713009bc57b3"

#define NS_IPRIVATEBROWSINGSERVICE_IID \
  {0x7ad4b7f1, 0x5a88, 0x41aa, \
    { 0x9b, 0x40, 0x71, 0x30, 0x09, 0xbc, 0x57, 0xb3 }}

class NS_NO_VTABLE nsIPrivateBrowsingService : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IPRIVATEBROWSINGSERVICE_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIPrivateBrowsingService, NS_IPRIVATEBROWSINGSERVICE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPRIVATEBROWSINGSERVICE \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPRIVATEBROWSINGSERVICE(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPRIVATEBROWSINGSERVICE(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsPrivateBrowsingService : public nsIPrivateBrowsingService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPRIVATEBROWSINGSERVICE

  nsPrivateBrowsingService();

private:
  ~nsPrivateBrowsingService();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsPrivateBrowsingService, nsIPrivateBrowsingService)

nsPrivateBrowsingService::nsPrivateBrowsingService()
{
  /* member initializers and constructor code */
}

nsPrivateBrowsingService::~nsPrivateBrowsingService()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIPrivateBrowsingServiceObsolete_h__ */
