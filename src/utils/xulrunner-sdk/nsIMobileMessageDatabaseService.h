/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/mobilemessage/interfaces/nsIMobileMessageDatabaseService.idl
 */

#ifndef __gen_nsIMobileMessageDatabaseService_h__
#define __gen_nsIMobileMessageDatabaseService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#define MOBILE_MESSAGE_DATABASE_SERVICE_CID \
{ 0x0d84b9c2, 0x8f76, 0x4ba4,    \
{ 0xa5, 0xcd, 0xdb, 0xfb, 0x01, 0xdf, 0xda, 0x99 } }
#define MOBILE_MESSAGE_DATABASE_SERVICE_CONTRACTID "@mozilla.org/mobilemessage/mobilemessagedatabaseservice;1"
class nsIDOMMozSmsFilter; /* forward declaration */

class nsISmsRequest; /* forward declaration */


/* starting interface:    nsIMobileMessageDatabaseService */
#define NS_IMOBILEMESSAGEDATABASESERVICE_IID_STR "ce9232ca-6a08-11e2-b971-c795004622e7"

#define NS_IMOBILEMESSAGEDATABASESERVICE_IID \
  {0xce9232ca, 0x6a08, 0x11e2, \
    { 0xb9, 0x71, 0xc7, 0x95, 0x00, 0x46, 0x22, 0xe7 }}

class NS_NO_VTABLE nsIMobileMessageDatabaseService : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IMOBILEMESSAGEDATABASESERVICE_IID)

  /* [binaryname(GetMessageMoz)] void getMessage (in long messageId, in nsISmsRequest request); */
  NS_IMETHOD GetMessageMoz(int32_t messageId, nsISmsRequest *request) = 0;

  /* void deleteMessage (in long messageId, in nsISmsRequest request); */
  NS_IMETHOD DeleteMessage(int32_t messageId, nsISmsRequest *request) = 0;

  /* void createMessageList (in nsIDOMMozSmsFilter filter, in boolean reverse, in nsISmsRequest request); */
  NS_IMETHOD CreateMessageList(nsIDOMMozSmsFilter *filter, bool reverse, nsISmsRequest *request) = 0;

  /* void getNextMessageInList (in long listId, in nsISmsRequest request); */
  NS_IMETHOD GetNextMessageInList(int32_t listId, nsISmsRequest *request) = 0;

  /* void clearMessageList (in long listId); */
  NS_IMETHOD ClearMessageList(int32_t listId) = 0;

  /* void markMessageRead (in long messageId, in boolean value, in nsISmsRequest request); */
  NS_IMETHOD MarkMessageRead(int32_t messageId, bool value, nsISmsRequest *request) = 0;

  /* void getThreadList (in nsISmsRequest request); */
  NS_IMETHOD GetThreadList(nsISmsRequest *request) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIMobileMessageDatabaseService, NS_IMOBILEMESSAGEDATABASESERVICE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIMOBILEMESSAGEDATABASESERVICE \
  NS_IMETHOD GetMessageMoz(int32_t messageId, nsISmsRequest *request); \
  NS_IMETHOD DeleteMessage(int32_t messageId, nsISmsRequest *request); \
  NS_IMETHOD CreateMessageList(nsIDOMMozSmsFilter *filter, bool reverse, nsISmsRequest *request); \
  NS_IMETHOD GetNextMessageInList(int32_t listId, nsISmsRequest *request); \
  NS_IMETHOD ClearMessageList(int32_t listId); \
  NS_IMETHOD MarkMessageRead(int32_t messageId, bool value, nsISmsRequest *request); \
  NS_IMETHOD GetThreadList(nsISmsRequest *request); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIMOBILEMESSAGEDATABASESERVICE(_to) \
  NS_IMETHOD GetMessageMoz(int32_t messageId, nsISmsRequest *request) { return _to GetMessageMoz(messageId, request); } \
  NS_IMETHOD DeleteMessage(int32_t messageId, nsISmsRequest *request) { return _to DeleteMessage(messageId, request); } \
  NS_IMETHOD CreateMessageList(nsIDOMMozSmsFilter *filter, bool reverse, nsISmsRequest *request) { return _to CreateMessageList(filter, reverse, request); } \
  NS_IMETHOD GetNextMessageInList(int32_t listId, nsISmsRequest *request) { return _to GetNextMessageInList(listId, request); } \
  NS_IMETHOD ClearMessageList(int32_t listId) { return _to ClearMessageList(listId); } \
  NS_IMETHOD MarkMessageRead(int32_t messageId, bool value, nsISmsRequest *request) { return _to MarkMessageRead(messageId, value, request); } \
  NS_IMETHOD GetThreadList(nsISmsRequest *request) { return _to GetThreadList(request); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIMOBILEMESSAGEDATABASESERVICE(_to) \
  NS_IMETHOD GetMessageMoz(int32_t messageId, nsISmsRequest *request) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMessageMoz(messageId, request); } \
  NS_IMETHOD DeleteMessage(int32_t messageId, nsISmsRequest *request) { return !_to ? NS_ERROR_NULL_POINTER : _to->DeleteMessage(messageId, request); } \
  NS_IMETHOD CreateMessageList(nsIDOMMozSmsFilter *filter, bool reverse, nsISmsRequest *request) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateMessageList(filter, reverse, request); } \
  NS_IMETHOD GetNextMessageInList(int32_t listId, nsISmsRequest *request) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNextMessageInList(listId, request); } \
  NS_IMETHOD ClearMessageList(int32_t listId) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearMessageList(listId); } \
  NS_IMETHOD MarkMessageRead(int32_t messageId, bool value, nsISmsRequest *request) { return !_to ? NS_ERROR_NULL_POINTER : _to->MarkMessageRead(messageId, value, request); } \
  NS_IMETHOD GetThreadList(nsISmsRequest *request) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetThreadList(request); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsMobileMessageDatabaseService : public nsIMobileMessageDatabaseService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIMOBILEMESSAGEDATABASESERVICE

  nsMobileMessageDatabaseService();

