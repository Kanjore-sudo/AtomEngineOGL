#include "vertexShader.hlsl"
float4 PS_main(PS_INPUT input) : SV_Target
{
    return input.Color;
}