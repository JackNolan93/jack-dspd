/*
 * HOWTO write an External for Pure data
 * (c) 2001-2006 IOhannes m zmölnig zmoelnig[AT]iem.at
 *
 * this is the source-code for the fourth example in the HOWTO
 * it creates a simple dsp-object:
 * 2 input signals are mixed into 1 output signal
 * the mixing-factor can be set via the 3rd inlet
 *
 * for legal issues please see the file LICENSE.txt
 */

#include "m_pd.h"

static t_class *square_tilde_class;

typedef struct _square_tilde {
    t_object x_obj;

    t_float x_frequency;
    t_float x_phase;
    t_float x_phase_increment;

    t_inlet *x_in_phase;
    t_outlet*x_out;
} t_square_tilde;

t_int *square_tilde_perform(t_int *w)
{
    t_square_tilde *x = (t_square_tilde *)(w[1]);
    t_sample    *out =      (t_sample *)(w[2]);
    int            n =             (int)(w[3]);
    
    t_float x_phase_increment = x->x_frequency / 44100;
    
    double dphase = x->x_phase;

    for(int i = 0; i < n; i++)
    {
        dphase += x_phase_increment;
        
        if (dphase > 1.0)
            dphase -= 1.0;
        
        out [i] = dphase > 0.5 ? 1.0 : -1.0;
    }
    
    x->x_phase = dphase;

    return (w+4);
}

void square_tilde_dsp(t_square_tilde *x, t_signal **sp)
{
    dsp_add(square_tilde_perform, 3, x, sp[1]->s_vec, sp[0]->s_n);
}

void square_tilde_free(t_square_tilde *x)
{
    outlet_free(x->x_out);
}

void *square_tilde_new(t_floatarg f)
{
    t_square_tilde *x = (t_square_tilde *)pd_new(square_tilde_class);

    x->x_phase = 0.0;
    x->x_frequency = f;

    x->x_in_phase = floatinlet_new(&x->x_obj, &x->x_phase);

    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void square_tilde_setup (void)
{
    square_tilde_class = class_new(gensym("square~"),
        (t_newmethod)square_tilde_new,
        (t_method)square_tilde_free,
        sizeof(t_square_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (square_tilde_class, t_square_tilde, x_frequency);

    class_addmethod(square_tilde_class,
      (t_method)square_tilde_dsp, gensym("dsp"), A_CANT, 0);
}

