//
// Complex_fwd.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Rick Yang (rick68 at gmail dot com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#ifndef EIGENJS_COMPLEX_FWD_HPP
#define EIGENJS_COMPLEX_FWD_HPP

#include <boost/config.hpp>

#include <complex>

namespace EigenJS {

BOOST_CONSTEXPR char complex_class_name[] = "Complex";

template <
  typename ScalarType = double
, typename ValueType = std::complex<ScalarType>
, const char* ClassName = complex_class_name
> class Complex;

}  // namespace EigenJS

#endif  // EIGENJS_COMPLEX_FWD_HPP
