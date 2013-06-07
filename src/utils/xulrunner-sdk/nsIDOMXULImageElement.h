/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/xul/nsIDOMXULImageElement.idl
 */

#ifndef __gen_nsIDOMXULImageElement_h__
#define __gen_nsIDOMXULImageElement_h__


#ifndef __gen_nsIDOMElement_h__
#include "nsIDOMElement.h"
#endif

#ifndef __gen_nsIDOMXULElement_h__
#include "nsIDOMXULElement.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMXULImageElement */
#define NS_IDOMXULIMAGEELEMENT_IID_STR "a21944ea-fb11-4b37-80ed-38c8d12d0649"

#define NS_IDOMXULIMAGEELEMENT_IID \
  {0xa21944ea, 0xfb11, 0x4b37, \
    { 0x80, 0xed, 0x38, 0xc8, 0xd1, 0x2d, 0x06, 0x49 }}

class NS_NO_VTABLE nsIDOMXULImageElement : public nsIDOMXULElement {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMXULIMAGEELEMENT_IID)

  /* attribute DOMString src; */
  NS_IMETHOD GetSrc(nsAString & aSrc) = 0;
  NS_IMETHOD SetSrc(const nsAString & aSrc) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMXULImageElement, NS_IDOMXULIMAGEELEMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMXULIMAGEELEMENT \
  NS_IMETHOD GetSrc(nsAString & aSrc); \
  NS_IMETHOD SetSrc(const nsAString & aSrc); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMXULIMAGEELEMENT(_to) \
  NS_IMETHOD GetSrc(nsAString & aSrc) { return _to GetSrc(aSrc); } \
  NS_IMETHOD SetSrc(const nsAString & aSrc) { return _to SetSrc(aSrc); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMXULIMAGEELEMENT(_to) \
  NS_IMETHOD GetSrc(nsAString & aSrc) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSrc(aSrc); } \
  NS_IMETHOD SetSrc(const nsAString & aSrc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSrc(aSrc); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMXULImageElement : public nsIDOMXULImageElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMXULIMAGEELEMENT

  nsDOMXULImageElement();

private:
  ~nsDOMXULImageElement();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMXULImageElement, nsIDOMXULImageElement)

nsDOMXULImageElement::nsDOMXULImageElement()
{
  /* member initializers and constructor code */
}

nsDOMXULImageElement::~nsDOMXULImageElement()
{
  /* destructor code */
}

/* attribute DOMString src; */
NS_IMETHODIMP nsDOMXULImageElement::GetSrc(nsAString & aSrc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMXULImageElement::SetSrc(const nsAString & aSrc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMXULImageElement_h__ */
