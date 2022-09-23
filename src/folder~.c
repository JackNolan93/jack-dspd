#include "m_pd.h"
#include <math.h>

static t_class *folder_tilde_class;

typedef struct _folder_tilde {
    t_object x_obj;

    t_float x_threshold;
    t_float x_f;
    
    t_inlet *x_in_threshold;
    t_outlet*x_out;
    
} t_folder_tilde;

t_int *folder_tilde_perform(t_int *w)
{
    t_folder_tilde *x = (t_folder_tilde *) (w[1]);
    t_sample    *in =     (t_sample *) (w[2]);
    t_sample    *out =      (t_sample *) (w[3]);
    int            n =             (int) (w[4]);
    
    for(int i = 0; i < n; i++)
    {
        if (in [i] > x->x_threshold)
            out [i] = in [i] - (2 * (in [i] - x->x_threshold));
        else if (in [i] < - x->x_threshold)
            out [i] = in [i] - (2 * (in [i] + x->x_threshold));
    }
    
    return (w+5);
}

void folder_tilde_dsp(t_folder_tilde *x, t_signal **sp)
{
    dsp_add(folder_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void folder_tilde_free(t_folder_tilde *x)
{
    outlet_free(x->x_out);
}

void *folder_tilde_new(t_floatarg f)
{
    t_folder_tilde *x = (t_folder_tilde *)pd_new(folder_tilde_class);

    x->x_threshold = 1.0;
    x->x_f = 0;

    x->x_in_threshold = floatinlet_new(&x->x_obj, &x->x_threshold);
    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void folder_tilde_setup (void)
{
    folder_tilde_class = class_new(gensym("folder~"),
        (t_newmethod)folder_tilde_new,
        (t_method)folder_tilde_free,
        sizeof(t_folder_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);
    
    CLASS_MAINSIGNALIN (folder_tilde_class, t_folder_tilde, x_f);

    class_addmethod(folder_tilde_class,
      (t_method)folder_tilde_dsp, gensym("dsp"), A_CANT, 0);
}



