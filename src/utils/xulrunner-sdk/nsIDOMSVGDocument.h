/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/interfaces/svg/nsIDOMSVGDocument.idl
 */

#ifndef __gen_nsIDOMSVGDocument_h__
#define __gen_nsIDOMSVGDocument_h__


#ifndef __gen_nsIDOMDocument_h__
#include "nsIDOMDocument.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMSVGElement; /* forward declaration */


/* starting interface:    nsIDOMSVGDocument */
#define NS_IDOMSVGDOCUMENT_IID_STR "8fe506e4-5563-4b16-9228-182071e3f8f8"

#define NS_IDOMSVGDOCUMENT_IID \
  {0x8fe506e4, 0x5563, 0x4b16, \
    { 0x92, 0x28, 0x18, 0x20, 0x71, 0xe3, 0xf8, 0xf8 }}

class NS_NO_VTABLE nsIDOMSVGDocument : public nsIDOMDocument {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMSVGDOCUMENT_IID)

  /* readonly attribute DOMString domain; */
  NS_IMETHOD GetDomain(nsAString & aDomain) = 0;

  /* readonly attribute nsIDOMSVGElement rootElement; */
  NS_IMETHOD GetRootElement(nsIDOMSVGElement * *aRootElement) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMSVGDocument, NS_IDOMSVGDOCUMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMSVGDOCUMENT \
  NS_IMETHOD GetDomain(nsAString & aDomain); \
  NS_IMETHOD GetRootElement(nsIDOMSVGElement * *aRootElement); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMSVGDOCUMENT(_to) \
  NS_IMETHOD GetDomain(nsAString & aDomain) { return _to GetDomain(aDomain); } \
  NS_IMETHOD GetRootElement(nsIDOMSVGElement * *aRootElement) { return _to GetRootElement(aRootElement); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMSVGDOCUMENT(_to) \
  NS_IMETHOD GetDomain(nsAString & aDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDomain(aDomain); } \
  NS_IMETHOD GetRootElement(nsIDOMSVGElement * *aRootElement) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRootElement(aRootElement); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMSVGDocument : public nsIDOMSVGDocument
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMSVGDOCUMENT

  nsDOMSVGDocument();

private:
  ~nsDOMSVGDocument();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMSVGDocument, nsIDOMSVGDocument)

nsDOMSVGDocument::nsDOMSVGDocument()
{
  /* member initializers and constructor code */
}

nsDOMSVGDocument::~nsDOMSVGDocument()
{
  /* destructor code */
}

/* readonly attribute DOMString domain; */
NS_IMETHODIMP nsDOMSVGDocument::GetDomain(nsAString & aDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMSVGElement rootElement; */
NS_IMETHODIMP nsDOMSVGDocument::GetRootElement(nsIDOMSVGElement * *aRootElement)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMSVGDocument_h__ */
