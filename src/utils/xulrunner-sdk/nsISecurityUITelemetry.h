/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/security/manager/boot/public/nsISecurityUITelemetry.idl
 */

#ifndef __gen_nsISecurityUITelemetry_h__
#define __gen_nsISecurityUITelemetry_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISecurityUITelemetry */
#define NS_ISECURITYUITELEMETRY_IID_STR "d5c7d771-53a7-40e5-8247-fb6a8795cae8"

#define NS_ISECURITYUITELEMETRY_IID \
  {0xd5c7d771, 0x53a7, 0x40e5, \
    { 0x82, 0x47, 0xfb, 0x6a, 0x87, 0x95, 0xca, 0xe8 }}

class NS_NO_VTABLE nsISecurityUITelemetry : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISECURITYUITELEMETRY_IID)

  enum {
    WARNING_ADDON_ASKING_PREVENTED = 1U,
    WARNING_ADDON_ASKING_PREVENTED_CLICK_THROUGH = 2U,
    WARNING_CONFIRM_ADDON_INSTALL = 3U,
    WARNING_CONFIRM_ADDON_INSTALL_CLICK_THROUGH = 4U,
    WARNING_CONFIRM_POST_TO_INSECURE_FROM_SECURE = 9U,
    WARNING_CONFIRM_POST_TO_INSECURE_FROM_SECURE_CLICK_THROUGH = 10U,
    WARNING_MALWARE_PAGE = 13U,
    WARNING_MALWARE_PAGE_WHY_BLOCKED = 14U,
    WARNING_MALWARE_PAGE_GET_ME_OUT_OF_HERE = 15U,
    WARNING_MALWARE_PAGE_IGNORE_WARNING = 16U,
    WARNING_PHISHING_PAGE = 17U,
    WARNING_PHISHING_PAGE_WHY_BLOCKED = 18U,
    WARNING_PHISHING_PAGE_GET_ME_OUT_OF_HERE = 19U,
    WARNING_PHISHING_PAGE_IGNORE_WARNING = 20U,
    WARNING_BAD_CERT = 21U,
    WARNING_BAD_CERT_STS = 22U,
    WARNING_BAD_CERT_CLICK_ADD_EXCEPTION = 23U,
    WARNING_BAD_CERT_CLICK_VIEW_CERT = 24U,
    WARNING_BAD_CERT_DONT_REMEMBER_EXCEPTION = 25U,
    WARNING_BAD_CERT_GET_ME_OUT_OF_HERE = 27U,
    WARNING_BAD_CERT_UNDERSTAND_RISKS = 28U,
    WARNING_BAD_CERT_TECHINICAL_DETAILS = 29U,
    WARNING_BAD_CERT_ADD_EXCEPTION_BASE = 30U,
    WARNING_BAD_CERT_ADD_EXCEPTION_FLAG_UNTRUSTED = 1U,
    WARNING_BAD_CERT_ADD_EXCEPTION_FLAG_DOMAIN = 2U,
    WARNING_BAD_CERT_ADD_EXCEPTION_FLAG_TIME = 4U,
    WARNING_BAD_CERT_CONFIRM_ADD_EXCEPTION_BASE = 38U,
    WARNING_BAD_CERT_CONFIRM_ADD_EXCEPTION_FLAG_UNTRUSTED = 1U,
    WARNING_BAD_CERT_CONFIRM_ADD_EXCEPTION_FLAG_DOMAIN = 2U,
    WARNING_BAD_CERT_CONFIRM_ADD_EXCEPTION_FLAG_TIME = 4U,
    WARNING_GEOLOCATION_REQUEST = 46U,
    WARNING_GEOLOCATION_REQUEST_SHARE_LOCATION = 47U,
    WARNING_GEOLOCATION_REQUEST_ALWAYS_SHARE = 48U,
    WARNING_GEOLOCATION_REQUEST_NEVER_SHARE = 49U,
    WARNING_INSECURE_UPDATE = 50U,
    WARNING_NO_SECURE_UPDATE = 51U
  };

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISecurityUITelemetry, NS_ISECURITYUITELEMETRY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISECURITYUITELEMETRY \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISECURITYUITELEMETRY(_to) \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISECURITYUITELEMETRY(_to) \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSecurityUITelemetry : public nsISecurityUITelemetry
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISECURITYUITELEMETRY

  nsSecurityUITelemetry();

private:
  ~nsSecurityUITelemetry();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSecurityUITelemetry, nsISecurityUITelemetry)

nsSecurityUITelemetry::nsSecurityUITelemetry()
{
  /* member initializers and constructor code */
}

nsSecurityUITelemetry::~nsSecurityUITelemetry()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISecurityUITelemetry_h__ */
