uniform float time;
uniform vec2 resolution;

void main() {
    // Calculate the color based on time and resolution
    vec2 p = (gl_FragCoord.xy / resolution.xy);
    vec3 col = vec3(0.0);

    // Create a dynamic gradient background
    col += 0.5 + 0.5 * cos(time + p.xyx + vec3(0, 2, 4));

    // Add a pulsating circle in the center
    vec2 center = vec2(0.5, 0.5);
    float radius = 0.2 + 0.1 * sin(time);
    float circle = smoothstep(radius, radius + 0.01, length(p - center));
    col += vec3(circle, circle, circle);

    // Add a moving, colorful wave pattern
    float wave = sin(p.x * 10.0 - time) * cos(p.y * 10.0 - time) * 0.2;
    col += vec3(abs(wave), abs(wave), abs(wave));

    // Output the final color
    gl_FragColor = vec4(col, 1.0);
}
