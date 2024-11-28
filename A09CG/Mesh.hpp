

/**************
 Creae the meshes, as described below
 
 WARNING!
 Since it is a C program, you can use for loops and functions if you think they can be helpful in your solution.
 However, please include all your code in this file, since it will be put in an automatic correction process
 for the final evaluation. Please also be cautious when using standard libraries and symbols, since they
 might not be available in all the development environments (especially, they might not be available
 in the final evaluation environment, preventing your code from compiling).
 This WARNING will be valid far ALL THE ASSIGNMENTs, but it will not be repeated in the following texts,
 so please remember these advices carefully!
 
***************/

void MakeSquare(float size, std::vector<std::array<float,6>> &vertices, std::vector<uint32_t> &indices) {
// Creates a square, on the xz-plane, aligned with the axis, and centered in the origin.
// The length of the four sides is in parameter >size<.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a std::array<float,6> element.
// In particular, the first three elements (index 0,1,2) encode the position of the vertex (x in index 0,
// y in index 1, and z in index 2). The second set of three elements (index 3,4,5) encode the direction
// of the normal vector for the considerd vertex (N.x in index 3, N.y in index 4, and N.z in index 5).
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: this procedure has already been implemented. You can keep it as is
	vertices = {
				   {-size/2.0f,0.0f,-size/2.0f,0.0f,1.0f,0.0f},
				   {-size/2.0f,0.0f, size/2.0f,0.0f,1.0f,0.0f},
				   { size/2.0f,0.0f,-size/2.0f,0.0f,1.0f,0.0f},
				   { size/2.0f,0.0f, size/2.0f,0.0f,1.0f,0.0f}};
	indices = {0, 1, 2,    1, 3, 2};
}

void MakeCube(float size, std::vector<std::array<float,6>> &vertices, std::vector<uint32_t> &indices) {
// Creates a cube, with the faces perpendicular to the axis, and centered in the origin.
// The length of one edge of the cube is >size<.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a std::array<float,6> element.
// In particular, the first three elements (index 0,1,2) encode the position of the vertex (x in index 0,
// y in index 1, and z in index 2). The second set of three elements (index 3,4,5) encode the direction
// of the normal vector for the considerd vertex (N.x in index 3, N.y in index 4, and N.z in index 5).
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a square. You can use it as a side of the cube (please remember
// to change the value of the y component, otherwise the result will be wrong

    float halfSize = size / 2.0f;

    vertices = {
            // Front face
            {-halfSize, -halfSize,  halfSize,  0.0f,  0.0f,  1.0f},
            { halfSize, -halfSize,  halfSize,  0.0f,  0.0f,  1.0f},
            { halfSize,  halfSize,  halfSize,  0.0f,  0.0f,  1.0f},
            {-halfSize,  halfSize,  halfSize,  0.0f,  0.0f,  1.0f},

            // Back face
            {-halfSize, -halfSize, -halfSize,  0.0f,  0.0f, -1.0f},
            { halfSize, -halfSize, -halfSize,  0.0f,  0.0f, -1.0f},
            { halfSize,  halfSize, -halfSize,  0.0f,  0.0f, -1.0f},
            {-halfSize,  halfSize, -halfSize,  0.0f,  0.0f, -1.0f},

            // Left face
            {-halfSize, -halfSize, -halfSize, -1.0f,  0.0f,  0.0f},
            {-halfSize,  halfSize, -halfSize, -1.0f,  0.0f,  0.0f},
            {-halfSize,  halfSize,  halfSize, -1.0f,  0.0f,  0.0f},
            {-halfSize, -halfSize,  halfSize, -1.0f,  0.0f,  0.0f},

            // Right face
            { halfSize, -halfSize, -halfSize,  1.0f,  0.0f,  0.0f},
            { halfSize,  halfSize, -halfSize,  1.0f,  0.0f,  0.0f},
            { halfSize,  halfSize,  halfSize,  1.0f,  0.0f,  0.0f},
            { halfSize, -halfSize,  halfSize,  1.0f,  0.0f,  0.0f},

            // Top face
            {-halfSize,  halfSize, -halfSize,  0.0f,  1.0f,  0.0f},
            { halfSize,  halfSize, -halfSize,  0.0f,  1.0f,  0.0f},
            { halfSize,  halfSize,  halfSize,  0.0f,  1.0f,  0.0f},
            {-halfSize,  halfSize,  halfSize,  0.0f,  1.0f,  0.0f},

            // Bottom face
            {-halfSize, -halfSize, -halfSize,  0.0f, -1.0f,  0.0f},
            { halfSize, -halfSize, -halfSize,  0.0f, -1.0f,  0.0f},
            { halfSize, -halfSize,  halfSize,  0.0f, -1.0f,  0.0f},
            {-halfSize, -halfSize,  halfSize,  0.0f, -1.0f,  0.0f}
    };

    // Define the indices for the cube (6 faces, 2 triangles per face, 3 vertices per triangle)
    indices = {
            0, 1, 2,  2, 3, 0,   // Front face
            4, 6, 5,  6, 4, 7,   // Back face
            9, 8, 10, 11, 10, 8, // Left face
            15, 12, 14, 13, 14, 12, // Right face
            17, 16, 18, 19, 18, 16, // Top face
            23, 20, 22, 21, 22, 20  // Bottom face
    };
}

void MakeCylinder(float radius, float height, int slices, std::vector<std::array<float,6>> &vertices, std::vector<uint32_t> &indices) {
// Creates a cylinder, approximated by a prism with a base composed by a regular polygon with >slices< sides.
// The radius of the cylinder is >radius<, and it height is >height<. The cylinder has its centere
// in the origin, and spans half above and half below the plane that passes thorugh the origin.
// The top and bottom caps are are aligned with xz-plane and perpendicular to the y-axis.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a std::array<float,6> element.
// In particular, the first three elements (index 0,1,2) encode the position of the vertex (x in index 0,
// y in index 1, and z in index 2). The second set of three elements (index 3,4,5) encode the direction
// of the normal vector for the considerd vertex (N.x in index 3, N.y in index 4, and N.z in index 5).
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a rectangle. You have to change it, or you will obtain a wrong result
// You should use a for loop, and you should start from the procedure to create a circle seen during the lesson

    float halfHeight = height / 2.0f;
    float angleStep = 2 * M_PI / slices;

    // Top and bottom center points
    vertices.push_back({0.0f, halfHeight, 0.0f, 0.0f, 1.0f, 0.0f}); // Top center
    vertices.push_back({0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f}); // Bottom center

    // Generate vertices for the top and bottom circles
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // Top circle vertex
        vertices.push_back({x, halfHeight, z, 0.0f, 1.0f, 0.0f});

        // Bottom circle vertex
        vertices.push_back({x, -halfHeight, z, 0.0f, -1.0f, 0.0f});

        // Side vertices
        vertices.push_back({x, halfHeight, z, x, 0.0f, z});
        vertices.push_back({x, -halfHeight, z, x, 0.0f, z});
    }

    // Create indices for the top and bottom faces
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;

        // Top face (clockwise order)
        indices.push_back(0);
        indices.push_back(2 + 4 * next);
        indices.push_back(2 + 4 * i);

        // Bottom face (counterclockwise order)
        indices.push_back(1);
        indices.push_back(3 + 4 * i);
        indices.push_back(3 + 4 * next);
    }

    // Create indices for the side faces
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;

        // First triangle
        indices.push_back(4 + 4 * i);
        indices.push_back(4 + 4 * next);
        indices.push_back(5 + 4 * i);

        // Second triangle
        indices.push_back(5 + 4 * i);
        indices.push_back(4 + 4 * next);
        indices.push_back(5 + 4 * next);
    }
}

