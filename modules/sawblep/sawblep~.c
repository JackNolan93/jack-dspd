#include "m_pd.h"

static t_class *sawblep_tilde_class;

typedef struct _sawblep_tilde {
    t_object x_obj;

    t_float x_frequency;
    t_float x_phase;
    t_float x_phase_increment;

    t_inlet *x_in_phase;
    t_outlet*x_out;
} t_sawblep_tilde;


double poly_blep (t_sawblep_tilde *x, double t)
{
    if (t < x->x_phase_increment)
    {
        t /= x->x_phase_increment;
        return t+t - t*t - 1.0;
    }
    else if (t > 1.0 - x->x_phase_increment)
    {
        t = (t - 1.0) / x->x_phase_increment;
        return t*t + t+t + 1.0;
    }
    else return 0.0;
}

t_int *sawblep_tilde_perform (t_int *w)
{
    t_sawblep_tilde *x = (t_sawblep_tilde *)(w[1]);
    t_sample    *out =      (t_sample *)(w[2]);
    int            n =             (int)(w[3]);
    
    t_float x_phase_increment = x->x_frequency / 44100; // TODO: add fetch for samplerate
    
    double dphase = x->x_phase;
    double outValue = 0.0;

    for(int i = 0; i < n; i++)
    {
        dphase += x_phase_increment;
        
        if (dphase > 1.0)
            dphase -= 1.0;
        
        outValue = ((1.0 - dphase) * 2.0) - 1.0;
        outValue += poly_blep (x, dphase);
        
        out [i] = outValue;
    }
    
    x->x_phase = dphase;

    return (w+4);
}

void sawblep_tilde_dsp (t_sawblep_tilde *x, t_signal **sp)
{
    dsp_add(sawblep_tilde_perform, 3, x, sp[1]->s_vec, sp[0]->s_n);
}

void sawblep_tilde_free (t_sawblep_tilde *x)
{
    outlet_free(x->x_out);
}

void *sawblep_tilde_new (t_floatarg f)
{
    t_sawblep_tilde *x = (t_sawblep_tilde *) pd_new (sawblep_tilde_class);

    x->x_phase = 0.0;
    x->x_frequency = f;

    x->x_in_phase = floatinlet_new (&x->x_obj, &x->x_phase);

    x->x_out = outlet_new (&x->x_obj, &s_signal);

    return (void *)x;
}

void sawblep_tilde_setup (void)
{
    sawblep_tilde_class = class_new (gensym ("sawblep~"),
        (t_newmethod)sawblep_tilde_new,
        (t_method)sawblep_tilde_free,
        sizeof (t_sawblep_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (sawblep_tilde_class, t_sawblep_tilde, x_frequency);

    class_addmethod (sawblep_tilde_class,
      (t_method) sawblep_tilde_dsp, gensym ("dsp"), A_CANT, 0);
}

