package com.aldebaran.qimessaging;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;

import com.aldebaran.qimessaging.ServiceDirectory;
import com.aldebaran.qimessaging.Session;
import com.aldebaran.qimessaging.GenericObject;
import com.aldebaran.qimessaging.ReplyService;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * Integration test for QiMessaging java bindings.
 */
public class TypeTest
{
  public GenericObject    proxy = null;
  public GenericObject    obj = null;
  public Session          s = null;
  public Session          client = null;
  public ServiceDirectory sd = null;

  @Before
  public void setUp() throws Exception
  {
    sd = new ServiceDirectory();
    s = new Session();
    client = new Session();

    // Get Service directory listening url.
    String url = sd.listenUrl();

    // Create new QiMessaging generic object
    obj = new GenericObject();

    // Get instance of ReplyService
    QimessagingService reply = new ReplyService();

    // Register event 'Fire'
    obj.advertiseSignal("fire::(i)");
    obj.advertiseMethod("reply::s(s)", reply);
    obj.advertiseMethod("answer::s()", reply);
    obj.advertiseMethod("add::i(iii)", reply);
    obj.advertiseMethod("info::(sib)(sib)", reply);
    obj.advertiseMethod("answer::i(i)", reply);
    obj.advertiseMethod("answerFloat::f(f)", reply);
    obj.advertiseMethod("answerBool::b(b)", reply);
    obj.advertiseMethod("abacus::{ib}({ib})", reply);
//    obj.advertiseMethod("abacus::{mm}({ib})", reply);
    obj.advertiseMethod("echoFloatList::[m]([f])", reply);

    // Connect session to Service Directory
    s.connect(url).sync();

    // Register service as serviceTest
    assertTrue("Service must be registered", s.registerService("serviceTest", obj));

    // Connect client session to service directory
    client.connect(url);

    // Get a proxy to serviceTest
    proxy = client.service("serviceTest");
    assertNotNull(proxy);
  }

  @After
  public void tearDown()
  {
    obj = null;
    proxy = null;

    s.close();
    client.close();

    s = null;
    client = null;
    sd = null;
  }

  /**
   * Test String conversion
   */
  @Test
  public void testString()
  {
    String ret = null;
    try {
      ret = proxy.<String>call("reply", "plaf");
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertEquals("plafbim !", ret);

    try {
      ret = proxy.<String>call("answer");
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertEquals("42 !", ret);
  }

  /**
   * Test Integer conversion
   */
  @Test
  public void testInt()
  {
    Integer ret = null;
    try {
      ret = proxy.<Integer>call("answer", 41);
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertEquals(42, ret.intValue());
  }

  /**
   * Test Float conversion
   */
  @Test
  public void testFloat()
  {
    Float ret = null;
    try {
      ret = proxy.<Float>call("answerFloat", 41.2f);
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertEquals(42.2f, ret.floatValue(), 0.1f);
  }

  /**
   * Test Boolean conversion
   */
  public void testBoolean()
  {
    Boolean ret = null;
    try {
      ret = proxy.<Boolean>call("answerBool", false);
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertTrue("Result must be true", ret);
  }

  /**
   * Test Map conversion
   */
  public void testEmptyMap()
  {
    Map<Integer, Boolean> args = new Hashtable<Integer, Boolean>();

    Map<Integer, Boolean> ret = null;
    try {
      ret = proxy.<Hashtable<Integer, Boolean> >call("abacus", args);
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertTrue("Result must be empty", ret.size() == 0);
  }

  /**
   * Test Map conversion
   */
  public void testIntegerBooleanMap()
  {
    Map<Integer, Boolean> args = new Hashtable<Integer, Boolean>();
    args.put(4, true);
    args.put(3, false);
    args.put(2, false);
    args.put(1, true);

    Map<Integer, Boolean> ret = null;
    try {
      ret = proxy.<Hashtable<Integer, Boolean> >call("abacus", args);
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertFalse("Result must be false", ret.get(1));
    assertTrue("Result must be true", ret.get(2));
    assertTrue("Result must be true", ret.get(3));
    assertFalse("Result must be false", ret.get(4));
  }

  /**
   * Test List conversion
   */
  public void testEmptyList()
  {
    List<Float> args = new ArrayList<Float>();

    List<Float> ret = null;
    try {
      ret = proxy.<ArrayList<Float> >call("echoFloatList", args);
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertTrue("Result must be empty", ret.size() == 0);
  }

  /**
   * Test List conversion
   */
  public void testIntegerList()
  {
    List<Float> args = new ArrayList<Float>();
    args.add(13.3f);
    args.add(1342.3f);
    args.add(13.4f);
    args.add(1.0f);
    args.add(0.1f);

    List<Float> ret = null;
    try {
      ret = proxy.<ArrayList<Float> >call("echoFloatList", args);
    }
    catch (CallError e)
    {
      fail("Call Error must not be thrown : " + e.getMessage());
    }

    assertEquals(args, ret);
  }
}