//
// CMatrix/instance_method_isDiagonal.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_CMATRIX_INSTANCE_METHOD_ISDIAGONAL_HPP
#define EIGENJS_CMATRIX_INSTANCE_METHOD_ISDIAGONAL_HPP

#include "../common_macro.hpp"

namespace EigenJS {

EIGENJS_INSTANCE_METHOD(CMatrix, isDiagonal,
{
  EIGENJS_COMMON_MATRIX_INSTANCE_METHOD_ISDIAGONAL_CONTEXT()
})

}  // namespace EigenJS

#endif  // EIGENJS_CMATRIX_INSTANCE_METHOD_ISDIAGONAL_HPP
