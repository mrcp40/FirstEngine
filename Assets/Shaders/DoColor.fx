// simple shader that takes positions and can add color

// need to know what information is in a vertex
struct VS_INPUT
{
	float3 position : POSITION;
    float4 color : COLOR;
};

// need a resulting set of data after processing the vertex
struct VS_OUTPUT
{
	float4 position : SV_Position;
    float4 color : COLOR;
};

// neeed a function to apply information to the vertex for every vertex
// 3D Graphics and Applications, this is the primitives manager
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = float4(input.position, 1.0f);
    output.color = input.color;
	return output;
}

// need a function to apply the color of a pixel
float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color;
}