#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our
{

#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    class Mesh
    {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO, VAO;

        // Vertex Buffer Object: data of the vertices
        // Element Buffer Object: data of the indices of those vertices (3 in our case)
        // Vertex Array Object: pointers to the attributes of those vertices (colors and other attributes set by glVertexAttribPointer)

        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;

    public:
        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            // For the attribute locations, we use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

            // Create a vertex array object and 'bind' (select) it
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // Create a vertex buffer and bind it so we can then fill it with the vertices' data
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
            // GL_ARRAY_BUFFER: Vertex attributes
            // vertices.size() * sizeof(Vertex): size of the buffer's data in bytes
            // &vertices.front(): pointer to the first element of the buffer's data
            // GL_STATIC_DRAW: the data will only be modified once, by the application, and used as a source for GL drawing commands

            // Similarly for the element buffer
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), &elements.front(), GL_STATIC_DRAW);
            // GL_ELEMENT_ARRAY_BUFFER: Vertex array indices

            // Set the position attribute locations
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
            // ATTRIB_LOC_POSITION: index of attribute to be modified
            // 3: number of components of the attribute
            // GL_FLOAT: data type of each component attribute
            // GL_FALSE: whether the data should be normalized (i.e. divided by MAX to get 0 to 1 or -1 to 1)
            // sizeof(Vertex): offset between consecutive attribute occurrences in the buffer, in bytes
            // (void *)offsetof(Vertex, position): offset of the attribute in the buffer, in bytes

            // Enable the position attribute using its location
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);

            // Similarly for other attributes
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);

            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);

            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);

            // Unbind the vertex array object and the buffers
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // Store the number of elements in "elementCount" since it will be needed for drawing
            elementCount = (GLsizei)elements.size();
        }

        // this function should render the mesh
        void draw()
        {
            // Bind the vertex array object
            glBindVertexArray(VAO);

            // How did it know the EBO to draw?

            // Draw the mesh
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
            // GL_TRIANGLES: primitive type to be rendered
            // elementCount: number of elements to be rendered
            // GL_UNSIGNED_INT: data type of the indices
            // 0: offset of the first index to be read

            // Unbind the vertex array object
            glBindVertexArray(0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            // Delete the vertex array, vertex buffer and element buffer
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}