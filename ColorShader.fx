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
// ColorShader
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//

struct VS_INPUT
{
   float4 mPosition : POSITION;
};

struct VS_OUTPUT
{
   float4 mPosition : POSITION;
};

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjectionMatrix;
float4	gColor = float4(0.0f, 1.0f, 0.0f, 1.0f);

VS_OUTPUT VS(VS_INPUT Input)
{
   VS_OUTPUT Output;
   
   Output.mPosition = mul(Input.mPosition, gWorldMatrix);
   Output.mPosition = mul(Output.mPosition, gViewMatrix);
   Output.mPosition = mul(Output.mPosition,gProjectionMatrix);
   
   return Output;
}
   

float4 PS() : COLOR
{
   return (gColor);
}
//--------------------------------------------------------------//
// Technique Section for ColorShader
//--------------------------------------------------------------//
technique ColorShader
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

