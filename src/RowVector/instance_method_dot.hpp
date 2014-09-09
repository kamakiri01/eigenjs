//
// RowVector/instance_method_dot.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_ROWVECTOR_INSTANCE_METHOD_DOT_HPP
#define EIGENJS_ROWVECTOR_INSTANCE_METHOD_DOT_HPP

namespace EigenJS {

EIGENJS_INSTANCE_METHOD(RowVector, dot,
{
  NanScope();

  if (args.Length() == 1) {
    const T* const& obj = node::ObjectWrap::Unwrap<T>(args.This());
    const typename T::value_type& value = **obj;
    const typename T::value_type::Index& n = value.cols();

    if (Vector::is_vector(args[0])) {
      const Vector* const& rhs_obj =
          node::ObjectWrap::Unwrap<Vector>(args[0]->ToObject());
      const typename Vector::value_type& rhs_vector = **rhs_obj;
      const typename Vector::value_type::Index& m = rhs_vector.rows();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      NanReturnValue(NanNew(value.dot(rhs_vector.transpose())));
    } else if (RowVector::is_rowvector(args[0])) {
      const RowVector* const& rhs_obj =
          node::ObjectWrap::Unwrap<RowVector>(args[0]->ToObject());
      const typename RowVector::value_type& rhs_rowvector = **rhs_obj;
      const typename RowVector::value_type::Index& m = rhs_rowvector.cols();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      NanReturnValue(NanNew(value.dot(rhs_rowvector)));
    } else if (VectorBlock::is_vectorblock(args[0])) {
      const VectorBlock* const& rhs_obj =
          node::ObjectWrap::Unwrap<VectorBlock>(args[0]->ToObject());
      const typename VectorBlock::value_type& rhs_vectorblock = **rhs_obj;
      const typename VectorBlock::value_type::Index& m =
          rhs_vectorblock.rows();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      NanReturnValue(NanNew(value.dot(rhs_vectorblock.transpose())));
    } else if (RowVectorBlock::is_rowvectorblock(args[0])) {
      const RowVectorBlock* const& rhs_obj =
          node::ObjectWrap::Unwrap<RowVectorBlock>(args[0]->ToObject());
      const typename RowVectorBlock::value_type& rhs_rowvectorblock =
          **rhs_obj;
      const typename RowVectorBlock::value_type::Index& m =
          rhs_rowvectorblock.cols();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      NanReturnValue(NanNew(value.dot(rhs_rowvectorblock)));
    } else if (CVector::is_cvector(args[0])) {
      const CVector* const& rhs_obj =
          node::ObjectWrap::Unwrap<CVector>(args[0]->ToObject());
      const typename CVector::value_type& rhs_cvector = **rhs_obj;
      const typename CVector::value_type::Index& m = rhs_cvector.rows();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      const typename Complex::value_type&& result =
          value.dot(rhs_cvector.transpose());

      v8::Local<v8::Value> argv[] = {
        NanNew<v8::Number>(result.real())
      , NanNew<v8::Number>(result.imag())
      };

      NanReturnValue(
        Complex::new_instance(
          args
        , sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
        )
      );
    } else if (CRowVector::is_crowvector(args[0])) {
      const CRowVector* const& rhs_obj =
          node::ObjectWrap::Unwrap<CRowVector>(args[0]->ToObject());
      const typename CRowVector::value_type& rhs_crowvector = **rhs_obj;
      const typename CRowVector::value_type::Index& m = rhs_crowvector.cols();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      const typename Complex::value_type& result = value.dot(rhs_crowvector);

      v8::Local<v8::Value> argv[] = {
        NanNew<v8::Number>(result.real())
      , NanNew<v8::Number>(result.imag())
      };

      NanReturnValue(
        Complex::new_instance(
          args
        , sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
        )
      );
    } else if (CVectorBlock::is_cvectorblock(args[0])) {
      const CVectorBlock* const& rhs_obj =
          node::ObjectWrap::Unwrap<CVectorBlock>(args[0]->ToObject());
      const typename CVectorBlock::value_type& rhs_cvectorblock = **rhs_obj;
      const typename CVectorBlock::value_type::Index& m =
          rhs_cvectorblock.rows();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      const typename Complex::value_type&& result =
          value.dot(rhs_cvectorblock.transpose());

      v8::Local<v8::Value> argv[] = {
        NanNew<v8::Number>(result.real())
      , NanNew<v8::Number>(result.imag())
      };

      NanReturnValue(
        Complex::new_instance(
          args
        , sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
        )
      );
    } else if (CRowVectorBlock::is_crowvectorblock(args[0])) {
      const CRowVectorBlock* const& rhs_obj =
          node::ObjectWrap::Unwrap<CRowVectorBlock>(args[0]->ToObject());
      const typename CRowVectorBlock::value_type& rhs_crowvectorblock =
          **rhs_obj;
      const typename CRowVectorBlock::value_type::Index& m =
          rhs_crowvectorblock.cols();

      if (n != m) {
        EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
        NanReturnUndefined();
      }

      const typename Complex::value_type&& result =
          value.dot(rhs_crowvectorblock);

      v8::Local<v8::Value> argv[] = {
        NanNew<v8::Number>(result.real())
      , NanNew<v8::Number>(result.imag())
      };

      NanReturnValue(
        Complex::new_instance(
          args
        , sizeof(argv) / sizeof(v8::Local<v8::Value>)
        , argv
        )
      );
    }
  }

  EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
  NanReturnUndefined();
})

}  // namespace EigenJS

#endif  // EIGENJS_ROWVECTOR_INSTANCE_METHOD_DOT_HPP
