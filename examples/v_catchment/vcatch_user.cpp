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

#include "vcatch_user.h"

#include <fclaw2d_include_all.h>

#include <fclaw2d_clawpatch.h>
#include <fc2d_geoclaw.h>


static
void vatch_problem_setup(fclaw2d_global_t* glob)
{
    const user_options_t* user = vcatch_get_options(glob);

    if (glob->mpirank == 0)
    {
        FILE *f = fopen("setprob.data","w");
        fprintf(f,  "%-24d      %s",user->example,"\% example\n");
        fprintf(f,  "%-24d      %s",user->rainfall,"\% rainfall\n");
        fprintf(f,  "%-24.16f   %s",user->rainfall_rate,"\% rainfall_rate\n");
        fprintf(f,  "%-24.16f   %s",user->rainfall_time,"\% rainfall_time\n");
        fprintf(f,  "%-24.16f   %s",user->mannings_channel,"\% mannings_channel\n");
        fprintf(f,  "%-24.16f   %s",user->mannings_slope,"\% mannings_slope\n");
        fprintf(f,  "%-24.16f   %s",user->y_channel,"\% y_channel\n");
        fprintf(f,  "%-24.16f   %s",user->dry_tol,"\% dry_tol\n");
        fclose(f);
    }

    /* We want to make sure node 0 gets here before proceeding */
    fclaw2d_domain_barrier (glob->domain);  /* redundant?  */
    SETPROB();
}



void vcatch_link_solvers(fclaw2d_global_t *glob)
{

   fclaw2d_vtable_t *vt = fclaw2d_vt();
   vt->problem_setup = vatch_problem_setup;

    /* These are set by GeoClaw for convenience, but the user
       can set these with customized functions, if desired. */
    fc2d_geoclaw_vtable_t* geoclaw_vt = fc2d_geoclaw_vt();

    geoclaw_vt->qinit = &VCATCH_QINIT;
    geoclaw_vt->src2  = &VCATCH_SRC2;

    fclaw2d_clawpatch_vtable_t *clawpatch_vt = fclaw2d_clawpatch_vt();

    clawpatch_vt->fort_conservation_check = &VCATCH_FLOODED;

    //geoclaw_vt->setaux = &VCATCH_SETAUX;

}
