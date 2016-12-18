float4x4	matWVP;
float4x4	matWV;
float		fFar;

struct VS_OUTPUT 
{
	float4 Posistion	: POSITION0;
	float4 Depth		: TEXCOORD0;
};

VS_OUTPUT vs_main( float4 Posistion : POSITION0 )
{
   VS_OUTPUT Output;
   Output.Posistion = mul( Posistion, matWVP );
   Output.Depth = mul( Posistion, matWV );
   return( Output );
}

float4 ps_main(VS_OUTPUT Input) : COLOR0
{   
	float4 color = Input.Depth.z / fFar;
	return( color );
}


//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 vs_main();
      PixelShader = compile ps_2_0 ps_main();
   }
}

