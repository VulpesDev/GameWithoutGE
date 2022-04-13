

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float rect(vec2 position, vec2 size, vec2 coord)
{
    size =  (0.5 - size) / 0.77;
    vec2 bl = step(vec2(size.x + position.x, size.y + position.y), coord);
    vec2 ur = step(vec2(size.x - position.x, size.y - position.y), 1. - coord);
    return bl.x * bl.y * ur.x * ur.y;
}

void main(){
    vec2 coord = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.964, 0.929, 0.862);

    color = mix(color, vec3(0.662, 0.129, 0.137), rect(vec2(-0.5,0.5), vec2(0.25,0.35), coord));
    color = mix(color, vec3(0.949, 0.682, 0.180), rect(vec2(0.5,0.5), vec2(0.15,0.35), coord));
    color = mix(color, vec3(0.011, 0.403, 0.650), rect(vec2(0.5,-0.5), vec2(0.35,0.2), coord));
    //Horizontal Lines
    color = mix(color, vec3(0.0, 0.0, 0.0), rect(vec2(0.5,-0.4), vec2(0.75,0.128), coord));
    color = mix(color, vec3(0.0, 0.0, 0.0), rect(vec2(0.5,0.18), vec2(0.9,0.128), coord));
    color = mix(color, vec3(0.0, 0.0, 0.0), rect(vec2(0.5,0.34), vec2(0.9,0.128), coord));
    //Vertical Lines
    color = mix(color, vec3(0.0, 0.0, 0.0), rect(vec2(0.44,0.18), vec2(0.128,0.9), coord));
    color = mix(color, vec3(0.0, 0.0, 0.0), rect(vec2(0.21,0.18), vec2(0.128,0.9), coord));
    color = mix(color, vec3(0.0, 0.0, 0.0), rect(vec2(-0.32,0.18), vec2(0.128,0.9), coord));
    color = mix(color, vec3(0.0, 0.0, 0.0), rect(vec2(-0.44,0.42), vec2(0.128,0.3), coord));

    gl_FragColor = vec4(color,1.0);
}
