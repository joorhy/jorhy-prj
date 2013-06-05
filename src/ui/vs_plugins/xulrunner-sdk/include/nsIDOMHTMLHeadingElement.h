/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/html/nsIDOMHTMLHeadingElement.idl
 */

#ifndef __gen_nsIDOMHTMLHeadingElement_h__
#define __gen_nsIDOMHTMLHeadingElement_h__


#ifndef __gen_nsIDOMHTMLElement_h__
#include "nsIDOMHTMLElement.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMHTMLHeadingElement */
#define NS_IDOMHTMLHEADINGELEMENT_IID_STR "b302d445-7b7b-4b6d-9c6d-aec30ce4f2e0"

#define NS_IDOMHTMLHEADINGELEMENT_IID \
  {0xb302d445, 0x7b7b, 0x4b6d, \
    { 0x9c, 0x6d, 0xae, 0xc3, 0x0c, 0xe4, 0xf2, 0xe0 }}

class NS_NO_VTABLE nsIDOMHTMLHeadingElement : public nsIDOMHTMLElement {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMHTMLHEADINGELEMENT_IID)

  /* attribute DOMString align; */
  NS_IMETHOD GetAlign(nsAString & aAlign) = 0;
  NS_IMETHOD SetAlign(const nsAString & aAlign) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMHTMLHeadingElement, NS_IDOMHTMLHEADINGELEMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMHTMLHEADINGELEMENT \
  NS_IMETHOD GetAlign(nsAString & aAlign); \
  NS_IMETHOD SetAlign(const nsAString & aAlign); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMHTMLHEADINGELEMENT(_to) \
  NS_IMETHOD GetAlign(nsAString & aAlign) { return _to GetAlign(aAlign); } \
  NS_IMETHOD SetAlign(const nsAString & aAlign) { return _to SetAlign(aAlign); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMHTMLHEADINGELEMENT(_to) \
  NS_IMETHOD GetAlign(nsAString & aAlign) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAlign(aAlign); } \
  NS_IMETHOD SetAlign(const nsAString & aAlign) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAlign(aAlign); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMHTMLHeadingElement : public nsIDOMHTMLHeadingElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMHTMLHEADINGELEMENT

  nsDOMHTMLHeadingElement();

private:
  ~nsDOMHTMLHeadingElement();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMHTMLHeadingElement, nsIDOMHTMLHeadingElement)

nsDOMHTMLHeadingElement::nsDOMHTMLHeadingElement()
{
  /* member initializers and constructor code */
}

nsDOMHTMLHeadingElement::~nsDOMHTMLHeadingElement()
{
  /* destructor code */
}

/* attribute DOMString align; */
NS_IMETHODIMP nsDOMHTMLHeadingElement::GetAlign(nsAString & aAlign)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMHTMLHeadingElement::SetAlign(const nsAString & aAlign)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMHTMLHeadingElement_h__ */
