/*
**  Copyright (C) 2015 Aldebaran Robotics
**  See COPYING for the license
*/
package com.aldebaran.qi;

import java.lang.reflect.Method;

public class AnyObject {

  static
  {
    // Loading native C++ libraries.
    if (!EmbeddedTools.LOADED_EMBEDDED_LIBRARY)
    {
      EmbeddedTools loader = new EmbeddedTools();
      loader.loadEmbeddedLibraries();
    }
  }

  private long    _p;

  private static native long     property(long pObj, String property);
  private static native long     setProperty(long pObj, String property, Object value);
  private static native long     asyncCall(long pObject, String method, Object[] args);
  private static native String   printMetaObject(long pObject);
  private static native void     destroy(long pObj);
  private static native long     connect(long pObject, String method, Object instance, String className, String eventName);
  private static native long     disconnect(long pObject, long subscriberId);
  private static native long     post(long pObject, String name, Object[] args);

  public static native Object decodeJSON(String str);
  public static native String encodeJSON(Object obj);

  /**
   * AnyObject constructor is not public,
   * user must use DynamicObjectBuilder.
   * @see DynamicObjectBuilder
   */
  AnyObject(long p)
  {
    this._p = p;
  }

  public Future<Void> setProperty(String property, Object o) throws Exception
  {
    return new Future<Void>(AnyObject.setProperty(_p, property, o));
  }

  public <T> Future<T> property(String property)
  {
    return new Future<T>(AnyObject.property(_p, property));
  }

  /**
   * Perform asynchronous call and return Future return value
   * @param method Method name to call
   * @param args Arguments to be forward to remote method
   * @return Future method return value
   * @throws CallError
   */
  public <T> Future<T> call(String method, Object ... args) throws CallError
  {
    com.aldebaran.qi.Future<T> ret = null;

    try
    {
      ret = new com.aldebaran.qi.Future<T>(AnyObject.asyncCall(_p, method, args));
    } catch (Exception e)
    {
      throw new CallError(e.getMessage());
    }

    if (ret.isValid() == false)
      throw new CallError("Future is null.");

    try
    {
      return ret;
    } catch (Exception e)
    {
      throw new CallError(e.getMessage());
    }
  }

  /**
   * Connect a callback to a foreign event.
   * @param eventName Name of the event
   * @param callback Callback name
   * @param object Instance of class implementing callback
   * @return an unique subscriber id
   * @throws Exception If callback method is not found in object instance.
   */
  public long connect(String eventName, String callback, Object object) throws Exception
  {
    Class<?extends Object> c = object.getClass();
    Method[] methods = c.getDeclaredMethods();

    for (Method method : methods)
    {
      String className = object.getClass().toString();
      className = className.substring(6); // Remove "class "
      className = className.replace('.', '/');

      // If method name match signature
      if (callback.contains(method.getName()) == true)
        return AnyObject.connect(_p, callback, object, className, eventName);
    }

    throw new Exception("Cannot find " + callback + " in object " + object.toString());
  }

  /**
   * Disconnect a previously registered callback.
   * @param subscriberId id returned by connect()
   *
   */
  public long disconnect(long subscriberId)
  {
    return AnyObject.disconnect(_p, subscriberId);
  }

  /**
   * Post an event advertised with advertiseEvent method.
   * @see advertiseEvent
   * @param eventName Name of the event to trigger.
   * @param args Arguments sent to callback
   */
  public void post(String eventName, Object ... args)
  {
    AnyObject.post(_p, eventName, args);
  }

  public String toString()
  {
    return AnyObject.printMetaObject(_p);
  }

  /**
   * Called by garbage collector
   * Finalize is overriden to manually delete C++ data
   */
  @Override
  protected void finalize() throws Throwable
  {
    AnyObject.destroy(_p);
    super.finalize();
  }
}
