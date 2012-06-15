
/*
*  AUTOGENERATED CODE, DO NOT EDIT
*
*  Author(s):
*  - Cedric GESTES <gestes@aldebaran-robotics.com>
*  - Chris  Kilner <ckilner@aldebaran-robotics.com>
*
*  Copyright (C) 2010, 2011, 2012 Aldebaran Robotics
*/

#pragma once
#ifndef _QIMESSAGING_DETAILS_CALLFUNCTOR_HPP_
#define _QIMESSAGING_DETAILS_CALLFUNCTOR_HPP_

#include <qimessaging/functor.hpp>
#include <qimessaging/buffer.hpp>

namespace qi
{

  template <typename R>
  qi::Future<R> callFunctor(Functor *f) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1, typename P2>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1, const P2 &p2) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    dsi << p2;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1, typename P2, typename P3>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1, const P2 &p2, const P3 &p3) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    dsi << p2;
    dsi << p3;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    dsi << p2;
    dsi << p3;
    dsi << p4;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    dsi << p2;
    dsi << p3;
    dsi << p4;
    dsi << p5;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    dsi << p2;
    dsi << p3;
    dsi << p4;
    dsi << p5;
    dsi << p6;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6, const P7 &p7) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    dsi << p2;
    dsi << p3;
    dsi << p4;
    dsi << p5;
    dsi << p6;
    dsi << p7;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }


  template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
  qi::Future<R> callFunctor(Functor *f, const P0 &p0, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6, const P7 &p7, const P8 &p8) {
    qi::Buffer            argsBuf;
    qi::DataStream        dsi(argsBuf);
    qi::FunctorParameters args(argsBuf);
    qi::FunctorResult     ret;
    qi::Future<R>         future;

    qi::makeFunctorResult<R>(&ret, &future);
    dsi << p0;
    dsi << p1;
    dsi << p2;
    dsi << p3;
    dsi << p4;
    dsi << p5;
    dsi << p6;
    dsi << p7;
    dsi << p8;
    if (qi::detail::sanityCheckAndReport(dsi, ret))
      f->call(args, ret);
    return future;
  }

}
#endif  // _QIMESSAGING_DETAILS_CALLFUNCTOR_HPP_
