#include "SolidMurnaghanHP98.h"

namespace TCorrPT {

auto thermoPropertiesMinMurnaghanEOSHP98(Reaktoro::Temperature t, Reaktoro::Pressure p, Substance subst, ThermoPropertiesSubstance tps) -> ThermoPropertiesSubstance
{
    auto Pst = subst.referenceP() / bar_to_Pa; // in bar
    auto Tst = subst.referenceT(); // in K
    auto Vst = subst.thermoReferenceProperties().volume; // j/bar
    auto T   = t;
    auto P = p / bar_to_Pa; // in bar
    auto P_Pst = P - Pst;
    auto T_Tst = T -Tst;
//    auto Ts2   = Tst*Tst;
//    auto T05   = sqrt(T);
//    auto Tst05 = sqrt(Tst);
    auto k0 = subst.thermoParameters().isothermal_compresibility; // bulk modulus k in kbar at 298 K
    auto a0 = subst.thermoParameters().isobaric_expansivity; // in 1/K

    if ((P_Pst != 0 || T_Tst !=0 ) && fabs(Vst.val) > 1e-09 && fabs(a0) > 1e-09 && fabs(k0) > 1e-09)
    {
        auto PP = P/1000.;  // P is used in kbar in HP98
//        aW.twp->Alp = a0 * (1. - 10./pow(T,0.5) );  // expansion at T
        auto kap = k0 * ( 1. - (1.5e-4)*(T-Tst) );
//        aW.twp->Bet = 1./PP * (1. - pow( (1.- 4.*PP/(kap + 4.*PP )), 0.25 ));  // compressibility at T (to check)
        auto Vt = Vst * (1.+ a0*(T-Tst)-20.*a0*(pow(T,0.5)-pow(Tst,0.5)) );

        // increment thermodynamic properties
        auto dg = ( (1./3.)*Vt*kap*(pow((1.+4.*PP/kap),0.75 )- 1.) * (1000.) );
        auto ds = ( - ( (Vst*kap/3.)*(a0-10.*a0*pow(T,-0.5)) * (pow((1.+4.*PP/kap),0.75)-1.)
                   - (Vt*k0/3.)*(1.5e-4) * (pow((1.+4.*PP/kap),0.75)-1.)
                   + Vt*PP*(1.5e-4)/(1.-(1.5e-4)*(T-Tst)) * pow((1.+4.*PP/kap),(-0.25)) ) * (1000.) );
        auto dh = dg + T*ds;
        auto dv = ( Vt*pow( (1.- 4.*PP/(kap + 4.*PP )),0.25 ));
        auto dcp = - T * ( (5./3.)*Vst*a0*kap/pow(T,1.5) * (pow((1.+4.*PP/kap),0.75)-1.)
                    - (2./3.)*Vst*(a0-10.*a0/pow(T,0.5))*k0*(1.5e-4) * (pow((1.+4*PP/kap),0.75)-1.)
                    + 2.*Vst*(a0-10.*a0/pow(T,0.5))*PP*(1.5e-4) / (1.-(1.5e-4)*(T-Tst)) * pow((1.+4.*PP/kap),(-0.25))
                    - Vt*pow(PP,2.)*pow((1.5e-4),2.) / ( pow((1.-(1.5e-4)*(T-Tst)),3.)*k0 )
                    * pow((1.+4*PP/kap),(-1.25)) ) * (1000.);

        tps.gibbs_energy     += dg;
        tps.entropy          += ds;
        tps.enthalpy         += dh;
        tps.volume           += dv;
        tps.heat_capacity_cp += dcp;


    } else // Molar volume assumed independent of T and P
    {
        tps.volume           = Vst;
        tps.gibbs_energy    += Vst * P_Pst;
        tps.enthalpy        += Vst * P_Pst;
        tps.internal_energy  = tps.enthalpy - P*tps.volume;
        tps.helmholtz_energy = tps.internal_energy - (T+273.15)*tps.entropy;
    }
    return tps;
}

}