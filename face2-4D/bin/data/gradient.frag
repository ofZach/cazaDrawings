
uniform vec2 ptToFadeFrom1;
uniform vec2 ptToFadeFrom2;
uniform vec2 ptToFadeFrom3;

void main(){
    float dist1 = distance(ptToFadeFrom1, gl_FragCoord.xy);
    float dist2 = distance(ptToFadeFrom2, gl_FragCoord.xy);
    float dist3 = distance(ptToFadeFrom3, gl_FragCoord.xy);
    
    // smoothstep...
    float pct1 = 1.0 - dist1 / 100.0;
    if (pct1 < 0.0) pct1 = 0.0;
    
    float pct2 = 1.0 - dist2 / 100.0;
    if (pct2 < 0.0) pct2 = 0.0;

    float pct3 = 1.0 - dist3 / 100.0;
    if (pct3 < 0.0) pct3 = 0.0;

    //    pct = pow(pct, 0.1);
    //vec2 ss = vec2(gl_FragCoord.x / resolution.x, gl_FragCoord.y/resolution.y);
    
    // hotspots don't overlap we can just add them, otherwise need to develop this out
    gl_FragColor = vec4( vec3( (pct1+pct2+pct3)*0.6 + 0.2), 1.0);
//    gl_FragColor = vec4( vec3(0.2), 1.0);
  // toggle between (ss, k, 1.0) & (ss, 0.0, 1.0)
}