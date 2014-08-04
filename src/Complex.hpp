//
// EigenJS.cpp
// ~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_COMPLEX_HPP
#define EIGENJS_COMPLEX_HPP

#include <node.h>
#include <v8.h>

#include <nan.h>

#include <eigen3/Eigen/src/Core/NumTraits.h>

#include <algorithm>
#include <complex>
#include <sstream>

#include "base.hpp"

#define EIGENJS_COMPLEX_CLASS_METHOD( NAME )                                 \
static NAN_METHOD( NAME ) {                                                  \
  complex_type c;                                                            \
  NanScope();                                                                \
                                                                             \
  if ( args.Length() == 1 ) {                                                \
    if( is_complex( args[0] ) ) {                                            \
      new (&c) complex_type(                                                 \
          node::ObjectWrap::Unwrap<Complex>(                                 \
              args[0]->ToObject()                                            \
          )->complex_                                                        \
      );                                                                     \
    } else if ( base_type::is_scalar( args[0] ) ) {                          \
      new (&c) complex_type(args[0]->NumberValue(), 0);                      \
    }                                                                        \
                                                                             \
    const complex_type& NAME = std::NAME( c );                               \
    const element_type& real = NAME.real();                                  \
    const element_type& imag = NAME.imag();                                  \
                                                                             \
    v8::Local<v8::Function> ctor = NanNew( base_type::constructor );         \
    v8::Local<v8::Value> argv[] = {                                          \
        NanNew<v8::Number>( real )                                           \
      , NanNew<v8::Number>( imag )                                           \
    };                                                                       \
                                                                             \
    v8::Local<v8::Object> new_complex = ctor->NewInstance(                   \
        sizeof( argv ) / sizeof( v8::Local<v8::Value> )                      \
      , argv                                                                 \
    );                                                                       \
                                                                             \
    NanReturnValue( new_complex );                                           \
  }                                                                          \
                                                                             \
  NanReturnUndefined();                                                      \
}                                                                            \
/**/

#define EIGENJS_COMPLEX_BINARY_OPERATOR( NAME, OP )                          \
static NAN_METHOD( NAME ) {                                                  \
  complex_type c;                                                            \
  NanScope();                                                                \
                                                                             \
  if ( args.Length() == 1 ) {                                                \
    if( is_complex( args[0] ) ) {                                            \
      new (&c) complex_type(                                                 \
          node::ObjectWrap::Unwrap<Complex>(                                 \
              args[0]->ToObject()                                            \
          )->complex_                                                        \
      );                                                                     \
    } else if ( base_type::is_scalar( args[0] ) ) {                          \
      new (&c) complex_type(args[0]->NumberValue(), 0);                      \
    }                                                                        \
                                                                             \
    const Complex* obj = node::ObjectWrap::Unwrap<Complex>( args.This() );   \
                                                                             \
    c = obj->complex_ OP c;                                                  \
                                                                             \
    v8::Local<v8::Function> ctor = NanNew( base_type::constructor );         \
    v8::Local<v8::Value> argv[] = {                                          \
        NanNew<v8::Number>( c.real() )                                       \
      , NanNew<v8::Number>( c.imag() )                                       \
    };                                                                       \
                                                                             \
    v8::Local<v8::Object> new_complex = ctor->NewInstance(                   \
        sizeof( argv ) / sizeof( v8::Local<v8::Value> )                      \
      , argv                                                                 \
    );                                                                       \
                                                                             \
    NanReturnValue( new_complex );                                           \
  }                                                                          \
                                                                             \
  NanReturnUndefined();                                                      \
}                                                                            \
/**/

#define EIGENJS_COMPLEX_BINARY_OPERATOR_COMMUTATIVE( NAME, OP )              \
static NAN_METHOD( NAME ) {                                                  \
  complex_type c;                                                            \
  NanScope();                                                                \
                                                                             \
  if ( args.Length() == 1 ) {                                                \
    if( is_complex( args[0] ) ) {                                            \
      new (&c) complex_type(                                                 \
          node::ObjectWrap::Unwrap<Complex>(                                 \
              args[0]->ToObject()                                            \
          )->complex_                                                        \
      );                                                                     \
    } else if ( base_type::is_scalar( args[0] ) ) {                          \
      new (&c) complex_type(args[0]->NumberValue(), 0);                      \
    }                                                                        \
                                                                             \
    Complex* obj = node::ObjectWrap::Unwrap<Complex>( args.This() );         \
                                                                             \
    obj->complex_ OP##= c;                                                   \
                                                                             \
    NanReturnValue( args.This() );                                           \
  }                                                                          \
                                                                             \
  NanReturnUndefined();                                                      \
}                                                                            \
/**/

