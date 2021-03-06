/*
**
** Author(s):
**  - Pierre ROULLON <proullon@aldebaran-robotics.com>
**
** Copyright (C) 2012, 2013 Aldebaran Robotics
** See COPYING for the license
*/

#include <cstring>

#include <qi/log.hpp>
#include <qi/applicationsession.hpp>
#include <jnitools.hpp>
#include "application_jni.hpp"

qiLogCategory("qimessaging.jni");

static jlong app = 0;

jlong createApplication(JNIEnv* env, jobjectArray jargs, const boost::function<jlong(int& argc, char**& argv)>& fn)
{
  if (app)
  {
    throwJavaError(env, "Tried to create more than one application");
    return 0;
  }

  int argc = env->GetArrayLength(jargs);
  char **argv = new char*[argc + 1];

  // can we do something about this?
  argv[0] = new char[5];
  memcpy(argv[0], "java", 5);

  for (int i = 0; i < argc; ++i)
  {
    jstring jarg = (jstring)env->GetObjectArrayElement(jargs, i);
    jsize arglen = env->GetStringUTFLength(jarg);
    argv[i+1] = new char[arglen+1];
    const char* argchars = env->GetStringUTFChars(jarg, NULL);
    memcpy(argv[i+1], argchars, arglen);
    argv[i+1][arglen] = '\0';
    env->ReleaseStringUTFChars(jarg, argchars);
  }

  ++argc; // account for the first argument that we push_front()ed
  int cargc = argc;
  char** cargv = new char*[cargc];
  memcpy(cargv, argv, argc * sizeof(*argv));

  app = fn(cargc, cargv);

  for (int i = 0; i < argc; ++i)
    delete[] argv[i];
  delete[] argv;
  delete[] cargv;

  return app;
}

jlong newApplicationSession(JNIEnv* env, jstring jdefaultUrl, jboolean listen, int& cargc, char**& cargv)
{
  if (jdefaultUrl)
  {
    const char* cdefurl = env->GetStringUTFChars(jdefaultUrl, NULL);
    std::string defaultUrl(cdefurl);
    env->ReleaseStringUTFChars(jdefaultUrl, cdefurl);

    return (jlong)new qi::ApplicationSession(cargc, cargv, 0, defaultUrl);
  }
  else
    return (jlong)new qi::ApplicationSession(cargc, cargv);
}

jlong Java_com_aldebaran_qi_Application_qiApplicationCreate(JNIEnv *env, jclass QI_UNUSED(jobj), jobjectArray jargs, jstring jdefaultUrl, jboolean listen)
{
  return createApplication(env, jargs, boost::bind(newApplicationSession, env, jdefaultUrl, listen, _1, _2));
}

jlong Java_com_aldebaran_qi_Application_qiApplicationGetSession(JNIEnv *,jclass, jlong pApplication)
{
  qi::ApplicationSession* app = reinterpret_cast<qi::ApplicationSession*>(pApplication);

  return (jlong)app->session().get();
}

void Java_com_aldebaran_qi_Application_qiApplicationDestroy(JNIEnv *,jclass, jlong pApplication)
{
  qi::Application* app = reinterpret_cast<qi::Application *>(pApplication);

  delete app;
}

void Java_com_aldebaran_qi_Application_qiApplicationStart(JNIEnv *env, jclass, jlong pApplication)
{
  qi::ApplicationSession* app = reinterpret_cast<qi::ApplicationSession*>(pApplication);

  try
  {
    app->start();
  }
  catch (std::exception& e)
  {
    throwJavaError(env, e.what());
  }
}

void Java_com_aldebaran_qi_Application_qiApplicationRun(JNIEnv *env, jclass, jlong pApplication)
{
  qi::ApplicationSession* app = reinterpret_cast<qi::ApplicationSession*>(pApplication);

  try
  {
    app->run();
  }
  catch (std::exception& e)
  {
    throwJavaError(env, e.what());
  }
}

void Java_com_aldebaran_qi_Application_qiApplicationStop(JNIEnv *, jclass, jlong pApplication)
{
  qi::ApplicationSession* app = reinterpret_cast<qi::ApplicationSession*>(pApplication);

  app->stop();
}

void Java_com_aldebaran_qi_Application_setLogCategory(JNIEnv *env, jclass cls, jstring category, jlong verbosity)
{
  ::qi::log::addFilter(qi::jni::toString(category), (qi::LogLevel)verbosity, 0);
}
