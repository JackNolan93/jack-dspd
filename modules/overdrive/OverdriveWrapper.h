#include <Effects/overdrive.h>

extern "C" void * OverdriveCreate ()
{
   return new daisysp::Overdrive ();
}

extern "C" void OverdriveRelease (void * object)
{
    delete static_cast<daisysp::Overdrive *> (object);
}

extern "C" void OverdriveInit (void * object)
{
    static_cast <daisysp::Overdrive *> (object)->Init ();
}

extern "C" float OverdriveProcess (void * object, float in)
{
    return static_cast <daisysp::Overdrive *> (object)->Process (in);
}

extern "C" void OverdriveSetDrive (void * object, float drive)
{
    static_cast <daisysp::Overdrive *> (object)->SetDrive (drive);
}

