//
// CMatrix/instance_method_get.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_CMATRIX_INSTANCE_METHOD_GET_HPP
#define EIGENJS_CMATRIX_INSTANCE_METHOD_GET_HPP

namespace EigenJS {

EIGENJS_INSTANCE_METHOD(CMatrix, get,
{
  typedef typename CMatrix::Complex Complex;

  NanScope();

  if (args.Length() == 2 &&
      args[0]->IsNumber() &&
      args[1]->IsNumber()
  ) {
    const CMatrix* const& obj = node::ObjectWrap::Unwrap<CMatrix>(args.This());
    const typename CMatrix::cmatrix_type& cmatrix = **obj;
    const typename CMatrix::cmatrix_type::Index& row = args[0]->Uint32Value();
    const typename CMatrix::cmatrix_type::Index& col = args[1]->Uint32Value();

    if (CMatrix::is_out_of_range(cmatrix, row, col))
      NanReturnUndefined();

    const typename CMatrix::complex_type& c = cmatrix(row, col);

    v8::Local<v8::Value> argv[] = {
      NanNew<v8::Number>(c.real())
    , NanNew<v8::Number>(c.imag())
    };

    NanReturnValue(
      Complex::new_instance(
        args
      , sizeof( argv ) / sizeof( v8::Local<v8::Value> )
      , argv
      )
    );
  }

  NanReturnUndefined();
})

}  // namespace EigenJS

#endif  // EIGENJS_CMATRIX_INSTANCE_METHOD_GET_HPP