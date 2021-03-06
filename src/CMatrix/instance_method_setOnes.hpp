//
// CMatrix/instance_method_setOnes.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_CMATRIX_INSTANCE_METHOD_SETONES_HPP
#define EIGENJS_CMATRIX_INSTANCE_METHOD_SETONES_HPP

namespace EigenJS {

EIGENJS_INSTANCE_METHOD(CMatrix, setOnes,
{
  EIGENJS_COMMON_MATRIX_INSTANCE_METHOD_SETONES_CONTEXT()
})

}  // namespace EigenJS

#endif  // EIGENJS_CMATRIX_INSTANCE_METHOD_SETONES_HPP
