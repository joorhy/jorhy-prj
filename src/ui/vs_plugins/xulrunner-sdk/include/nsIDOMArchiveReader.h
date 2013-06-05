/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/dom/file/nsIDOMArchiveReader.idl
 */

#ifndef __gen_nsIDOMArchiveReader_h__
#define __gen_nsIDOMArchiveReader_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMArchiveRequest; /* forward declaration */


/* starting interface:    nsIDOMArchiveReader */
#define NS_IDOMARCHIVEREADER_IID_STR "a616ab85-fc3a-4028-9f10-f8620ee1b8e1"

#define NS_IDOMARCHIVEREADER_IID \
  {0xa616ab85, 0xfc3a, 0x4028, \
    { 0x9f, 0x10, 0xf8, 0x62, 0x0e, 0xe1, 0xb8, 0xe1 }}

class NS_NO_VTABLE nsIDOMArchiveReader : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMARCHIVEREADER_IID)

  /* nsIDOMArchiveRequest getFilenames (); */
  NS_IMETHOD GetFilenames(nsIDOMArchiveRequest * *_retval) = 0;

  /* nsIDOMArchiveRequest getFile (in DOMString filename); */
  NS_IMETHOD GetFile(const nsAString & filename, nsIDOMArchiveRequest * *_retval) = 0;

  /* nsIDOMArchiveRequest getFiles (); */
  NS_IMETHOD GetFiles(nsIDOMArchiveRequest * *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMArchiveReader, NS_IDOMARCHIVEREADER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMARCHIVEREADER \
  NS_IMETHOD GetFilenames(nsIDOMArchiveRequest * *_retval); \
  NS_IMETHOD GetFile(const nsAString & filename, nsIDOMArchiveRequest * *_retval); \
  NS_IMETHOD GetFiles(nsIDOMArchiveRequest * *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMARCHIVEREADER(_to) \
  NS_IMETHOD GetFilenames(nsIDOMArchiveRequest * *_retval) { return _to GetFilenames(_retval); } \
  NS_IMETHOD GetFile(const nsAString & filename, nsIDOMArchiveRequest * *_retval) { return _to GetFile(filename, _retval); } \
  NS_IMETHOD GetFiles(nsIDOMArchiveRequest * *_retval) { return _to GetFiles(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMARCHIVEREADER(_to) \
  NS_IMETHOD GetFilenames(nsIDOMArchiveRequest * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFilenames(_retval); } \
  NS_IMETHOD GetFile(const nsAString & filename, nsIDOMArchiveRequest * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFile(filename, _retval); } \
  NS_IMETHOD GetFiles(nsIDOMArchiveRequest * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFiles(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMArchiveReader : public nsIDOMArchiveReader
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMARCHIVEREADER

  nsDOMArchiveReader();

private:
  ~nsDOMArchiveReader();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMArchiveReader, nsIDOMArchiveReader)

nsDOMArchiveReader::nsDOMArchiveReader()
{
  /* member initializers and constructor code */
}

nsDOMArchiveReader::~nsDOMArchiveReader()
{
  /* destructor code */
}

/* nsIDOMArchiveRequest getFilenames (); */
NS_IMETHODIMP nsDOMArchiveReader::GetFilenames(nsIDOMArchiveRequest * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMArchiveRequest getFile (in DOMString filename); */
NS_IMETHODIMP nsDOMArchiveReader::GetFile(const nsAString & filename, nsIDOMArchiveRequest * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMArchiveRequest getFiles (); */
NS_IMETHODIMP nsDOMArchiveReader::GetFiles(nsIDOMArchiveRequest * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_ARCHIVEREADER_CID                         \
{0xb6b8c817, 0x4e9a, 0x46f8,                         \
{0x9e, 0x3e, 0x3d, 0x96, 0x79, 0x01, 0xa2, 0x80}}
#define NS_ARCHIVEREADER_CONTRACTID \
"@mozilla.org/files/archivereader;1"

#endif /* __gen_nsIDOMArchiveReader_h__ */
