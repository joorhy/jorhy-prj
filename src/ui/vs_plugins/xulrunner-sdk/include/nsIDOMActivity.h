/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/activities/interfaces/nsIDOMActivity.idl
 */

#ifndef __gen_nsIDOMActivity_h__
#define __gen_nsIDOMActivity_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

#ifndef __gen_nsIDOMDOMRequest_h__
#include "nsIDOMDOMRequest.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMMozActivity */
#define NS_IDOMMOZACTIVITY_IID_STR "1f59cd9a-b8b5-4a98-bd2a-897b73584946"

#define NS_IDOMMOZACTIVITY_IID \
  {0x1f59cd9a, 0xb8b5, 0x4a98, \
    { 0xbd, 0x2a, 0x89, 0x7b, 0x73, 0x58, 0x49, 0x46 }}

class NS_NO_VTABLE nsIDOMMozActivity : public nsIDOMDOMRequest {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMMOZACTIVITY_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMMozActivity, NS_IDOMMOZACTIVITY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMMOZACTIVITY \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMMOZACTIVITY(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMMOZACTIVITY(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMMozActivity : public nsIDOMMozActivity
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMMOZACTIVITY

  nsDOMMozActivity();

private:
  ~nsDOMMozActivity();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMMozActivity, nsIDOMMozActivity)

nsDOMMozActivity::nsDOMMozActivity()
{
  /* member initializers and constructor code */
}

nsDOMMozActivity::~nsDOMMozActivity()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMActivity_h__ */
