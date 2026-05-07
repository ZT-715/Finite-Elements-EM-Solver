# Finite Elements Solver

Solves meshes described with the [.msh version 2](https://gmsh.info/doc/texinfo/gmsh.html#MSH-file-format-version-2-_0028Legacy_0029) file format, created with the meshing software [Gmsh](https://gmsh.info/doc/texinfo/gmsh.html/).

To generate version 2 .msh files on the current Gmsh version 4, or greater, go to `Files -> Export -> Mesh .msh -> Version 2 ASCII` and mark the `Save all elements` option.

## Mesh Files

The expected format follows the structure described in [Gmsh Documentation §10.3.1](https://gmsh.info/doc/texinfo/gmsh.html#MSH-file-format-version-2-_0028Legacy_0029):

```msh
version-number file-type data-size
$EndMeshFormat
$Nodes
number-of-nodes
node-number x-coord y-coord z-coord
…
$EndNodes
$Elements
number-of-elements
elm-number elm-type number-of-tags < tag > … node-number-list
…
$EndElements
```
### Example
```msh
$MeshFormat
2.2 0 8
$EndMeshFormat
$Nodes
6                  six mesh nodes:
1 0.0 0.0 0.0        node #1: coordinates (0.0, 0.0, 0.0)
2 1.0 0.0 0.0        node #2: coordinates (1.0, 0.0, 0.0)
3 1.0 1.0 0.0        etc.
4 0.0 1.0 0.0
5 2.0 0.0 0.0
6 2.0 1.0 0.0
$EndNodes
$Elements
2                  two elements:
1 3 2 99 2 1 2 3 4   quad #1: type 3, phys 99, ent 2, nodes 1 2 3 4
2 3 2 99 2 2 5 6 3   quad #2: type 3, phys 99, ent 2, nodes 2 5 6 3
$EndElements
```