namespace EigenJS {

template <typename ValueType, const char* ClassName>
class Complex : public node::ObjectWrap, base<Complex, ValueType, ClassName> {
  typedef base<::EigenJS::Complex, ValueType, ClassName> base_type;
  typedef typename base_type::element_type element_type;
  typedef typename base_type::complex_type complex_type;

 public:
  static void Init(v8::Handle<v8::Object> exports) {
    NanScope();

    v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
    tpl->SetClassName(NanNew(ClassName));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "abs", abs);
    NODE_SET_PROTOTYPE_METHOD(tpl, "arg", arg);
    NODE_SET_PROTOTYPE_METHOD(tpl, "norm", norm);
    NODE_SET_PROTOTYPE_METHOD(tpl, "conj", conj);
    NODE_SET_PROTOTYPE_METHOD(tpl, "add", add);
    NODE_SET_PROTOTYPE_METHOD(tpl, "adda", adda);
    NODE_SET_PROTOTYPE_METHOD(tpl, "sub", sub);
    NODE_SET_PROTOTYPE_METHOD(tpl, "suba", suba);
    NODE_SET_PROTOTYPE_METHOD(tpl, "mul", mul);
    NODE_SET_PROTOTYPE_METHOD(tpl, "mula", mula);
    NODE_SET_PROTOTYPE_METHOD(tpl, "div", div);
    NODE_SET_PROTOTYPE_METHOD(tpl, "diva", diva);

    NODE_SET_METHOD(tpl, "polar", polar);
    NODE_SET_METHOD(tpl, "proj", proj);

    NODE_SET_METHOD(tpl, "cos", cos);
    NODE_SET_METHOD(tpl, "cosh", cosh);
    NODE_SET_METHOD(tpl, "exp", exp);
    NODE_SET_METHOD(tpl, "log", log);
    NODE_SET_METHOD(tpl, "log10", log10);
    NODE_SET_METHOD(tpl, "pow", pow);
    NODE_SET_METHOD(tpl, "sin", sin);
    NODE_SET_METHOD(tpl, "sinh", sinh);
    NODE_SET_METHOD(tpl, "sqrt", sqrt);
    NODE_SET_METHOD(tpl, "tan", tan);
    NODE_SET_METHOD(tpl, "tanh", tanh);
    NODE_SET_METHOD(tpl, "acos", acos);
    NODE_SET_METHOD(tpl, "acosh", acosh);
    NODE_SET_METHOD(tpl, "asin", asin);
    NODE_SET_METHOD(tpl, "asinh", asinh);
    NODE_SET_METHOD(tpl, "atan", atan);
    NODE_SET_METHOD(tpl, "atanh", atanh);

    NODE_SET_PROTOTYPE_METHOD(tpl, "equals", equals);
    NODE_SET_PROTOTYPE_METHOD(tpl, "isApprox", isApprox);
    NODE_SET_PROTOTYPE_METHOD(tpl, "toString", toString);

    v8::Local<v8::ObjectTemplate> proto = tpl->PrototypeTemplate();
    proto->SetAccessor(NanNew("real"), get_real, set_real);
    proto->SetAccessor(NanNew("imag"), get_imag, set_imag);

    NanAssignPersistent(base_type::constructor, tpl->GetFunction());
    exports->Set(NanNew(ClassName), tpl->GetFunction());

    NanAssignPersistent(base_type::function_template, tpl);
  }

  static NAN_METHOD(abs) {
    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
    NanScope();

    NanReturnValue(NanNew(std::abs(obj->complex_)));
  }

  static NAN_METHOD(arg) {
    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
    NanScope();

    NanReturnValue(NanNew(std::arg(obj->complex_)));
  }

  static NAN_METHOD(norm) {
    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
    NanScope();

    NanReturnValue(NanNew(std::norm(obj->complex_)));
  }

  static NAN_METHOD(conj) {
    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
    const complex_type& c = std::conj(obj->complex_);
    const element_type& real = c.real();
    const element_type& imag = c.imag();
    NanScope();

    v8::Local<v8::Function> ctor = NanNew(base_type::constructor);
    v8::Local<v8::Value> argv[] = {
        NanNew<v8::Number>(real)
      , NanNew<v8::Number>(imag)
    };

    v8::Local<v8::Object> new_complex = ctor->NewInstance(
        sizeof(argv) / sizeof(v8::Local<v8::Value>)
      , argv
    );

    NanReturnValue(new_complex);
  }

