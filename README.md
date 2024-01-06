# matrices for OpenGL

Representing matrices in c++20, specifically for OpenGL.  
Made for the `scop` project for 42 Nice.

## Features
### Matrices and Vectors
- Addition and subtraction
- Scalar multiplication and division
- Matrix-Matrix multiplication
- Transposition
- Average of 2 matrices/vectors
- Vector magnitude
- Vector normalization
- Angle between 2 vectors (2D and 3D)
- Dot product
- Cross product
### OpenGL
- Scaling matrix
- Rotation matrix
- Translation matrix
- View matrix (camera)
- Orthographic projection matrix
- Perspective projection matrix

## How to use

You can use this however you like, I honestly don't care.  

You can see `tests.cpp` to get a sense of how to use this `Matrix` class.  
Avoid using `unsigned` types and `integer` types in general actually.  
This is best used with `float` and `double`.

This class was made with column-matrices in mind, so don't try to use row-matrices, it won't work.  
Though you can always use `Matrix::transpose()` to go from one to the other.  

Don't forget that matrix-matrix multiplication and vector cross product are NOT commutative!

### OpenGL

For use with OpenGL, I recommend making wrapper classes using this class.  
You'll be able to do more specialized things, and you'll be able to enforce a data type.  
  
I personnally have a `Transform` class that represents any transformation matrix.  
You know, the ones that make you go from one space to the next.  
  
I also have a `Camera` class that is a wrapper for the `Transform` class.  
  
So go have fun with extreme amounts of boilerplate!  
All in all, yous should avoid using "*naked*" matrices.  

And remember! For model matrices, use the SRT order:
- Scaling
- Rotation
- Translation

This order prevents transformation matrices from negatively impacting each other.  
Though it doesn't prevent Gimbal lock... (you're dreaming if you think I'm gonna learn what a fucking quaternion is)
