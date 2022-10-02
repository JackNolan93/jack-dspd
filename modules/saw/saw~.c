#include "m_pd.h"

static t_class *saw_tilde_class;

typedef struct _saw_tilde {
    t_object x_obj;

    t_float x_frequency;
    t_float x_phase;
    t_float x_phase_increment;

    t_inlet *x_in_phase;
    t_outlet*x_out;
} t_saw_tilde;

t_int *saw_tilde_perform(t_int *w)
{
    t_saw_tilde *x = (t_saw_tilde *)(w[1]);
    t_sample *out = (t_sample *)(w[3]);
    int n = (int)(w[4]);
    
    t_float x_phase_increment = x->x_frequency / 44100;
    
    double dphase = x->x_phase;

    for(int i = 0; i < n; i++)
    {
        dphase += x_phase_increment;
        
        if (dphase > 1.0)
            dphase -= 1.0;
        
        out [i] = ((1 - dphase) * 2.0) - 1.0;
    }
    
    x->x_phase = dphase;

    return (w+6);
}

void saw_tilde_dsp(t_saw_tilde *x, t_signal **sp)
{
    dsp_add(saw_tilde_perform, 5, x,
          sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n, sp[0]->s_sr);
}

void saw_tilde_free(t_saw_tilde *x)
{
    outlet_free(x->x_out);
}

void *saw_tilde_new(t_floatarg f)
{
    t_saw_tilde * x = (t_saw_tilde *)pd_new(saw_tilde_class);

    x->x_phase = 0.0;
    x->x_frequency = f;

    x->x_in_phase = floatinlet_new(&x->x_obj, &x->x_phase);

    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void saw_tilde_setup (void)
{
    saw_tilde_class = class_new (gensym ("saw~"),
        (t_newmethod) saw_tilde_new,
        (t_method) saw_tilde_free,
        sizeof (t_saw_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (saw_tilde_class, t_saw_tilde, x_frequency);

    class_addmethod (saw_tilde_class,
      (t_method)saw_tilde_dsp, gensym ("dsp"), A_CANT, 0);
}

