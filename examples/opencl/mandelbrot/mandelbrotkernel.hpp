// Copyright (c)       2014 Martin Stumpf
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef MANDELBROT_MANDELBROTKERNEL_H_
#define MANDELBROT_MANDELBROTKERNEL_H_

static const char* mandelbrot_kernels =
"                                                                            \n"
"    __kernel void mandelbrot_noalias(global unsigned char* out,             \n"
"                                     global double* position)               \n"
"    {                                                                       \n"
"                                                                            \n"
"        /* calculating index and position */                                \n"
"        size_t tid = get_global_id(0);                                      \n"
"        size_t size = get_global_size();                                    \n"
"                                                                            \n"
"        double startx = position[0];                                        \n"
"        double starty = position[1];                                        \n"
"        double sizex = position[2];                                         \n"
"        double sizey = position[3];                                         \n"
"                                                                            \n"
"        double posx = startx + (sizex * tid) / (size - 1);                  \n"
"        double posy = starty + (sizey * tid) / (size - 1);                  \n"
"                                                                            \n"
"        double mag_square = 0.0;                                            \n"
"        unsigned long iter = 0;                                             \n"
"        double x = 0.0;                                                     \n"
"        double y = 0.0;                                                     \n"
"                                                                            \n"
"        /* const, need to be more usefull */                                \n"
"        unsigned long maxiter = 10000;                                      \n"
"        double bailout = 10000.0;                                           \n"
"                                                                            \n"
"        // main calculation                                                 \n"
"        while(mag_square <= bailout && iter < maxiter)                      \n"
"        {                                                                   \n"
"            double xt = x * x - y * y + posx;                               \n"
"            double yt = 2 * x * y + posy;                                   \n"
"            x = xt;                                                         \n"
"            y = yt;                                                         \n"
"            iter = iter + 1;                                                \n"
"            mag_square = x * x + y * y;                                     \n"
"        }                                                                   \n"
"                                                                            \n"
"        // smoothing                                                        \n"
"        double iter_smooth = iter - log(log(mag_square) / log(4)) / log(2); \n"
"        double val = fmod(0.42 * log(iter_smooth) / log(10), 1);            \n"
"                                                                            \n"
"        if(iter == maxiter)                                                 \n"
"        {                                                                   \n"
"            out[3*tid + 0] = 0;                                             \n"
"            out[3*tid + 1] = 0;                                             \n"
"            out[3*tid + 2] = 0;                                             \n"
"        }                                                                   \n"
"        else                                                                \n"
"        {                                                                   \n"
"            out[3*tid + 0] = (unsigned char) (200 * val);                   \n"
"            out[3*tid + 1] = (unsigned char) (200 * val);                   \n"
"            out[3*tid + 2] = (unsigned char) (200 * val);                   \n"
"        }                                                                   \n"
"                                                                            \n"
"    }                                                                       \n"
"                                                                            \n";

#endif

