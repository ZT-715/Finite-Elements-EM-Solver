//
// Created by Gabriel Zanella on 08/05/26.
//

#pragma once

#include <vector>
#include <set>
#include <array>
#include <filesystem>

namespace ifrs::parser {

using point_t = std::array<double, 3>;
using Node = std::pair<size_t, point_t>;

enum ElementType {
    UNKNOWN = 0,

    // First-order elements
    LINE            = 1,   // 2-node line
    TRIANGLE        = 2,   // 3-node triangle
    QUAD            = 3,   // 4-node quadrangle
    TETRA           = 4,   // 4-node tetrahedron
    HEXA            = 5,   // 8-node hexahedron
    PRISM           = 6,   // 6-node prism
    PYRAMID         = 7,   // 5-node pyramid

    // Second-order elements
    LINE2           = 8,   // 3-node second-order line
    TRIANGLE2       = 9,   // 6-node second-order triangle
    QUAD2           = 10,  // 9-node second-order quadrangle
    TETRA2          = 11,  // 10-node second-order tetrahedron
    HEXA2           = 12,  // 27-node second-order hexahedron
    PRISM2          = 13,  // 18-node second-order prism
    PYRAMID2        = 14,  // 14-node second-order pyramid

    // Special elements
    POINT           = 15,  // 1-node point

    // Reduced second-order elements
    QUAD2_SERENDIPITY   = 16, // 8-node second-order quadrangle
    HEXA2_SERENDIPITY   = 17, // 20-node second-order hexahedron
    PRISM2_SERENDIPITY  = 18, // 15-node second-order prism
    PYRAMID2_SERENDIPITY= 19  // 13-node second-order pyramid
};

    // String conversion
    constexpr  std::string to_string(const ElementType& value)
    {
        switch (value) {
            case ElementType::LINE:                  return "LINE";
            case ElementType::TRIANGLE:              return "TRIANGLE";
            case ElementType::QUAD:                  return "QUAD";
            case ElementType::TETRA:                 return "TETRA";
            case ElementType::HEXA:                  return "HEXA";
            case ElementType::PRISM:                 return "PRISM";
            case ElementType::PYRAMID:               return "PYRAMID";

            case ElementType::LINE2:                 return "LINE2";
            case ElementType::TRIANGLE2:             return "TRIANGLE2";
            case ElementType::QUAD2:                 return "QUAD2";
            case ElementType::TETRA2:                return "TETRA2";
            case ElementType::HEXA2:                 return "HEXA2";
            case ElementType::PRISM2:                return "PRISM2";
            case ElementType::PYRAMID2:              return "PYRAMID2";

            case ElementType::POINT:                 return "POINT";

            case ElementType::QUAD2_SERENDIPITY:     return "QUAD2_SERENDIPITY";
            case ElementType::HEXA2_SERENDIPITY:     return "HEXA2_SERENDIPITY";
            case ElementType::PRISM2_SERENDIPITY:    return "PRISM2_SERENDIPITY";
            case ElementType::PYRAMID2_SERENDIPITY:  return "PYRAMID2_SERENDIPITY";

            default:                    return "UNKNOWN";
        }
    }

// elm-number elm-type number-of-tags < tag > … node-number-list
class Element {
    size_t _id = 0;
    ElementType _type = ElementType::UNKNOWN;
    size_t _num_of_tags = 0;
    std::vector<int> _tags; // Tags may be zero or negative "ghost tags"
    std::vector<size_t> _nodes;
    public:

    Element() = default;
    auto& number()  { return this->_id; }
    auto& type()  { return this->_type; }
    auto& num_of_tags()  { return this->_num_of_tags; }
    auto& tags()  { return this->_tags; }
    auto& nodes()  { return this->_nodes; }
    ~Element() = default;
};

class ParseMsh {
    public:
        enum class ParserState;

        ParseMsh(const std::filesystem::path& filepath);

        /**
        * Aquire defined nodes from msh
        */
        std::vector<Node> get_nodes() const;

        /**
        * Elements from the msh
        */
        std::vector<Element> get_elements() const;

    private:
      Node parse_node(const std::string& line);
      Element parse_element(const std::string& line);
      static ParserState parse_state(const std::string& input);

      std::vector<Node> nodes;
      std::vector<Element> elements;
};

} // ifparser

