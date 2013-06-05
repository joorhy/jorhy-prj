/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/svg/nsIDOMSVGElement.idl
 */

#ifndef __gen_nsIDOMSVGElement_h__
#define __gen_nsIDOMSVGElement_h__


#ifndef __gen_nsIDOMElement_h__
#include "nsIDOMElement.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMSVGAnimatedString; /* forward declaration */

class nsIDOMCSSStyleDeclaration; /* forward declaration */

class nsIDOMCSSValue; /* forward declaration */


/* starting interface:    nsIDOMSVGElement */
#define NS_IDOMSVGELEMENT_IID_STR "7ccf8faf-29b4-4113-bb23-bc187bac27cf"

#define NS_IDOMSVGELEMENT_IID \
  {0x7ccf8faf, 0x29b4, 0x4113, \
    { 0xbb, 0x23, 0xbc, 0x18, 0x7b, 0xac, 0x27, 0xcf }}

class NS_NO_VTABLE nsIDOMSVGElement : public nsIDOMElement {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMSVGELEMENT_IID)

  /* attribute DOMString id; */
  NS_IMETHOD GetId(nsAString & aId) = 0;
  NS_IMETHOD SetId(const nsAString & aId) = 0;

  /* readonly attribute nsIDOMSVGElement ownerSVGElement; */
  NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGElement * *aOwnerSVGElement) = 0;

  /* readonly attribute nsIDOMSVGElement viewportElement; */
  NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement) = 0;

  /* readonly attribute nsIDOMSVGAnimatedString className; */
  NS_IMETHOD GetClassName(nsIDOMSVGAnimatedString * *aClassName) = 0;

  /* readonly attribute nsIDOMCSSStyleDeclaration style; */
  NS_IMETHOD GetStyle(nsIDOMCSSStyleDeclaration * *aStyle) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMSVGElement, NS_IDOMSVGELEMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMSVGELEMENT \
  NS_IMETHOD GetId(nsAString & aId); \
  NS_IMETHOD SetId(const nsAString & aId); \
  NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGElement * *aOwnerSVGElement); \
  NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement); \
  NS_IMETHOD GetClassName(nsIDOMSVGAnimatedString * *aClassName); \
  NS_IMETHOD GetStyle(nsIDOMCSSStyleDeclaration * *aStyle); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMSVGELEMENT(_to) \
  NS_IMETHOD GetId(nsAString & aId) { return _to GetId(aId); } \
  NS_IMETHOD SetId(const nsAString & aId) { return _to SetId(aId); } \
  NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGElement * *aOwnerSVGElement) { return _to GetOwnerSVGElement(aOwnerSVGElement); } \
  NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement) { return _to GetViewportElement(aViewportElement); } \
  NS_IMETHOD GetClassName(nsIDOMSVGAnimatedString * *aClassName) { return _to GetClassName(aClassName); } \
  NS_IMETHOD GetStyle(nsIDOMCSSStyleDeclaration * *aStyle) { return _to GetStyle(aStyle); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMSVGELEMENT(_to) \
  NS_IMETHOD GetId(nsAString & aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetId(aId); } \
  NS_IMETHOD SetId(const nsAString & aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetId(aId); } \
  NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGElement * *aOwnerSVGElement) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOwnerSVGElement(aOwnerSVGElement); } \
  NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetViewportElement(aViewportElement); } \
  NS_IMETHOD GetClassName(nsIDOMSVGAnimatedString * *aClassName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassName(aClassName); } \
  NS_IMETHOD GetStyle(nsIDOMCSSStyleDeclaration * *aStyle) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStyle(aStyle); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMSVGElement : public nsIDOMSVGElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMSVGELEMENT

  nsDOMSVGElement();

private:
  ~nsDOMSVGElement();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMSVGElement, nsIDOMSVGElement)

nsDOMSVGElement::nsDOMSVGElement()
{
  /* member initializers and constructor code */
}

nsDOMSVGElement::~nsDOMSVGElement()
{
  /* destructor code */
}

/* attribute DOMString id; */
NS_IMETHODIMP nsDOMSVGElement::GetId(nsAString & aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMSVGElement::SetId(const nsAString & aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMSVGElement ownerSVGElement; */
NS_IMETHODIMP nsDOMSVGElement::GetOwnerSVGElement(nsIDOMSVGElement * *aOwnerSVGElement)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMSVGElement viewportElement; */
NS_IMETHODIMP nsDOMSVGElement::GetViewportElement(nsIDOMSVGElement * *aViewportElement)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMSVGAnimatedString className; */
NS_IMETHODIMP nsDOMSVGElement::GetClassName(nsIDOMSVGAnimatedString * *aClassName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMCSSStyleDeclaration style; */
NS_IMETHODIMP nsDOMSVGElement::GetStyle(nsIDOMCSSStyleDeclaration * *aStyle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMSVGElement_h__ */
