===============================================================================

                             SpinXForm v0.1

                              Keenan Crane
                             August 16, 2011

===============================================================================


--------------
0. CONTENTS
--------------

  0. CONTENTS
  1. ABOUT
  2. DEPENDENCIES
  3. BUILDING
  4. TESTING
  5. USAGE
   A. INPUTS
   B. COMMAND LINE MODE
   C. INTERACTIVE MODE
  6. FILE FORMATS
   A. Wavefront OBJ
   B. Truevision TGA
  7. SOURCE CODE
  8. LICENSE


-----------
1. ABOUT
-----------

This archive contains a C++ implementation of an algorithm for computing
conformal transformations of polygon meshes.  It is based on the paper

  K. Crane, U. Pinkall, and P. Schroeder, "Spin Transformations of
  Discrete Surfaces," ACM Transactions on Graphics (SIGGRAPH) 2011.

The basic functionality is to take a manifold, triangulated mesh (without
boundary) plus a grayscale image map as input, and produce a new mesh
with the same connectivity but modified vertex positions.  Triangles in the new
mesh will have nearly the same angles and aspect ratios as those from the
original mesh, but with curvature that differs by the amount specified in the
input image.  (See the paper above for more details.)  In the GUI version of
SpinXForm the input image is reloaded from disk every time the deformation is
updated.  This way the user can "paint" a curvature change in some external
program (such as Adobe Photoshop) and immediately view the resulting effect
on the surface.

PLEASE NOTE that this is research code and has not been tested extensively.
Luckily, it was written by a friendly researcher who is happy to help you out
via email in your times of trouble: keenan@cs.caltech.edu

Thanks to Robert Bridson for providing the preconditioned conjugate gradient
code (found in the "pcg" subdirectory).


------------------
2. DEPENDENCIES
------------------

In order to make the code as easy as possible to build, several distributions
are available, each with an increasing number of dependencies:

  -spinxform_nodep  -- no dependencies; should build with any C++ compiler
  -spinxform_opengl -- depends only on OpenGL and GLUT
  -spinxform_fast   -- depends on OpenGL, GLUT, and SuiteSparse

The first two distributions are easiest to build, but also exhibit suboptimal
performance because they use a simple conjugate gradient solver (with only a
diagonal preconditioner).  The "fast" version depends on Tim Davis' CHOLMOD
cholesky factorization library:

http://www.cise.ufl.edu/research/sparse/cholmod/

which in turn depends on SuiteSparse and METIS:

http://www.cise.ufl.edu/research/sparse/SuiteSparse/
http://glaros.dtc.umn.edu/gkhome/views/metis

as well as some (hopefully optimized!) BLAS/LAPACK implementation.  On
UNIX-like systems you will probably end up needing the libraries

  bamd.a
  libcamd.a
  libcolamd.a
  libccolamd.a
  libcholmod.a

from SuiteSparse and

  libmetis.a

from METIS.  If you want to avoid compiling all of SuiteSparse, you can simply
type "make" in each of the appropriate Lib directories (e.g., AMD/Lib) after
setting up UFConfig and copying the resulting library (.a) files to
/usr/local/bin or some other appropriate place.  Further instructions on
building SuiteSparse and its dependencies can be found on the SuiteSparse home
page.

On Mac OS X, the easiest way to link to an efficient BLAS
implementation is by adding the framework

  -framework Accelerate

On other platforms, Kazushige Goto's GotoBLAS library is a popular choice:

  http://www.tacc.utexas.edu/tacc-projects/gotoblas2/


--------------
3. BUILDING
--------------

On UNIX-like systems, you should simply need to type

  make

at the command line in the root install directory.  This should build the
command-line utility "spinxform."  On Windows it may be simplest to install Cygwin:

  http://www.cygwin.com/

which includes an implementation of the GNUMake system which can be used to
execute the Makefiles for SpinXForm, SuiteSparse, and METIS.  If you need to build
code that does not depend on Cygwin DLLs, MINGW is an option:

  http://www.mingw.org/

Finally, a VisualStudio project has been included, but uses only the (slower)
conjugate gradient solver.  For compiling SuiteSparse, METIS, or BLAS
with VisualStudio, you may want to take a look at

  http://matrixprogramming.com/2008/05/umfpack-vc


-------------
4. TESTING
-------------

To test that SpinXForm is working properly, type

   make test

at the command line.  Results produced by SpinXForm will be checked against
reference solutions included in th distribution.  Depending on output
formatting and the libraries used for BLAS, linear solver, etc., your result
may not match the reference solution exactly, but it should be pretty close.


-----------
5. USAGE
-----------

