void main() {
    gl_FrontColor   = gl_Color;
    gl_Position     = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    gl_TexCoord[0]  = gl_MultiTexCoord0;
}
