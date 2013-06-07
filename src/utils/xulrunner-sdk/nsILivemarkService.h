/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/toolkit/components/places/nsILivemarkService.idl
 */

#ifndef __gen_nsILivemarkService_h__
#define __gen_nsILivemarkService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIURI; /* forward declaration */

class nsINavBookmarksService; /* forward declaration */


/* starting interface:    nsILivemarkService */
#define NS_ILIVEMARKSERVICE_IID_STR "62a5fe00-d85c-4a63-aef7-176d8f1b189d"

#define NS_ILIVEMARKSERVICE_IID \
  {0x62a5fe00, 0xd85c, 0x4a63, \
    { 0xae, 0xf7, 0x17, 0x6d, 0x8f, 0x1b, 0x18, 0x9d }}

class NS_NO_VTABLE nsILivemarkService : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ILIVEMARKSERVICE_IID)

  /* void start (); */
  NS_IMETHOD Start(void) = 0;

  /* void stopUpdateLivemarks (); */
  NS_IMETHOD StopUpdateLivemarks(void) = 0;

  /* long long createLivemark (in long long folder, in AString name, in nsIURI siteURI, in nsIURI feedURI, in long index); */
  NS_IMETHOD CreateLivemark(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval) = 0;

  /* long long createLivemarkFolderOnly (in long long folder, in AString name, in nsIURI siteURI, in nsIURI feedURI, in long index); */
  NS_IMETHOD CreateLivemarkFolderOnly(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval) = 0;

  /* boolean isLivemark (in long long folder); */
  NS_IMETHOD IsLivemark(int64_t folder, bool *_retval) = 0;

  /* long long getLivemarkIdForFeedURI (in nsIURI aFeedURI); */
  NS_IMETHOD GetLivemarkIdForFeedURI(nsIURI *aFeedURI, int64_t *_retval) = 0;

  /* nsIURI getSiteURI (in long long container); */
  NS_IMETHOD GetSiteURI(int64_t container, nsIURI * *_retval) = 0;

  /* void setSiteURI (in long long container, in nsIURI siteURI); */
  NS_IMETHOD SetSiteURI(int64_t container, nsIURI *siteURI) = 0;

  /* nsIURI getFeedURI (in long long container); */
  NS_IMETHOD GetFeedURI(int64_t container, nsIURI * *_retval) = 0;

  /* void setFeedURI (in long long container, in nsIURI feedURI); */
  NS_IMETHOD SetFeedURI(int64_t container, nsIURI *feedURI) = 0;

  /* void reloadAllLivemarks (); */
  NS_IMETHOD ReloadAllLivemarks(void) = 0;

  /* void reloadLivemarkFolder (in long long folderID); */
  NS_IMETHOD ReloadLivemarkFolder(int64_t folderID) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsILivemarkService, NS_ILIVEMARKSERVICE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILIVEMARKSERVICE \
  NS_IMETHOD Start(void); \
  NS_IMETHOD StopUpdateLivemarks(void); \
  NS_IMETHOD CreateLivemark(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval); \
  NS_IMETHOD CreateLivemarkFolderOnly(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval); \
  NS_IMETHOD IsLivemark(int64_t folder, bool *_retval); \
  NS_IMETHOD GetLivemarkIdForFeedURI(nsIURI *aFeedURI, int64_t *_retval); \
  NS_IMETHOD GetSiteURI(int64_t container, nsIURI * *_retval); \
  NS_IMETHOD SetSiteURI(int64_t container, nsIURI *siteURI); \
  NS_IMETHOD GetFeedURI(int64_t container, nsIURI * *_retval); \
  NS_IMETHOD SetFeedURI(int64_t container, nsIURI *feedURI); \
  NS_IMETHOD ReloadAllLivemarks(void); \
  NS_IMETHOD ReloadLivemarkFolder(int64_t folderID); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILIVEMARKSERVICE(_to) \
  NS_IMETHOD Start(void) { return _to Start(); } \
  NS_IMETHOD StopUpdateLivemarks(void) { return _to StopUpdateLivemarks(); } \
  NS_IMETHOD CreateLivemark(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval) { return _to CreateLivemark(folder, name, siteURI, feedURI, index, _retval); } \
  NS_IMETHOD CreateLivemarkFolderOnly(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval) { return _to CreateLivemarkFolderOnly(folder, name, siteURI, feedURI, index, _retval); } \
  NS_IMETHOD IsLivemark(int64_t folder, bool *_retval) { return _to IsLivemark(folder, _retval); } \
  NS_IMETHOD GetLivemarkIdForFeedURI(nsIURI *aFeedURI, int64_t *_retval) { return _to GetLivemarkIdForFeedURI(aFeedURI, _retval); } \
  NS_IMETHOD GetSiteURI(int64_t container, nsIURI * *_retval) { return _to GetSiteURI(container, _retval); } \
  NS_IMETHOD SetSiteURI(int64_t container, nsIURI *siteURI) { return _to SetSiteURI(container, siteURI); } \
  NS_IMETHOD GetFeedURI(int64_t container, nsIURI * *_retval) { return _to GetFeedURI(container, _retval); } \
  NS_IMETHOD SetFeedURI(int64_t container, nsIURI *feedURI) { return _to SetFeedURI(container, feedURI); } \
  NS_IMETHOD ReloadAllLivemarks(void) { return _to ReloadAllLivemarks(); } \
  NS_IMETHOD ReloadLivemarkFolder(int64_t folderID) { return _to ReloadLivemarkFolder(folderID); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILIVEMARKSERVICE(_to) \
  NS_IMETHOD Start(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Start(); } \
  NS_IMETHOD StopUpdateLivemarks(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->StopUpdateLivemarks(); } \
  NS_IMETHOD CreateLivemark(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateLivemark(folder, name, siteURI, feedURI, index, _retval); } \
  NS_IMETHOD CreateLivemarkFolderOnly(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateLivemarkFolderOnly(folder, name, siteURI, feedURI, index, _retval); } \
  NS_IMETHOD IsLivemark(int64_t folder, bool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsLivemark(folder, _retval); } \
  NS_IMETHOD GetLivemarkIdForFeedURI(nsIURI *aFeedURI, int64_t *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLivemarkIdForFeedURI(aFeedURI, _retval); } \
  NS_IMETHOD GetSiteURI(int64_t container, nsIURI * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSiteURI(container, _retval); } \
  NS_IMETHOD SetSiteURI(int64_t container, nsIURI *siteURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSiteURI(container, siteURI); } \
  NS_IMETHOD GetFeedURI(int64_t container, nsIURI * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFeedURI(container, _retval); } \
  NS_IMETHOD SetFeedURI(int64_t container, nsIURI *feedURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFeedURI(container, feedURI); } \
  NS_IMETHOD ReloadAllLivemarks(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReloadAllLivemarks(); } \
  NS_IMETHOD ReloadLivemarkFolder(int64_t folderID) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReloadLivemarkFolder(folderID); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLivemarkService : public nsILivemarkService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILIVEMARKSERVICE

  nsLivemarkService();

private:
  ~nsLivemarkService();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLivemarkService, nsILivemarkService)

