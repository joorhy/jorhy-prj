/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/activities/interfaces/nsIActivityProxy.idl
 */

#ifndef __gen_nsIActivityProxy_h__
#define __gen_nsIActivityProxy_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMMozActivity; /* forward declaration */

class nsIDOMMozActivityOptions; /* forward declaration */

class nsIDOMWindow; /* forward declaration */


/* starting interface:    nsIActivityProxy */
#define NS_IACTIVITYPROXY_IID_STR "3f9e0695-f466-4111-a8fa-ed5c0751c42b"

#define NS_IACTIVITYPROXY_IID \
  {0x3f9e0695, 0xf466, 0x4111, \
    { 0xa8, 0xfa, 0xed, 0x5c, 0x07, 0x51, 0xc4, 0x2b }}

class NS_NO_VTABLE nsIActivityProxy : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACTIVITYPROXY_IID)

  /* void startActivity (in nsIDOMMozActivity activity, in nsIDOMMozActivityOptions options, in nsIDOMWindow window); */
  NS_IMETHOD StartActivity(nsIDOMMozActivity *activity, nsIDOMMozActivityOptions *options, nsIDOMWindow *window) = 0;

  /* void cleanup (); */
  NS_IMETHOD Cleanup(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIActivityProxy, NS_IACTIVITYPROXY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACTIVITYPROXY \
  NS_IMETHOD StartActivity(nsIDOMMozActivity *activity, nsIDOMMozActivityOptions *options, nsIDOMWindow *window); \
  NS_IMETHOD Cleanup(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACTIVITYPROXY(_to) \
  NS_IMETHOD StartActivity(nsIDOMMozActivity *activity, nsIDOMMozActivityOptions *options, nsIDOMWindow *window) { return _to StartActivity(activity, options, window); } \
  NS_IMETHOD Cleanup(void) { return _to Cleanup(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACTIVITYPROXY(_to) \
  NS_IMETHOD StartActivity(nsIDOMMozActivity *activity, nsIDOMMozActivityOptions *options, nsIDOMWindow *window) { return !_to ? NS_ERROR_NULL_POINTER : _to->StartActivity(activity, options, window); } \
  NS_IMETHOD Cleanup(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Cleanup(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsActivityProxy : public nsIActivityProxy
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACTIVITYPROXY

  nsActivityProxy();

private:
  ~nsActivityProxy();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsActivityProxy, nsIActivityProxy)

nsActivityProxy::nsActivityProxy()
{
  /* member initializers and constructor code */
}

nsActivityProxy::~nsActivityProxy()
{
  /* destructor code */
}

/* void startActivity (in nsIDOMMozActivity activity, in nsIDOMMozActivityOptions options, in nsIDOMWindow window); */
NS_IMETHODIMP nsActivityProxy::StartActivity(nsIDOMMozActivity *activity, nsIDOMMozActivityOptions *options, nsIDOMWindow *window)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void cleanup (); */
NS_IMETHODIMP nsActivityProxy::Cleanup()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIActivityProxy_h__ */
