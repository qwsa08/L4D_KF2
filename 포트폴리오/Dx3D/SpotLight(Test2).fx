//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// NormalMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string NormalMapping_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gWorldViewProjectionMatrix : WorldViewProjection;

float4 gWorldLightPosition;
float4 gWorldCameraPosition;

float4 gFlashLight;

float4 gFlashLightDirection
<
   string UIName = "gFlashLightDirection";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 0.00, -1.00, 0.00, 1.00 );
float4 gLightDirection
<
   string UIName = "gLightDirection";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 );

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;
   float3 mTangent: TANGENT;
   float3 mBinormal: BINORMAL;
   float2 mUV: TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
   float2 mUV: TEXCOORD0;
   float3 mLightDir : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
   
   float3 mFlashDir : TEXCOORD6;
  
   float4 mPos : TEXCOORD7;
};

VS_OUTPUT NormalMapping_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul( Input.mPosition, gWorldViewProjectionMatrix );
   Output.mUV = Input.mUV;

   float4 worldPosition = mul( Input.mPosition, gWorldMatrix );
   float3 WorldlightDir = gLightDirection;
   Output.mLightDir = normalize(WorldlightDir);
   
   float3 FlashLightDir = gFlashLightDirection;
   Output.mFlashDir = normalize(FlashLightDir);
   
   float3 viewDir = normalize(gFlashLightDirection);
   Output.mViewDir = viewDir;
   
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   Output.N = normalize(worldNormal);
   
   float3 worldTangent = mul(Input.mTangent, (float3x3)gWorldMatrix );
   Output.T = normalize(worldTangent);
   
   float3 worldBinormal = mul(Input.mBinormal, (float3x3)gWorldMatrix );
   Output.B = normalize(worldBinormal);
   
   Output.mPos = mul(worldPosition, gViewMatrix);
   //Output.mPos = Output.mPosition;
   
   return Output;
}




struct PS_INPUT
{
   float4 mPosition : POSITION;
   float2 mUV : TEXCOORD0;
   float3 mLightDir : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
   
   float3 mFlashDir : TEXCOORD6;
   
   float4 mPos : TEXCOORD7;
};

texture DiffuseMap_Tex
<
   string ResourceName = ".\\Map\\maps\\cs_havana_texture_0.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture SpecularMap_Tex
<
   string ResourceName = ".\\Map\\maps\\SpacularMap\\cs_havana_texture_0_SPEC.png";
>;
sampler2D SpecularSampler = sampler_state
{
   Texture = (SpecularMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture NormalMap_Tex
<
   string ResourceName = ".\\Map\\maps\\NomalMaps\\cs_havana_texture_0_NRM.png";
>;
sampler2D NormalSampler = sampler_state
{
   Texture = (NormalMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};

float3 gLightColor
<
   string UIName = "gLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 1.00, 1.00 );
float3 gFlashColor
<
   string UIName = "gFlashColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 1.00, 1.00 );

float4 gFlashLightCenter
<
   string UIName = "gFlashLightCenter";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 0.00, 0.00, 0.00, 1.00 );
float gFlashLightRange
<
   string UIName = "gFlashLightRange";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 100.00 );

float4 NormalMapping_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float3 tangentNormal = tex2D(NormalSampler, Input.mUV).xyz;
   tangentNormal = normalize(tangentNormal * 2 - 1);
   
   float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   TBN = transpose(TBN);
   float3 worldNormal = mul(TBN, tangentNormal);
   
   float4 albedo1 = tex2D(DiffuseSampler, Input.mUV);
   float3 lightDir1 = normalize(Input.mLightDir);
   float3 diffuse1 = saturate(dot(worldNormal, -lightDir1));
   diffuse1 = gLightColor * albedo1.rgb * diffuse1;
   
   float3 specular1 = 0;
   if ( diffuse1.x > 0 )
   {
      float3 reflection = reflect(lightDir1, worldNormal);
      float3 viewDir = normalize(Input.mViewDir); 

      specular1 = saturate(dot(reflection, -viewDir ));
      specular1 = pow(specular1, 20.0f);
      
      float4 specularIntensity  = tex2D(SpecularSampler, Input.mUV);
      specular1 *= specularIntensity.rgb * gLightColor;
   }
   float3 ambient1 = float3(0.1f, 0.1f, 0.1f) * albedo1;
   
   //=======================================================
   
   float4 albedo2 = tex2D(DiffuseSampler, Input.mUV);
   float3 ambient2 = float3(0.1f, 0.1f, 0.1f) * albedo2;
   float3 lightDir2 = normalize(Input.mFlashDir); 
   float3 diffuse2 = saturate(dot(worldNormal, -lightDir2));
   
   float Length = length(Input.mPos - gFlashLightCenter);
   
   if(Length > gFlashLightRange) 
      diffuse2 = 0.f;
      
   else  
      diffuse2 = gFlashColor * albedo2.rgb * diffuse2;
   
   float3 specular2 = 0;
   if ( diffuse2.x > 0 )
   {
      float3 reflection = reflect(lightDir2, worldNormal);
      float3 viewDir = normalize(Input.mViewDir); 

      specular2 = saturate(dot(reflection, -viewDir ));
      specular2 = pow(specular2, 20.0f);
      
      float4 specularIntensity  = tex2D(SpecularSampler, Input.mUV);
      specular2 *= specularIntensity.rgb * gFlashColor;
   }
   
   return float4(ambient1 + diffuse1 + specular1, 1) 
   + float4(ambient2 + diffuse2 + specular2, 1);
}

//--------------------------------------------------------------//
// Technique Section for NormalMapping
//--------------------------------------------------------------//
technique NormalMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 NormalMapping_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 NormalMapping_Pass_0_Pixel_Shader_ps_main();
   }

}

