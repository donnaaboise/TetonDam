/*
Copyright (c) 2012 Carsten Burstedde, Donna Calhoun
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef VCATCH_USER_H
#define VCATCH_USER_H

#include <fclaw2d_include_all.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct user_options
{
    int example;

    int rainfall;
    double rainfall_time;
    double rainfall_rate;

    double y_channel;

    double mannings_channel;
    double mannings_slope;

    double dry_tol;

    int claw_version;

    int is_registered;
} user_options_t;


user_options_t*  vcatch_options_register (fclaw_app_t * app,
                                          const char *configfile);

user_options_t* vcatch_get_options(fclaw2d_global_t *glob);

void vcatch_options_store (fclaw2d_global_t* glob, user_options_t* vcatch_opt);





void vcatch_link_solvers(fclaw2d_global_t *glob);


#define SETPROB   FCLAW_F77_FUNC(setprob,SETPROB)
void SETPROB();

#define VCATCH_SETAUX  FCLAW_F77_FUNC(vcatch_setaux, VCATCH_SETAUX)
void VCATCH_SETAUX(const int* mbc,
                   const int* mx, const int* my,
                   const double* xlower, const double* ylower,
                   const double* dx, const double* dy,
                   const int* maux, double aux[],
                   const int* is_ghost, const int* nghost,
                   const int* mint);


#define VCATCH_QINIT   FCLAW_F77_FUNC(vcatch_qinit,VCATCH_QINIT)
void VCATCH_QINIT(const int* meqn,const int* mbc,
                 const int* mx, const int* my,
                 const double* xlower, const double* ylower,
                 const double* dx, const double* dy,
                 double q[], const int* maux, double aux[]);


#define VCATCH_SRC2    FCLAW_F77_FUNC(vcatch_src2, VCATCH_SRC2)
void VCATCH_SRC2(const int* meqn,
                 const int* mbc, const int* mx,const int* my,
                 const double* xlower, const double* ylower,
                 const double* dx, const double* dy, double q[],
                 const int* maux, double aux[], const double* t,
                 const double* dt);


/** Fortran subroutine name */
#define VCATCH_FLOODED FCLAW_F77_FUNC(vcatch_flooded, VCATCH_FLOODED)
void VCATCH_FLOODED(int *mx, int *my, int* mbc, int* meqn,
                    double *dx, double *dy,
                    double* area, double *q, double* sum,
                    double* c_kahan);

/* Mappings */
fclaw2d_map_context_t* fclaw2d_map_new_nomap();

#ifdef __cplusplus
}
#endif

#endif
