/* THIS FILE IS AUTOGENERATED - DO NOT EDIT */

#ifndef mozilla_dom_HTMLPropertiesCollectionBinding_h__
#define mozilla_dom_HTMLPropertiesCollectionBinding_h__

#include "mozilla/ErrorResult.h"
#include "mozilla/dom/BindingDeclarations.h"
#include "mozilla/dom/DOMJSClass.h"
#include "mozilla/dom/DOMJSProxyHandler.h"

class XPCWrappedNativeScope;
namespace mozilla {
namespace dom {

class HTMLPropertiesCollection;

} // namespace dom
} // namespace mozilla

namespace mozilla {
namespace dom {

class PropertyNodeList;

} // namespace dom
} // namespace mozilla


namespace mozilla {
namespace dom {

template <>
struct PrototypeTraits<prototypes::id::HTMLPropertiesCollection>
{
  enum
  {
    Depth = 1
  };
  typedef mozilla::dom::HTMLPropertiesCollection NativeType;
};
template <>
struct PrototypeTraits<prototypes::id::PropertyNodeList>
{
  enum
  {
    Depth = 1
  };
  typedef mozilla::dom::PropertyNodeList NativeType;
};
template <>
struct PrototypeIDMap<mozilla::dom::HTMLPropertiesCollection>
{
  enum
  {
    PrototypeID = prototypes::id::HTMLPropertiesCollection
  };
};
template <>
struct PrototypeIDMap<mozilla::dom::PropertyNodeList>
{
  enum
  {
    PrototypeID = prototypes::id::PropertyNodeList
  };
};
} // namespace dom
} // namespace mozilla


namespace mozilla {
namespace dom {

namespace HTMLPropertiesCollectionBinding {

  extern const NativePropertyHooks sNativePropertyHooks;

  void
  CreateInterfaceObjects(JSContext* aCx, JSObject* aGlobal, JSObject** protoAndIfaceArray);

  inline JSObject* GetProtoObject(JSContext* aCx, JSObject* aGlobal)
  {

    /* Get the interface prototype object for this class.  This will create the
       object as needed. */

    /* Make sure our global is sane.  Hopefully we can remove this sometime */
    if (!(js::GetObjectClass(aGlobal)->flags & JSCLASS_DOM_GLOBAL)) {
      return NULL;
    }
    /* Check to see whether the interface objects are already installed */
    JSObject** protoAndIfaceArray = GetProtoAndIfaceArray(aGlobal);
    JSObject* cachedObject = protoAndIfaceArray[prototypes::id::HTMLPropertiesCollection];
    if (!cachedObject) {
      CreateInterfaceObjects(aCx, aGlobal, protoAndIfaceArray);
      cachedObject = protoAndIfaceArray[prototypes::id::HTMLPropertiesCollection];
    }

    /* cachedObject might _still_ be null, but that's OK */
    return cachedObject;
  }

  inline JSObject* GetConstructorObject(JSContext* aCx, JSObject* aGlobal)
  {

    /* Get the interface object for this class.  This will create the object as
       needed. */

    /* Make sure our global is sane.  Hopefully we can remove this sometime */
    if (!(js::GetObjectClass(aGlobal)->flags & JSCLASS_DOM_GLOBAL)) {
      return NULL;
    }
    /* Check to see whether the interface objects are already installed */
    JSObject** protoAndIfaceArray = GetProtoAndIfaceArray(aGlobal);
    JSObject* cachedObject = protoAndIfaceArray[constructors::id::HTMLPropertiesCollection];
    if (!cachedObject) {
      CreateInterfaceObjects(aCx, aGlobal, protoAndIfaceArray);
      cachedObject = protoAndIfaceArray[constructors::id::HTMLPropertiesCollection];
    }

    /* cachedObject might _still_ be null, but that's OK */
    return cachedObject;
  }

  bool
  ResolveOwnProperty(JSContext* cx, JSObject* wrapper, JSObject* obj, jsid id, JSPropertyDescriptor* desc, unsigned flags);

  bool
  EnumerateOwnProperties(JSContext* cx, JSObject* wrapper, JSObject* obj, JS::AutoIdVector& props);

  JSObject*
  DefineDOMInterface(JSContext* aCx, JSObject* aGlobal, bool* aEnabled);

  extern const DOMClass Class;

  class DOMProxyHandler : public mozilla::dom::DOMProxyHandler
  {
    inline DOMProxyHandler();

  public:
    bool
    getOwnPropertyDescriptor(JSContext* cx, JSObject* proxy, jsid id, JSPropertyDescriptor* desc, unsigned flags);

    bool
    getOwnPropertyNames(JSContext* cx, JSObject* proxy, JS::AutoIdVector& props);

    bool
    hasOwn(JSContext* cx, JSObject* proxy, jsid id, bool* bp);

    bool
    get(JSContext* cx, JSObject* proxy, JSObject* receiver, jsid id, JS::Value* vp);

    JSString*
    obj_toString(JSContext* cx, JSObject* proxy);

    void
    finalize(JSFreeOp* fop, JSObject* proxy);

