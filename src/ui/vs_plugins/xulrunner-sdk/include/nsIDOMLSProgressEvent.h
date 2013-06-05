/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/load-save/nsIDOMLSProgressEvent.idl
 */

#ifndef __gen_nsIDOMLSProgressEvent_h__
#define __gen_nsIDOMLSProgressEvent_h__


#ifndef __gen_nsIDOMEvent_h__
#include "nsIDOMEvent.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMLSInput; /* forward declaration */


/* starting interface:    nsIDOMLSProgressEvent */
#define NS_IDOMLSPROGRESSEVENT_IID_STR "5343c259-78c1-4f20-a81f-5ddce4f0188e"

#define NS_IDOMLSPROGRESSEVENT_IID \
  {0x5343c259, 0x78c1, 0x4f20, \
    { 0xa8, 0x1f, 0x5d, 0xdc, 0xe4, 0xf0, 0x18, 0x8e }}

class NS_NO_VTABLE nsIDOMLSProgressEvent : public nsIDOMEvent {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMLSPROGRESSEVENT_IID)

  /* readonly attribute nsIDOMLSInput input; */
  NS_IMETHOD GetInput(nsIDOMLSInput * *aInput) = 0;

  /* readonly attribute unsigned long position; */
  NS_IMETHOD GetPosition(uint32_t *aPosition) = 0;

  /* readonly attribute unsigned long totalSize; */
  NS_IMETHOD GetTotalSize(uint32_t *aTotalSize) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMLSProgressEvent, NS_IDOMLSPROGRESSEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMLSPROGRESSEVENT \
  NS_IMETHOD GetInput(nsIDOMLSInput * *aInput); \
  NS_IMETHOD GetPosition(uint32_t *aPosition); \
  NS_IMETHOD GetTotalSize(uint32_t *aTotalSize); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMLSPROGRESSEVENT(_to) \
  NS_IMETHOD GetInput(nsIDOMLSInput * *aInput) { return _to GetInput(aInput); } \
  NS_IMETHOD GetPosition(uint32_t *aPosition) { return _to GetPosition(aPosition); } \
  NS_IMETHOD GetTotalSize(uint32_t *aTotalSize) { return _to GetTotalSize(aTotalSize); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMLSPROGRESSEVENT(_to) \
  NS_IMETHOD GetInput(nsIDOMLSInput * *aInput) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInput(aInput); } \
  NS_IMETHOD GetPosition(uint32_t *aPosition) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPosition(aPosition); } \
  NS_IMETHOD GetTotalSize(uint32_t *aTotalSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTotalSize(aTotalSize); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMLSProgressEvent : public nsIDOMLSProgressEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMLSPROGRESSEVENT

  nsDOMLSProgressEvent();

private:
  ~nsDOMLSProgressEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMLSProgressEvent, nsIDOMLSProgressEvent)

nsDOMLSProgressEvent::nsDOMLSProgressEvent()
{
  /* member initializers and constructor code */
}

nsDOMLSProgressEvent::~nsDOMLSProgressEvent()
{
  /* destructor code */
}

/* readonly attribute nsIDOMLSInput input; */
NS_IMETHODIMP nsDOMLSProgressEvent::GetInput(nsIDOMLSInput * *aInput)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long position; */
NS_IMETHODIMP nsDOMLSProgressEvent::GetPosition(uint32_t *aPosition)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long totalSize; */
NS_IMETHODIMP nsDOMLSProgressEvent::GetTotalSize(uint32_t *aTotalSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMLSProgressEvent_h__ */
