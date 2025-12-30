// Automatically generated C++ file on Tue Dec 30 07:26:04 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD fc_4level_x1.cpp kernel32.lib


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
#undef Udc

#include <cmath>
#include <vector>

std::vector<double> pwm(4, 0.0);
std::vector<double> pwm_prev(4, 0.0);

double dt       = 0;
double prev_t   = 0;
double dt_count = 0;

// class pwm_modulator
//
typedef struct t_gates
{
    double hi;
    double lo;
};

extern "C" __declspec(dllexport) void fc_4level_x1(void **opaque, double t, union uData *data)
{

    double  Udc   = data[0].d; // input
    double &gate1 = data[1].d; // output
    double &gate2 = data[2].d; // output
    double &gate3 = data[3].d; // output
    double &gate4 = data[4].d; // output
    double &gate5 = data[5].d; // output
    double &gate6 = data[6].d; // output
    double &gate7 = data[7].d; // output
    double &gate8 = data[8].d; // output

    double timestep = 0.0;
    if (t > 0.0) timestep = t - prev_t; // needed for initial count

    t_gates gates = {.hi = 0.0, .lo = 0.0};

    double sw_frequency = 500e3;
    double sw_period = 1/sw_frequency;
    
    double bridge_voltage_ref = 50.0;
    double deadtime = 10.0e-9;

    if (t > 10.0e-3)
    {
        bridge_voltage_ref = 100.0;
    }

    double duty = bridge_voltage_ref/200.0;
    double lower_bound = 0.5-duty/2.0;
    double upper_bound = 0.5+duty/2.0;

    double carrier[4];
    for (int i = 0; i < 4; ++i) {
        carrier[i] = std::fmod(t + sw_period * i / 4.0, sw_period) / sw_period;
        pwm[i] = ((carrier[i] > lower_bound) && (carrier[i] < upper_bound)) ? 5.0 : 0.0;
    }

    if (dt_count >= 0.0)
    {
        dt_count = dt_count - timestep;
    }

    if (pwm_prev[0] != pwm[0] )
    {
        dt_count = deadtime;
    }

    if (dt_count >= 0.0)
    {
        gates.hi = 0.0; gates.lo=0.0;
    } else 
    {
        gates.hi = pwm[0]; gates.lo = 5.0-pwm[0];
    }

    gate1 = 
    gate2 = 
    gate3 = 
    gate4 = gates.hi;

    gate5 = 
    gate6 = 
    gate7 = 
    gate8 = gates.lo;

    pwm_prev = pwm;
    prev_t = t;

}
