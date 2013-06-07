/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/base/nsISiteSpecificUserAgent.idl
 */

#ifndef __gen_nsISiteSpecificUserAgent_h__
#define __gen_nsISiteSpecificUserAgent_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIURI; /* forward declaration */


/* starting interface:    nsISiteSpecificUserAgent */
#define NS_ISITESPECIFICUSERAGENT_IID_STR "604a64af-9809-4c2f-a91d-f6ebfa21f6cb"

#define NS_ISITESPECIFICUSERAGENT_IID \
  {0x604a64af, 0x9809, 0x4c2f, \
    { 0xa9, 0x1d, 0xf6, 0xeb, 0xfa, 0x21, 0xf6, 0xcb }}

class NS_NO_VTABLE nsISiteSpecificUserAgent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISITESPECIFICUSERAGENT_IID)

  /* AString getUserAgentForURI (in nsIURI aURI); */
  NS_IMETHOD GetUserAgentForURI(nsIURI *aURI, nsAString & _retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISiteSpecificUserAgent, NS_ISITESPECIFICUSERAGENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISITESPECIFICUSERAGENT \
  NS_IMETHOD GetUserAgentForURI(nsIURI *aURI, nsAString & _retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISITESPECIFICUSERAGENT(_to) \
  NS_IMETHOD GetUserAgentForURI(nsIURI *aURI, nsAString & _retval) { return _to GetUserAgentForURI(aURI, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISITESPECIFICUSERAGENT(_to) \
  NS_IMETHOD GetUserAgentForURI(nsIURI *aURI, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUserAgentForURI(aURI, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSiteSpecificUserAgent : public nsISiteSpecificUserAgent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISITESPECIFICUSERAGENT

  nsSiteSpecificUserAgent();

private:
  ~nsSiteSpecificUserAgent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSiteSpecificUserAgent, nsISiteSpecificUserAgent)

nsSiteSpecificUserAgent::nsSiteSpecificUserAgent()
{
  /* member initializers and constructor code */
}

nsSiteSpecificUserAgent::~nsSiteSpecificUserAgent()
{
  /* destructor code */
}

/* AString getUserAgentForURI (in nsIURI aURI); */
NS_IMETHODIMP nsSiteSpecificUserAgent::GetUserAgentForURI(nsIURI *aURI, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISiteSpecificUserAgent_h__ */
