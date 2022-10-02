#include <Effects/reverbsc.h>

extern "C" void * ReverbScCreate ()
{
   return new daisysp::ReverbSc ();
}

extern "C" void ReverbScRelease (void * object)
{
    delete static_cast<daisysp::ReverbSc *> (object);
}

extern "C" void ReverbScInit (void * object, float sampleRate)
{
    static_cast <daisysp::ReverbSc *> (object)->Init (sampleRate);
}

extern "C" float ReverbScProcess (void * object, float in1, float * out1, float * out2)
{
    return static_cast <daisysp::ReverbSc *> (object)->Process (in1, in1, out1, out2);
}

extern "C" void ReverbScSetFreq (void * object, float frequency)
{
    static_cast <daisysp::ReverbSc *> (object)->SetLpFreq (frequency);
}

 extern "C" void ReverbScSetFeedback (void * object, float feedback)
 {
     static_cast <daisysp::ReverbSc *> (object)->SetFeedback (feedback);
 }

