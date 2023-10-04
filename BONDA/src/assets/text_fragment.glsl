//#version 330 core
//out vec4 FragColor;
//  
//in vec3 ourColor;
//in vec2 TexCoord;
//
//uniform sampler2D ourTexture;
//
//void main()
//{
//    FragColor = texture(ourTexture, TexCoord);
//}


#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float u_time;  // Uniforme para controlar o tempo
uniform int u_bonda;
void main()
{
 
    
    float speed = 5;
    float amplitude = 0.005; 
    // Calcula o deslocamento horizontal baseado no tempo e na velocidade
    float displacement = amplitude * sin(u_time * speed);

    // Ajusta as coordenadas de textura para criar o movimento
    vec2 offset = vec2(displacement, 0.0);
    vec2 adjustedTexCoord = TexCoord + offset;

    // Certifique-se de que as coordenadas de textura não ultrapassem 0.0 e 1.0
    adjustedTexCoord = clamp(adjustedTexCoord, 0.0, 1.0);

    // Amostra a textura usando as coordenadas de textura ajustadas

    if(u_bonda == 0){
        FragColor = texture(ourTexture, TexCoord);
    }
    else{
        FragColor = texture(ourTexture, adjustedTexCoord);
    }
}
