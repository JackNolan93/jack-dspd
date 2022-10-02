#include "m_pd.h"
#include "OverdriveWrapper.h"
#include <math.h>

static t_class *overdrive_tilde_class;

typedef struct _overdrive_tilde {
    t_object x_obj;
    void * cpp_obj;

    t_float x_drive;

    t_outlet * x_out;
} t_overdrive_tilde;

t_int * overdrive_tilde_perform (t_int * w)
{
    t_overdrive_tilde *x = (t_overdrive_tilde *) (w[1]);
    t_sample     *in =    (t_sample *) (w[2]);
    t_sample    *out =    (t_sample *) (w[3]);
    int            n =           (int) (w[4]);
    
    OverdriveSetDrive (x->cpp_obj, x->x_drive);
    
    for(int i = 0; i < n; i++)
        out[i] = OverdriveProcess (x->cpp_obj, in[i]);
    
    return (w+5);
}

void overdrive_tilde_dsp (t_overdrive_tilde * x, t_signal ** sp)
{
    dsp_add (overdrive_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void overdrive_tilde_free (t_overdrive_tilde * x)
{
    outlet_free(x->x_out);
    OverdriveRelease (x->cpp_obj);
}

void * overdrive_tilde_new (t_floatarg f)
{
    t_overdrive_tilde *x = (t_overdrive_tilde *)pd_new(overdrive_tilde_class);

    x->x_drive = 0.0;
    
    floatinlet_new (&x->x_obj, &x->x_drive);
    x->x_out = outlet_new(&x->x_obj, &s_signal);

    x->cpp_obj = OverdriveCreate ();
    OverdriveInit (x->cpp_obj);

    return (void *)x;
}

extern "C" void overdrive_tilde_setup (void)
{
    overdrive_tilde_class = class_new(gensym("overdrive~"),
        (t_newmethod)overdrive_tilde_new,
        (t_method)overdrive_tilde_free,
        sizeof(t_overdrive_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (overdrive_tilde_class, t_overdrive_tilde, x_drive);

    class_addmethod(overdrive_tilde_class,
      (t_method)overdrive_tilde_dsp, gensym("dsp"), A_CANT, 0);
}




