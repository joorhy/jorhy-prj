/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/sms/interfaces/nsIDOMMozSmsMessage.idl
 */

#ifndef __gen_nsIDOMMozSmsMessage_h__
#define __gen_nsIDOMMozSmsMessage_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#include "jspubtd.h"

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMMozSmsMessage */
#define NS_IDOMMOZSMSMESSAGE_IID_STR "59fc5ea8-33fe-40ba-890b-b9abaeb5ac26"

#define NS_IDOMMOZSMSMESSAGE_IID \
  {0x59fc5ea8, 0x33fe, 0x40ba, \
    { 0x89, 0x0b, 0xb9, 0xab, 0xae, 0xb5, 0xac, 0x26 }}

class NS_NO_VTABLE nsIDOMMozSmsMessage : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMMOZSMSMESSAGE_IID)

  /* readonly attribute long id; */
  NS_IMETHOD GetId(int32_t *aId) = 0;

  /* readonly attribute DOMString delivery; */
  NS_IMETHOD GetDelivery(nsAString & aDelivery) = 0;

  /* readonly attribute DOMString deliveryStatus; */
  NS_IMETHOD GetDeliveryStatus(nsAString & aDeliveryStatus) = 0;

  /* readonly attribute DOMString sender; */
  NS_IMETHOD GetSender(nsAString & aSender) = 0;

  /* readonly attribute DOMString receiver; */
  NS_IMETHOD GetReceiver(nsAString & aReceiver) = 0;

  /* readonly attribute DOMString body; */
  NS_IMETHOD GetBody(nsAString & aBody) = 0;

  /* readonly attribute DOMString messageClass; */
  NS_IMETHOD GetMessageClass(nsAString & aMessageClass) = 0;

  /* [implicit_jscontext] readonly attribute jsval timestamp; */
  NS_IMETHOD GetTimestamp(JSContext* cx, JS::Value *aTimestamp) = 0;

  /* readonly attribute boolean read; */
  NS_IMETHOD GetRead(bool *aRead) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMMozSmsMessage, NS_IDOMMOZSMSMESSAGE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMMOZSMSMESSAGE \
  NS_IMETHOD GetId(int32_t *aId); \
  NS_IMETHOD GetDelivery(nsAString & aDelivery); \
  NS_IMETHOD GetDeliveryStatus(nsAString & aDeliveryStatus); \
  NS_IMETHOD GetSender(nsAString & aSender); \
  NS_IMETHOD GetReceiver(nsAString & aReceiver); \
  NS_IMETHOD GetBody(nsAString & aBody); \
  NS_IMETHOD GetMessageClass(nsAString & aMessageClass); \
  NS_IMETHOD GetTimestamp(JSContext* cx, JS::Value *aTimestamp); \
  NS_IMETHOD GetRead(bool *aRead); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMMOZSMSMESSAGE(_to) \
  NS_IMETHOD GetId(int32_t *aId) { return _to GetId(aId); } \
  NS_IMETHOD GetDelivery(nsAString & aDelivery) { return _to GetDelivery(aDelivery); } \
  NS_IMETHOD GetDeliveryStatus(nsAString & aDeliveryStatus) { return _to GetDeliveryStatus(aDeliveryStatus); } \
  NS_IMETHOD GetSender(nsAString & aSender) { return _to GetSender(aSender); } \
  NS_IMETHOD GetReceiver(nsAString & aReceiver) { return _to GetReceiver(aReceiver); } \
  NS_IMETHOD GetBody(nsAString & aBody) { return _to GetBody(aBody); } \
  NS_IMETHOD GetMessageClass(nsAString & aMessageClass) { return _to GetMessageClass(aMessageClass); } \
  NS_IMETHOD GetTimestamp(JSContext* cx, JS::Value *aTimestamp) { return _to GetTimestamp(cx, aTimestamp); } \
  NS_IMETHOD GetRead(bool *aRead) { return _to GetRead(aRead); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMMOZSMSMESSAGE(_to) \
  NS_IMETHOD GetId(int32_t *aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetId(aId); } \
  NS_IMETHOD GetDelivery(nsAString & aDelivery) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDelivery(aDelivery); } \
  NS_IMETHOD GetDeliveryStatus(nsAString & aDeliveryStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDeliveryStatus(aDeliveryStatus); } \
  NS_IMETHOD GetSender(nsAString & aSender) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSender(aSender); } \
  NS_IMETHOD GetReceiver(nsAString & aReceiver) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetReceiver(aReceiver); } \
  NS_IMETHOD GetBody(nsAString & aBody) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBody(aBody); } \
  NS_IMETHOD GetMessageClass(nsAString & aMessageClass) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMessageClass(aMessageClass); } \
  NS_IMETHOD GetTimestamp(JSContext* cx, JS::Value *aTimestamp) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTimestamp(cx, aTimestamp); } \
  NS_IMETHOD GetRead(bool *aRead) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRead(aRead); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMMozSmsMessage : public nsIDOMMozSmsMessage
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMMOZSMSMESSAGE

  nsDOMMozSmsMessage();

private:
  ~nsDOMMozSmsMessage();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMMozSmsMessage, nsIDOMMozSmsMessage)

nsDOMMozSmsMessage::nsDOMMozSmsMessage()
{
  /* member initializers and constructor code */
}

nsDOMMozSmsMessage::~nsDOMMozSmsMessage()
{
  /* destructor code */
}

/* readonly attribute long id; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetId(int32_t *aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString delivery; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetDelivery(nsAString & aDelivery)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString deliveryStatus; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetDeliveryStatus(nsAString & aDeliveryStatus)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString sender; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetSender(nsAString & aSender)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString receiver; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetReceiver(nsAString & aReceiver)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString body; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetBody(nsAString & aBody)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString messageClass; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetMessageClass(nsAString & aMessageClass)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [implicit_jscontext] readonly attribute jsval timestamp; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetTimestamp(JSContext* cx, JS::Value *aTimestamp)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean read; */
NS_IMETHODIMP nsDOMMozSmsMessage::GetRead(bool *aRead)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMMozSmsMessage_h__ */
