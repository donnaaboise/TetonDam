/*
Copyright (c) 2019-2022 Carsten Burstedde, Donna Calhoun, Hannah Spero
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

#include <vcatch_user.h>

static int s_vcatch_options_package_id = -1;

static void*
vcatch_register (user_options_t* user_opt, sc_options_t * opt)
{

    sc_options_add_int (opt, 0, "example", &user_opt->example, 0, "[user] 0 [0]");

    sc_options_add_bool (opt, 0, "rainfall", &user_opt->rainfall, 1, "[user] Use rain [T]");

    sc_options_add_double (opt, 0, "rainfall-time", &user_opt->rainfall_time, 5400, "[user] Rainfall time [5400]");

    sc_options_add_double (opt, 0, "rainfall-rate", &user_opt->rainfall_rate, 3e-6, "[user] Rainfall time [3e-6]");

    sc_options_add_double (opt, 0, "dry-tol", &user_opt->dry_tol, 1e-8, 
                           "[user] Dry tolerance [1e-8]");

    sc_options_add_double (opt, 0, "y-channel", &user_opt->y_channel, 3e-6, 
                           "[user] channel half width [15]");

    sc_options_add_double (opt, 0, "mannings-channel", &user_opt->mannings_channel, 0.15, 
                           "[user] Mannings (channel) [0.15]");

    sc_options_add_double (opt, 0, "mannings-slope", &user_opt->mannings_slope, 0.015, 
                           "[user] Mannings (slope) [0.015]");

    user_opt->is_registered = 1;
    return NULL;
}

static fclaw_exit_type_t
vcatch_postprocess (user_options_t * user_opt)
{

    return FCLAW_NOEXIT;
}


static fclaw_exit_type_t
vcatch_check(user_options_t *vcatch_opt)
{
    return FCLAW_NOEXIT;
}

static
void vcatch_destroy (user_options_t * user_opt)
{
    /* Nothing to do */
}

/* ------------------------------------------------------
   This is boiler plate below here .... don't change 

   Generic calls to options handling;  each calls 
   package specific options call back
   ------------------------------------------------------ */

static void*
options_register (fclaw_app_t * app, void *package, sc_options_t * opt)
{
    user_options_t *vcatch_opt;

    FCLAW_ASSERT (app != NULL);
    FCLAW_ASSERT (package != NULL);

    vcatch_opt = (user_options_t*) package;

    return vcatch_register(vcatch_opt,opt);
}


static fclaw_exit_type_t
options_postprocess (fclaw_app_t * app, void *package, void *registered)
{
    user_options_t *vcatch_opt;

    FCLAW_ASSERT (app != NULL);
    FCLAW_ASSERT (package != NULL);
    FCLAW_ASSERT (registered == NULL);

    vcatch_opt = (user_options_t*) package;
    FCLAW_ASSERT (vcatch_opt->is_registered);

    return vcatch_postprocess (vcatch_opt);
}


static fclaw_exit_type_t
options_check (fclaw_app_t * app, void *package, void *registered)
{
    user_options_t *vcatch_opt;

    FCLAW_ASSERT (app != NULL);
    FCLAW_ASSERT (package != NULL);
    FCLAW_ASSERT (registered == NULL);

    vcatch_opt = (user_options_t*) package;
    FCLAW_ASSERT (vcatch_opt->is_registered);

    return vcatch_check(vcatch_opt);    
}

static void
options_destroy (fclaw_app_t * app, void *package, void *registered)
{
    user_options_t *vcatch_opt;

    FCLAW_ASSERT (app != NULL);
    FCLAW_ASSERT (package != NULL);
    FCLAW_ASSERT (registered == NULL);

    vcatch_opt = (user_options_t*) package;
    FCLAW_ASSERT (vcatch_opt->is_registered);

    vcatch_destroy (vcatch_opt);

    FCLAW_FREE (vcatch_opt);
}

static const fclaw_app_options_vtable_t vcatch_options_vtable = {
    options_register,
    options_postprocess,
    options_check,
    options_destroy,
};

/* ----------------------------------------------------------
   Public interface to clawpack options
   ---------------------------------------------------------- */
user_options_t*  vcatch_options_register (fclaw_app_t * app,
                                          const char *configfile)
{
    user_options_t *vcatch_opt;

    FCLAW_ASSERT (app != NULL);

    vcatch_opt = FCLAW_ALLOC (user_options_t, 1);
    fclaw_app_options_register (app, "user", configfile,
                                &vcatch_options_vtable, vcatch_opt);
    
    fclaw_app_set_attribute(app,"user",vcatch_opt);
    return vcatch_opt;
}

user_options_t* vcatch_get_options(fclaw2d_global_t *glob)
{
    int id = s_vcatch_options_package_id;
    return (user_options_t*) fclaw_package_get_options(glob,id);
}

void vcatch_options_store (fclaw2d_global_t* glob, user_options_t* user_opt)
{
    int id = fclaw_package_container_add_pkg(glob,user_opt);
    s_vcatch_options_package_id = id;
}