nsLivemarkService::nsLivemarkService()
{
  /* member initializers and constructor code */
}

nsLivemarkService::~nsLivemarkService()
{
  /* destructor code */
}

/* void start (); */
NS_IMETHODIMP nsLivemarkService::Start()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void stopUpdateLivemarks (); */
NS_IMETHODIMP nsLivemarkService::StopUpdateLivemarks()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long long createLivemark (in long long folder, in AString name, in nsIURI siteURI, in nsIURI feedURI, in long index); */
NS_IMETHODIMP nsLivemarkService::CreateLivemark(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long long createLivemarkFolderOnly (in long long folder, in AString name, in nsIURI siteURI, in nsIURI feedURI, in long index); */
NS_IMETHODIMP nsLivemarkService::CreateLivemarkFolderOnly(int64_t folder, const nsAString & name, nsIURI *siteURI, nsIURI *feedURI, int32_t index, int64_t *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isLivemark (in long long folder); */
NS_IMETHODIMP nsLivemarkService::IsLivemark(int64_t folder, bool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long long getLivemarkIdForFeedURI (in nsIURI aFeedURI); */
NS_IMETHODIMP nsLivemarkService::GetLivemarkIdForFeedURI(nsIURI *aFeedURI, int64_t *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIURI getSiteURI (in long long container); */
NS_IMETHODIMP nsLivemarkService::GetSiteURI(int64_t container, nsIURI * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setSiteURI (in long long container, in nsIURI siteURI); */
NS_IMETHODIMP nsLivemarkService::SetSiteURI(int64_t container, nsIURI *siteURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIURI getFeedURI (in long long container); */
NS_IMETHODIMP nsLivemarkService::GetFeedURI(int64_t container, nsIURI * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setFeedURI (in long long container, in nsIURI feedURI); */
NS_IMETHODIMP nsLivemarkService::SetFeedURI(int64_t container, nsIURI *feedURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void reloadAllLivemarks (); */
NS_IMETHODIMP nsLivemarkService::ReloadAllLivemarks()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void reloadLivemarkFolder (in long long folderID); */
NS_IMETHODIMP nsLivemarkService::ReloadLivemarkFolder(int64_t folderID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define LMANNO_FEEDURI "livemark/feedURI"

#endif /* __gen_nsILivemarkService_h__ */
