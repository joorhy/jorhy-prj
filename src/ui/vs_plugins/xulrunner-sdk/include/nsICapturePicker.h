/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/layout/forms/nsICapturePicker.idl
 */

#ifndef __gen_nsICapturePicker_h__
#define __gen_nsICapturePicker_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMWindow; /* forward declaration */

class nsIDOMFile; /* forward declaration */


/* starting interface:    nsICapturePicker */
#define NS_ICAPTUREPICKER_IID_STR "a4e2b2de-5712-4f80-aabb-7de3a747f227"

#define NS_ICAPTUREPICKER_IID \
  {0xa4e2b2de, 0x5712, 0x4f80, \
    { 0xaa, 0xbb, 0x7d, 0xe3, 0xa7, 0x47, 0xf2, 0x27 }}

class NS_NO_VTABLE nsICapturePicker : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICAPTUREPICKER_IID)

  enum {
    MODE_STILL = 1,
    MODE_AUDIO_CLIP = 2,
    MODE_VIDEO_CLIP = 3,
    MODE_VIDEO_NO_SOUND_CLIP = 4,
    RETURN_OK = 0,
    RETURN_CANCEL = 1
  };

  /* void init (in nsIDOMWindow parent, in AString title, in unsigned long mode); */
  NS_IMETHOD Init(nsIDOMWindow *parent, const nsAString & title, uint32_t mode) = 0;

  /* unsigned long show (); */
  NS_IMETHOD Show(uint32_t *_retval) = 0;

  /* boolean modeMayBeAvailable (in unsigned long mode); */
  NS_IMETHOD ModeMayBeAvailable(uint32_t mode, bool *_retval) = 0;

  /* readonly attribute nsIDOMFile file; */
  NS_IMETHOD GetFile(nsIDOMFile * *aFile) = 0;

  /* attribute AString type; */
  NS_IMETHOD GetType(nsAString & aType) = 0;
  NS_IMETHOD SetType(const nsAString & aType) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsICapturePicker, NS_ICAPTUREPICKER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICAPTUREPICKER \
  NS_IMETHOD Init(nsIDOMWindow *parent, const nsAString & title, uint32_t mode); \
  NS_IMETHOD Show(uint32_t *_retval); \
  NS_IMETHOD ModeMayBeAvailable(uint32_t mode, bool *_retval); \
  NS_IMETHOD GetFile(nsIDOMFile * *aFile); \
  NS_IMETHOD GetType(nsAString & aType); \
  NS_IMETHOD SetType(const nsAString & aType); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICAPTUREPICKER(_to) \
  NS_IMETHOD Init(nsIDOMWindow *parent, const nsAString & title, uint32_t mode) { return _to Init(parent, title, mode); } \
  NS_IMETHOD Show(uint32_t *_retval) { return _to Show(_retval); } \
  NS_IMETHOD ModeMayBeAvailable(uint32_t mode, bool *_retval) { return _to ModeMayBeAvailable(mode, _retval); } \
  NS_IMETHOD GetFile(nsIDOMFile * *aFile) { return _to GetFile(aFile); } \
  NS_IMETHOD GetType(nsAString & aType) { return _to GetType(aType); } \
  NS_IMETHOD SetType(const nsAString & aType) { return _to SetType(aType); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICAPTUREPICKER(_to) \
  NS_IMETHOD Init(nsIDOMWindow *parent, const nsAString & title, uint32_t mode) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(parent, title, mode); } \
  NS_IMETHOD Show(uint32_t *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Show(_retval); } \
  NS_IMETHOD ModeMayBeAvailable(uint32_t mode, bool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ModeMayBeAvailable(mode, _retval); } \
  NS_IMETHOD GetFile(nsIDOMFile * *aFile) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFile(aFile); } \
  NS_IMETHOD GetType(nsAString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_IMETHOD SetType(const nsAString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetType(aType); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsCapturePicker : public nsICapturePicker
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICAPTUREPICKER

  nsCapturePicker();

private:
  ~nsCapturePicker();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsCapturePicker, nsICapturePicker)

nsCapturePicker::nsCapturePicker()
{
  /* member initializers and constructor code */
}

nsCapturePicker::~nsCapturePicker()
{
  /* destructor code */
}

/* void init (in nsIDOMWindow parent, in AString title, in unsigned long mode); */
NS_IMETHODIMP nsCapturePicker::Init(nsIDOMWindow *parent, const nsAString & title, uint32_t mode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long show (); */
NS_IMETHODIMP nsCapturePicker::Show(uint32_t *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean modeMayBeAvailable (in unsigned long mode); */
NS_IMETHODIMP nsCapturePicker::ModeMayBeAvailable(uint32_t mode, bool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMFile file; */
NS_IMETHODIMP nsCapturePicker::GetFile(nsIDOMFile * *aFile)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString type; */
NS_IMETHODIMP nsCapturePicker::GetType(nsAString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsCapturePicker::SetType(const nsAString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsICapturePicker_h__ */
