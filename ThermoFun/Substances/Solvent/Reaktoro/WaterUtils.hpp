// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2015 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// Reaktoro includes (modified DM 11.05.2016)
#include <Common/ScalarTypes.hpp>
#include "Common/ThermoScalar.hpp"

namespace ThermoFun {

/// Calculate the density of water using the Haar-Gallagher-Kell (1984) equation of state
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @return The density of water (in units of kg/m3)
auto waterDensityHGK(Reaktoro_::Temperature T, Reaktoro_::Pressure P, int state) -> Reaktoro_::ThermoScalar;

/// Calculate the density of water using the Wagner and Pruss (1995) equation of state
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @return The density of water (in units of kg/m3)
auto waterDensityWagnerPruss(Reaktoro_::Temperature T, Reaktoro_::Pressure P, int state) -> Reaktoro_::ThermoScalar;

/// Calculate the pressure of water using the Haar-Gallagher-Kell (1984) equation of state
/// @param T The temperature of water (in units of K)
/// @param D The density of water (in units of kg/m3)
/// @return The pressure of water (in units of Pa)
auto waterPressureHGK(Reaktoro_::Temperature T, Reaktoro_::ThermoScalar D) -> Reaktoro_::ThermoScalar;

/// Calculate the pressure of water using the Wagner and Pruss (1995) equation of state
/// @param T The temperature of water (in units of K)
/// @param D The density of water (in units of kg/m3)
/// @return The pressure of water (in units of Pa)
auto waterPressureWagnerPruss(Reaktoro_::Temperature T, Reaktoro_::ThermoScalar D) -> Reaktoro_::ThermoScalar;

/// Calculate the saturated pressure of water using the Wagner and Pruss (1995) equation of state
/// @param T The temperature of water (in units of K)
/// @return The saturated pressure of water (in units of Pa)
auto waterSaturatedPressureWagnerPruss(Reaktoro_::Temperature T) -> Reaktoro_::ThermoScalar;

/// Calculate the saturated liquid-density of water using the Wagner and Pruss (1995) equation of state
/// @param T The temperature of water (in units of K)
/// @return The saturated liquid-density of water (in units of kg/m3)
auto waterSaturatedLiquidDensityWagnerPruss(Reaktoro_::Temperature T) -> Reaktoro_::ThermoScalar;

/// Calculate the saturated vapour-density of water using the Wagner and Pruss (1995) equation of state
/// @param T The temperature of water (in units of K)
/// @return The saturated vapour-density of water (in units of kg/m3)
auto waterSaturatedVapourDensityWagnerPruss(Reaktoro_::Temperature T) -> Reaktoro_::ThermoScalar;

} // namespace Reaktoro

namespace ThermoFun
{
// Forward declarations
struct PropertiesSolvent;

auto waterIdealGas (Reaktoro_::Temperature t, ThermoFun::PropertiesSolvent &wp) -> void;

}
