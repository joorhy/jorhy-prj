/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/rel-m-rel-xr_w32_bld-000000000/build/accessible/public/nsIAccessibleRelation.idl
 */

#ifndef __gen_nsIAccessibleRelation_h__
#define __gen_nsIAccessibleRelation_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIArray_h__
#include "nsIArray.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIAccessible; /* forward declaration */


/* starting interface:    nsIAccessibleRelation */
#define NS_IACCESSIBLERELATION_IID_STR "f42a1589-70ab-4704-877f-4a9162bbe188"

#define NS_IACCESSIBLERELATION_IID \
  {0xf42a1589, 0x70ab, 0x4704, \
    { 0x87, 0x7f, 0x4a, 0x91, 0x62, 0xbb, 0xe1, 0x88 }}

class NS_NO_VTABLE nsIAccessibleRelation : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IACCESSIBLERELATION_IID)

  enum {
    RELATION_NUL = 0U,
    RELATION_CONTROLLED_BY = 1U,
    RELATION_FIRST = 1U,
    RELATION_CONTROLLER_FOR = 2U,
    RELATION_LABEL_FOR = 3U,
    RELATION_LABELLED_BY = 4U,
    RELATION_MEMBER_OF = 5U,
    RELATION_NODE_CHILD_OF = 6U,
    RELATION_FLOWS_TO = 7U,
    RELATION_FLOWS_FROM = 8U,
    RELATION_SUBWINDOW_OF = 9U,
    RELATION_EMBEDS = 10U,
    RELATION_EMBEDDED_BY = 11U,
    RELATION_POPUP_FOR = 12U,
    RELATION_PARENT_WINDOW_OF = 13U,
    RELATION_DESCRIBED_BY = 14U,
    RELATION_DESCRIPTION_FOR = 15U,
    RELATION_LAST = 15U,
    RELATION_DEFAULT_BUTTON = 16384U
  };

  /* readonly attribute unsigned long relationType; */
  NS_IMETHOD GetRelationType(uint32_t *aRelationType) = 0;

  /* readonly attribute unsigned long targetsCount; */
  NS_IMETHOD GetTargetsCount(uint32_t *aTargetsCount) = 0;

  /* nsIAccessible getTarget (in unsigned long index); */
  NS_IMETHOD GetTarget(uint32_t index, nsIAccessible * *_retval) = 0;

  /* nsIArray getTargets (); */
  NS_IMETHOD GetTargets(nsIArray * *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAccessibleRelation, NS_IACCESSIBLERELATION_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLERELATION \
  NS_IMETHOD GetRelationType(uint32_t *aRelationType); \
  NS_IMETHOD GetTargetsCount(uint32_t *aTargetsCount); \
  NS_IMETHOD GetTarget(uint32_t index, nsIAccessible * *_retval); \
  NS_IMETHOD GetTargets(nsIArray * *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLERELATION(_to) \
  NS_IMETHOD GetRelationType(uint32_t *aRelationType) { return _to GetRelationType(aRelationType); } \
  NS_IMETHOD GetTargetsCount(uint32_t *aTargetsCount) { return _to GetTargetsCount(aTargetsCount); } \
  NS_IMETHOD GetTarget(uint32_t index, nsIAccessible * *_retval) { return _to GetTarget(index, _retval); } \
  NS_IMETHOD GetTargets(nsIArray * *_retval) { return _to GetTargets(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLERELATION(_to) \
  NS_IMETHOD GetRelationType(uint32_t *aRelationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRelationType(aRelationType); } \
  NS_IMETHOD GetTargetsCount(uint32_t *aTargetsCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTargetsCount(aTargetsCount); } \
  NS_IMETHOD GetTarget(uint32_t index, nsIAccessible * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTarget(index, _retval); } \
  NS_IMETHOD GetTargets(nsIArray * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTargets(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleRelation : public nsIAccessibleRelation
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLERELATION

  nsAccessibleRelation();

private:
  ~nsAccessibleRelation();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleRelation, nsIAccessibleRelation)

nsAccessibleRelation::nsAccessibleRelation()
{
  /* member initializers and constructor code */
}

nsAccessibleRelation::~nsAccessibleRelation()
{
  /* destructor code */
}

/* readonly attribute unsigned long relationType; */
NS_IMETHODIMP nsAccessibleRelation::GetRelationType(uint32_t *aRelationType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long targetsCount; */
NS_IMETHODIMP nsAccessibleRelation::GetTargetsCount(uint32_t *aTargetsCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible getTarget (in unsigned long index); */
NS_IMETHODIMP nsAccessibleRelation::GetTarget(uint32_t index, nsIAccessible * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIArray getTargets (); */
NS_IMETHODIMP nsAccessibleRelation::GetTargets(nsIArray * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessibleRelation_h__ */
