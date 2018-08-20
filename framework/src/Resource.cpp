#include "stdafx.h"
#include "Resource.h"

/* Note: GFont: private to protected!  Add null constructor. */
GFontExt::GFontExt(RenderDevice* _rd, const std::string &filename, BinaryInput &b){
	renderDevice = _rd;
    debugAssert(renderDevice);
    debugAssertM(renderDevice->initialized(), 
        "You must call RenderDevice::init before constructing a GFont");
    debugAssertM(renderDevice->supportsTextureFormat(TextureFormat::A8),
        "This graphics card does not support the GL_ALPHA8 texture format used by GFont.");
    debugAssertGLOk();

    int ver = b.readInt32();
    debugAssertM(ver == 1, "Can't read font files other than version 1");
    (void)ver;

    // Read the widths
    for (int c = 0; c < 128; ++c) {
        subWidth[c] = b.readUInt16();
    }

    baseline = b.readUInt16();
    int texWidth = b.readUInt16();
    charWidth  = texWidth / 16;
    charHeight = texWidth / 16;

    // The input may not be a power of 2
    int width  = ceilPow2(charWidth * 16);
    int height = ceilPow2(charHeight * 8);
 
    // Create a texture
    const uint8* ptr = ((uint8*)b.getCArray()) + b.getPosition();
    texture = 
        Texture::fromMemory(filename, &ptr,
            TextureFormat::A8, width, height, 1, TextureFormat::A8, 
            Texture::CLAMP, Texture::TRILINEAR_MIPMAP, Texture::DIM_2D);
}

GFontRef GFontExt::fromMemory(RenderDevice* _rd, const std::string &filename, 
						  const uint8 *bytes, const int size){	

	BinaryInput b(bytes, size, G3D_LITTLE_ENDIAN, true, true);						  
	return new GFontExt(_rd, filename, b);
						  
}