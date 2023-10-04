
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform float u_time; // Uniforme para controlar o tempo
uniform float u_music;
void main()
{
    vec2 fragCoord = gl_FragCoord.xy;

    float speed  = 5;
    // Define a quantidade de movimento com base no tempo e na velocidade
    float movement = 0.15 * sin(u_time * speed);

    // Ajusta a cor de todos os fragmentos, movendo todos da direita para a esquerda
    
    FragColor = vec4(ourColor + vec3(-movement, 0.0, 0.0), 1.0);
}


