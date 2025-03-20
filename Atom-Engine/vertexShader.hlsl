struct VS_INPUT
{
    float3 Position : POSITION;

    float4 Color : COLOR;
};

struct PS_INPUT
{
    float4 Position : POSITION;
    float4 Color : COLOR;
};

PS_INPUT VS_main(VS_INPUT input)
{
    PS_INPUT output;
    output.Position = float4(input.Position, 1.0f);
    output.Color = input.Color;
    return output;
}