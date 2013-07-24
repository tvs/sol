# Sol

## VERSION
Version 0.1, February 4, 2010

## DESCRIPTION
Sol is a C++ ray tracer designed for a computer graphics course. The hope is to create a
framework that can then be added to over the course of the semester.

## BUILDING AND RUNNING
# BUILDING
Run Gnumake from the top-level directory of the project by using the command:
`$ make`

This will place the executable in the top-level directory

# RUNNING
Run Sol from the top-level directory of the project by using the command:
`$ ./sol > [imagefile.ppm]`

For different images, comment or uncomment macros in src/main.cpp

# CLEANING
To remove the object files created during compilation:
`$ make clean`

To remove the object files and the executable:
`$ make clobber`

## REQUIREMENTS

* G++ compiler
* Make

## RECOMMENDED

* PPM viewing application

## AUTHOR
Travis Hall

trvs.hll@gmail.com

## FILE MANIFEST

* Makefile                      Makefile for building the entire project

### SOURCE
* src/bbox.h                    Bounding box class
* src/bvh.{cpp,h}               Bounding volume hierarchy class
* src/camera.h                  Camera class for setting up the view and projection
* src/light.h                   Light class
* src/main.cpp                  Main program class (for rendering several options)
* src/Makefile                  Makefile for compiling this subdirectory
* src/marbletexture.{cpp,h}     Marble texturing class
* src/material.h                Simple material class for coloring/texturing/lighting
* src/noisetexture.{cpp,h}      Perlin noise texture class (hardcoded for testing)
* src/ray.h                     Ray class
* src/scene.{cpp,h}             Scene class for containing the entire modeling configuration
* src/simpletexture.{cpp,h}     Simple solid-colored texture class
* src/texture.h                 Parent texture class

* src/color/Makefile
* src/color/rgb.h               RGB color class

* src/image/image.{cpp,h}       PPM image class
* src/image/Makefile

* src/shapes/bezierpatch.{cpp,h}  Bezier patch class
* src/shapes/beztrianglemesh.{cpp,h}  Triangle mesh helper class for Bezier patch
* src/shapes/instance.{cpp,h}   Instancing class (wraps a shape primitive)
* src/shapes/Makefile
* src/shapes/plane.{cpp,h}      Infinite plane primitive
* src/shapes/shape.h            Parent class for all ray traceable objects
* src/shapes/teapot.{cpp,h}     Standard teapot rendering class using Bezier patches
* src/shapes/triangle.{cpp,h}   2D Triangle primitive
* src/shapes/unitsphere.{cpp,h} Unit sphere primitive

* src/util/dynarray.h           Dynamic array class
* src/util/hitrecord.h          Hit-record class
* src/util/Makefile
* src/util/matrix.{cpp,h}       3x3 Matrix class
* src/util/noise.{cpp,h}        Perlin noise routines
* src/util/onb.{cpp,h}          Orthonormal basis class
* src/util/qsplit.h             Helper routine for the bounding volume hierarchy
* src/util/rng.h                Portable random number generator
* src/util/vector2d.h           Two-dimensional vector class
* src/util/vector3d.h           Three-dimensional vector class

### DOCUMENTS
* doc/README

### IMAGES
* images/2lights.ppm            Sample image using two lights instead of just one.
* images/2lights-attenuated.ppm Sample image using two lights instead of just one, with
                                attenuation values set as: constant = 1, linear = 0.02,
                                quadratic = 0 
* images/balls.ppm              Stacked cannonballs
* images/bezpatch.ppm           Sample Bezier patch
* images/marbletest.ppm         Stacked cannonballs using marble textures
* images/noisetest.ppm          Stacked cannonballs using noise textures (testing noise)
* images/superglow.ppm          The sample image with the white ball set with a specular
                                component of 1.0 and a translucency of 0.5 
* images/teapot.ppm             Teapot sample render using marble textures
* images/trianglemeshtest.ppm   Triangle mesh testing (renders quadrilateral as triangles)