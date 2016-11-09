#ifndef REACTION_H
#define REACTION_H

// C++ includes
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace TCorrPT {

class ThermoPropertiesReaction;
class ThermoParametersReaction;

/**
 * @brief The Reaction class is a type used to describe a reaction
 */
class Reaction
{
public:
    /// Constrcut a default Reaction instance
    Reaction();

    /// Construct a copy of an Reaction instance
    Reaction(const Reaction& other);

    /// Assign an Reaction instance to this instance
    auto operator=(Reaction other) -> Reaction&;

    /// Destroy this instance
    virtual ~Reaction();

    // Set functions
    /// Set the name of the Reaction.
    auto setName(std::string name) -> void;

    auto setReactants(std::map<std::string, int> reactants) -> void;

    auto setReferenceT(double T) -> void;

    auto setReferenceP(double P) -> void;

//    /// Set the formula of the Reaction.
//    auto setFormula(std::string formula) -> void;

//    /// Set the name of the reaction that defines the Reaction properties.
//    auto setReaction(std::string reaction) -> void;

    // Get functions
    /// Return the name of the chemical Reaction
    auto name() const -> std::string;

    auto reactants() -> std::map<std::string, int>;

    auto thermo_ref_prop() -> ThermoPropertiesReaction;

    auto thermo_parameters() -> ThermoParametersReaction;

    auto referenceT() const -> double;

    auto referenceP() const -> double;

//    /// Return the formula of the chemical Reaction
//    auto formula() const -> std::string;


private:
    struct Impl;

    std::unique_ptr<Impl> pimpl;
};

} // namespace TCorrPT

#endif // REACTION_H
