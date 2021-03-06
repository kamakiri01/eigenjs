//
// RowVector/instance_method_minCoeff.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_ROWVECTOR_INSTANCE_METHOD_MINCOEFF_HPP
#define EIGENJS_ROWVECTOR_INSTANCE_METHOD_MINCOEFF_HPP

namespace EigenJS {

EIGENJS_INSTANCE_METHOD(RowVector, minCoeff,
{
  NanScope();

  const T* const& obj = node::ObjectWrap::Unwrap<T>(args.This());
  const typename T::value_type& value = **obj;

  if (args.Length() == 1) {
    typename T::scalar_type min = typename T::scalar_type();
    typename T::value_type::Index rowId = typename T::value_type::Index();
    typename T::value_type::Index colId = typename T::value_type::Index();

    if (args[0]->IsFunction()) {
      // workaround for RowVectorBlock
      min = RowVectorBlock::is_rowvectorblock(args.This())
          ? typename RowVector::value_type(value).minCoeff(&colId)
          : value.minCoeff(&colId);

      v8::Local<v8::Value> argv[] = {
        NanNew<v8::Integer>(rowId)
      , NanNew<v8::Integer>(colId)
      };

      NanMakeCallback(
          args.This()
        , args[0].As<v8::Function>()
        , sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
        );

      NanReturnValue(NanNew<v8::Number>(min));
    } else if (args[0]->IsObject()) {
      v8::Local<v8::Object> result = args[0]->ToObject();

      // workaround for RowVectorBlock
      min = RowVectorBlock::is_rowvectorblock(args.This())
          ? typename RowVector::value_type(value).minCoeff(&colId)
          : value.minCoeff(&colId);

      const v8::Local<v8::Number>& result_min = NanNew<v8::Number>(min);

      result->Set(NanNew("minCoeff"), result_min);
      result->Set(NanNew("rowId"), NanNew<v8::Integer>(rowId));
      result->Set(NanNew("colId"), NanNew<v8::Integer>(colId));

      NanReturnValue(result_min);
    }
  }

  NanReturnValue(NanNew<v8::Number>(value.minCoeff()));
})

}  // namespace EigenJS

#endif  // EIGENJS_ROWVECTOR_INSTANCE_METHOD_MINCOEFF_HPP
