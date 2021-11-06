#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the side-length

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main(){
    vec2 pos = gl_FragCoord.xy - center; //calculate the manhattan distance and save in vec pos 
    if (abs(pos.x) + abs(pos.y) <= sideLength/2) frag_color = outside_color; //check that the point is within the manhattan distance 
    //and half the sidelength and color the point accordingly
    else frag_color = inside_color;
}