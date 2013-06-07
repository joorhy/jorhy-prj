/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/sms/interfaces/nsISmsRequest.idl
 */

#ifndef __gen_nsISmsRequest_h__
#define __gen_nsISmsRequest_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#include "jspubtd.h"

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMMozSmsMessage; /* forward declaration */


/* starting interface:    nsISmsRequest */
#define NS_ISMSREQUEST_IID_STR "82a6d16d-cf33-4745-8662-8b5d441f512f"

#define NS_ISMSREQUEST_IID \
  {0x82a6d16d, 0xcf33, 0x4745, \
    { 0x86, 0x62, 0x8b, 0x5d, 0x44, 0x1f, 0x51, 0x2f }}

class NS_NO_VTABLE nsISmsRequest : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISMSREQUEST_IID)

  enum {
    SUCCESS_NO_ERROR = 0U,
    NO_SIGNAL_ERROR = 1U,
    NOT_FOUND_ERROR = 2U,
    UNKNOWN_ERROR = 3U,
    INTERNAL_ERROR = 4U
  };

  /* void notifyMessageSent (in nsIDOMMozSmsMessage message); */
  NS_IMETHOD NotifyMessageSent(nsIDOMMozSmsMessage *message) = 0;

  /* void notifySendMessageFailed (in long error); */
  NS_IMETHOD NotifySendMessageFailed(int32_t error) = 0;

  /* void notifyMessageGot (in nsIDOMMozSmsMessage message); */
  NS_IMETHOD NotifyMessageGot(nsIDOMMozSmsMessage *message) = 0;

  /* void notifyGetMessageFailed (in long error); */
  NS_IMETHOD NotifyGetMessageFailed(int32_t error) = 0;

  /* void notifyMessageDeleted (in boolean deleted); */
  NS_IMETHOD NotifyMessageDeleted(bool deleted) = 0;

  /* void notifyDeleteMessageFailed (in long error); */
  NS_IMETHOD NotifyDeleteMessageFailed(int32_t error) = 0;

  /* void notifyMessageListCreated (in long listId, in nsIDOMMozSmsMessage message); */
  NS_IMETHOD NotifyMessageListCreated(int32_t listId, nsIDOMMozSmsMessage *message) = 0;

  /* void notifyReadMessageListFailed (in long error); */
  NS_IMETHOD NotifyReadMessageListFailed(int32_t error) = 0;

  /* void notifyNextMessageInListGot (in nsIDOMMozSmsMessage message); */
  NS_IMETHOD NotifyNextMessageInListGot(nsIDOMMozSmsMessage *message) = 0;

  /* void notifyNoMessageInList (); */
  NS_IMETHOD NotifyNoMessageInList(void) = 0;

  /* void notifyMessageMarkedRead (in boolean read); */
  NS_IMETHOD NotifyMessageMarkedRead(bool read) = 0;

  /* void notifyMarkMessageReadFailed (in long error); */
  NS_IMETHOD NotifyMarkMessageReadFailed(int32_t error) = 0;

  /* [implicit_jscontext] void notifyThreadList (in jsval threadList); */
  NS_IMETHOD NotifyThreadList(const JS::Value & threadList, JSContext* cx) = 0;

  /* void notifyThreadListFailed (in long error); */
  NS_IMETHOD NotifyThreadListFailed(int32_t error) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISmsRequest, NS_ISMSREQUEST_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISMSREQUEST \
  NS_IMETHOD NotifyMessageSent(nsIDOMMozSmsMessage *message); \
  NS_IMETHOD NotifySendMessageFailed(int32_t error); \
  NS_IMETHOD NotifyMessageGot(nsIDOMMozSmsMessage *message); \
  NS_IMETHOD NotifyGetMessageFailed(int32_t error); \
  NS_IMETHOD NotifyMessageDeleted(bool deleted); \
  NS_IMETHOD NotifyDeleteMessageFailed(int32_t error); \
  NS_IMETHOD NotifyMessageListCreated(int32_t listId, nsIDOMMozSmsMessage *message); \
  NS_IMETHOD NotifyReadMessageListFailed(int32_t error); \
  NS_IMETHOD NotifyNextMessageInListGot(nsIDOMMozSmsMessage *message); \
  NS_IMETHOD NotifyNoMessageInList(void); \
  NS_IMETHOD NotifyMessageMarkedRead(bool read); \
  NS_IMETHOD NotifyMarkMessageReadFailed(int32_t error); \
  NS_IMETHOD NotifyThreadList(const JS::Value & threadList, JSContext* cx); \
  NS_IMETHOD NotifyThreadListFailed(int32_t error); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISMSREQUEST(_to) \
  NS_IMETHOD NotifyMessageSent(nsIDOMMozSmsMessage *message) { return _to NotifyMessageSent(message); } \
  NS_IMETHOD NotifySendMessageFailed(int32_t error) { return _to NotifySendMessageFailed(error); } \
  NS_IMETHOD NotifyMessageGot(nsIDOMMozSmsMessage *message) { return _to NotifyMessageGot(message); } \
  NS_IMETHOD NotifyGetMessageFailed(int32_t error) { return _to NotifyGetMessageFailed(error); } \
  NS_IMETHOD NotifyMessageDeleted(bool deleted) { return _to NotifyMessageDeleted(deleted); } \
  NS_IMETHOD NotifyDeleteMessageFailed(int32_t error) { return _to NotifyDeleteMessageFailed(error); } \
  NS_IMETHOD NotifyMessageListCreated(int32_t listId, nsIDOMMozSmsMessage *message) { return _to NotifyMessageListCreated(listId, message); } \
  NS_IMETHOD NotifyReadMessageListFailed(int32_t error) { return _to NotifyReadMessageListFailed(error); } \
  NS_IMETHOD NotifyNextMessageInListGot(nsIDOMMozSmsMessage *message) { return _to NotifyNextMessageInListGot(message); } \
  NS_IMETHOD NotifyNoMessageInList(void) { return _to NotifyNoMessageInList(); } \
  NS_IMETHOD NotifyMessageMarkedRead(bool read) { return _to NotifyMessageMarkedRead(read); } \
  NS_IMETHOD NotifyMarkMessageReadFailed(int32_t error) { return _to NotifyMarkMessageReadFailed(error); } \
  NS_IMETHOD NotifyThreadList(const JS::Value & threadList, JSContext* cx) { return _to NotifyThreadList(threadList, cx); } \
  NS_IMETHOD NotifyThreadListFailed(int32_t error) { return _to NotifyThreadListFailed(error); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISMSREQUEST(_to) \
  NS_IMETHOD NotifyMessageSent(nsIDOMMozSmsMessage *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyMessageSent(message); } \
  NS_IMETHOD NotifySendMessageFailed(int32_t error) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifySendMessageFailed(error); } \
  NS_IMETHOD NotifyMessageGot(nsIDOMMozSmsMessage *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyMessageGot(message); } \
  NS_IMETHOD NotifyGetMessageFailed(int32_t error) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyGetMessageFailed(error); } \
  NS_IMETHOD NotifyMessageDeleted(bool deleted) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyMessageDeleted(deleted); } \
  NS_IMETHOD NotifyDeleteMessageFailed(int32_t error) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyDeleteMessageFailed(error); } \
  NS_IMETHOD NotifyMessageListCreated(int32_t listId, nsIDOMMozSmsMessage *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyMessageListCreated(listId, message); } \
  NS_IMETHOD NotifyReadMessageListFailed(int32_t error) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyReadMessageListFailed(error); } \
  NS_IMETHOD NotifyNextMessageInListGot(nsIDOMMozSmsMessage *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyNextMessageInListGot(message); } \
  NS_IMETHOD NotifyNoMessageInList(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyNoMessageInList(); } \
  NS_IMETHOD NotifyMessageMarkedRead(bool read) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyMessageMarkedRead(read); } \
  NS_IMETHOD NotifyMarkMessageReadFailed(int32_t error) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyMarkMessageReadFailed(error); } \
  NS_IMETHOD NotifyThreadList(const JS::Value & threadList, JSContext* cx) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyThreadList(threadList, cx); } \
  NS_IMETHOD NotifyThreadListFailed(int32_t error) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyThreadListFailed(error); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSmsRequest : public nsISmsRequest
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISMSREQUEST

  nsSmsRequest();

