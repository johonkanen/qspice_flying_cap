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

typedef struct t_gates
{
    double hi;
    double lo;
};

t_gates c_gates_off = {.hi = 0.0, .lo = 0.0};

std::vector<double> pwm(4, 0.0);
std::vector<double> pwm_prev(4, 0.0);
std::vector<double> dt_count(4, 0.0);

double dt       = 0;
double prev_t   = 0;

extern "C" __declspec(dllexport) void fc_4level_x1(void **opaque, double t, union uData *data)
{

    double &Udc   = data[0].d; // input
    double &gate1 = data[1].d; // output
    double &gate2 = data[2].d; // output
    double &gate3 = data[3].d; // output
    double &gate4 = data[4].d; // output
    double &gate5 = data[5].d; // output
    double &gate6 = data[6].d; // output
    double &gate7 = data[7].d; // output
    double &gate8 = data[8].d; // output
    double &iload = data[9].d; // output

    double &test1 = data[10].d; // output
    double &test2 = data[11].d; // output
    double &test3 = data[12].d; // output
    double &test4 = data[13].d; // output

    double timestep = 0.0;
    if (t > 0.0) timestep = t - prev_t; // needed for initial count

    double bridge_voltage_ref = 180.0;
    double deadtime = 20.0e-9;

    double duty = 172.0/200.0;

    //--------------------------------
    const int number_of_carriers = 3;
    std::vector<t_gates> gates(number_of_carriers, c_gates_off);
    std::vector<double> phase(number_of_carriers, 0.0);
    std::vector<double> carrier(number_of_carriers, 0.0);

    // phase[0] = 0.07;

    double sw_frequency = 250e3/number_of_carriers;
    double sw_period = 1/sw_frequency;

    for (int i = 0; i < number_of_carriers; ++i) {

        double lower_bound = 0.5-duty/2.0;
        double upper_bound = 0.5+duty/2.0;

        carrier[i] = std::fmod(t + sw_period * i / (double)number_of_carriers + sw_period*phase[i], sw_period) / sw_period;
        pwm[i] = ((carrier[i] > lower_bound) && (carrier[i] < upper_bound)) ? 5.0 : 0.0;

        if (dt_count[i] >= 0.0)
        {
            dt_count[i] = dt_count[i] - timestep;
        }

        if (pwm_prev[i] != pwm[i] )
        {
            dt_count[i] = deadtime;
        }

        if (dt_count[i] >= 0.0)
        {
            gates[i] = c_gates_off;
        } else
        {
            gates[i].hi = pwm[i];
            gates[i].lo = 5.0-pwm[i];
        }
    }
    //--------------------------------
    iload = 10.0;
    if (t > 50e-3) iload = -10.0;
    if (t > 80e-3) iload = 0.0;

    Udc = 200.0;
    if (t > 5e-3)
    {
        Udc = 170.0;
    }


    gate1 = gates[0].hi;
    gate2 = gates[0].hi;
    gate3 = gates[1].hi;
    gate4 = gates[2].hi;

    gate5 = gates[2].lo;
    gate6 = gates[1].lo;
    gate7 = gates[0].lo;
    gate8 = gates[0].lo;

    test1 = carrier[0] * 5.0;
    test2 = carrier[1] * 5.0;
    test3 = carrier[2] * 5.0;
    test4 = carrier[2] * 5.0;

    pwm_prev = pwm;
    prev_t = t;

}
