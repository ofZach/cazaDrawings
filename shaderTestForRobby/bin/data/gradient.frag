
uniform vec2 ptToFadeFrom;

void main()
{
 

    float dist = distance(ptToFadeFrom, gl_FragCoord.xy);
    
    // smoothstep...
    float pct = 1.0 - dist / 200.0;
    if (pct < 0.0) pct = 0.0;
    pct = pow(pct, 0.1);
    //vec2 ss = vec2(gl_FragCoord.x / resolution.x, gl_FragCoord.y/resolution.y);
  gl_FragColor = vec4( vec3(pct*0.5 + 0.5), 1.0);
  // toggle between (ss, k, 1.0) & (ss, 0.0, 1.0)
}