    bool
    getElementIfPresent(JSContext* cx, JSObject* proxy, JSObject* receiver, uint32_t index, JS::Value* vp, bool* present);

    static DOMProxyHandler*
    getInstance();

    bool
    delete_(JSContext* cx, JSObject* proxy, jsid id, bool* bp);
  };

  bool
  Is(JSObject* obj);

  JSObject*
  Wrap(JSContext* aCx, JSObject* aScope, mozilla::dom::HTMLPropertiesCollection* aObject, nsWrapperCache* aCache, bool* aTriedToWrap);

  template <class T>
  inline JSObject* Wrap(JSContext* aCx, JSObject* aScope, T* aObject, bool* aTriedToWrap)
  {
    return Wrap(aCx, aScope, aObject, aObject, aTriedToWrap);
  }

} // namespace HTMLPropertiesCollectionBinding



namespace PropertyNodeListBinding {

  extern const NativePropertyHooks sNativePropertyHooks;

  void
  CreateInterfaceObjects(JSContext* aCx, JSObject* aGlobal, JSObject** protoAndIfaceArray);

  inline JSObject* GetProtoObject(JSContext* aCx, JSObject* aGlobal)
  {

    /* Get the interface prototype object for this class.  This will create the
       object as needed. */

    /* Make sure our global is sane.  Hopefully we can remove this sometime */
    if (!(js::GetObjectClass(aGlobal)->flags & JSCLASS_DOM_GLOBAL)) {
      return NULL;
    }
    /* Check to see whether the interface objects are already installed */
    JSObject** protoAndIfaceArray = GetProtoAndIfaceArray(aGlobal);
    JSObject* cachedObject = protoAndIfaceArray[prototypes::id::PropertyNodeList];
    if (!cachedObject) {
      CreateInterfaceObjects(aCx, aGlobal, protoAndIfaceArray);
      cachedObject = protoAndIfaceArray[prototypes::id::PropertyNodeList];
    }

    /* cachedObject might _still_ be null, but that's OK */
    return cachedObject;
  }

  inline JSObject* GetConstructorObject(JSContext* aCx, JSObject* aGlobal)
  {

    /* Get the interface object for this class.  This will create the object as
       needed. */

    /* Make sure our global is sane.  Hopefully we can remove this sometime */
    if (!(js::GetObjectClass(aGlobal)->flags & JSCLASS_DOM_GLOBAL)) {
      return NULL;
    }
    /* Check to see whether the interface objects are already installed */
    JSObject** protoAndIfaceArray = GetProtoAndIfaceArray(aGlobal);
    JSObject* cachedObject = protoAndIfaceArray[constructors::id::PropertyNodeList];
    if (!cachedObject) {
      CreateInterfaceObjects(aCx, aGlobal, protoAndIfaceArray);
      cachedObject = protoAndIfaceArray[constructors::id::PropertyNodeList];
    }

    /* cachedObject might _still_ be null, but that's OK */
    return cachedObject;
  }

  bool
  ResolveOwnProperty(JSContext* cx, JSObject* wrapper, JSObject* obj, jsid id, JSPropertyDescriptor* desc, unsigned flags);

  bool
  EnumerateOwnProperties(JSContext* cx, JSObject* wrapper, JSObject* obj, JS::AutoIdVector& props);

  JSObject*
  DefineDOMInterface(JSContext* aCx, JSObject* aGlobal, bool* aEnabled);

  extern const DOMClass Class;

  class DOMProxyHandler : public mozilla::dom::DOMProxyHandler
  {
    inline DOMProxyHandler();

  public:
    bool
    getOwnPropertyDescriptor(JSContext* cx, JSObject* proxy, jsid id, JSPropertyDescriptor* desc, unsigned flags);

    bool
    getOwnPropertyNames(JSContext* cx, JSObject* proxy, JS::AutoIdVector& props);

    bool
    hasOwn(JSContext* cx, JSObject* proxy, jsid id, bool* bp);

    bool
    get(JSContext* cx, JSObject* proxy, JSObject* receiver, jsid id, JS::Value* vp);

    JSString*
    obj_toString(JSContext* cx, JSObject* proxy);

    void
    finalize(JSFreeOp* fop, JSObject* proxy);

    bool
    getElementIfPresent(JSContext* cx, JSObject* proxy, JSObject* receiver, uint32_t index, JS::Value* vp, bool* present);

    static DOMProxyHandler*
    getInstance();

    bool
    delete_(JSContext* cx, JSObject* proxy, jsid id, bool* bp);
  };

  bool
  Is(JSObject* obj);

  JSObject*
  Wrap(JSContext* aCx, JSObject* aScope, mozilla::dom::PropertyNodeList* aObject, nsWrapperCache* aCache, bool* aTriedToWrap);

  template <class T>
  inline JSObject* Wrap(JSContext* aCx, JSObject* aScope, T* aObject, bool* aTriedToWrap)
  {
    return Wrap(aCx, aScope, aObject, aObject, aTriedToWrap);
  }

} // namespace PropertyNodeListBinding



} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_HTMLPropertiesCollectionBinding_h__
