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

*elm-type:* defines the geometrical type of the n-th element:

* 1: 2-node line.
* 2: 3-node triangle.
* 3: 4-node quadrangle.
* 4: 4-node tetrahedron.
* 5: 8-node hexahedron.
* 6: 6-node prism.
* 7: 5-node pyramid.
* 8: 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
* 9: 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
* 10: 9-node second order quadrangle (4 nodes associated with the vertices, 4 with the edges and 1 with the face).
* 11: 10-node second order tetrahedron (4 nodes associated with the vertices and 6 with the edges).
* 12: 27-node second order hexahedron (8 nodes associated with the vertices, 12 with the edges, 6 with the faces and 1 with the volume).
* 13: 18-node second order prism (6 nodes associated with the vertices, 9 with the edges and 3 with the quadrangular faces).
* 14: 14-node second order pyramid (5 nodes associated with the vertices, 8 with the edges and 1 with the quadrangular face).
* 15: 1-node point.
* 16: 8-node second order quadrangle (4 nodes associated with the vertices and 4 with the edges).
* 17: 20-node second order hexahedron (8 nodes associated with the vertices and 12 with the edges).
* 18: 15-node second order prism (6 nodes associated with the vertices and 9 with the edges).
* 19: 13-node second order pyramid (5 nodes associated with the vertices and 8 with the edges).



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