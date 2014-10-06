//
// CVector.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_CVECTOR_HPP
#define EIGENJS_CVECTOR_HPP

#include <v8.h>
#include <node.h>
#include <nan.h>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include "base.hpp"
#include "definition.hpp"
#include "Complex.hpp"
#include "CMatrix.hpp"
#include "CVector_fwd.hpp"
#include "CVector/definitions.hpp"
#include "throw_error.hpp"

namespace EigenJS {

template <
  typename ScalarType
, typename ValueType
, const char* ClassName
>
class CVector : public base<CVector, ScalarType, ValueType, ClassName> {
 public:
  typedef base<::EigenJS::CVector, ScalarType, ValueType, ClassName> base_type;

  typedef ScalarType scalar_type;
  typedef ValueType value_type;

  typedef ::EigenJS::Complex<scalar_type> Complex;

  typedef ::EigenJS::CMatrix<scalar_type> CMatrix;
  typedef ::EigenJS::CMatrixBlock<scalar_type> CMatrixBlock;
  typedef ::EigenJS::CVectorBlock<scalar_type> CVectorBlock;
  typedef ::EigenJS::CRowVector<scalar_type> CRowVector;
  typedef ::EigenJS::CRowVectorBlock<scalar_type> CRowVectorBlock;

  typedef ::EigenJS::Matrix<scalar_type> Matrix;
  typedef ::EigenJS::MatrixBlock<scalar_type> MatrixBlock;
  typedef ::EigenJS::Vector<scalar_type> Vector;
  typedef ::EigenJS::VectorBlock<scalar_type> VectorBlock;
  typedef ::EigenJS::RowVector<scalar_type> RowVector;
  typedef ::EigenJS::RowVectorBlock<scalar_type> RowVectorBlock;

 public:
  static void Init(v8::Handle<v8::Object> exports) {
    NanScope();

    v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
    NanAssignPersistent(base_type::function_template, tpl);
    tpl->SetClassName(NanNew(ClassName));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    EIGENJS_OBJECT_INITIALIZE(CMatrix, tpl)
    EIGENJS_OBJECT_INITIALIZE(CVector, tpl)

    exports->Set(NanNew(ClassName), tpl->GetFunction());
    NanAssignPersistent(base_type::constructor, tpl->GetFunction());
  }

 private:
  explicit CVector(const typename value_type::Index& rows)
    : base_type()
      { *base_type::value_ptr_ = value_type::Zero(rows, 1); }

  ~CVector() {}

