
#include "m_pd.h"
#include <math.h>

static t_class *squareblep_tilde_class;

enum WTFWaveshape
{
    wTFOscSin = 0,
    wTFOscSaw,
    wTFOscSquare,
    wTFOscTriangle,
};

typedef struct _squareblep_tilde
{
    t_object x_obj;

    t_float x_frequency;
    t_float x_phase;
    t_float x_phase_increment;
    
    enum WTFWaveshape wave1;
    enum WTFWaveshape wave2;

    t_inlet *x_in_phase;
    t_outlet*x_out;
} t_squareblep_tilde;

double poly_blep (t_squareblep_tilde *x, double t)
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

t_int *squareblep_tilde_perform(t_int *w)
{
    t_squareblep_tilde *x = (t_squareblep_tilde *) (w[1]);
    t_sample    *freq =     (t_sample *) (w[2]);
    t_sample    *out =      (t_sample *) (w[3]);
    int            n =             (int) (w[4]);
    
    x->x_phase_increment = freq [0] / 44100;
    double dphase = x->x_phase;
    double sample = 0.0;

    for(int i = 0; i < n; i++)
    {

        while (dphase > 1.0)
            dphase -= 1.0;
        
        sample = dphase < 0.5 ? 1.0 : -1.0;
        
        sample += poly_blep (x, dphase);
        sample -= poly_blep (x, fmod (dphase + 0.5, 1.0));
        
        out [i] = sample;
        
        dphase += x->x_phase_increment;
    }
    
    x->x_phase = dphase;

    return (w+5);
}

void squareblep_tilde_dsp(t_squareblep_tilde *x, t_signal **sp)
{
    dsp_add(squareblep_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void squareblep_tilde_free(t_squareblep_tilde *x)
{
    outlet_free(x->x_out);
}

void *squareblep_tilde_new(t_floatarg f)
{
    t_squareblep_tilde *x = (t_squareblep_tilde *)pd_new(squareblep_tilde_class);

    x->x_phase = 0.0;
    x->x_frequency = f;

    x->x_in_phase = floatinlet_new(&x->x_obj, &x->x_phase);
    
    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void squareblep_tilde_setup (void)
{
    squareblep_tilde_class = class_new(gensym("squareblep~"),
        (t_newmethod)squareblep_tilde_new,
        (t_method)squareblep_tilde_free,
        sizeof(t_squareblep_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (squareblep_tilde_class, t_squareblep_tilde, x_frequency);

    class_addmethod(squareblep_tilde_class,
      (t_method)squareblep_tilde_dsp, gensym("dsp"), A_CANT, 0);
}


