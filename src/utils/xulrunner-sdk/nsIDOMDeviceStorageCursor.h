/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/devicestorage/nsIDOMDeviceStorageCursor.idl
 */

#ifndef __gen_nsIDOMDeviceStorageCursor_h__
#define __gen_nsIDOMDeviceStorageCursor_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMDeviceStorageCursor */
#define NS_IDOMDEVICESTORAGECURSOR_IID_STR "995dff99-ed70-4780-ac9a-4b58cd491186"

#define NS_IDOMDEVICESTORAGECURSOR_IID \
  {0x995dff99, 0xed70, 0x4780, \
    { 0xac, 0x9a, 0x4b, 0x58, 0xcd, 0x49, 0x11, 0x86 }}

class NS_NO_VTABLE nsIDOMDeviceStorageCursor : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMDEVICESTORAGECURSOR_IID)

  /* void continue (); */
  NS_IMETHOD Continue(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMDeviceStorageCursor, NS_IDOMDEVICESTORAGECURSOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMDEVICESTORAGECURSOR \
  NS_IMETHOD Continue(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMDEVICESTORAGECURSOR(_to) \
  NS_IMETHOD Continue(void) { return _to Continue(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMDEVICESTORAGECURSOR(_to) \
  NS_IMETHOD Continue(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Continue(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMDeviceStorageCursor : public nsIDOMDeviceStorageCursor
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMDEVICESTORAGECURSOR

  nsDOMDeviceStorageCursor();

private:
  ~nsDOMDeviceStorageCursor();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMDeviceStorageCursor, nsIDOMDeviceStorageCursor)

nsDOMDeviceStorageCursor::nsDOMDeviceStorageCursor()
{
  /* member initializers and constructor code */
}

nsDOMDeviceStorageCursor::~nsDOMDeviceStorageCursor()
{
  /* destructor code */
}

/* void continue (); */
NS_IMETHODIMP nsDOMDeviceStorageCursor::Continue()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMDeviceStorageCursor_h__ */
