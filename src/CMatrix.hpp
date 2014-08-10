//
// CMatirx.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_CMATRIX_HPP
#define EIGENJS_CMATRIX_HPP

#include <v8.h>
#include <node.h>
#include <nan.h>

#include <eigen3/Eigen/Dense>

#include "base.hpp"
#include "definition.hpp"
#include "Complex.hpp"
#include "Matrix.hpp"
#include "CMatrix/definitions.hpp"

namespace EigenJS {

template <typename ValueType, const char* ClassName>
class CMatrix : public base<CMatrix, ValueType, ClassName> {
 public:
  typedef base<::EigenJS::CMatrix, ValueType, ClassName> base_type;

  typedef typename base_type::element_type element_type;
  typedef typename base_type::complex_type complex_type;
  typedef typename base_type::matrix_type matrix_type;
  typedef typename base_type::cmatrix_type cmatrix_type;

  typedef typename base_type::Complex Complex;
  typedef typename base_type::Matrix Matrix;

 public:
  static void Init(v8::Handle<v8::Object> exports) {
    NanScope();

    v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
    NanAssignPersistent(base_type::function_template, tpl);
    tpl->SetClassName(NanNew(ClassName));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    EIGENJS_OBJECT_INITIALIZE(CMatrix, tpl)

    exports->Set(NanNew(ClassName), tpl->GetFunction());

    NanAssignPersistent(base_type::constructor, tpl->GetFunction());
  }

 public:
  NAN_INLINE cmatrix_type& operator*() {
    return cmatrix_;
  }

  NAN_INLINE const cmatrix_type& operator*() const {
    return cmatrix_;
  }

  NAN_INLINE cmatrix_type* operator->() {
    return &cmatrix_;
  }

  NAN_INLINE const cmatrix_type* operator->() const {
    return &cmatrix_;
  }

 private:
  CMatrix(
    const typename cmatrix_type::Index& rows
  , const typename cmatrix_type::Index& cols
  ) : cmatrix_(cmatrix_type::Zero(rows, cols))
  {}

  ~CMatrix() {}

  static NAN_METHOD(New) {
    NanScope();

    if (args.Length() < 2) {
      NanThrowError(
          "Tried creating complex matrix without rows and columns arguments");
      NanReturnUndefined();
    }

    if (args.IsConstructCall()) {
      typename cmatrix_type::Index rows = args[0]->Uint32Value();
      typename cmatrix_type::Index columns = args[1]->Uint32Value();
      CMatrix* obj = new CMatrix(rows, columns);
      obj->Wrap(args.This());
      NanReturnValue(args.This());
    } else {
      v8::Local<v8::Function> ctor = NanNew(base_type::constructor);
      v8::Local<v8::Value> argv[] = {args[0], args[1]};
      NanReturnValue(
        ctor->NewInstance(
          sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
        )
      );
    }
  }

 private:
  cmatrix_type cmatrix_;
};

}  // namespace EigenJS

#endif  // EIGENJS_CMATRIX_HPP