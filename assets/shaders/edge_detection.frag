uniform vec2 i_resolution;
uniform sampler2D i_tex_base;

in vec2 vertTexCoord0;
out vec4 fragColor;

//vec4 CannySearch(vec4 thresh)
//{

//  // magdir holds { dx, dy, mag, direct }



//  vec4 magdir = texture(i_tex_base, vertTexCoord0);

//  float alpha = 0.5/sin(3.14159/8); // eight directions on grid

//  vec2 offset = round( vec2(alpha) * magdir.xy/magdir.zz );

//  vec4 fwdneighbour, backneighbour;

//  fwdneighbour = texture(i_tex_base, vertTexCoord0 + offset );

//  backneighbour = texture(i_tex_base, vertTexCoord0 + offset );



//  vec4 colorO;

//  if ( fwdneighbour.z > magdir.z || backneighbour.z > magdir.z )

//    colorO = vec4(0.0, 0.0, 0.0, 0.0); // not an edgel



//  else

//    colorO = vec4(1.0, 1.0, 1.0, 1.0); // is an edgel

//  if ( magdir.z < thresh.x )

//    colorO  = vec4(0.0, 0.0, 0.0, 0.0); // thresholding



//  return colorO;

//}

//void main() 
//{
//  fragColor = CannySearch(vec4(0.4f));
//}

//mat3 sx = mat3( 
//    1.0, 2.0, 1.0, 
//    0.0, 0.0, 0.0, 
//   -1.0, -2.0, -1.0 
//);
//mat3 sy = mat3( 
//    1.0, 0.0, -1.0, 
//    2.0, 0.0, -2.0, 
//    1.0, 0.0, -1.0 
//);

//void main()
//{
//    vec3 diffuse = texture(i_tex_base, vertTexCoord0.st).rgb;
//    mat3 I;
//    for (int i=0; i<3; i++) {
//        for (int j=0; j<3; j++) {
//            vec3 sample  = texelFetch(i_tex_base, ivec2(gl_FragCoord) + ivec2(i-1,j-1), 0 ).rgb;
//            I[i][j] = length(sample); 
//		}
//	}

//	float gx = dot(sx[0], I[0]) + dot(sx[1], I[1]) + dot(sx[2], I[2]); 
//	float gy = dot(sy[0], I[0]) + dot(sy[1], I[1]) + dot(sy[2], I[2]);

//	float g = sqrt(pow(gx, 2.0)+pow(gy, 2.0));
//	fragColor = vec4(diffuse - vec3(g), 1.0);
//} 

vec2 texel = vec2(1.0 / i_resolution.x, 1.0 / i_resolution.y);
mat3 G[9];
// hard coded matrix values!!!! as suggested in https://github.com/neilmendoza/ofxPostProcessing/blob/master/src/EdgePass.cpp#L45
const mat3 g0 = mat3( 0.3535533845424652, 0, -0.3535533845424652, 0.5, 0, -0.5, 0.3535533845424652, 0, -0.3535533845424652 );
const mat3 g1 = mat3( 0.3535533845424652, 0.5, 0.3535533845424652, 0, 0, 0, -0.3535533845424652, -0.5, -0.3535533845424652 );
const mat3 g2 = mat3( 0, 0.3535533845424652, -0.5, -0.3535533845424652, 0, 0.3535533845424652, 0.5, -0.3535533845424652, 0 );
const mat3 g3 = mat3( 0.5, -0.3535533845424652, 0, -0.3535533845424652, 0, 0.3535533845424652, 0, 0.3535533845424652, -0.5 );
const mat3 g4 = mat3( 0, -0.5, 0, 0.5, 0, 0.5, 0, -0.5, 0 );
const mat3 g5 = mat3( -0.5, 0, 0.5, 0, 0, 0, 0.5, 0, -0.5 );
const mat3 g6 = mat3( 0.1666666716337204, -0.3333333432674408, 0.1666666716337204, -0.3333333432674408, 0.6666666865348816, -0.3333333432674408, 0.1666666716337204, -0.3333333432674408, 0.1666666716337204 );
const mat3 g7 = mat3( -0.3333333432674408, 0.1666666716337204, -0.3333333432674408, 0.1666666716337204, 0.6666666865348816, 0.1666666716337204, -0.3333333432674408, 0.1666666716337204, -0.3333333432674408 );
const mat3 g8 = mat3( 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408 );

void main(void) {

	G[0] = g0,
	G[1] = g1,
	G[2] = g2,
	G[3] = g3,
	G[4] = g4,
	G[5] = g5,
	G[6] = g6,
	G[7] = g7,
	G[8] = g8;

	mat3 I;
	float cnv[9];
	vec3 samp;

	/* fetch the 3x3 neighbourhood and use the RGB vector's length as intensity value */
	for (float i=0.0; i<3.0; i++) {
		for (float j=0.0; j<3.0; j++) {
			samp = texture(i_tex_base, vertTexCoord0 + texel * vec2(i-1.0,j-1.0) ).rgb;
			I[int(i)][int(j)] = length(samp);
		}
	}

	/* calculate the convolution values for all the masks */
	for (int i=0; i<9; i++) {
		float dp3 = dot(G[i][0], I[0]) + dot(G[i][1], I[1]) + dot(G[i][2], I[2]);
		cnv[i] = dp3 * dp3;
	}

	float M = (cnv[0] + cnv[1]) + (cnv[2] + cnv[3]);
	float S = (cnv[4] + cnv[5]) + (cnv[6] + cnv[7]) + (cnv[8] + M);

	fragColor = vec4(vec3(sqrt(M/S)), texture( i_tex_base, vertTexCoord0).a );

}
