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
#include <math.h>
#include <stdbool.h>

static t_class *phasesin_tilde_class;

typedef struct _phasesin_tilde {
    t_object x_obj;

    t_float x_frequency;
    
    t_float x_phase;
    t_float x_phase_increment;
    t_float x_distortion_phase;
    
    t_float x_y_centre;

    t_inlet *x_in_centre;
    t_outlet*x_out;
} t_phasesin_tilde;

t_int * phasesin_tilde_perform (t_int *w)
{
    t_phasesin_tilde * x = (t_phasesin_tilde *)(w[1]);
    t_sample * centre_point = (t_sample *)(w[2]);
    t_sample * out = (t_sample *)(w[3]);
    int n = (int)(w[4]);
    
    x->x_phase_increment = x->x_frequency / 44100;
    
    for(int i = 0; i < n; i++)
    {
        if (x->x_phase < centre_point [i])
        {
            float m = x->x_y_centre / centre_point [i];
            x->x_distortion_phase = x->x_phase * m;
        }
        else
        {
            float m2 = (1.0 - x->x_y_centre) / (1.0 - centre_point [i]);
            float c = 1.0 - m2;
            x->x_distortion_phase = x->x_phase * m2 + c;
        }

        out [i] = cos (x->x_distortion_phase * M_PI * 2.0);
        
        x->x_phase += x->x_phase_increment;
        
        while (x->x_phase >= 1)
            x->x_phase -= 1;
    }
    
    return (w+5);
}

void phasesin_tilde_dsp(t_phasesin_tilde *x, t_signal **sp)
{
    dsp_add(phasesin_tilde_perform, 4, x, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}

void phasesin_tilde_free(t_phasesin_tilde *x)
{
    outlet_free(x->x_out);
    inlet_free(x->x_in_centre);
}

void *phasesin_tilde_new(t_floatarg f)
{
    t_phasesin_tilde *x = (t_phasesin_tilde *)pd_new(phasesin_tilde_class);

    x->x_phase = 0.0;
    x->x_distortion_phase = 0.0;
    x->x_frequency = f;

    x->x_in_centre = inlet_new (&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    floatinlet_new(&x->x_obj, &x->x_y_centre);
    
    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void phasesin_tilde_setup (void)
{
    phasesin_tilde_class = class_new(gensym("phasesin~"),
        (t_newmethod)phasesin_tilde_new,
        (t_method)phasesin_tilde_free,
        sizeof(t_phasesin_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (phasesin_tilde_class, t_phasesin_tilde, x_frequency);

    class_addmethod(phasesin_tilde_class,
      (t_method)phasesin_tilde_dsp, gensym("dsp"), A_CANT, 0);
}

