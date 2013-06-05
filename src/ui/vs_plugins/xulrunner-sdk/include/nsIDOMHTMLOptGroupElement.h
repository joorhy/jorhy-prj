/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/html/nsIDOMHTMLOptGroupElement.idl
 */

#ifndef __gen_nsIDOMHTMLOptGroupElement_h__
#define __gen_nsIDOMHTMLOptGroupElement_h__


#ifndef __gen_nsIDOMHTMLElement_h__
#include "nsIDOMHTMLElement.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMHTMLOptGroupElement */
#define NS_IDOMHTMLOPTGROUPELEMENT_IID_STR "bedb0d8d-030e-409a-b3b5-28dc0e0d9c34"

#define NS_IDOMHTMLOPTGROUPELEMENT_IID \
  {0xbedb0d8d, 0x030e, 0x409a, \
    { 0xb3, 0xb5, 0x28, 0xdc, 0x0e, 0x0d, 0x9c, 0x34 }}

class NS_NO_VTABLE nsIDOMHTMLOptGroupElement : public nsIDOMHTMLElement {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMHTMLOPTGROUPELEMENT_IID)

  /* attribute boolean disabled; */
  NS_IMETHOD GetDisabled(bool *aDisabled) = 0;
  NS_IMETHOD SetDisabled(bool aDisabled) = 0;

  /* attribute DOMString label; */
  NS_IMETHOD GetLabel(nsAString & aLabel) = 0;
  NS_IMETHOD SetLabel(const nsAString & aLabel) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMHTMLOptGroupElement, NS_IDOMHTMLOPTGROUPELEMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMHTMLOPTGROUPELEMENT \
  NS_IMETHOD GetDisabled(bool *aDisabled); \
  NS_IMETHOD SetDisabled(bool aDisabled); \
  NS_IMETHOD GetLabel(nsAString & aLabel); \
  NS_IMETHOD SetLabel(const nsAString & aLabel); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMHTMLOPTGROUPELEMENT(_to) \
  NS_IMETHOD GetDisabled(bool *aDisabled) { return _to GetDisabled(aDisabled); } \
  NS_IMETHOD SetDisabled(bool aDisabled) { return _to SetDisabled(aDisabled); } \
  NS_IMETHOD GetLabel(nsAString & aLabel) { return _to GetLabel(aLabel); } \
  NS_IMETHOD SetLabel(const nsAString & aLabel) { return _to SetLabel(aLabel); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMHTMLOPTGROUPELEMENT(_to) \
  NS_IMETHOD GetDisabled(bool *aDisabled) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDisabled(aDisabled); } \
  NS_IMETHOD SetDisabled(bool aDisabled) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDisabled(aDisabled); } \
  NS_IMETHOD GetLabel(nsAString & aLabel) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLabel(aLabel); } \
  NS_IMETHOD SetLabel(const nsAString & aLabel) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLabel(aLabel); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMHTMLOptGroupElement : public nsIDOMHTMLOptGroupElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMHTMLOPTGROUPELEMENT

  nsDOMHTMLOptGroupElement();

private:
  ~nsDOMHTMLOptGroupElement();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMHTMLOptGroupElement, nsIDOMHTMLOptGroupElement)

nsDOMHTMLOptGroupElement::nsDOMHTMLOptGroupElement()
{
  /* member initializers and constructor code */
}

nsDOMHTMLOptGroupElement::~nsDOMHTMLOptGroupElement()
{
  /* destructor code */
}

/* attribute boolean disabled; */
NS_IMETHODIMP nsDOMHTMLOptGroupElement::GetDisabled(bool *aDisabled)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMHTMLOptGroupElement::SetDisabled(bool aDisabled)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute DOMString label; */
NS_IMETHODIMP nsDOMHTMLOptGroupElement::GetLabel(nsAString & aLabel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMHTMLOptGroupElement::SetLabel(const nsAString & aLabel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMHTMLOptGroupElement_h__ */
