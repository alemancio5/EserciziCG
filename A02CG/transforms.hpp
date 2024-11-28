

void SetTransform(A02 *A) {
/**************
 Using A->SetMatrix(i, M, focus) where:
 i -> index of the matrix to set (0 .. 14)
 M -> transform matrix to use
 focus -> true if you want to add the focus to that piece (only one please)
 
 solve the puzzle. Piece 0 is already in place, and the correct transform to put in place piece 1, is
 the identity matrix. Find the correct transformations to place the other 13 pieces (i = 2..14).
 The suggestion is to work on the pieces one at a time, setting the focus to the one you are working on.
 The piece with the focus, will be displayed in red. Moreover, its origin, and the orientation and size
 of its axis will be shown. This is necessary because not all the pieces have their center in the origin,
 but remember that the transformations, assumes that the center is in the origin. Some pieces (especially
 the ones with a high index) will require a combination of transformations, since the transform is not
 centered with the origin or the main axes.
 
 WARNING!
 Since it is a C program, you can use for loops and functions if you think they can be helpful in your solution.
 However, please include all your code in this file, since it will be put in an automatic correction process
 for the final evaluation. Please also be cautious when using standard libraries and symbols, since they
 might not be available in all the development environments (especially, they might not be available
 in the final evaluation environment, preventing your code from compiling).
 This WARNING will be valid far ALL THE ASSIGNMENTs, but it will not be repeated in the following texts,
 so please remember these advices carefully!
 
***************/
	glm::mat4 M;

	// this is the only one in place, and that should not be modified
	M = glm::mat4(1.0f);
	A->SetMatrix(0,  M, false);

	// this is an example on how to highlight a piece and move it.
	// to put it in place, just replace the following line with an identity matrix,
	// that is: A->SetMatrix(0,  M, false);
	// M = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f, 0.0f, -1.6f)), glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::mat4(1.0f);
	A->SetMatrix(1,  M, false);

	// FROM THIS POINT ON, you have to find the correct transform to solve the puzzle.
	M = glm::translate(glm::scale(glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(-2.0f, 0.0f, -1.0f));
	A->SetMatrix(2,  M, false);

    M = glm::translate(glm::rotate(glm::radians(-15.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
    A->SetMatrix(3,  M, false);

    M = glm::translate(glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(-2.0f, -0.1f, 1.0f));
	A->SetMatrix(4,  M, false);
	
	M = glm::translate(glm::vec3(4.0f, 0.0f, 4.0f));
	A->SetMatrix(5,  M, false);
	
	M = glm::translate(glm::scale(glm::vec3(2.0f, 1.0f, 1.25f)), glm::vec3(0.0f, 0.0f, -1.0f));
	A->SetMatrix(6,  M, false);
	
	M = glm::translate(glm::shearZ3D(glm::mat4(1.0f), -0.5f, 0.0f), glm::vec3(2.0f, 0.0f, -1.0f));
	A->SetMatrix(7,  M, false);

    M =  glm::shearZ3D(glm::mat4(1.0f), -0.051f, 0.0f) * glm::rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 2.0f, 0.0f)) * glm::rotate(glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(2.5f, 1.0f, 1.0f)) *
            glm::rotate(glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::shearX3D(glm::mat4(1.0f), 0.0f, -0.25f) * glm::translate(glm::vec3(-0.35f, 0.0f, 0.4f)) * glm::scale(glm::vec3(0.98f, 1.0f, 1.25f)) *
            glm::shearZ3D(glm::mat4(1.0f), -0.05f, 0.0f) * glm::scale(glm::vec3(1.0f, 1.0f, 0.98f)) * glm::translate(glm::vec3(0.0f, 0.0f, 0.011f)) * glm::scale(glm::vec3(1.0f, 1.0f, 1.01f));
    A->SetMatrix(8,  M, false);
	
	M = glm::mat4(1.0f);
	A->SetMatrix(9,  M, false);
	
	M = glm::translate(glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)), glm::vec3(-1.0f, 1.0f, 1.5f));
	A->SetMatrix(10, M, false);

    M = glm::translate(glm::rotate(glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(-2.7,2,-0.88));
    A->SetMatrix(11, M, false);
	
	M = glm::translate(glm::rotate(glm::scale(glm::vec3(1.0f, 1.0f, 0.5f)), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 2.0f, 0.0f));
	A->SetMatrix(12, M, false);

	M = glm::translate(glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(-0.92f, -0.708f, 0.91f));
	A->SetMatrix(13, M, false);
	
	M = glm::translate(glm::rotate(glm::radians(-210.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(2.23f, 2.00f, 0.13f));
	A->SetMatrix(14, M, false);
}
