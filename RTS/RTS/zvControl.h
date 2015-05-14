#ifndef ZVSTEROWANIE_H
#define ZVSTEROWANIE_H
#include "zvGUI.h"
#include "zvCamera.h"
#include "zvGame.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class Control: public IEventReceiver{
public:
	struct SMouseState{
		position2di Position;
		bool LeftButtonDown;
		bool LeftButtonPressed;
		float wheel;
		SMouseState() : LeftButtonDown(false),LeftButtonPressed(false),wheel(0) {
		}
	} MouseState;

	Control(void);
	void cleanPressed(void);
	virtual bool OnEvent(const SEvent & event);
	virtual bool OnKeyUp(EKEY_CODE key);

	// Sprawdza czy klawisz (klucz) zosta³ u¿yty
	virtual bool IsKeyDown( EKEY_CODE keyCode ) const{
		return KeyIsDown[ keyCode ];
	}
	virtual bool IsMouseDown( ) const{
		return MouseState.LeftButtonDown;
	}
	virtual bool IsMousePressed( ) const{
		return MouseState.LeftButtonPressed;
	}
	virtual bool IsKeyPressed( EKEY_CODE keyCode ) const{
		return KeyIsPressed[ keyCode ];
	}
	virtual int IsKeyDownNum() const{
		for(int i='0';i<='9';i++){
			if(KeyIsDown[i]==true){return i-'0';}
		}
		return -1;
	}
	float getWheelState();
	int getMouseX();
	int getMouseY();
	int control(IrrlichtDevice * device,f32 frameDeltaTime,ListObject*allObiekt, MainGUI * mainGUI);
private:
	// U¿ywamy by zgromadziæ aktualny stan ka¿dego klawisza (klucza)
	bool KeyIsDown[ KEY_KEY_CODES_COUNT ];
	bool KeyIsPressed[ KEY_KEY_CODES_COUNT ];
	bool flagaKeyIsPressed;
	bool KeyIsDownTemp[ KEY_KEY_CODES_COUNT ];

};


#endif