  static NAN_METHOD(polar) {
    NanScope();

    if (args.Length() == 2 &&
        args[0]->IsNumber() &&
        args[1]->IsNumber()) {
      const element_type& rho = args[0]->NumberValue();
      const element_type& theta = args[1]->NumberValue();

      v8::Local<v8::Function> ctor = NanNew(base_type::constructor);
      v8::Local<v8::Value> argv[] = {
          NanNew<v8::Number>(rho)
        , NanNew<v8::Number>(theta)
      };

      v8::Local<v8::Object> new_complex = ctor->NewInstance(
          sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
      );

      NanReturnValue(new_complex);
    }

    NanReturnUndefined();
  }

  EIGENJS_COMPLEX_BINARY_OPERATOR(add, +)
  EIGENJS_COMPLEX_BINARY_OPERATOR_COMMUTATIVE(adda, +)
  EIGENJS_COMPLEX_BINARY_OPERATOR(sub, -)
  EIGENJS_COMPLEX_BINARY_OPERATOR_COMMUTATIVE(suba, -)
  EIGENJS_COMPLEX_BINARY_OPERATOR(mul, *)
  EIGENJS_COMPLEX_BINARY_OPERATOR_COMMUTATIVE(mula, *)
  EIGENJS_COMPLEX_BINARY_OPERATOR(div, /)
  EIGENJS_COMPLEX_BINARY_OPERATOR_COMMUTATIVE(diva, /)

  EIGENJS_COMPLEX_CLASS_METHOD(proj)
  EIGENJS_COMPLEX_CLASS_METHOD(cos)
  EIGENJS_COMPLEX_CLASS_METHOD(cosh)
  EIGENJS_COMPLEX_CLASS_METHOD(exp)
  EIGENJS_COMPLEX_CLASS_METHOD(log)
  EIGENJS_COMPLEX_CLASS_METHOD(log10)
  EIGENJS_COMPLEX_CLASS_METHOD(sin)
  EIGENJS_COMPLEX_CLASS_METHOD(sinh)
  EIGENJS_COMPLEX_CLASS_METHOD(sqrt)
  EIGENJS_COMPLEX_CLASS_METHOD(tan)
  EIGENJS_COMPLEX_CLASS_METHOD(tanh)
  EIGENJS_COMPLEX_CLASS_METHOD(acos)
  EIGENJS_COMPLEX_CLASS_METHOD(acosh)
  EIGENJS_COMPLEX_CLASS_METHOD(asin)
  EIGENJS_COMPLEX_CLASS_METHOD(asinh)
  EIGENJS_COMPLEX_CLASS_METHOD(atan)
  EIGENJS_COMPLEX_CLASS_METHOD(atanh)

  static NAN_METHOD(pow) {
    NanScope();

    if (args.Length() == 2 &&
        is_complex_or_saclar(args[0]) &&
        is_complex_or_saclar(args[1])) {
      const bool& arg0_is_complex = is_complex(args[0]);
      const bool& arg1_is_complex = is_complex(args[1]);
      const bool& arg0_is_scalar = base_type::is_scalar(args[0]);
      const bool& arg1_is_scalar = base_type::is_scalar(args[1]);
      complex_type c;

      if (arg0_is_complex && arg1_is_complex) {
        const Complex* obj0 =
            node::ObjectWrap::Unwrap<Complex>(args[0]->ToObject());
        const Complex* obj1 =
            node::ObjectWrap::Unwrap<Complex>(args[1]->ToObject());
        c = std::pow(obj0->complex_, obj1->complex_);
      } else if (arg0_is_complex && arg1_is_scalar) {
        const Complex* obj0 =
            node::ObjectWrap::Unwrap<Complex>(args[0]->ToObject());
        const element_type& scalar1 = args[1]->NumberValue();
        c = std::pow(obj0->complex_, scalar1);
      } else if (arg0_is_scalar && arg1_is_complex) {
        const element_type& scalar0 = args[0]->NumberValue();
        const Complex* obj1 =
            node::ObjectWrap::Unwrap<Complex>(args[1]->ToObject());
        c = std::pow(scalar0, obj1->complex_);
      } else if (arg0_is_scalar && arg1_is_scalar) {
        const element_type& scalar0 = args[0]->NumberValue();
        const element_type& scalar1 = args[1]->NumberValue();
        c = std::pow(scalar0, scalar1);
      }

      v8::Local<v8::Function> ctor = NanNew(base_type::constructor);
      v8::Local<v8::Value> argv[] = {
          NanNew<v8::Number>(c.real())
        , NanNew<v8::Number>(c.imag())
      };

      v8::Local<v8::Object> new_complex = ctor->NewInstance(
          sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
      );

      NanReturnValue(new_complex);
    }

    NanReturnUndefined();
  }

