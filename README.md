# EigenJS [![NPM version][npm-image]][npm-url] [![Downloads][downloads-image]][npm-url] [![Build Status][travis-image]][travis-url] [![Gitter chat][gitter-image]][gitter-url]
The goal of this project is to port Eigen library into JavaScript for linear algebar.

[npm-image]: http://img.shields.io/npm/v/eigenjs.svg
[npm-url]: https://npmjs.org/package/eigenjs

[downloads-image]: http://img.shields.io/npm/dm/eigenjs.svg

[travis-image]: https://travis-ci.org/rick68/eigenjs.svg?branch=master
[travis-url]: https://travis-ci.org/rick68/eigenjs

[gitter-image]: https://badges.gitter.im/rick68/eigenjs.png
[gitter-url]: https://gitter.im/rick68/eigenjs

## Getting started
First download and install [Eigen](http://eigen.tuxfamily.org). In OS X, you can simply use [Homebrew](http://brew.sh) and do:

```bash
$ brew install eigen
```

then either use npm:

```bash
$ npm install eigenjs
```

## Matrix methods

### Eigen.Matrix(rows, cols)

```js
var Matrix = require('eigenjs').Matrix
  , mat = new Matrix(2, 3);
console.log('mat =\n%s', mat);
```

```txt
mat =
0 0 0
0 0 0
```

### Eigen.Matrix.rows() & Eigen.Matrix.cols()

```js
var Matrix = require('eigenjs').Matrix
  , mat = new Matrix(2, 3);
console.log('mat.rows() =', mat.rows());
console.log('mat.cols() =', mat.cols());
```

```txt
mat.rows() = 2
mat.cols() = 3
```

### Eigen.Matrix.set(row, col, value)

```js
var Matrix = require('eigenjs').Matrix
  , mat = new Matrix(2, 2);
mat.set(0, 0, 1);
mat.set(0, 1, 2);
mat.set(1, 0, 3);
mat.set(1, 1, 4);
console.log('mat = \n%s', mat);```

```txt
mat =
1 2
3 4
```
