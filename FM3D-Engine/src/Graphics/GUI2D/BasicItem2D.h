#pragma once
#include <Engine.h>

namespace ENGINE_NAME {
	class ENGINE_DLL BasicItem2D {

	public:

		enum AUTODOCK
		{
			VERTICAL_TOP,
			VERTICAL_BOTTOM,
			VERTICAL_STRETCH,
			VERTICAL_CENTER,

			HORIZONTAL_TOP,
			HORIZONTAL_BOTTOM,
			HORIZONTAL_STRETCH,
			HORIZONTAL_CENTER
		};
		
	protected:
		Quad m_box;		
						//4 Clickcheck
		Vector2f ccresult;
						//visibility 
		float visquad;
		float visfloat;

	public:

	#pragma region GET
		inline uint	GetColor() { return m_box.GetColor(); }
		inline Vector3f GetKoords() { return m_box.GetPos0(); }
		inline 		float GetKoordX() { return m_box.GetPos0().x; }
		inline		float GetKoordY() { return m_box.GetPos0().y; }
 		inline float GetZ() { return m_box.GetPos0().z; }
		inline Vector3f GetSize() { return Vector3f(m_box.GetPos1().x - m_box.GetPos0().x, m_box.GetPos1().y - m_box.GetPos0().y); }
		inline 		float GetSizeX() { return m_box.GetPos1().x - m_box.GetPos0().x; }
		inline		float GetSizeY() { return m_box.GetPos1().y - m_box.GetPos0().y; }
		inline Texture *GetTexture() { return m_box.GetTexture(); }

		inline Quad *GetBoxAdress() { return &m_box; }
	#pragma endregion


	#pragma region SET

		inline void SetColor(uint p_color) { m_box.SetColor(p_color); }
		inline void SetZ(float p_z) { m_box.SetZ(p_z); }
		inline void SetKoords(float p_koordx, float p_koordy) { m_box.SetPosition0(p_koordx, p_koordy, GetZ()); m_box.SetPosition1( Vector2f(p_koordx + GetSize().x, p_koordy + GetSize().y)); }
		inline void SetSize(float p_sizex, float p_sizey) {}
		inline void SetTexture(Texture *p_texture) { m_box.SetTexture(p_texture); }


	#pragma endregion

		bool Click(int keyID);	//done
		void AutoSize();		//done
		void AutoDock();		

		void VTop();
		void VBottom();
		void VStretch();
		void VCenter();

		void HTop();
		void HBottom();
		void HStretch();
		void HCenter();

		void PicVisibility(float);
		void TextVisibility(float);
		bool ccRectangle();
		bool ccEllipse();
		bool Render();
		bool Update();


	};
}