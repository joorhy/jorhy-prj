/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/svg/nsIDOMSVGEvent.idl
 */

#ifndef __gen_nsIDOMSVGEvent_h__
#define __gen_nsIDOMSVGEvent_h__


#ifndef __gen_nsIDOMEvent_h__
#include "nsIDOMEvent.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMSVGEvent */
#define NS_IDOMSVGEVENT_IID_STR "d6a2c07c-8a67-4a6e-adde-f668edb4a852"

#define NS_IDOMSVGEVENT_IID \
  {0xd6a2c07c, 0x8a67, 0x4a6e, \
    { 0xad, 0xde, 0xf6, 0x68, 0xed, 0xb4, 0xa8, 0x52 }}

class NS_NO_VTABLE nsIDOMSVGEvent : public nsIDOMEvent {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMSVGEVENT_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMSVGEvent, NS_IDOMSVGEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMSVGEVENT \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMSVGEVENT(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMSVGEVENT(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMSVGEvent : public nsIDOMSVGEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMSVGEVENT

  nsDOMSVGEvent();

private:
  ~nsDOMSVGEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMSVGEvent, nsIDOMSVGEvent)

nsDOMSVGEvent::nsDOMSVGEvent()
{
  /* member initializers and constructor code */
}

nsDOMSVGEvent::~nsDOMSVGEvent()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMSVGEvent_h__ */
