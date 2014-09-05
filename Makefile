TOPLEVEL ?= $(dir $(lastword $(MAKEFILE_LIST)))
CPPLINT ?= $(TOPLEVEL)/cpplint.py
PYTHON ?= python

SOURCES = \
    src/CMatrix.hpp \
    src/CMatrix/class_method_Constant.hpp \
    src/CMatrix/class_method_Identity.hpp \
    src/CMatrix/class_method_Ones.hpp \
    src/CMatrix/class_method_Random.hpp \
    src/CMatrix/class_method_Zero.hpp \
    src/CMatrix/definitions.hpp \
    src/CMatrix/instance_method_add.hpp \
    src/CMatrix/instance_method_adda.hpp \
    src/CMatrix/instance_method_adjoint.hpp \
    src/CMatrix/instance_method_block.hpp \
    src/CMatrix/instance_method_cols.hpp \
    src/CMatrix/instance_method_conjugate.hpp \
    src/CMatrix/instance_method_determinant.hpp \
    src/CMatrix/instance_method_diagonal.hpp \
    src/CMatrix/instance_method_div.hpp \
    src/CMatrix/instance_method_diva.hpp \
    src/CMatrix/instance_method_equals.hpp \
    src/CMatrix/instance_method_get.hpp \
    src/CMatrix/instance_method_inverse.hpp \
    src/CMatrix/instance_method_isApprox.hpp \
    src/CMatrix/instance_method_isDiagonal.hpp \
    src/CMatrix/instance_method_isIdentity.hpp \
    src/CMatrix/instance_method_isOnes.hpp \
    src/CMatrix/instance_method_isSquare.hpp \
    src/CMatrix/instance_method_mul.hpp \
    src/CMatrix/instance_method_mula.hpp \
    src/CMatrix/instance_method_rows.hpp \
    src/CMatrix/instance_method_set.hpp \
    src/CMatrix/instance_method_sub.hpp \
    src/CMatrix/instance_method_suba.hpp \
    src/CMatrix/instance_method_toString.hpp \
    src/CMatrix/instance_method_trace.hpp \
    src/CMatrix/instance_method_transpose.hpp \
    src/CMatrix/macro.hpp \
    src/CMatrixBlock.hpp \
    src/CMatrixBlock/instance_method_mula.hpp \
    src/CMatrixBlock/definitions.hpp \
    src/CMatrixBlock_fwd.hpp \
    src/CMatrix_fwd.hpp \
    src/CRowVector.hpp \
    src/CRowVector/class_method_Constant.hpp \
    src/CRowVector/definitions.hpp \
    src/CRowVector/instance_method_get.hpp \
    src/CRowVector/instance_method_mula.hpp \
    src/CRowVector/instance_method_set.hpp \
    src/CRowVector_fwd.hpp \
    src/CRowVectorBlock.hpp \
    src/CRowVectorBlock/definitions.hpp \
    src/CRowVectorBlock_fwd.hpp \
    src/CVector.hpp \
    src/CVector/class_method_Constant.hpp \
    src/CVector/definitions.hpp \
    src/CVector/instance_method_get.hpp \
    src/CVector/instance_method_mula.hpp \
    src/CVector/instance_method_set.hpp \
    src/CVector_fwd.hpp \
    src/CVectorBlock.hpp \
    src/CVectorBlock/definitions.hpp \
    src/CVectorBlock_fwd.hpp \
    src/Complex.hpp \
    src/Complex/class_method_acos.hpp \
    src/Complex/class_method_acosh.hpp \
    src/Complex/class_method_asin.hpp \
    src/Complex/class_method_asinh.hpp \
    src/Complex/class_method_atan.hpp \
    src/Complex/class_method_atanh.hpp \
    src/Complex/class_method_cos.hpp \
    src/Complex/class_method_cosh.hpp \
    src/Complex/class_method_exp.hpp \
    src/Complex/class_method_log.hpp \
    src/Complex/class_method_log10.hpp \
    src/Complex/class_method_polar.hpp \
    src/Complex/class_method_pow.hpp \
    src/Complex/class_method_proj.hpp \
    src/Complex/class_method_sin.hpp \
    src/Complex/class_method_sinh.hpp \
    src/Complex/class_method_sqrt.hpp \
    src/Complex/class_method_tan.hpp \
    src/Complex/class_method_tanh.hpp \
    src/Complex/definitions.hpp \
    src/Complex/instance_method_abs.hpp \
    src/Complex/instance_method_add.hpp \
    src/Complex/instance_method_adda.hpp \
    src/Complex/instance_method_arg.hpp \
    src/Complex/instance_method_conj.hpp \
    src/Complex/instance_method_div.hpp \
    src/Complex/instance_method_diva.hpp \
    src/Complex/instance_method_equals.hpp \
    src/Complex/instance_method_isApprox.hpp \
    src/Complex/instance_method_mul.hpp \
    src/Complex/instance_method_mula.hpp \
    src/Complex/instance_method_norm.hpp \
    src/Complex/instance_method_sub.hpp \
    src/Complex/instance_method_suba.hpp \
    src/Complex/instance_method_toString.hpp \
    src/Complex/macro.hpp \
    src/Complex/property_accessor_imag.hpp \
    src/Complex/property_accessor_real.hpp \
    src/Complex_fwd.hpp \
    src/EigenJS.cpp \
    src/Matrix.hpp \
    src/Matrix/class_method_Constant.hpp \
    src/Matrix/class_method_Identity.hpp \
    src/Matrix/class_method_Ones.hpp \
    src/Matrix/class_method_Random.hpp \
    src/Matrix/class_method_Zero.hpp \
    src/Matrix/definitions.hpp \
    src/Matrix/instance_method_add.hpp \
    src/Matrix/instance_method_adda.hpp \
    src/Matrix/instance_method_adjoint.hpp \
    src/Matrix/instance_method_block.hpp \
    src/Matrix/instance_method_cols.hpp \
    src/Matrix/instance_method_conjugate.hpp \
    src/Matrix/instance_method_determinant.hpp \
    src/Matrix/instance_method_diagonal.hpp \
    src/Matrix/instance_method_div.hpp \
    src/Matrix/instance_method_diva.hpp \
    src/Matrix/instance_method_equals.hpp \
    src/Matrix/instance_method_get.hpp \
    src/Matrix/instance_method_inverse.hpp \
    src/Matrix/instance_method_isApprox.hpp \
    src/Matrix/instance_method_isDiagonal.hpp \
    src/Matrix/instance_method_isIdentity.hpp \
    src/Matrix/instance_method_isOnes.hpp \
    src/Matrix/instance_method_isSquare.hpp \
    src/Matrix/instance_method_mul.hpp \
    src/Matrix/instance_method_mula.hpp \
    src/Matrix/instance_method_rows.hpp \
    src/Matrix/instance_method_set.hpp \
    src/Matrix/instance_method_sub.hpp \
    src/Matrix/instance_method_suba.hpp \
    src/Matrix/instance_method_toString.hpp \
    src/Matrix/instance_method_trace.hpp \
    src/Matrix/instance_method_transpose.hpp \
    src/Matrix/macro.hpp \
    src/MatrixBlock.hpp \
    src/MatrixBlock/instance_method_mula.hpp \
    src/MatrixBlock/definitions.hpp \
    src/MatrixBlock_fwd.hpp \
    src/Matrix_fwd.hpp \
    src/RowVector.hpp \
    src/RowVector/class_method_Constant.hpp \
    src/RowVector/definitions.hpp \
    src/RowVector/instance_method_block.hpp \
    src/RowVector/instance_method_get.hpp \
    src/RowVector/instance_method_mula.hpp \
    src/RowVector/instance_method_set.hpp \
    src/RowVector_fwd.hpp \
    src/RowVectorBlock.hpp \
    src/RowVectorBlock/definitions.hpp \
    src/RowVectorBlock_fwd.hpp \
    src/Vector.hpp \
    src/Vector/class_method_Constant.hpp \
    src/Vector/definitions.hpp \
    src/Vector/instance_method_block.hpp \
    src/Vector/instance_method_get.hpp \
    src/Vector/instance_method_mula.hpp \
    src/Vector/instance_method_set.hpp \
    src/Vector_fwd.hpp \
    src/VectorBlock.hpp \
    src/VectorBlock/definitions.hpp \
    src/VectorBlock_fwd.hpp \
    src/base.hpp \
    src/common_macro.hpp \
    src/definition.hpp \
    src/detail/add_complex.hpp \
    src/detail/initializer.hpp \
    src/detail/is_eigen_block.hpp \
    src/detail/is_eigen_matrix.hpp \
    src/detail/is_matrix_or_cmatrix.hpp \
    src/detail/is_rowvector_or_crowvector.hpp \
    src/detail/is_vector_or_cvector.hpp \
    src/detail/property_accessor_base.hpp \
    src/detail/unwrap_block.hpp \
    src/detail/unwrap_eigen_block.hpp \
    src/throw_error.hpp

FILTER = -build/c++11,-build/include_what_you_use,-whitespace/braces,-whitespace/parens,-whitespace/operators

all:
	cd $(TOPLEVEL) && node-gyp configure build

clean:
	cd $(TOPLEVEL) && node-gyp clean

distclean: clean
	cd $(TOPLEVEL) && rm -rf node_modules

test: force
	cd $(TOPLEVEL) && mocha $(TOPLEVEL)/test/*.js

lint: force
	cd $(TOPLEVEL) && $(PYTHON) $(CPPLINT) --filter=$(FILTER) --extensions=hpp,cpp $(SOURCES)

PHONY += force
force:

.PHONY: $(PHONY)
