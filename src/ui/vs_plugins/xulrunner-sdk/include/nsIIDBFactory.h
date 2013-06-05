/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/indexedDB/nsIIDBFactory.idl
 */

#ifndef __gen_nsIIDBFactory_h__
#define __gen_nsIIDBFactory_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#include "jspubtd.h"

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIIDBKeyRange; /* forward declaration */

class nsIIDBOpenDBRequest; /* forward declaration */


/* starting interface:    nsIIDBFactory */
#define NS_IIDBFACTORY_IID_STR "3c763a8f-df53-491d-9635-e1d959e43c0c"

#define NS_IIDBFACTORY_IID \
  {0x3c763a8f, 0xdf53, 0x491d, \
    { 0x96, 0x35, 0xe1, 0xd9, 0x59, 0xe4, 0x3c, 0x0c }}

class NS_NO_VTABLE nsIIDBFactory : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IIDBFACTORY_IID)

  /* [implicit_jscontext,optional_argc] nsIIDBOpenDBRequest open ([Null (Stringify)] in DOMString name, [optional] in long long version); */
  NS_IMETHOD Open(const nsAString & name, int64_t version, JSContext* cx, uint8_t _argc, nsIIDBOpenDBRequest * *_retval) = 0;

  /* [implicit_jscontext] nsIIDBOpenDBRequest deleteDatabase (in AString name); */
  NS_IMETHOD DeleteDatabase(const nsAString & name, JSContext* cx, nsIIDBOpenDBRequest * *_retval) = 0;

  /* [implicit_jscontext] short cmp (in jsval first, in jsval second); */
  NS_IMETHOD Cmp(const JS::Value & first, const JS::Value & second, JSContext* cx, int16_t *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIIDBFactory, NS_IIDBFACTORY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIIDBFACTORY \
  NS_IMETHOD Open(const nsAString & name, int64_t version, JSContext* cx, uint8_t _argc, nsIIDBOpenDBRequest * *_retval); \
  NS_IMETHOD DeleteDatabase(const nsAString & name, JSContext* cx, nsIIDBOpenDBRequest * *_retval); \
  NS_IMETHOD Cmp(const JS::Value & first, const JS::Value & second, JSContext* cx, int16_t *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIIDBFACTORY(_to) \
  NS_IMETHOD Open(const nsAString & name, int64_t version, JSContext* cx, uint8_t _argc, nsIIDBOpenDBRequest * *_retval) { return _to Open(name, version, cx, _argc, _retval); } \
  NS_IMETHOD DeleteDatabase(const nsAString & name, JSContext* cx, nsIIDBOpenDBRequest * *_retval) { return _to DeleteDatabase(name, cx, _retval); } \
  NS_IMETHOD Cmp(const JS::Value & first, const JS::Value & second, JSContext* cx, int16_t *_retval) { return _to Cmp(first, second, cx, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIIDBFACTORY(_to) \
  NS_IMETHOD Open(const nsAString & name, int64_t version, JSContext* cx, uint8_t _argc, nsIIDBOpenDBRequest * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Open(name, version, cx, _argc, _retval); } \
  NS_IMETHOD DeleteDatabase(const nsAString & name, JSContext* cx, nsIIDBOpenDBRequest * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->DeleteDatabase(name, cx, _retval); } \
  NS_IMETHOD Cmp(const JS::Value & first, const JS::Value & second, JSContext* cx, int16_t *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Cmp(first, second, cx, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsIDBFactory : public nsIIDBFactory
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIIDBFACTORY

  nsIDBFactory();

private:
  ~nsIDBFactory();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsIDBFactory, nsIIDBFactory)

nsIDBFactory::nsIDBFactory()
{
  /* member initializers and constructor code */
}

nsIDBFactory::~nsIDBFactory()
{
  /* destructor code */
}

/* [implicit_jscontext,optional_argc] nsIIDBOpenDBRequest open ([Null (Stringify)] in DOMString name, [optional] in long long version); */
NS_IMETHODIMP nsIDBFactory::Open(const nsAString & name, int64_t version, JSContext* cx, uint8_t _argc, nsIIDBOpenDBRequest * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [implicit_jscontext] nsIIDBOpenDBRequest deleteDatabase (in AString name); */
NS_IMETHODIMP nsIDBFactory::DeleteDatabase(const nsAString & name, JSContext* cx, nsIIDBOpenDBRequest * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [implicit_jscontext] short cmp (in jsval first, in jsval second); */
NS_IMETHODIMP nsIDBFactory::Cmp(const JS::Value & first, const JS::Value & second, JSContext* cx, int16_t *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIIDBFactory_h__ */
