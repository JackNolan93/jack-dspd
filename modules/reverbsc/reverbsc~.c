#include "m_pd.h"
#include "ReverbscWrapper.h"
#include <math.h>
#include <algorithm>

static t_class *reverbsc_tilde_class;

typedef struct _reverbsc_tilde {
    t_object x_obj;
    
    void * cpp_obj;

    t_float x_feedback;
    t_float x_lp_f;

    t_outlet * x_out_1;
    t_outlet * x_out_2;
} t_reverbsc_tilde;

t_int * reverbsc_tilde_perform (t_int * w)
{
    t_reverbsc_tilde *x = (t_reverbsc_tilde *) (w[1]);
    t_sample    *in =     (t_sample *) (w[2]);
    t_sample    *out1 =   (t_sample *) (w[3]);
    t_sample    *out2 =   (t_sample *) (w[4]);
    int            n =           (int) (w[5]);
    
    ReverbScSetFreq (x->cpp_obj, x->x_lp_f);
    ReverbScSetFeedback (x->cpp_obj, x->x_feedback);
    
    for(int i = 0; i < n; i++)
    {
        ReverbScProcess (x->cpp_obj, in[i], &out1[i], &out2[i]);
    }
    
    return (w+6);
}

void reverbsc_tilde_dsp (t_reverbsc_tilde * x, t_signal ** sp)
{
    dsp_add (reverbsc_tilde_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}

void reverbsc_tilde_free (t_reverbsc_tilde * x)
{
    outlet_free(x->x_out_1);
    outlet_free(x->x_out_2);
    ReverbScRelease (x->cpp_obj);
}

void * reverbsc_tilde_new (t_floatarg f)
{
    t_reverbsc_tilde *x = (t_reverbsc_tilde *)pd_new(reverbsc_tilde_class);

    x->x_feedback = 0.5;
    x->x_lp_f = 0;
    
    floatinlet_new (&x->x_obj, &x->x_feedback);
    floatinlet_new (&x->x_obj, &x->x_lp_f);
    x->x_out_1 = outlet_new(&x->x_obj, &s_signal);
    x->x_out_2 = outlet_new(&x->x_obj, &s_signal);
    
    x->cpp_obj = ReverbScCreate ();
    ReverbScInit (x->cpp_obj, 44100);

    return (void *)x;
}

extern "C" void reverbsc_tilde_setup (void)
{
    reverbsc_tilde_class = class_new(gensym("reverbsc~"),
        (t_newmethod)reverbsc_tilde_new,
        (t_method)reverbsc_tilde_free,
        sizeof(t_reverbsc_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (reverbsc_tilde_class, t_reverbsc_tilde, x_feedback);

    class_addmethod(reverbsc_tilde_class,
      (t_method)reverbsc_tilde_dsp, gensym("dsp"), A_CANT, 0);
}




