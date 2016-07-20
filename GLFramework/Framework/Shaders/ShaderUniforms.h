//
//  ShaderUniforms.h
//  GLFramework
//
//  Created by Peter Kennedy on 7/19/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef GLFramework_ShaderUniforms_h
#define GLFramework_ShaderUniforms_h

// Positioning
static const char* WVP_LOCATION = "gWVP";
static const char* WORLD_LOCATION = "gWorld";
static const char* EYE_WORLD_POS_LOCATION = "gEyeWorldPos";

// PBR
static const char* ROUGHNESS_LOCATION = "gRoughness";
static const char* LINEAR_ROUGHNESS_LOCATION ="gLinearRoughness";
static const char* METAL_MASK_LOCATION ="gMetalMask";
static const char* REFLECTIVITY_LOCATION = "gReflectivity";

// Phong
static const char* MAT_SPECULAR_INTENSITY_LOCATION = "gMatSpecularIntensity";
static const char* MAT_SPECULAR_POWER_LOCATION = "gMatSpecularPower";


#endif