SpinXForm can be executed from the command line (see Section 5B), by running
SpinXForm.app (on Mac OS X), or by running SpinXForm.bat (Windows).  On Mac OS
X the user will be prompted for the mesh file and then the corresponding image
file.  In Windows, inputs are specified by editing SpinXForm.bat.

5A. INPUTS
----------

Meshes should be encoded as Wavefront OBJ files; images should be encoded as
grayscale, 8 bits per pixel Truevision TGA files.  (See Section 6 for more
information on file formats.)  

The input image file represents the requested change in curvature as grayscale
values.  A value of 128 (~50%) represents no change; values greater than 128
indicates an increase in curvature, and values less than 128 indicate a
decrease.

** Note: the input mesh MUST have texture coordinates! **

Values are mapped from the image to the surface using texture coordinates in
the range [0,1] x [0,1].  This means that the image is treated as a SQUARE
image, independent of its actual dimensions.


5B. COMMAND LINE MODE
---------------------

The SpinXForm executable takes two input arguments and one optional output argument:

   spinxform mesh.obj image.tga [result.obj]

These arguments can be specified on the command line or by creating a .BAT file
in Windows.  Specifying an output argument runs SpinXForm in batch mode: rather
than displaying the GUI, results are simply written to the command line.


5C. INTERACTIVE MODE
--------------------

The graphical user interface (GUI) displays the current state of the mesh.  The
view is controlled by clicking and dragging anywhere in the main window.
Right-clicking brings up the main menu with the following options:

  [space] Transform  - reload the image from disk and update the deformation
      [r] Reset Mesh - restore the surface to its original configuration
      [w] Write Mesh - write the transformed mesh to "result.obj"
      [q] Exit       - quit SpinXForm

The "view" submenu contains the following options:

  [s] Smooth Shaded  - draws the surface using smooth shading
  [f] Wireframe      - draws the surface as flat-shaded triangles with outlined edges
  [e] QC Error       - displays the per-face deviation from original triangle shape
  [p] Rho            - displays the requested change in curvature
  [t] Textured       - displays a checkerboard pattern
  [-] Shrink Texture - decreases the size of the checkerboard pattern
  [+] Grow Texture   - increases the size of the checkerboard pattern

Each of these options has a keyboard equivalent, indicated in square brackets [].
Note that the checkerboard pattern will look good only if the initial texture
coordinates come from something like a conformal parameterization of the surface.


------------------
6. FILE FORMATS
------------------

6A. Wavefront OBJ
-----------------

A Wavefront OBJ file specifies vertex and face data for a polygonal surface
mesh, as well as vertex texture coordinates.  Vertex data is specified by lines
of the form

  v [x] [y] [z]

where [x], [y], and [z] are x, y and z vertex coordinates.  Texture coordinates
are similarly specified via

  vt [u] [v]

Face data is specified by lines of the form

  f [i1]/[j1] [i2]/[j2] ... [in]/[jn]

where [i1], [i2], etc., are 1-based indices into the vertex list and [j1],
j[2], etc., are indices into the list of texture coordinates.  For
instance, the following data specifies a simple mesh of a square
consisting of two triangles:

  v 0 0 0
  v 1 0 0
  v 1 1 0
  v 0 1 0
  vt 0 0
  vt 1 0
  vt 1 1
  vt 0 1
  f 1/1 3/3 4/4
  f 1/1 2/2 3/3

Note that SpinXForm supports only meshes where all faces are triangles.  Vertex
normals are ignored.

6B. Truevision TGA
------------------

TGA is a very simple bitmap image format consisting of a fixed amount of header
data followed by a chunk of color data.  A more detailed specification can be
found at

http://en.wikipedia.org/wiki/Truevision_TGA

Note that SpinXForm supports only uncompressed grayscale images at 8 bits per pixel.


-----------------
7. SOURCE CODE
-----------------

As an alternative to the command-line utility, you can of course interface with
the code directly.  Basic usage looks like:

  Mesh mesh;
  Image image;
  mesh.read( "mesh.obj" );                  // read a polygon mesh
  image.read( "image.tga" );                // read an image
  const double scale = 5.;                  // set the magnitude of rho
  mesh.setCurvatureChange( image, scale );  // set the values of rho
  mesh.updateDeformation();                 // compute the solution
  mesh.write( "result.obj" );               // write the transformed surface


-------------
8. LICENSE
-------------

SpinXForm is covered by the following free software license based on the 2-clause
BSD license.  This license is compatible with most other free software licenses,
including the GNU General Public License.

*
* Copyright 2011 Keenan Crane. All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
* SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
* The views and conclusions contained in the software and documentation are those
* of the author and should not be interpreted as representing official policies,
* either expressed or implied, of any other person or institution.
*

