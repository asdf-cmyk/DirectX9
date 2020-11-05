float4x4 gWorldMatrix : World ;
float4x4 gViewMatrix : View ;
float4x4 gProjectionMatrix : Projection ;
float4   gWorldLightPosition = float4( 500.00, 500.00, -500.00, 1.00 ) ;
float4   gWorldCameraPosition : ViewPosition ;

struct VS_INPUT 
{
   float4 mPosition : POSITION0;
   float3 mNormal   : NORMAL ;
   float2 mUV       : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION0;
   float2 mUV       : TEXCOORD0;
   float3 mDiffuse  : TEXCOORD1 ;
   float3 mViewDir  : TEXCOORD2 ;
   float3 mReflection : TEXCOORD3;
};

VS_OUTPUT VS( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul( Input.mPosition, gWorldMatrix );
   float3 lightDir = Output.mPosition.xyz - gWorldLightPosition.xyz;
   lightDir = normalize(lightDir);
   
   float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir ;
   
   Output.mPosition = mul( Output.mPosition, gViewMatrix );
   Output.mPosition = mul( Output.mPosition, gProjectionMatrix );
   
   float3 worldNormal = mul(Input.mNormal, (float3x3)gWorldMatrix);
   worldNormal = normalize(worldNormal);
   
   Output.mDiffuse = dot(-lightDir, worldNormal);
   Output.mReflection = reflect(lightDir, worldNormal) ;
   
   Output.mUV = Input.mUV ;
   
   return (Output) ;
   
}


struct PS_INPUT
{
   float2 mUV      : TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir : TEXCOORD2;
   float3 mReflection : TEXCOORD3;
};

texture DiffuseMap_Tex1;
sampler2D DiffuseSampler1 = sampler_state
{
	Texture = (DiffuseMap_Tex1);
};

texture DiffuseMap_Tex2;
sampler2D DiffuseSampler2 = sampler_state
{
	Texture = (DiffuseMap_Tex2);
};

texture AlphaMap_Tex;
sampler2D AlphaSampler = sampler_state
{
	Texture = (AlphaMap_Tex);
};

float3 gLightColor = float3(0.70, 0.70, 1.00);
float3 fogTest;

float4 PS(PS_INPUT Input) : COLOR0
{   
   float4 albedo1 = tex2D(DiffuseSampler1, Input.mUV);
   float4 albedo2 = tex2D(DiffuseSampler2, Input.mUV);
   float4 alpha = tex2D(AlphaSampler, Input.mUV);

   float3 diffuse1 = (albedo1 * alpha);
   float3 diffuse2 = (albedo2 * (1-alpha));
   float3 diffuse = gLightColor * (diffuse1 + diffuse2);

   float3 reflection = normalize(Input.mReflection);
   float3 viewDir = normalize(Input.mViewDir);
   
   float3 specular = 0;
   if(diffuse.x > 0)
   {
      specular = saturate(dot(reflection, -viewDir));
      specular = pow(specular, 20.0f);
      
      float4 specularIntensity = tex2D(AlphaSampler, Input.mUV);
      specular *= specularIntensity.rgb * gLightColor ;
   }
   
   float3 ambient = float3(0.1f, 0.1f, 0.1f);
   
   return float4( ambient + diffuse + specular, 1.0f ) ; 
}
//--------------------------------------------------------------//
// Technique Section for Splatting
//--------------------------------------------------------------//
technique Splatting
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

