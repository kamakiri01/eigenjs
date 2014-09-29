//
// CFullPivLU/instance_method_permutationP.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_CFULLPIVLU_INSTANCE_METHOD_PERMUTATIONP_HPP
#define EIGENJS_CFULLPIVLU_INSTANCE_METHOD_PERMUTATIONP_HPP

namespace EigenJS {

EIGENJS_INSTANCE_METHOD(CFullPivLU, permutationP,
{
  const T* const& obj = node::ObjectWrap::Unwrap<T>(args.This());
  const typename T::value_type& value = **obj;

  NanScope();

  v8::Local<v8::Value> argv[] = {
    NanNew<v8::Integer>(0)  /* rows */
  , NanNew<v8::Integer>(0)  /* cols */
  };

  v8::Local<v8::Object> instance = CMatrix::new_instance(
    args
  , sizeof(argv) / sizeof(v8::Local<v8::Value>)
  , argv
  );

  CMatrix* new_obj = node::ObjectWrap::Unwrap<CMatrix>(instance);
  typename CMatrix::value_type& new_cmatrix = **new_obj;

  new_cmatrix = value.permutationP().toDenseMatrix().template
      cast<typename Complex::value_type>();

  NanReturnValue(instance);
})

}  // namespace EigenJS

#endif  // EIGENJS_CFULLPIVLU_INSTANCE_METHOD_PERMUTATIONP_HPP