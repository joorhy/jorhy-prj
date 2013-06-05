/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/accessible/public/nsIAccessibleEvent.idl
 */

#ifndef __gen_nsIAccessibleEvent_h__
#define __gen_nsIAccessibleEvent_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIAccessible; /* forward declaration */

class nsIAccessibleDocument; /* forward declaration */

class nsIDOMNode; /* forward declaration */

#define NS_ACCESSIBLE_EVENT_TOPIC "accessible-event"

/* starting interface:    nsIAccessibleEvent */
#define NS_IACCESSIBLEEVENT_IID_STR "7f66a33a-9ed7-4fd4-87a8-e431b0f43368"

#define NS_IACCESSIBLEEVENT_IID \
  {0x7f66a33a, 0x9ed7, 0x4fd4, \
    { 0x87, 0xa8, 0xe4, 0x31, 0xb0, 0xf4, 0x33, 0x68 }}

class NS_NO_VTABLE nsIAccessibleEvent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLEEVENT_IID)

  enum {
    EVENT_SHOW = 1U,
    EVENT_HIDE = 2U,
    EVENT_REORDER = 3U,
    EVENT_ACTIVE_DECENDENT_CHANGED = 4U,
    EVENT_FOCUS = 5U,
    EVENT_STATE_CHANGE = 6U,
    EVENT_LOCATION_CHANGE = 7U,
    EVENT_NAME_CHANGE = 8U,
    EVENT_DESCRIPTION_CHANGE = 9U,
    EVENT_VALUE_CHANGE = 10U,
    EVENT_HELP_CHANGE = 11U,
    EVENT_DEFACTION_CHANGE = 12U,
    EVENT_ACTION_CHANGE = 13U,
    EVENT_ACCELERATOR_CHANGE = 14U,
    EVENT_SELECTION = 15U,
    EVENT_SELECTION_ADD = 16U,
    EVENT_SELECTION_REMOVE = 17U,
    EVENT_SELECTION_WITHIN = 18U,
    EVENT_ALERT = 19U,
    EVENT_FOREGROUND = 20U,
    EVENT_MENU_START = 21U,
    EVENT_MENU_END = 22U,
    EVENT_MENUPOPUP_START = 23U,
    EVENT_MENUPOPUP_END = 24U,
    EVENT_CAPTURE_START = 25U,
    EVENT_CAPTURE_END = 26U,
    EVENT_MOVESIZE_START = 27U,
    EVENT_MOVESIZE_END = 28U,
    EVENT_CONTEXTHELP_START = 29U,
    EVENT_CONTEXTHELP_END = 30U,
    EVENT_DRAGDROP_START = 31U,
    EVENT_DRAGDROP_END = 32U,
    EVENT_DIALOG_START = 33U,
    EVENT_DIALOG_END = 34U,
    EVENT_SCROLLING_START = 35U,
    EVENT_SCROLLING_END = 36U,
    EVENT_MINIMIZE_START = 37U,
    EVENT_MINIMIZE_END = 38U,
    EVENT_DOCUMENT_LOAD_COMPLETE = 39U,
    EVENT_DOCUMENT_RELOAD = 40U,
    EVENT_DOCUMENT_LOAD_STOPPED = 41U,
    EVENT_DOCUMENT_ATTRIBUTES_CHANGED = 42U,
    EVENT_DOCUMENT_CONTENT_CHANGED = 43U,
    EVENT_PROPERTY_CHANGED = 44U,
    EVENT_PAGE_CHANGED = 45U,
    EVENT_TEXT_ATTRIBUTE_CHANGED = 46U,
    EVENT_TEXT_CARET_MOVED = 47U,
    EVENT_TEXT_CHANGED = 48U,
    EVENT_TEXT_INSERTED = 49U,
    EVENT_TEXT_REMOVED = 50U,
    EVENT_TEXT_UPDATED = 51U,
    EVENT_TEXT_SELECTION_CHANGED = 52U,
    EVENT_VISIBLE_DATA_CHANGED = 53U,
    EVENT_TEXT_COLUMN_CHANGED = 54U,
    EVENT_SECTION_CHANGED = 55U,
    EVENT_TABLE_CAPTION_CHANGED = 56U,
    EVENT_TABLE_MODEL_CHANGED = 57U,
    EVENT_TABLE_SUMMARY_CHANGED = 58U,
    EVENT_TABLE_ROW_DESCRIPTION_CHANGED = 59U,
    EVENT_TABLE_ROW_HEADER_CHANGED = 60U,
    EVENT_TABLE_ROW_INSERT = 61U,
    EVENT_TABLE_ROW_DELETE = 62U,
    EVENT_TABLE_ROW_REORDER = 63U,
    EVENT_TABLE_COLUMN_DESCRIPTION_CHANGED = 64U,
    EVENT_TABLE_COLUMN_HEADER_CHANGED = 65U,
    EVENT_TABLE_COLUMN_INSERT = 66U,
    EVENT_TABLE_COLUMN_DELETE = 67U,
    EVENT_TABLE_COLUMN_REORDER = 68U,
    EVENT_WINDOW_ACTIVATE = 69U,
    EVENT_WINDOW_CREATE = 70U,
    EVENT_WINDOW_DEACTIVATE = 71U,
    EVENT_WINDOW_DESTROY = 72U,
    EVENT_WINDOW_MAXIMIZE = 73U,
    EVENT_WINDOW_MINIMIZE = 74U,
    EVENT_WINDOW_RESIZE = 75U,
    EVENT_WINDOW_RESTORE = 76U,
    EVENT_HYPERLINK_END_INDEX_CHANGED = 77U,
    EVENT_HYPERLINK_NUMBER_OF_ANCHORS_CHANGED = 78U,
    EVENT_HYPERLINK_SELECTED_LINK_CHANGED = 79U,
    EVENT_HYPERTEXT_LINK_ACTIVATED = 80U,
    EVENT_HYPERTEXT_LINK_SELECTED = 81U,
    EVENT_HYPERLINK_START_INDEX_CHANGED = 82U,
    EVENT_HYPERTEXT_CHANGED = 83U,
    EVENT_HYPERTEXT_NLINKS_CHANGED = 84U,
    EVENT_OBJECT_ATTRIBUTE_CHANGED = 85U,
    EVENT_VIRTUALCURSOR_CHANGED = 86U,
    EVENT_LAST_ENTRY = 87U
  };

  /* readonly attribute unsigned long eventType; */
  NS_IMETHOD GetEventType(uint32_t *aEventType) = 0;

  /* readonly attribute nsIAccessible accessible; */
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible) = 0;

  /* readonly attribute nsIAccessibleDocument accessibleDocument; */
  NS_IMETHOD GetAccessibleDocument(nsIAccessibleDocument * *aAccessibleDocument) = 0;

  /* readonly attribute nsIDOMNode DOMNode; */
  NS_IMETHOD GetDOMNode(nsIDOMNode * *aDOMNode) = 0;

  /* readonly attribute boolean isFromUserInput; */
  NS_IMETHOD GetIsFromUserInput(bool *aIsFromUserInput) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleEvent, NS_IACCESSIBLEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLEEVENT \
  NS_IMETHOD GetEventType(uint32_t *aEventType); \
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible); \
  NS_IMETHOD GetAccessibleDocument(nsIAccessibleDocument * *aAccessibleDocument); \
  NS_IMETHOD GetDOMNode(nsIDOMNode * *aDOMNode); \
  NS_IMETHOD GetIsFromUserInput(bool *aIsFromUserInput); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLEEVENT(_to) \
  NS_IMETHOD GetEventType(uint32_t *aEventType) { return _to GetEventType(aEventType); } \
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible) { return _to GetAccessible(aAccessible); } \
  NS_IMETHOD GetAccessibleDocument(nsIAccessibleDocument * *aAccessibleDocument) { return _to GetAccessibleDocument(aAccessibleDocument); } \
  NS_IMETHOD GetDOMNode(nsIDOMNode * *aDOMNode) { return _to GetDOMNode(aDOMNode); } \
  NS_IMETHOD GetIsFromUserInput(bool *aIsFromUserInput) { return _to GetIsFromUserInput(aIsFromUserInput); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLEEVENT(_to) \
  NS_IMETHOD GetEventType(uint32_t *aEventType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetEventType(aEventType); } \
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessible(aAccessible); } \
  NS_IMETHOD GetAccessibleDocument(nsIAccessibleDocument * *aAccessibleDocument) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessibleDocument(aAccessibleDocument); } \
  NS_IMETHOD GetDOMNode(nsIDOMNode * *aDOMNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDOMNode(aDOMNode); } \
  NS_IMETHOD GetIsFromUserInput(bool *aIsFromUserInput) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsFromUserInput(aIsFromUserInput); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleEvent : public nsIAccessibleEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLEEVENT

  nsAccessibleEvent();

