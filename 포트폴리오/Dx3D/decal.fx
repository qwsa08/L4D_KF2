float4x4	matWVP;
float4x4	matInvWorldView;
float4		CameraRightTop;

texture DepthMapTex;
sampler2D DepthMapSamp = sampler_state
{
	Texture = (DepthMapTex);
};

texture DecalTex;
sampler2D DiffuseSamp = sampler_state
{
	Texture = (DecalTex);
};

struct VS_OUTPUT 
{
	float4 Posistion	: POSITION0;
	float4 ClipPos		: TEXCOORD0;
};

VS_OUTPUT vs_main( float4 Posistion : POSITION0 )
{
   VS_OUTPUT Output;
   
   Output.ClipPos = mul( Posistion, matWVP );
   Output.Posistion = Output.ClipPos;
   return( Output );
}

float4 ps_main ( VS_OUTPUT In ) : COLOR
{
	float4 color = float4(1.0,0.0,0.0,0.0);

	float2 screenPosition = In.ClipPos.xy / In.ClipPos.w;

	float2 depth_uv = screenPosition.xy * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);
	
	float sceneDepth = tex2D( DepthMapSamp, depth_uv ).r;

	float3 ViewRay = float3( lerp(-CameraRightTop.xy, CameraRightTop.xy, depth_uv ), CameraRightTop.z );

	float4 ViewPos = float4( ViewRay.xyz * sceneDepth, 1.0 );
	
	float4 ObjPos = mul( ViewPos, matInvWorldView );

	float3 ObjAbs = abs(ObjPos.xyz / ObjPos.w);
	clip( 0.5 - ObjAbs );
	

	float2 uv = ObjPos.xz + 0.5;
	color = tex2D( DiffuseSamp, uv );
	
	//float dist = abs(ObjPos.z);
	//float scaleDistance = max(dist * 2.0f, 1.0f); 
	//float fadeOut = 1.0f - scaleDistance;
	//color.a *= fadeOut;
	
	//color *= ( 1.f - max( (ObjAbs.z-0.25f)/0.25, 0.f) );
	
	return color;
	
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

