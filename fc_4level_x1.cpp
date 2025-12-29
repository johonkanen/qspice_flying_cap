// Automatically generated C++ file on Sun Dec 28 09:08:33 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD fc_4level_x1.cpp kernel32.lib

#include <cmath>
union uData
{
   bool b;
   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i;
   unsigned int ui;
   float f;
   double d;
   long long int i64;
   unsigned long long int ui64;
   char *str;
   unsigned char *bytes;
};

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef gate1
#undef gate2
#undef gate3
#undef gate4
#undef gate5
#undef gate6
#undef gate7
#undef gate8

double pwm = 0;
double pwm_prev = 1;
double dt = 0;
double prev_t = 0;
double dt_count = 0;

extern "C" __declspec(dllexport) void fc_4level_x1(void **opaque, double t, union uData *data)
{
   double &gate1 = data[0].d; // output
   double &gate2 = data[1].d; // output
   double &gate3 = data[2].d; // output
   double &gate4 = data[3].d; // output
   double &gate5 = data[4].d; // output
   double &gate6 = data[5].d; // output
   double &gate7 = data[6].d; // output
   double &gate8 = data[7].d; // output

// Implement module evaluation code here:

    double carrier = std::fmod(t, 1e-6)*1e6;
    double bridge_voltage_ref = 50.0;
    double timestep = 0;
    if (t > 0.0)
        timestep = t - prev_t;

    if (t > 10.0e-3)
    {
        bridge_voltage_ref = 100.0;
    }

    double duty = bridge_voltage_ref/200.0;

    if ((carrier > (0.5-duty/2.0)) && (carrier < (0.5+duty/2.0)))
    {
        pwm = 5;

    } else
    {
        pwm = 0;

    }
    gate1 = pwm;
    gate2 = pwm;
    gate3 = pwm;
    gate4 = pwm;
    gate5 = 5-pwm;
    gate6 = 5-pwm;
    gate7 = 5-pwm;
    gate8 = 5-pwm;

    if (dt_count >= 0)
    {
        dt_count = dt_count - timestep;
    }

    if (pwm_prev != pwm )
    {
        dt_count = 10.0e-9;

    // if (dt_count >= 0.0)
    // {
        gate1 = 0;
        gate2 = 0;
        gate3 = 0;
        gate4 = 0;
        gate5 = 0;
        gate6 = 0;
        gate7 = 0;
        gate8 = 0;
    // }
    }

    pwm_prev = pwm;
    prev_t = t;

}
