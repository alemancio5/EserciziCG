/**************
 Create the meshes, as described below
 
 WARNING!
 Since it is a C program, you can use for loops and functions if you think they can be helpful in your solution.
 However, please include all your code in this file, since it will be put in an automatic correction process
 for the final evaluation. Please also be cautious when using standard libraries and symbols, since they
 might not be available in all the development environments (especially, they might not be available
 in the final evaluation environment, preventing your code from compiling).
 This WARNING will be valid far ALL THE ASSIGNMENTs, but it will not be repeated in the following texts,
 so please remember these advices carefully!
 
***************/

void MakeSquare(float size, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices) {
// Creates a square, on the xz-plane, aligned with the axis, and centered in the origin.
// The length of the four sides is in parameter >size<.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a glm::vec3 element. 
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: this procedure has already been implemented. You can keep it as is
	vertices = {
				   {-size/2.0f,0.0f,-size/2.0f},
				   {-size/2.0f,0.0f, size/2.0f},
				   { size/2.0f,0.0f,-size/2.0f},
				   { size/2.0f,0.0f, size/2.0f}
    };
	indices = {0,1,2,   1,3,2};
}

void MakeCube(float size, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices) {
// Creates a cube, with the faces perpendicular to the axis, and centered in the origin.
// The length of one edge of the cube is >size<.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a glm::vec3 element. 
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a square. You can use it as a side of the cube (please remember
// to change the value of the y component, otherwise the result will be wrong
	vertices = {
				   {-size/2.0f, -size/2.0f, -size/2.0f},
				   {-size/2.0f, -size/2.0f, size/2.0f},
				   {size/2.0f, -size/2.0f, -size/2.0f},
				   {size/2.0f, -size/2.0f, size/2.0f},
                   {-size/2.0f, size/2.0f, -size/2.0f},
                   {-size/2.0f, size/2.0f, size/2.0f},
                   {size/2.0f, size/2.0f, -size/2.0f},
                   {size/2.0f, size/2.0f, size/2.0f}
    };
	indices = {1,0,2,   3,1,2,   1,3,7,   7,5,1,   5,7,6,   4,5,6,
               1,5,4,   0,1,4,   0,6,2,   6,0,4,   3,2,7,   6,7,2};
}

void MakeCylinder(float radius, float height, int slices, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices) {
// Creates a cylinder, approximated by a prism with a base composed by a regular polygon with >slices< sides.
// The radius of the cylinder is >radius<, and it height is >height<. The cylinder has its center
// in the origin, and spans half above and half below the plane that passes through the origin.
// The top and bottom caps are aligned with xz-plane and perpendicular to the y-axis.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a glm::vec3 element. 
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a rectangle. You have to change it, or you will obtain a wrong result
// You should use a for loop, and you should start from the procedure to create a circle seen during the lesson
    vertices.resize(slices+1 + slices+1);
    indices.resize(3*slices + 3*slices + 3*2*slices);
    vertices[slices]= {0.0f,-height/2.0f,0.0f};
    vertices[slices+slices+1]= {0.0f,height/2.0f,0.0f};

    for(int i = 0; i < slices; i++) {
        float ang = 2 * M_PI * (float) i / (float) slices;

        // Define vertices for bottom and up face
        vertices[i] = glm::vec3(radius * sin(ang), -height / 2.0f, radius * cos(ang));
        vertices[i + (slices + 1)] = glm::vec3(radius * sin(ang), height / 2.0f, radius * cos(ang));

        // Define indices for bottom circle
        indices[3 * i] = slices;
        indices[3 * i + 1] = (i + 1) % slices;
        indices[3 * i + 2] = i;

        // Define indices for up circle
        indices[3 * (i + slices)] = slices + slices + 1;
        indices[3 * (i + slices) + 1] = i + (slices + 1);
        indices[3 * (i + slices) + 2] =
                (i + 1 + slices + 1) % ((slices * 2) + 1);
        if (indices[3 * (i + slices) + 2] == 0)
            indices[3 * (i + slices) + 2] += slices + 1;

        // Define indices for lateral faces
        indices[3 * (i + (slices * 2))] = i;
        indices[3 * (i + (slices * 2)) + 1] = (i + 1) % slices;
        indices[3 * (i + (slices * 2)) + 2] = i + (slices + 1);

        indices[3 * (i + (slices * 3))] = (i + 1 + slices + 1) % ((slices * 2) + 1);
        indices[3 * (i + (slices * 3)) + 1] = i + (slices + 1);
        indices[3 * (i + (slices * 3)) + 2] = (i + 1) % slices;
        if (indices[3 * (i + (slices * 3))] == 0)
            indices[3 * (i + (slices * 3))] += slices + 1;
    }
}

void MakeCone(float radius, float height, int slices, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices) {
// Creates a cone, approximated by a pyramid with a base composed by a regular polygon with >slices< sides.
// The radius of the cone is >radius<, and it height is >height<. The cone has its centere
// in the origin, and spans half above and half below the plane that passes thorugh the origin.
// The bottom cap is aligned with xz-plane and perpendicular to the y-axis.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a glm::vec3 element. 
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a triangle. You have to change it, or you will obtain a wrong result
// You should use a for loop, and you should start from the procedure to create a circle seen during the lesson
    // Resize the vectors to accommodate vertices and indices
    vertices.resize(slices + 2); // One vertex for the tip, slices + 1 for the base
    indices.resize(3 * slices * 2); // Each triangle consists of the tip, base vertex, and next base vertex

    // Create vertices for the base of the cone
    for (int i = 0; i < slices; ++i) {
        float ang = 2 * M_PI * static_cast<float>(i) / static_cast<float>(slices);
        vertices[i] = glm::vec3(radius * cos(ang), -height / 2.0f, radius * sin(ang));
    }
    vertices[slices] = glm::vec3(0.0f, -height / 2.0f, 0.0f); // Center vertex of the base
    vertices[slices + 1] = glm::vec3(0.0f, height / 2.0f, 0.0f); // Tip vertex

    // Create indices for the triangles forming the base
    for (int i = 0; i < slices; ++i) {
        indices[3 * i] = slices; // Index of the center vertex of the base
        indices[3 * i + 1] = i;
        indices[3 * i + 2] = (i + 1) % slices;
    }

    // Create indices for the triangles forming the sides of the cone
    for (int i = 0; i < slices; ++i) {
        indices[3 * slices + i * 3] = slices + 1; // Index of the tip vertex
        indices[3 * slices + i * 3 + 1] = (i + 1) % slices;
        indices[3 * slices + i * 3 + 2] = i;
    }
}

void MakeSphere(float radius, int rings, int slices, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices)
{
// Creates a sphere, approximated by a poliedron composed by >slices<, and >rings< rings.
// The radius of the sphere is >radius<, and it is centered in the origin.
// The procedure should fill the array contained in the >vertices< parameter, with the positions of
// the vertices of the primitive, expressed with their local coordinates in a glm::vec3 element. 
// Indices should be returned in the >indices< array, starting from 0, and up to vertices.size()-1.
// The primitive is encoded as an indexed triangle list, so the size of the >indices< array, should
// be a multiple of 3: each group of three indices, defines a different triangle.
//
// HINT: the procedure below creates a circle. You have to change it, or you will obtain a wrong result
// You should use two nested for loops, one used to span across the rings, and the other that spans along
// the rings.
	vertices.resize(slices+1);
	indices.resize(3*slices);
	vertices[slices]= {0.0f,0.0f,0.0f};
	for(int i = 0; i < slices; i++) {
		float ang = 2*M_PI * (float)i / (float)slices;
		vertices[i] = glm::vec3(radius * cos(ang), radius * sin(ang), 0.0f);
		indices[3*i] = slices;
		indices[3*i+1] = i;
		indices[3*i+2] = (i+1) % slices;
	}

    vertices.resize((slices + 1) * (slices / 2 + 1));
    indices.resize(3 * slices * slices);

    for (int i = 0; i <= slices / 2; ++i) {
        float theta = M_PI * (float)i / (float)(slices / 2); // inclination angle from top (0) to bottom (pi)
        float y = radius * cos(theta);
        float r = radius * sin(theta);
        for (int j = 0; j <= slices; ++j) {
            float phi = 2 * M_PI * (float)j / (float)slices; // azimuthal angle
            vertices[i * (slices + 1) + j] = glm::vec3(r * sin(phi), y, r * cos(phi));
        }
    }

    for (int i = 0; i < slices / 2; ++i) {
        for (int j = 0; j < slices; ++j) {
            int a = i * (slices + 1) + j;
            int b = a + slices + 1;

            indices[6 * (i * slices + j)] = a;
            indices[6 * (i * slices + j) + 1] = b;
            indices[6 * (i * slices + j) + 2] = a + 1;

            indices[6 * (i * slices + j) + 3] = b;
            indices[6 * (i * slices + j) + 4] = b + 1;
            indices[6 * (i * slices + j) + 5] = a + 1;
        }
    }
}

