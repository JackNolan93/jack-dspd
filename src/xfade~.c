#include "m_pd.h"

static t_class *xfade_tilde_class;

typedef struct _xfade_tilde {
      t_object x_obj;
      t_float x_pan;
      t_float f;

      t_inlet *x_in2;
      t_inlet *x_in3;
      t_outlet*x_out;
} t_xfade_tilde;

t_int *xfade_tilde_perform (t_int *w)
{
    t_sample    *in1 =      (t_sample *)(w[2]);
    t_sample    *in2 =      (t_sample *)(w[3]);
    t_sample    *out =      (t_sample *)(w[5]);
    int            n =             (int)(w[6]);
    t_float     *pan =       (t_float *)(w[4]);
    int i;
    
    for(i = 0; i < n; i++)
    {
        out [i] = in1 [i] * (1 - pan [i]) + in2 [i] * pan [i];
    }

    return (w+7);
}

void xfade_tilde_dsp (t_xfade_tilde *x, t_signal **sp)
{
    dsp_add(xfade_tilde_perform, 6, x,
        sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);
}

void xfade_tilde_free (t_xfade_tilde *x)
{
    inlet_free (x->x_in2);
    inlet_free (x->x_in3);

    outlet_free (x->x_out);
}

void *xfade_tilde_new (t_floatarg f)
{
    t_xfade_tilde *x = (t_xfade_tilde *) pd_new (xfade_tilde_class);

    x->x_pan = 0.0;

    x->x_in2 = inlet_new (&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->x_in3 = inlet_new (&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);

    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void xfade_tilde_setup(void) {
  xfade_tilde_class = class_new(gensym("xfade~"),
        (t_newmethod) xfade_tilde_new,
        (t_method) xfade_tilde_free,
        sizeof (t_xfade_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, 0);

  class_addmethod (xfade_tilde_class,
      (t_method) xfade_tilde_dsp, gensym ("dsp"), A_CANT, 0);

  CLASS_MAINSIGNALIN (xfade_tilde_class, t_xfade_tilde, f);
}
