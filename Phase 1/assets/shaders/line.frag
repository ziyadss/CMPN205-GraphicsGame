#version 330 core

out vec4 frag_color;

uniform float slope = 1.0;
uniform float intercept = 0.0;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    float y = slope * gl_FragCoord.x + intercept;
    
    // If point's height y-coordinate is less than or equal to y, set color to inside color
    frag_color = (gl_FragCoord.y <= y) ? inside_color : outside_color;
}