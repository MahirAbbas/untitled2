#pragma once

#include <string>
#include <d3d9helper.h>

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

class Model {
private:
	float r, g, b;
	std::string text;
	LPDIRECT3DTEXTURE9 texture = nullptr;
	int width = 400, height = 400;

public:
	Model() {
		r = g = b = 0.0f;
		text = "";

		//Create texture
		if (g_pd3dDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture, NULL) < 0)
			return;

		UpdateTexture();

	}

	void SetRed(const float rv) { r = rv; Update(); }
	void SetGreen(const float gv) { g = gv; Update(); }
	void SetBlue(const float bv) { b = bv; Update(); }

	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
	int GetTextureWidth() { return width; }
	int GetTextureHeight() { return height; }

	const std::string GetText() { return text; }

	void Update() {
		UpdateText();
		UpdateTexture();
	}

private:
	void UpdateText() {
		text = "red:=" + std::to_string(r) + " green:=" + std::to_string(g) + " blue:=" + std::to_string(b);
	}

	void UpdateTexture() {
		D3DLOCKED_RECT pLockedRect;
		if (texture->LockRect(0, &pLockedRect, NULL, 0) != D3D_OK)
			return;
		unsigned char B = (unsigned char)255 * b, R = (unsigned char)255 * r, G = (unsigned char)255 * g;
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++) {
				*(((unsigned char*)(pLockedRect.pBits)) + y * pLockedRect.Pitch + x * 4) = (unsigned char)B; //B
				*(((unsigned char*)(pLockedRect.pBits)) + y * pLockedRect.Pitch + x * 4 + 1) = (unsigned char)G; //G
				*(((unsigned char*)(pLockedRect.pBits)) + y * pLockedRect.Pitch + x * 4 + 2) = (unsigned char)R; //R
				*(((unsigned char*)(pLockedRect.pBits)) + y * pLockedRect.Pitch + x * 4 + 3) = (unsigned char)255; //A
			}
		texture->UnlockRect(0);
	}

};