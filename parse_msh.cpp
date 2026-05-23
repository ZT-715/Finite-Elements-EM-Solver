//
// Created by Gabriel Zanella on 08/05/26.
//

#include "parse_msh.hpp"

#include <fstream>
#include <iostream>
#include <cstdlib>

namespace ifrs::parser {

    enum class ParseMsh::ParserState {
        UNKNOWN,
        NODES,
        ELEMENTS
    };


    enum ElementState {
        ID = 0,
        TYPE,
        TAG_COUNT,
        TAGS,
        NODES,
        END
    };


    ParseMsh::ParserState
    ParseMsh::parse_state(const std::string& input) {
        if (input == "$Nodes")
            return ParseMsh::ParserState::NODES;
        else if (input == "$Elements")
            return ParseMsh::ParserState::ELEMENTS;
        else
            return ParseMsh::ParserState::UNKNOWN;
    }

    ParseMsh::ParseMsh(const std::filesystem::path& path) {
        std::ifstream file;
        file.open(path, std::ios_base::in);
        if (!file.is_open()) {
            std::printf("Failed to open file %s\n", path.string().c_str());
            return;
        }

        ParserState state = ParserState::UNKNOWN;
        bool first_value = false;
        for (std::string line; std::getline(file, line);) {
            if (line.empty()) continue;
            if (line[0] == '$')
            {
                state = parse_state(line);
                first_value = true;
                continue;
            }

            switch (state) {
                case ParseMsh::ParserState::NODES:
                {
                    if (first_value)
                    {
                        size_t node_total = std::stoi(line);
                        std::printf("Numero de nós: %lu\n", node_total);
                        nodes.resize(node_total);
                        first_value = false;
                        continue;
                    }
                    Node node = parse_node(line);
                    nodes.emplace_back(node);
                    std::printf("Node %s\n", line.c_str());
                    std::printf("id: %lu x: %f y: %f z: %f\n", node.first, node.second[0], node.second[1], node.second[2]);
                    break;
                }
                case ParseMsh::ParserState::ELEMENTS:
                {
                    if (first_value)
                    {
                        size_t element_total = std::stoi(line);
                        std::printf("Numero de elements: %lu\n", element_total);
                        elements.resize(element_total);
                        first_value = false;
                        continue;
                    }
                    std::printf("Element %s\n", line.c_str());
                    auto element = parse_element(line);
                    elements.emplace_back(element);
                    break;
                }
                default:
                {
                    break;
                }

            }
        }
    }

    Node ParseMsh::parse_node(const std::string& input) {
        std::array<double, 4> coord;

        size_t count = 0UL;
        std::string::size_type last_split = 0;
        while (last_split != std::string::npos) {
            auto next_split = input.find_first_of(' ', last_split + 1);
            auto result = std::atof(input.substr(last_split, next_split - last_split).c_str());
            coord[count] = result;
            last_split = next_split;
            count++;
        }

        return Node{static_cast<size_t>(coord[0]), {coord[1], coord[2], coord[3]}};
    }

    Element ParseMsh::parse_element(const std::string &input)
    {
        Element result;

        size_t tag_count = 0UL;

        std::string::size_type last_split = 0;
        ElementState state = ElementState::ID;
        while (last_split != std::string::npos) {
            auto next_split = input.find_first_of(' ', last_split + 1);
            switch (state)
            {
                case ElementState::ID:
                {
                    result.number() = std::stoul(input.substr(last_split, next_split - last_split));
                    state = ElementState::TYPE;

                    std::printf("id: %lu  ", result.number());

                    break;
                }
                case ElementState::TYPE:
                {
                    result.type() = ElementType(std::stoi(input.substr(last_split, next_split - last_split)));
                    state = ElementState::TAG_COUNT;

                    std::printf("type: %s  ", to_string(result.type()).c_str());
                    break;
                }
                case ElementState::TAG_COUNT:
                {
                    result.num_of_tags() = std::stoul(input.substr(last_split, next_split - last_split));
                    result.tags().resize(result.num_of_tags() + 2);
                    state = ElementState::TAGS;

                    std::printf("num. of tags: %lu  ", result.num_of_tags());
                    break;
                }
                case ElementState::TAGS:
                {
                    result.tags().at(tag_count) = std::stoi(input.substr(last_split, next_split - last_split));
                    if (tag_count >= result.num_of_tags()) state = ElementState::NODES;

                    std::printf("tag %lu: %i  ", tag_count, result.tags().back());
                    tag_count++;
                    break;
                }
                case ElementState::NODES:
                {
                    size_t node_id = std::stoul(input.substr(last_split, next_split - last_split));
                    result.nodes().emplace_back(node_id);
                    auto node_count = result.nodes().size();
                    if (next_split == std::string::npos) state = ElementState::END;
                    std::printf("node %lu: %lu  ", node_count, node_id);
                    break;
                }
                default:
                    break;
            }

            last_split = next_split;
        }
        printf("\n");

        return result;
    }

} // ifparser