  static NAN_METHOD(New) {
    const int& args_length = args.Length();

    NanScope();

    if (args_length == 1) {
      if (!args.IsConstructCall()) {
        v8::Local<v8::Value> argv[] = { args[0] };
        NanReturnValue(
          base_type::new_instance(
            args
          , sizeof(argv) / sizeof(v8::Local<v8::Value>)
          , argv
          )
        );
      }

      if (args[0]->IsNumber()) {
        typename value_type::Index size = args[0]->Int32Value();
        if (size >= 0) {
          CVector* obj = new CVector(size);
          obj->Wrap(args.This());
          NanReturnValue(args.This());
        }
      } else if (args[0]->IsArray()) {
        const v8::Local<v8::Array>& array = args[0].As<v8::Array>();
        uint32_t len = array->Length();
        CVector* obj = new CVector(len);
        CVector::value_type& cvector = **obj;

        for (uint32_t i = 0; i < len; ++i) {
          const v8::Local<v8::Value>& elem = array->Get(i);

          if (CVector::is_scalar(elem)) {
            cvector(i, 0) = elem->NumberValue();
          } else if (Complex::is_complex(elem->ToObject())) {
            const Complex* const& rhs_obj =
                node::ObjectWrap::Unwrap<Complex>(elem->ToObject());
            const typename Complex::value_type& elem_value = **rhs_obj;
            cvector(i, 0) = elem_value;
          }
        }

        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (CMatrix::is_cmatrix(args[0])) {
        const CMatrix* const& rhs_obj =
            node::ObjectWrap::Unwrap<CMatrix>(args[0]->ToObject());
        const typename CMatrix::value_type& rhs_cmatrix = **rhs_obj;
        const typename CMatrix::value_type::Index& rows = rhs_cmatrix.rows();
        const typename CMatrix::value_type::Index& cols = rhs_cmatrix.cols();

        if (rows != 1 && cols != 1) {
          EIGENJS_THROW_ERROR_THE_MATRIX_SIZE_MUST_BE_1XN_OR_MX1()
          NanReturnUndefined();
        }

        CVector* obj = new CVector(0);

        if (rows > cols) {
          **obj = rhs_cmatrix;
        } else {
          **obj = rhs_cmatrix.transpose();
        }

        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (CVector::is_cvector(args[0])) {
        const CVector* const& rhs_obj =
            node::ObjectWrap::Unwrap<CVector>(args[0]->ToObject());
        const typename CVector::value_type& rhs_cvector = **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_cvector;
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (CRowVector::is_crowvector(args[0])) {
        const CRowVector* const& rhs_obj =
            node::ObjectWrap::Unwrap<CRowVector>(args[0]->ToObject());
        const typename CRowVector::value_type& rhs_crowvector = **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_crowvector.transpose();
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (CMatrixBlock::is_cmatrixblock(args[0])) {
        const CMatrixBlock* const& rhs_obj =
            node::ObjectWrap::Unwrap<CMatrixBlock>(args[0]->ToObject());
        const typename CMatrixBlock::value_type& rhs_cmatrixblock = **rhs_obj;
        const typename CMatrix::value_type::Index& rows =
            rhs_cmatrixblock.rows();
        const typename CMatrix::value_type::Index& cols =
            rhs_cmatrixblock.cols();

        if (rows != 1 && cols != 1) {
          EIGENJS_THROW_ERROR_THE_MATRIX_SIZE_MUST_BE_1XN_OR_MX1()
          NanReturnUndefined();
        }

        CVector* obj = new CVector(0);

        if (rows > cols) {
          **obj = rhs_cmatrixblock;
        } else {
          **obj = rhs_cmatrixblock.transpose();
        }

        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (CVectorBlock::is_cvectorblock(args[0])) {
        const CVectorBlock* const& rhs_obj =
            node::ObjectWrap::Unwrap<CVectorBlock>(args[0]->ToObject());
        const typename CVectorBlock::value_type& rhs_cvectorblock = **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_cvectorblock;
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (CRowVectorBlock::is_crowvectorblock(args[0])) {
        const CRowVectorBlock* const& rhs_obj =
            node::ObjectWrap::Unwrap<CRowVectorBlock>(args[0]->ToObject());
        const typename CRowVectorBlock::value_type& rhs_crowvectorblock =
            **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_crowvectorblock.transpose();
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (Matrix::is_matrix(args[0])) {
        const Matrix* const& rhs_obj =
            node::ObjectWrap::Unwrap<Matrix>(args[0]->ToObject());
        const typename Matrix::value_type& rhs_matrix = **rhs_obj;
        const typename Matrix::value_type::Index& rows = rhs_matrix.rows();
        const typename Matrix::value_type::Index& cols = rhs_matrix.cols();

        if (rows != 1 && cols != 1) {
          EIGENJS_THROW_ERROR_THE_MATRIX_SIZE_MUST_BE_1XN_OR_MX1()
          NanReturnUndefined();
        }

        CVector* obj = new CVector(0);

        if (rows > cols) {
          **obj = rhs_matrix.template cast<typename Complex::value_type>();
        } else {
          **obj = rhs_matrix.transpose()
              .template cast<typename Complex::value_type>();
        }

        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (Vector::is_vector(args[0])) {
        const Vector* const& rhs_obj =
            node::ObjectWrap::Unwrap<Vector>(args[0]->ToObject());
        const typename Vector::value_type& rhs_vector = **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_vector.template cast<typename Complex::value_type>();
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (RowVector::is_rowvector(args[0])) {
        const RowVector* const& rhs_obj =
            node::ObjectWrap::Unwrap<RowVector>(args[0]->ToObject());
        const typename RowVector::value_type& rhs_rowvector = **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_rowvector.transpose()
            .template cast<typename Complex::value_type>();
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (MatrixBlock::is_matrixblock(args[0])) {
        const MatrixBlock* const& rhs_obj =
            node::ObjectWrap::Unwrap<MatrixBlock>(args[0]->ToObject());
        const typename MatrixBlock::value_type& rhs_matrixblock = **rhs_obj;
        const typename MatrixBlock::value_type::Index& rows =
            rhs_matrixblock.rows();
        const typename MatrixBlock::value_type::Index& cols =
            rhs_matrixblock.cols();

        if (rows != 1 && cols != 1) {
          EIGENJS_THROW_ERROR_THE_MATRIX_SIZE_MUST_BE_1XN_OR_MX1()
          NanReturnUndefined();
        }

        CVector* obj = new CVector(0);

        if (rows > cols) {
          **obj = rhs_matrixblock
              .template cast<typename Complex::value_type>();
        } else {
          **obj = rhs_matrixblock.transpose()
              .template cast<typename Complex::value_type>();
        }

        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (VectorBlock::is_vectorblock(args[0])) {
        const VectorBlock* const& rhs_obj =
            node::ObjectWrap::Unwrap<VectorBlock>(args[0]->ToObject());
        const typename VectorBlock::value_type& rhs_vectorblock = **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_vectorblock.template cast<typename Complex::value_type>();
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      } else if (RowVectorBlock::is_rowvectorblock(args[0])) {
        const RowVectorBlock* const& rhs_obj =
            node::ObjectWrap::Unwrap<RowVectorBlock>(args[0]->ToObject());
        const typename RowVectorBlock::value_type& rhs_rowvectorblock =
            **rhs_obj;

        CVector* obj = new CVector(0);
        **obj = rhs_rowvectorblock.transpose()
            .template cast<typename Complex::value_type>();
        obj->Wrap(args.This());
        NanReturnValue(args.This());
      }
    } else if (args_length == 2) {
      if (args[0]->IsNumber() && args[1]->IsNumber()) {
        const typename value_type::Index& rows = args[0]->Int32Value();
        const typename value_type::Index& cols = args[1]->Int32Value();
        (void)cols;

        if (rows >= 0 && cols >= 0) {
          if (args.IsConstructCall()) {
            CVector* obj = new CVector(rows);
            obj->Wrap(args.This());
            NanReturnValue(args.This());
          } else {
            v8::Local<v8::Value> argv[] = { args[0], args[1] };

            NanReturnValue(
              base_type::new_instance(
                args
              , sizeof(argv) / sizeof(v8::Local<v8::Value>)
              , argv
              )
            );
          }
        }
      }
    }

    EIGENJS_THROW_ERROR_INVALID_ARGUMENT()
    NanReturnUndefined();
  }
};

}  // namespace EigenJS

#endif  // EIGENJS_CVECTOR_HPP
