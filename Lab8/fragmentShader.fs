#version 330 core

in vec4 color;
out vec4 FragColor;
uniform bool changeColorFromMain = false;
uniform vec4 colorFromMain;

void main()
{
    vec4 finalColor;
    if(changeColorFromMain == false)
        finalColor = color;
     else
        finalColor = colorFromMain;


    FragColor = finalColor;
}