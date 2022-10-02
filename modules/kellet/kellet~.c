#include "m_pd.h"
#include <math.h>

static t_class *kellet_tilde_class;

typedef struct _kellet_tilde {
    t_object x_obj;

    t_float x_frequency;
    t_float x_resonance;
    
    t_float x_buf0;
    t_float x_buf1;

    t_inlet *x_in_frequency;
    t_outlet*x_out;
} t_kellet_tilde;

t_int *kellet_tilde_perform (t_int * w)
{
    t_kellet_tilde *x = (t_kellet_tilde *) (w[1]);
    t_sample    *in   =       (t_sample *) (w[2]);
    t_sample    *freq =       (t_sample *) (w[3]);
    t_sample    *out  =       (t_sample *) (w[4]);
    int            n  =              (int) (w[5]);
    
    t_float feedbackAmount = 0.0;
    
    for(int i = 0; i < n; i++)
    {
        freq [i] = fmax(fmin(freq [i], 0.99), 0.01);
        feedbackAmount = x->x_resonance + x->x_resonance/(1.0 - freq [i]);
        
        x->x_buf0 += freq [i] * (in[i] - x->x_buf0 + feedbackAmount * (x->x_buf0 - x->x_buf1));
        x->x_buf1 += freq [i] * (x->x_buf0 - x->x_buf1);
        
        out [i] = x->x_buf1;
    }

    return (w+6);
}

void kellet_tilde_dsp (t_kellet_tilde * x, t_signal ** sp)
{
    dsp_add(kellet_tilde_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}

void kellet_tilde_free (t_kellet_tilde * x)
{
    inlet_free (x->x_in_frequency);
    outlet_free(x->x_out);
}

void * kellet_tilde_new (t_floatarg f)
{
    t_kellet_tilde *x = (t_kellet_tilde *)pd_new(kellet_tilde_class);

    x->x_frequency = f;
    x->x_resonance = 0.0;
    x->x_buf0 = 0.0;
    x->x_buf1 = 0.0;

    x->x_in_frequency = inlet_new(&x->x_obj,  &x->x_obj.ob_pd, &s_signal, &s_signal);
    
    floatinlet_new(&x->x_obj, &x->x_resonance);
    
    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void kellet_tilde_setup (void)
{
    kellet_tilde_class = class_new(gensym("kellet~"),
        (t_newmethod)kellet_tilde_new,
        (t_method)kellet_tilde_free,
        sizeof(t_kellet_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (kellet_tilde_class, t_kellet_tilde, x_frequency);

    class_addmethod(kellet_tilde_class,
      (t_method)kellet_tilde_dsp, gensym("dsp"), A_CANT, 0);
}


