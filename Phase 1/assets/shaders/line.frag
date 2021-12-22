#version 330 core

out vec4 frag_color;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);
uniform float intercept = 0;
uniform float slope = 1.0;

void main()
{
    // calculating the max y-coordinate for the line 
    float y_coordinate = slope * gl_FragCoord.x + intercept;
    // compares the y-coordinate of the vertex to the max y-coordinate of the line
    if (gl_FragCoord.y <= y_coordinate)
    // if it's less than the lines, then the point is beneath the line, change its color to inside color
        frag_color = inside_color;
    else
    // else the point is above the line, change its color to outside color

        frag_color = outside_color;
}