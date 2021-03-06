//
// CMatrix/instance_method_setDiagonal.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_CMATRIX_INSTANCE_METHOD_SETDIAGONAL_HPP
#define EIGENJS_CMATRIX_INSTANCE_METHOD_SETDIAGONAL_HPP

#include "../common_macro.hpp"

namespace EigenJS {

EIGENJS_INSTANCE_METHOD(CMatrix, setDiagonal,
{
  NanScope();

  if (args.Length() == 2 && args[0]->IsNumber()) {
    T* obj = node::ObjectWrap::Unwrap<T>(args.This());
    typename T::value_type& value = **obj;
    typename T::value_type::Index index = args[0]->Int32Value();

    if (index <= -value.rows() || index >= value.cols()) {
      EIGENJS_THROW_ERROR_INVALID_INDEX_ARGUMENT()
      NanReturnUndefined();
    }

    auto diagonal = value.diagonal(index);

    if (CVector::is_cvector(args[1])) {
      const CVector* const& obj =
          node::ObjectWrap::Unwrap<CVector>(args[1]->ToObject());
      const typename CVector::value_type& rhs_cvector = **obj;

      if (rhs_cvector.rows() != diagonal.rows()) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      diagonal = rhs_cvector;

      NanReturnValue(args.This());
    } else if (CRowVector::is_crowvector(args[1])) {
      const CRowVector* const& obj =
          node::ObjectWrap::Unwrap<CRowVector>(args[1]->ToObject());
      const typename CRowVector::value_type& rhs_crowvector = **obj;

      if (rhs_crowvector.cols() != diagonal.rows()) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      diagonal = rhs_crowvector;

      NanReturnValue(args.This());
    } else if (Vector::is_vector(args[1])) {
      const Vector* const& obj =
          node::ObjectWrap::Unwrap<Vector>(args[1]->ToObject());
      const typename Vector::value_type& rhs_vector = **obj;

      if (rhs_vector.rows() != diagonal.rows()) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      diagonal = rhs_vector.template cast<typename Complex::value_type>();

      NanReturnValue(args.This());
    } else if (RowVector::is_rowvector(args[1])) {
      const RowVector* const& obj =
          node::ObjectWrap::Unwrap<RowVector>(args[1]->ToObject());
      const typename RowVector::value_type& rhs_rowvector = **obj;

      if (rhs_rowvector.cols() != diagonal.rows()) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      diagonal = rhs_rowvector.template cast<typename Complex::value_type>();

      NanReturnValue(args.This());
    }
  }

  EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
  NanReturnUndefined();
})

}  // namespace EigenJS

#endif  // EIGENJS_CMATRIX_INSTANCE_METHOD_SETDIAGONAL_HPP
