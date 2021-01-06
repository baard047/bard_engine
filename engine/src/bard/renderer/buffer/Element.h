/*
 * \file Element.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 18:46
 */

#pragma once
#include <cstdint>
#include <utility>
#include <bard/core/Base.h>

namespace bard
{

enum class ShaderDataType : uint_least8_t
{
    None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

struct BufferElement
{
    std::string name;
    ShaderDataType type = ShaderDataType::None;
    uint32_t size = 0;
    size_t offset = 0;
    bool normalized = false;

    BufferElement() = default;

    BufferElement( ShaderDataType type, std::string name, bool normalized = false )
            : name( std::move( name ) ),
              type( type ),
              size( shaderDataTypeSize( type ) ),
              offset( 0 ),
              normalized( normalized )
    {
    }

    inline uint32_t getComponentCount() const
    {
        switch ( type )
        {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 3; // 3* float3
            case ShaderDataType::Mat4:    return 4; // 4* float4
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Bool:    return 1;
            case ShaderDataType::None:    break;
        }

        BARD_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

private:
    uint32_t shaderDataTypeSize( ShaderDataType _type )
    {
        switch ( _type )
        {
            case ShaderDataType::Float:    return sizeof( float );
            case ShaderDataType::Float2:   return sizeof( float ) * 2;
            case ShaderDataType::Float3:   return sizeof( float ) * 3;
            case ShaderDataType::Float4:   return sizeof( float ) * 4;
            case ShaderDataType::Mat3:     return sizeof( float ) * 3 * 3;
            case ShaderDataType::Mat4:     return sizeof( float ) * 4 * 4;
            case ShaderDataType::Int:      return sizeof( int );
            case ShaderDataType::Int2:     return sizeof( int ) * 2;
            case ShaderDataType::Int3:     return sizeof( int ) * 3;
            case ShaderDataType::Int4:     return sizeof( int ) * 4;
            case ShaderDataType::Bool:     return sizeof( bool );
            case ShaderDataType::None:     break;
        }

        BARD_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
};

}