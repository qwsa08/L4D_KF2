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
// Bullet
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Bullet_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 mWVP : WorldViewProjection;
float4x4 mWV : WorldView;


struct VS_OUTPUT
{
   float4 Pos   :POSITION;
   float4 ClipPos :TEXCOORD0;
};

VS_OUTPUT Bullet_Pass_0_Vertex_Shader_vs_main(float4 Pos:POSITION)
{
   VS_OUTPUT Out = (VS_OUTPUT)0;
   Out.Pos = mul(Pos,mWVP);
   Out.ClipPos = mul(Pos,mWV);
   
   return Out;
}


texture texSamp_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\bullethole_snow.tga";
>;
sampler2D DiffuseSample = sampler_state
{
   Texture = (texSamp_Tex);
};
texture base_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\base.tga";
>;
sampler2D DepthMapSamp = sampler_state
{
   Texture = (base_Tex);
};
float3 CameraRightTop;
float4x4 mInvProj : ProjectionInverse;
float gFar : FarClipPlane;
float4x4 mInvWV : WorldViewInverse;

struct PS_INPUT
{
   float4 ClipPos     :TEXCOORD0;
};

float4 Bullet_Pass_0_Pixel_Shader_ps_main(PS_INPUT In):COLOR
{
   
   
   float4 col = float4(1.0,0.0,0.0,0.0);
   float4 ClipPos = In.ClipPos.z / gFar;
   ClipPos.x = ClipPos.x *0.5 + 0.5;
   ClipPos.y = -ClipPos.y *0.5 + 0.5;
   
   float depth = tex2D(DepthMapSamp,ClipPos.xy).r;
   float4 h = float4(ClipPos.x *2 -1 ,(1- ClipPos.y)*2-1,depth,1);
   float4 d = mul(h,mInvProj);
   float4 viewPos = d/gFar;
   
   float4 ObjPos = mul(viewPos,mInvWV);
   float3 ObjAbs = abs(ObjPos.xyz / ObjPos.w);
   clip(0.5 - ObjAbs);
   
   float2 uv = ObjPos.zx + 0.5;
   col = tex2D(DiffuseSample,uv);
   
   float dist = abs(ObjPos.z);
   float scaleDistance = max(dist * 2.0f, 1.0f);
   float fadeOut = 1.0f - scaleDistance;
   col.a *= fadeOut;
   
   col *= (1.f - max((ObjAbs.z-0.25f)/0.25,0.f));
   return col;
   
  }
//--------------------------------------------------------------//
// Technique Section for Bullet
//--------------------------------------------------------------//
technique Bullet
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Bullet_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Bullet_Pass_0_Pixel_Shader_ps_main();
   }

}

