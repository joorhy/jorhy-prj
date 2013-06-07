/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/sms/interfaces/nsISmsService.idl
 */

#ifndef __gen_nsISmsService_h__
#define __gen_nsISmsService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#include "jspubtd.h"

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMMozSmsMessage; /* forward declaration */

class nsIDOMMozSmsSegmentInfo; /* forward declaration */

class nsISmsRequest; /* forward declaration */

#define SMS_SERVICE_CID { 0xbada3cb8, 0xa568, 0x4dff, { 0xb5, 0x43, 0x52, 0xbb, 0xb3, 0x14, 0x31, 0x21 } }
#define SMS_SERVICE_CONTRACTID "@mozilla.org/sms/smsservice;1"

/* starting interface:    nsISmsService */
#define NS_ISMSSERVICE_IID_STR "4310bdb5-eefa-4f70-965a-74041228ab26"

#define NS_ISMSSERVICE_IID \
  {0x4310bdb5, 0xeefa, 0x4f70, \
    { 0x96, 0x5a, 0x74, 0x04, 0x12, 0x28, 0xab, 0x26 }}

class NS_NO_VTABLE nsISmsService : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISMSSERVICE_IID)

  /* boolean hasSupport (); */
  NS_IMETHOD HasSupport(bool *_retval) = 0;

  /* nsIDOMMozSmsSegmentInfo getSegmentInfoForText (in DOMString text); */
  NS_IMETHOD GetSegmentInfoForText(const nsAString & text, nsIDOMMozSmsSegmentInfo * *_retval) = 0;

  /* void send (in DOMString number, in DOMString message, in nsISmsRequest request); */
  NS_IMETHOD Send(const nsAString & number, const nsAString & message, nsISmsRequest *request) = 0;

  /* [implicit_jscontext] nsIDOMMozSmsMessage createSmsMessage (in long id, in DOMString delivery, in DOMString deliveryStatus, in DOMString sender, in DOMString receiver, in DOMString body, in DOMString messageClass, in jsval timestamp, in bool read); */
  NS_IMETHOD CreateSmsMessage(int32_t id, const nsAString & delivery, const nsAString & deliveryStatus, const nsAString & sender, const nsAString & receiver, const nsAString & body, const nsAString & messageClass, const JS::Value & timestamp, bool read, JSContext* cx, nsIDOMMozSmsMessage * *_retval) = 0;

  /* nsIDOMMozSmsSegmentInfo createSmsSegmentInfo (in long segments, in long charsPerSegment, in long charsAvailableInLastSegment); */
  NS_IMETHOD CreateSmsSegmentInfo(int32_t segments, int32_t charsPerSegment, int32_t charsAvailableInLastSegment, nsIDOMMozSmsSegmentInfo * *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISmsService, NS_ISMSSERVICE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISMSSERVICE \
  NS_IMETHOD HasSupport(bool *_retval); \
  NS_IMETHOD GetSegmentInfoForText(const nsAString & text, nsIDOMMozSmsSegmentInfo * *_retval); \
  NS_IMETHOD Send(const nsAString & number, const nsAString & message, nsISmsRequest *request); \
  NS_IMETHOD CreateSmsMessage(int32_t id, const nsAString & delivery, const nsAString & deliveryStatus, const nsAString & sender, const nsAString & receiver, const nsAString & body, const nsAString & messageClass, const JS::Value & timestamp, bool read, JSContext* cx, nsIDOMMozSmsMessage * *_retval); \
  NS_IMETHOD CreateSmsSegmentInfo(int32_t segments, int32_t charsPerSegment, int32_t charsAvailableInLastSegment, nsIDOMMozSmsSegmentInfo * *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISMSSERVICE(_to) \
  NS_IMETHOD HasSupport(bool *_retval) { return _to HasSupport(_retval); } \
  NS_IMETHOD GetSegmentInfoForText(const nsAString & text, nsIDOMMozSmsSegmentInfo * *_retval) { return _to GetSegmentInfoForText(text, _retval); } \
  NS_IMETHOD Send(const nsAString & number, const nsAString & message, nsISmsRequest *request) { return _to Send(number, message, request); } \
  NS_IMETHOD CreateSmsMessage(int32_t id, const nsAString & delivery, const nsAString & deliveryStatus, const nsAString & sender, const nsAString & receiver, const nsAString & body, const nsAString & messageClass, const JS::Value & timestamp, bool read, JSContext* cx, nsIDOMMozSmsMessage * *_retval) { return _to CreateSmsMessage(id, delivery, deliveryStatus, sender, receiver, body, messageClass, timestamp, read, cx, _retval); } \
  NS_IMETHOD CreateSmsSegmentInfo(int32_t segments, int32_t charsPerSegment, int32_t charsAvailableInLastSegment, nsIDOMMozSmsSegmentInfo * *_retval) { return _to CreateSmsSegmentInfo(segments, charsPerSegment, charsAvailableInLastSegment, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISMSSERVICE(_to) \
  NS_IMETHOD HasSupport(bool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->HasSupport(_retval); } \
  NS_IMETHOD GetSegmentInfoForText(const nsAString & text, nsIDOMMozSmsSegmentInfo * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSegmentInfoForText(text, _retval); } \
  NS_IMETHOD Send(const nsAString & number, const nsAString & message, nsISmsRequest *request) { return !_to ? NS_ERROR_NULL_POINTER : _to->Send(number, message, request); } \
  NS_IMETHOD CreateSmsMessage(int32_t id, const nsAString & delivery, const nsAString & deliveryStatus, const nsAString & sender, const nsAString & receiver, const nsAString & body, const nsAString & messageClass, const JS::Value & timestamp, bool read, JSContext* cx, nsIDOMMozSmsMessage * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateSmsMessage(id, delivery, deliveryStatus, sender, receiver, body, messageClass, timestamp, read, cx, _retval); } \
  NS_IMETHOD CreateSmsSegmentInfo(int32_t segments, int32_t charsPerSegment, int32_t charsAvailableInLastSegment, nsIDOMMozSmsSegmentInfo * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateSmsSegmentInfo(segments, charsPerSegment, charsAvailableInLastSegment, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSmsService : public nsISmsService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISMSSERVICE

  nsSmsService();

private:
  ~nsSmsService();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSmsService, nsISmsService)

nsSmsService::nsSmsService()
{
  /* member initializers and constructor code */
}

nsSmsService::~nsSmsService()
{
  /* destructor code */
}

/* boolean hasSupport (); */
NS_IMETHODIMP nsSmsService::HasSupport(bool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMMozSmsSegmentInfo getSegmentInfoForText (in DOMString text); */
NS_IMETHODIMP nsSmsService::GetSegmentInfoForText(const nsAString & text, nsIDOMMozSmsSegmentInfo * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void send (in DOMString number, in DOMString message, in nsISmsRequest request); */
NS_IMETHODIMP nsSmsService::Send(const nsAString & number, const nsAString & message, nsISmsRequest *request)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [implicit_jscontext] nsIDOMMozSmsMessage createSmsMessage (in long id, in DOMString delivery, in DOMString deliveryStatus, in DOMString sender, in DOMString receiver, in DOMString body, in DOMString messageClass, in jsval timestamp, in bool read); */
NS_IMETHODIMP nsSmsService::CreateSmsMessage(int32_t id, const nsAString & delivery, const nsAString & deliveryStatus, const nsAString & sender, const nsAString & receiver, const nsAString & body, const nsAString & messageClass, const JS::Value & timestamp, bool read, JSContext* cx, nsIDOMMozSmsMessage * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMMozSmsSegmentInfo createSmsSegmentInfo (in long segments, in long charsPerSegment, in long charsAvailableInLastSegment); */
NS_IMETHODIMP nsSmsService::CreateSmsSegmentInfo(int32_t segments, int32_t charsPerSegment, int32_t charsAvailableInLastSegment, nsIDOMMozSmsSegmentInfo * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISmsService_h__ */
