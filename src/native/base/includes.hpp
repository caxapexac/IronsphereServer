#ifndef LOGIC_INCLUDES_HPP
#define LOGIC_INCLUDES_HPP

#include "constants.hpp"
#include "constants_requests.hpp"
#include "constants_responses.hpp"
#include "constants_values.hpp"
#include "errors.hpp"
#include "interfaces.hpp"
#include "third_party_includes.hpp"

#include "../utils/json_tools.hpp"
using json_tools = nlohmann::json_tools;

/// For the sake of readability. This freaking language just doesn't support attributes.
/// God damn I'm creating serialization without reflection
/// Path to clearing your soul:
/// Learn c++
/// Break up with a girl
/// Make useless define
#define N_S /*Non serialized*/
#define OBSOLETE /*Obsolete*/
/// *You are here*
/// <doctype=html />
/// Delet yuself
/// Epik vin


#endif //LOGIC_INCLUDES_HPP