private:
  ~nsAccessibleEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleEvent, nsIAccessibleEvent)

nsAccessibleEvent::nsAccessibleEvent()
{
  /* member initializers and constructor code */
}

nsAccessibleEvent::~nsAccessibleEvent()
{
  /* destructor code */
}

/* readonly attribute unsigned long eventType; */
NS_IMETHODIMP nsAccessibleEvent::GetEventType(uint32_t *aEventType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible accessible; */
NS_IMETHODIMP nsAccessibleEvent::GetAccessible(nsIAccessible * *aAccessible)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessibleDocument accessibleDocument; */
NS_IMETHODIMP nsAccessibleEvent::GetAccessibleDocument(nsIAccessibleDocument * *aAccessibleDocument)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMNode DOMNode; */
NS_IMETHODIMP nsAccessibleEvent::GetDOMNode(nsIDOMNode * *aDOMNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean isFromUserInput; */
NS_IMETHODIMP nsAccessibleEvent::GetIsFromUserInput(bool *aIsFromUserInput)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIAccessibleStateChangeEvent */
#define NS_IACCESSIBLESTATECHANGEEVENT_IID_STR "9addd25d-8fa1-415e-94ec-6038f220d3e4"

#define NS_IACCESSIBLESTATECHANGEEVENT_IID \
  {0x9addd25d, 0x8fa1, 0x415e, \
    { 0x94, 0xec, 0x60, 0x38, 0xf2, 0x20, 0xd3, 0xe4 }}

class NS_NO_VTABLE nsIAccessibleStateChangeEvent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLESTATECHANGEEVENT_IID)

  /* readonly attribute unsigned long state; */
  NS_IMETHOD GetState(uint32_t *aState) = 0;

  /* boolean isExtraState (); */
  NS_IMETHOD IsExtraState(bool *_retval) = 0;

  /* boolean isEnabled (); */
  NS_IMETHOD IsEnabled(bool *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleStateChangeEvent, NS_IACCESSIBLESTATECHANGEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLESTATECHANGEEVENT \
  NS_IMETHOD GetState(uint32_t *aState); \
  NS_IMETHOD IsExtraState(bool *_retval); \
  NS_IMETHOD IsEnabled(bool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLESTATECHANGEEVENT(_to) \
  NS_IMETHOD GetState(uint32_t *aState) { return _to GetState(aState); } \
  NS_IMETHOD IsExtraState(bool *_retval) { return _to IsExtraState(_retval); } \
  NS_IMETHOD IsEnabled(bool *_retval) { return _to IsEnabled(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLESTATECHANGEEVENT(_to) \
  NS_IMETHOD GetState(uint32_t *aState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetState(aState); } \
  NS_IMETHOD IsExtraState(bool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsExtraState(_retval); } \
  NS_IMETHOD IsEnabled(bool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsEnabled(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleStateChangeEvent : public nsIAccessibleStateChangeEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLESTATECHANGEEVENT

  nsAccessibleStateChangeEvent();

private:
  ~nsAccessibleStateChangeEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleStateChangeEvent, nsIAccessibleStateChangeEvent)

nsAccessibleStateChangeEvent::nsAccessibleStateChangeEvent()
{
  /* member initializers and constructor code */
}

nsAccessibleStateChangeEvent::~nsAccessibleStateChangeEvent()
{
  /* destructor code */
}

/* readonly attribute unsigned long state; */
NS_IMETHODIMP nsAccessibleStateChangeEvent::GetState(uint32_t *aState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isExtraState (); */
NS_IMETHODIMP nsAccessibleStateChangeEvent::IsExtraState(bool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isEnabled (); */
NS_IMETHODIMP nsAccessibleStateChangeEvent::IsEnabled(bool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIAccessibleTextChangeEvent */
#define NS_IACCESSIBLETEXTCHANGEEVENT_IID_STR "21e0f8bd-5638-4964-870b-3c8e944ac4c4"

#define NS_IACCESSIBLETEXTCHANGEEVENT_IID \
  {0x21e0f8bd, 0x5638, 0x4964, \
    { 0x87, 0x0b, 0x3c, 0x8e, 0x94, 0x4a, 0xc4, 0xc4 }}

class NS_NO_VTABLE nsIAccessibleTextChangeEvent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLETEXTCHANGEEVENT_IID)

  /* readonly attribute long start; */
  NS_IMETHOD GetStart(int32_t *aStart) = 0;

  /* readonly attribute unsigned long length; */
  NS_IMETHOD GetLength(uint32_t *aLength) = 0;

  /* boolean isInserted (); */
  NS_IMETHOD IsInserted(bool *_retval) = 0;

  /* readonly attribute DOMString modifiedText; */
  NS_IMETHOD GetModifiedText(nsAString & aModifiedText) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleTextChangeEvent, NS_IACCESSIBLETEXTCHANGEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLETEXTCHANGEEVENT \
  NS_IMETHOD GetStart(int32_t *aStart); \
  NS_IMETHOD GetLength(uint32_t *aLength); \
  NS_IMETHOD IsInserted(bool *_retval); \
  NS_IMETHOD GetModifiedText(nsAString & aModifiedText); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLETEXTCHANGEEVENT(_to) \
  NS_IMETHOD GetStart(int32_t *aStart) { return _to GetStart(aStart); } \
  NS_IMETHOD GetLength(uint32_t *aLength) { return _to GetLength(aLength); } \
  NS_IMETHOD IsInserted(bool *_retval) { return _to IsInserted(_retval); } \
  NS_IMETHOD GetModifiedText(nsAString & aModifiedText) { return _to GetModifiedText(aModifiedText); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLETEXTCHANGEEVENT(_to) \
  NS_IMETHOD GetStart(int32_t *aStart) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStart(aStart); } \
  NS_IMETHOD GetLength(uint32_t *aLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLength(aLength); } \
  NS_IMETHOD IsInserted(bool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsInserted(_retval); } \
  NS_IMETHOD GetModifiedText(nsAString & aModifiedText) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetModifiedText(aModifiedText); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleTextChangeEvent : public nsIAccessibleTextChangeEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLETEXTCHANGEEVENT

  nsAccessibleTextChangeEvent();

private:
  ~nsAccessibleTextChangeEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleTextChangeEvent, nsIAccessibleTextChangeEvent)

nsAccessibleTextChangeEvent::nsAccessibleTextChangeEvent()
{
  /* member initializers and constructor code */
}

nsAccessibleTextChangeEvent::~nsAccessibleTextChangeEvent()
{
  /* destructor code */
}

/* readonly attribute long start; */
NS_IMETHODIMP nsAccessibleTextChangeEvent::GetStart(int32_t *aStart)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long length; */
NS_IMETHODIMP nsAccessibleTextChangeEvent::GetLength(uint32_t *aLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isInserted (); */
NS_IMETHODIMP nsAccessibleTextChangeEvent::IsInserted(bool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString modifiedText; */
NS_IMETHODIMP nsAccessibleTextChangeEvent::GetModifiedText(nsAString & aModifiedText)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIAccessibleHideEvent */
#define NS_IACCESSIBLEHIDEEVENT_IID_STR "a2bd2eca-3afa-489b-afb2-f93ef32ad99c"

#define NS_IACCESSIBLEHIDEEVENT_IID \
  {0xa2bd2eca, 0x3afa, 0x489b, \
    { 0xaf, 0xb2, 0xf9, 0x3e, 0xf3, 0x2a, 0xd9, 0x9c }}

class NS_NO_VTABLE nsIAccessibleHideEvent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLEHIDEEVENT_IID)

  /* readonly attribute nsIAccessible targetParent; */
  NS_IMETHOD GetTargetParent(nsIAccessible * *aTargetParent) = 0;

  /* readonly attribute nsIAccessible targetNextSibling; */
  NS_IMETHOD GetTargetNextSibling(nsIAccessible * *aTargetNextSibling) = 0;

  /* readonly attribute nsIAccessible targetPrevSibling; */
  NS_IMETHOD GetTargetPrevSibling(nsIAccessible * *aTargetPrevSibling) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleHideEvent, NS_IACCESSIBLEHIDEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLEHIDEEVENT \
  NS_IMETHOD GetTargetParent(nsIAccessible * *aTargetParent); \
  NS_IMETHOD GetTargetNextSibling(nsIAccessible * *aTargetNextSibling); \
  NS_IMETHOD GetTargetPrevSibling(nsIAccessible * *aTargetPrevSibling); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLEHIDEEVENT(_to) \
  NS_IMETHOD GetTargetParent(nsIAccessible * *aTargetParent) { return _to GetTargetParent(aTargetParent); } \
  NS_IMETHOD GetTargetNextSibling(nsIAccessible * *aTargetNextSibling) { return _to GetTargetNextSibling(aTargetNextSibling); } \
  NS_IMETHOD GetTargetPrevSibling(nsIAccessible * *aTargetPrevSibling) { return _to GetTargetPrevSibling(aTargetPrevSibling); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLEHIDEEVENT(_to) \
  NS_IMETHOD GetTargetParent(nsIAccessible * *aTargetParent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTargetParent(aTargetParent); } \
  NS_IMETHOD GetTargetNextSibling(nsIAccessible * *aTargetNextSibling) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTargetNextSibling(aTargetNextSibling); } \
  NS_IMETHOD GetTargetPrevSibling(nsIAccessible * *aTargetPrevSibling) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTargetPrevSibling(aTargetPrevSibling); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleHideEvent : public nsIAccessibleHideEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLEHIDEEVENT

  nsAccessibleHideEvent();

private:
  ~nsAccessibleHideEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleHideEvent, nsIAccessibleHideEvent)

nsAccessibleHideEvent::nsAccessibleHideEvent()
{
  /* member initializers and constructor code */
}

nsAccessibleHideEvent::~nsAccessibleHideEvent()
{
  /* destructor code */
}

/* readonly attribute nsIAccessible targetParent; */
NS_IMETHODIMP nsAccessibleHideEvent::GetTargetParent(nsIAccessible * *aTargetParent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible targetNextSibling; */
NS_IMETHODIMP nsAccessibleHideEvent::GetTargetNextSibling(nsIAccessible * *aTargetNextSibling)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible targetPrevSibling; */
NS_IMETHODIMP nsAccessibleHideEvent::GetTargetPrevSibling(nsIAccessible * *aTargetPrevSibling)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIAccessibleCaretMoveEvent */
#define NS_IACCESSIBLECARETMOVEEVENT_IID_STR "5675c486-a230-4d85-a4bd-33670826d5ff"

#define NS_IACCESSIBLECARETMOVEEVENT_IID \
  {0x5675c486, 0xa230, 0x4d85, \
    { 0xa4, 0xbd, 0x33, 0x67, 0x08, 0x26, 0xd5, 0xff }}

class NS_NO_VTABLE nsIAccessibleCaretMoveEvent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLECARETMOVEEVENT_IID)

  /* readonly attribute long caretOffset; */
  NS_IMETHOD GetCaretOffset(int32_t *aCaretOffset) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleCaretMoveEvent, NS_IACCESSIBLECARETMOVEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLECARETMOVEEVENT \
  NS_IMETHOD GetCaretOffset(int32_t *aCaretOffset); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLECARETMOVEEVENT(_to) \
  NS_IMETHOD GetCaretOffset(int32_t *aCaretOffset) { return _to GetCaretOffset(aCaretOffset); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLECARETMOVEEVENT(_to) \
  NS_IMETHOD GetCaretOffset(int32_t *aCaretOffset) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCaretOffset(aCaretOffset); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleCaretMoveEvent : public nsIAccessibleCaretMoveEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLECARETMOVEEVENT

  nsAccessibleCaretMoveEvent();

private:
  ~nsAccessibleCaretMoveEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleCaretMoveEvent, nsIAccessibleCaretMoveEvent)

nsAccessibleCaretMoveEvent::nsAccessibleCaretMoveEvent()
{
  /* member initializers and constructor code */
}

nsAccessibleCaretMoveEvent::~nsAccessibleCaretMoveEvent()
{
  /* destructor code */
}

/* readonly attribute long caretOffset; */
NS_IMETHODIMP nsAccessibleCaretMoveEvent::GetCaretOffset(int32_t *aCaretOffset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIAccessibleTableChangeEvent */
#define NS_IACCESSIBLETABLECHANGEEVENT_IID_STR "df517997-ed52-4ea2-b310-2f8e0fe64572"

#define NS_IACCESSIBLETABLECHANGEEVENT_IID \
  {0xdf517997, 0xed52, 0x4ea2, \
    { 0xb3, 0x10, 0x2f, 0x8e, 0x0f, 0xe6, 0x45, 0x72 }}

class NS_NO_VTABLE nsIAccessibleTableChangeEvent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLETABLECHANGEEVENT_IID)

  /* readonly attribute long rowOrColIndex; */
  NS_IMETHOD GetRowOrColIndex(int32_t *aRowOrColIndex) = 0;

  /* readonly attribute long numRowsOrCols; */
  NS_IMETHOD GetNumRowsOrCols(int32_t *aNumRowsOrCols) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleTableChangeEvent, NS_IACCESSIBLETABLECHANGEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLETABLECHANGEEVENT \
  NS_IMETHOD GetRowOrColIndex(int32_t *aRowOrColIndex); \
  NS_IMETHOD GetNumRowsOrCols(int32_t *aNumRowsOrCols); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLETABLECHANGEEVENT(_to) \
  NS_IMETHOD GetRowOrColIndex(int32_t *aRowOrColIndex) { return _to GetRowOrColIndex(aRowOrColIndex); } \
  NS_IMETHOD GetNumRowsOrCols(int32_t *aNumRowsOrCols) { return _to GetNumRowsOrCols(aNumRowsOrCols); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLETABLECHANGEEVENT(_to) \
  NS_IMETHOD GetRowOrColIndex(int32_t *aRowOrColIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRowOrColIndex(aRowOrColIndex); } \
  NS_IMETHOD GetNumRowsOrCols(int32_t *aNumRowsOrCols) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNumRowsOrCols(aNumRowsOrCols); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleTableChangeEvent : public nsIAccessibleTableChangeEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLETABLECHANGEEVENT

  nsAccessibleTableChangeEvent();

private:
  ~nsAccessibleTableChangeEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleTableChangeEvent, nsIAccessibleTableChangeEvent)

nsAccessibleTableChangeEvent::nsAccessibleTableChangeEvent()
{
  /* member initializers and constructor code */
}

nsAccessibleTableChangeEvent::~nsAccessibleTableChangeEvent()
{
  /* destructor code */
}

/* readonly attribute long rowOrColIndex; */
NS_IMETHODIMP nsAccessibleTableChangeEvent::GetRowOrColIndex(int32_t *aRowOrColIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long numRowsOrCols; */
NS_IMETHODIMP nsAccessibleTableChangeEvent::GetNumRowsOrCols(int32_t *aNumRowsOrCols)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIAccessibleVirtualCursorChangeEvent */
#define NS_IACCESSIBLEVIRTUALCURSORCHANGEEVENT_IID_STR "370e8b9b-2bbc-4bff-a9c7-16ddc54aea21"

#define NS_IACCESSIBLEVIRTUALCURSORCHANGEEVENT_IID \
  {0x370e8b9b, 0x2bbc, 0x4bff, \
    { 0xa9, 0xc7, 0x16, 0xdd, 0xc5, 0x4a, 0xea, 0x21 }}

class NS_NO_VTABLE nsIAccessibleVirtualCursorChangeEvent : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLEVIRTUALCURSORCHANGEEVENT_IID)

  /* readonly attribute nsIAccessible oldAccessible; */
  NS_IMETHOD GetOldAccessible(nsIAccessible * *aOldAccessible) = 0;

  /* readonly attribute long oldStartOffset; */
  NS_IMETHOD GetOldStartOffset(int32_t *aOldStartOffset) = 0;

  /* readonly attribute long oldEndOffset; */
  NS_IMETHOD GetOldEndOffset(int32_t *aOldEndOffset) = 0;

  /* readonly attribute short reason; */
  NS_IMETHOD GetReason(int16_t *aReason) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleVirtualCursorChangeEvent, NS_IACCESSIBLEVIRTUALCURSORCHANGEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLEVIRTUALCURSORCHANGEEVENT \
  NS_IMETHOD GetOldAccessible(nsIAccessible * *aOldAccessible); \
  NS_IMETHOD GetOldStartOffset(int32_t *aOldStartOffset); \
  NS_IMETHOD GetOldEndOffset(int32_t *aOldEndOffset); \
  NS_IMETHOD GetReason(int16_t *aReason); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLEVIRTUALCURSORCHANGEEVENT(_to) \
  NS_IMETHOD GetOldAccessible(nsIAccessible * *aOldAccessible) { return _to GetOldAccessible(aOldAccessible); } \
  NS_IMETHOD GetOldStartOffset(int32_t *aOldStartOffset) { return _to GetOldStartOffset(aOldStartOffset); } \
  NS_IMETHOD GetOldEndOffset(int32_t *aOldEndOffset) { return _to GetOldEndOffset(aOldEndOffset); } \
  NS_IMETHOD GetReason(int16_t *aReason) { return _to GetReason(aReason); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLEVIRTUALCURSORCHANGEEVENT(_to) \
  NS_IMETHOD GetOldAccessible(nsIAccessible * *aOldAccessible) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOldAccessible(aOldAccessible); } \
  NS_IMETHOD GetOldStartOffset(int32_t *aOldStartOffset) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOldStartOffset(aOldStartOffset); } \
  NS_IMETHOD GetOldEndOffset(int32_t *aOldEndOffset) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOldEndOffset(aOldEndOffset); } \
  NS_IMETHOD GetReason(int16_t *aReason) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetReason(aReason); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleVirtualCursorChangeEvent : public nsIAccessibleVirtualCursorChangeEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLEVIRTUALCURSORCHANGEEVENT

  nsAccessibleVirtualCursorChangeEvent();

private:
  ~nsAccessibleVirtualCursorChangeEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleVirtualCursorChangeEvent, nsIAccessibleVirtualCursorChangeEvent)

nsAccessibleVirtualCursorChangeEvent::nsAccessibleVirtualCursorChangeEvent()
{
  /* member initializers and constructor code */
}

nsAccessibleVirtualCursorChangeEvent::~nsAccessibleVirtualCursorChangeEvent()
{
  /* destructor code */
}

/* readonly attribute nsIAccessible oldAccessible; */
NS_IMETHODIMP nsAccessibleVirtualCursorChangeEvent::GetOldAccessible(nsIAccessible * *aOldAccessible)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long oldStartOffset; */
NS_IMETHODIMP nsAccessibleVirtualCursorChangeEvent::GetOldStartOffset(int32_t *aOldStartOffset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long oldEndOffset; */
NS_IMETHODIMP nsAccessibleVirtualCursorChangeEvent::GetOldEndOffset(int32_t *aOldEndOffset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute short reason; */
NS_IMETHODIMP nsAccessibleVirtualCursorChangeEvent::GetReason(int16_t *aReason)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessibleEvent_h__ */