void MakeCone(float radius, float height, int slices, std::vector<std::array<float,6>> &vertices, std::vector<uint32_t> &indices) {
// Creates a cone, approximated by a pyramid with a base composed by a regular polygon with >slices< sides.
// The radius of the cone is >radius<, and it height is >height<. The cone has its centere
// in the origin, and spans half above and half below the plane that passes thorugh the origin.
// The bottom cap is aligned with xz-plane and perpendicular to the y-axis.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a std::array<float,6> element.
// In particular, the first three elements (index 0,1,2) encode the position of the vertex (x in index 0,
// y in index 1, and z in index 2). The second set of three elements (index 3,4,5) encode the direction
// of the normal vector for the considerd vertex (N.x in index 3, N.y in index 4, and N.z in index 5).
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a triangle. You have to change it, or you will obtain a wrong result
// You should use a for loop, and you should start from the procedure to create a circle seen during the lesson

    float halfHeight = height / 2.0f;
    float angleStep = 2 * M_PI / slices;

    // Top vertex of the cone
    vertices.push_back({0.0f, halfHeight, 0.0f, 0.0f, 0.0f, 0.0f}); // Apex

    // Bottom center vertex
    vertices.push_back({0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f}); // Center of base

    // Generate vertices for the base circle
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // Base circle vertex
        vertices.push_back({x, -halfHeight, z, 0.0f, -1.0f, 0.0f});

        // Side vertex with normal
        float nx = x / sqrt(x * x + z * z);
        float nz = z / sqrt(x * x + z * z);
        vertices.push_back({x, -halfHeight, z, nx, radius / height, nz});
    }

    // Create indices for the base face
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;

        // Base face (clockwise order)
        indices.push_back(1);
        indices.push_back(2 + 2 * i);
        indices.push_back(2 + 2 * next);
    }

    // Create indices for the side faces
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;

        // Side face (clockwise order)
        indices.push_back(0); // Apex
        indices.push_back(3 + 2 * next); // Next base vertex
        indices.push_back(3 + 2 * i); // Current base vertex
    }
}

void MakeSphere(float radius, int rings, int slices, std::vector<std::array<float,6>> &vertices, std::vector<uint32_t> &indices)
{
// Creates a sphere, approximated by a poliedron composed by >slices<, and >rings< rings.
// The radius of the sphere is >radius<, and it is centered in the origin.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a std::array<float,6> element.
// In particular, the first three elements (index 0,1,2) encode the position of the vertex (x in index 0,
// y in index 1, and z in index 2). The second set of three elements (index 3,4,5) encode the direction
// of the normal vector for the considerd vertex (N.x in index 3, N.y in index 4, and N.z in index 5).
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a circle. You have to change it, or you will obtain a wrong result
// You should use two nested for loops, one used to span across the rings, and the other that spans along
// the rings.

    for (int i = 0; i <= rings; ++i) {
        float theta = i * M_PI / rings;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int j = 0; j <= slices; ++j) {
            float phi = j * 2 * M_PI / slices;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;

            std::array<float, 6> vertex = { radius * x, radius * y, radius * z, x, y, z };
            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < rings; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first = (i * (slices + 1)) + j;
            int second = first + slices + 1;

            // Rearrange indices to ensure correct face orientation
            indices.push_back(first);
            indices.push_back(first + 1);
            indices.push_back(second);

            indices.push_back(second);
            indices.push_back(first + 1);
            indices.push_back(second + 1);
        }
    }
}