  static NAN_METHOD(equals) {
    NanScope();

    if (args.Length() == 1 && is_complex(args[0])) {
      const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
      const Complex* rhs_obj =
          node::ObjectWrap::Unwrap<Complex>(args[0]->ToObject());
      NanReturnValue(NanNew<v8::Boolean>(obj->complex_ == rhs_obj->complex_));
    }

    NanReturnUndefined();
  }

  static NAN_METHOD(isApprox) {
    const int& args_length = args.Length();
    NanScope();

    if (args_length == 0 || args_length > 2)
      NanReturnUndefined();

    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
    const Complex* rhs_obj =
        node::ObjectWrap::Unwrap<Complex>(args[0]->ToObject());
    const complex_type& v = obj->complex_;
    const complex_type& w = rhs_obj->complex_;

    typedef Eigen::NumTraits<complex_type> num_traits;
    const typename num_traits::Real& prec =
        args_length == 2
      ? args[1]->NumberValue()
      : num_traits::dummy_precision();

    NanReturnValue(
      NanNew(
        std::norm(v - w) <= prec * prec *
            (std::min)(std::norm(v), std::norm(w))
      )
    );
  }

  static NAN_METHOD(toString) {
    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
    NanScope();

    std::ostringstream result;
    result << obj->complex_;

    NanReturnValue(NanNew(result.str().c_str()));

    NanReturnUndefined();
  }

  static NAN_GETTER(get_real) {
    NanScope();

    if (!NanGetInternalFieldPointer(args.This(), 0))
      NanReturnValue(args.This());

    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());

    NanReturnValue(NanNew(obj->complex_.real()));
  }

  static NAN_SETTER(set_real) {
    if (value->IsNumber()) {
      Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
      obj->complex_ = complex_type(
          value->NumberValue()
        , obj->complex_.imag()
      );
    }
  }

  static NAN_GETTER(get_imag) {
    NanScope();

    if (!NanGetInternalFieldPointer(args.This(), 0))
      NanReturnValue(args.This());

    const Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());

    NanReturnValue(NanNew(obj->complex_.imag()));
  }

  static NAN_SETTER(set_imag) {
    if (value->IsNumber()) {
      Complex* obj = node::ObjectWrap::Unwrap<Complex>(args.This());
      obj->complex_ = complex_type(
          obj->complex_.real()
        , value->NumberValue()
      );
    }
  }

 private:
  Complex(const element_type& real, const element_type& imag)
    : complex_(real, imag)
  {}
  ~Complex() {}

  static NAN_METHOD(New) {
    NanScope();

    if (args.Length() < 2) {
      NanThrowError("Tried creating complex without real and imag arguments");
      NanReturnUndefined();
    }

    if (args.IsConstructCall()) {
      const element_type& real = args[0]->NumberValue();
      const element_type& imag = args[1]->NumberValue();
      Complex* obj = new Complex(real, imag);
      obj->Wrap(args.This());
      NanReturnValue(args.This());
    } else {
      v8::Local<v8::Function> ctr = NanNew(base_type::constructor);
      v8::Local<v8::Value> argv[] = {args[0], args[1]};
      NanReturnValue(
        ctr->NewInstance(
            sizeof(argv) / sizeof(v8::Local<v8::Value>)
          , argv
        )
      );
    }
  }

 public:
  static inline bool is_complex(const v8::Handle<v8::Value>& arg) {
    return base_type::HasInstance(arg) ? true : false;
  }

  static inline bool is_complex_or_saclar(const v8::Handle<v8::Value>& arg) {
    return base_type::HasInstance(arg) || arg->IsNumber()
      ? true : false;
  }

 private:
  complex_type complex_;
};

}  // namespace EigenJS

#undef EIGENJS_COMPLEX_CLASS_METHOD

#endif  // EIGENJS_COMPLEX_HPP