private:
  ~nsSmsRequest();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSmsRequest, nsISmsRequest)

nsSmsRequest::nsSmsRequest()
{
  /* member initializers and constructor code */
}

nsSmsRequest::~nsSmsRequest()
{
  /* destructor code */
}

/* void notifyMessageSent (in nsIDOMMozSmsMessage message); */
NS_IMETHODIMP nsSmsRequest::NotifyMessageSent(nsIDOMMozSmsMessage *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifySendMessageFailed (in long error); */
NS_IMETHODIMP nsSmsRequest::NotifySendMessageFailed(int32_t error)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyMessageGot (in nsIDOMMozSmsMessage message); */
NS_IMETHODIMP nsSmsRequest::NotifyMessageGot(nsIDOMMozSmsMessage *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyGetMessageFailed (in long error); */
NS_IMETHODIMP nsSmsRequest::NotifyGetMessageFailed(int32_t error)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyMessageDeleted (in boolean deleted); */
NS_IMETHODIMP nsSmsRequest::NotifyMessageDeleted(bool deleted)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyDeleteMessageFailed (in long error); */
NS_IMETHODIMP nsSmsRequest::NotifyDeleteMessageFailed(int32_t error)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyMessageListCreated (in long listId, in nsIDOMMozSmsMessage message); */
NS_IMETHODIMP nsSmsRequest::NotifyMessageListCreated(int32_t listId, nsIDOMMozSmsMessage *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyReadMessageListFailed (in long error); */
NS_IMETHODIMP nsSmsRequest::NotifyReadMessageListFailed(int32_t error)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyNextMessageInListGot (in nsIDOMMozSmsMessage message); */
NS_IMETHODIMP nsSmsRequest::NotifyNextMessageInListGot(nsIDOMMozSmsMessage *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyNoMessageInList (); */
NS_IMETHODIMP nsSmsRequest::NotifyNoMessageInList()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyMessageMarkedRead (in boolean read); */
NS_IMETHODIMP nsSmsRequest::NotifyMessageMarkedRead(bool read)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyMarkMessageReadFailed (in long error); */
NS_IMETHODIMP nsSmsRequest::NotifyMarkMessageReadFailed(int32_t error)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [implicit_jscontext] void notifyThreadList (in jsval threadList); */
NS_IMETHODIMP nsSmsRequest::NotifyThreadList(const JS::Value & threadList, JSContext* cx)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyThreadListFailed (in long error); */
NS_IMETHODIMP nsSmsRequest::NotifyThreadListFailed(int32_t error)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISmsRequest_h__ */
