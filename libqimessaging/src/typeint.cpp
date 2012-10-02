#include <qimessaging/typespecialized.hpp>
#include <qimessaging/genericvaluespecialized.hpp>

namespace qi {

template<typename T> class TypeIntImpl:
  public TypeInt
{
public:
  typedef typename detail::TypeImplMethodsBySize<T, detail::TypeAutoClone, TypeDefaultSerialize>::type
   ImplType;
  virtual int64_t get(void* value) const
  {
    return *(T*)ImplType::Access::ptrFromStorage(&value);
  }
  virtual void set(void** storage, int64_t value)
  {
    *(T*)ImplType::Access::ptrFromStorage(storage) = (T)value;
  }
  _QI_BOUNCE_TYPE_METHODS(ImplType);
};


#define INTEGRAL_TYPE(t) \
static bool BOOST_PP_CAT(unused_ , __LINE__) = registerType(typeid(t), new TypeIntImpl<t>());

/** Integral types.
 * Since long is neither int32 nor uint32 on 32 bit platforms,
 * use all known native types instead of size/signedness explicit
 * types.
 */
INTEGRAL_TYPE(bool);
INTEGRAL_TYPE(char);
INTEGRAL_TYPE(signed char);
INTEGRAL_TYPE(unsigned char);
INTEGRAL_TYPE(short);
INTEGRAL_TYPE(unsigned short);
INTEGRAL_TYPE(int);
INTEGRAL_TYPE(unsigned int);
INTEGRAL_TYPE(long);
INTEGRAL_TYPE(unsigned long);
INTEGRAL_TYPE(long long);
INTEGRAL_TYPE(unsigned long long);

}

QI_REGISTER_MAPPING("i", qi::int32_t);
QI_REGISTER_MAPPING("I", qi::uint32_t);


namespace qi {


template<typename T> class TypeFloatImpl: public TypeFloat
{
public:
  typedef typename detail::TypeImplMethodsBySize<T, detail::TypeAutoClone, TypeDefaultSerialize>::type
  ImplType;
  virtual double get(void* value) const
  {
    return *(T*)ImplType::Access::ptrFromStorage(&value);
  }
  virtual void set(void** storage, double value)
  {
    *(T*)ImplType::Access::ptrFromStorage(storage) = (T)value;
  }
  _QI_BOUNCE_TYPE_METHODS(ImplType);
};

#define FLOAT_TYPE(t) \
static bool BOOST_PP_CAT(unused_ , __LINE__) = registerType(typeid(t), new TypeFloatImpl<t>());

FLOAT_TYPE(float);
FLOAT_TYPE(double);
}

QI_REGISTER_MAPPING("d", double);
QI_REGISTER_MAPPING("f", float);