private:
  ~nsMobileMessageDatabaseService();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsMobileMessageDatabaseService, nsIMobileMessageDatabaseService)

nsMobileMessageDatabaseService::nsMobileMessageDatabaseService()
{
  /* member initializers and constructor code */
}

nsMobileMessageDatabaseService::~nsMobileMessageDatabaseService()
{
  /* destructor code */
}

/* [binaryname(GetMessageMoz)] void getMessage (in long messageId, in nsISmsRequest request); */
NS_IMETHODIMP nsMobileMessageDatabaseService::GetMessageMoz(int32_t messageId, nsISmsRequest *request)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void deleteMessage (in long messageId, in nsISmsRequest request); */
NS_IMETHODIMP nsMobileMessageDatabaseService::DeleteMessage(int32_t messageId, nsISmsRequest *request)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void createMessageList (in nsIDOMMozSmsFilter filter, in boolean reverse, in nsISmsRequest request); */
NS_IMETHODIMP nsMobileMessageDatabaseService::CreateMessageList(nsIDOMMozSmsFilter *filter, bool reverse, nsISmsRequest *request)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getNextMessageInList (in long listId, in nsISmsRequest request); */
NS_IMETHODIMP nsMobileMessageDatabaseService::GetNextMessageInList(int32_t listId, nsISmsRequest *request)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void clearMessageList (in long listId); */
NS_IMETHODIMP nsMobileMessageDatabaseService::ClearMessageList(int32_t listId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void markMessageRead (in long messageId, in boolean value, in nsISmsRequest request); */
NS_IMETHODIMP nsMobileMessageDatabaseService::MarkMessageRead(int32_t messageId, bool value, nsISmsRequest *request)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getThreadList (in nsISmsRequest request); */
NS_IMETHODIMP nsMobileMessageDatabaseService::GetThreadList(nsISmsRequest *request)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIMobileMessageDatabaseService_h__ */
