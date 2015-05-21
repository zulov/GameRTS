#include "zvControl.h"

bool Control::OnEvent( const SEvent & event){
	if( event.EventType == irr::EET_KEY_INPUT_EVENT ){
		KeyIsDownTemp[event.KeyInput.Key]=KeyIsDown[event.KeyInput.Key];
		KeyIsDown[ event.KeyInput.Key ] = event.KeyInput.PressedDown;
	}
	if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == false)
	{
		if ( OnKeyUp(event.KeyInput.Key) )
			return true;
	}
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			MouseState.LeftButtonDown = true;
			MouseState.LeftButtonPressed = false;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			MouseState.LeftButtonPressed = true;
			MouseState.LeftButtonDown = false;
			break;
		case EMIE_MOUSE_MOVED:
			MouseState.Position.X = event.MouseInput.X;
			MouseState.Position.Y = event.MouseInput.Y;
			break;
		case EMIE_MOUSE_WHEEL:
			MouseState.wheel=event.MouseInput.Wheel;
			break;
		default:
			//MouseState.
			break;
		}
	}
	return false;
}

int Control::getMouseX(){
	return MouseState.Position.X;
}
int Control::getMouseY(){
	return MouseState.Position.Y;
}

Control::Control(){
	for( u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i ){
		KeyIsDown[i] = false;
		KeyIsPressed[i] = false;
		KeyIsDownTemp[i] = false;
	}
	flagaKeyIsPressed=false;
}

void Control::cleanPressed(void){
	//if (flagaKeyIsPressed==true){
	for( u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i ){
		KeyIsPressed[i] = false;
	}
	flagaKeyIsPressed=false;
	//	}
	MouseState.LeftButtonPressed=false;
	MouseState.wheel=0;
	//dopisac jescze jedn stan ze zdarzenie jest po kliknieciu

}

float Control::getWheelState(){
	return MouseState.wheel;
}

bool Control::OnKeyUp(irr::EKEY_CODE key){
	KeyIsPressed[key]=true;
	flagaKeyIsPressed=true;
	return true;
}

int Control::control(f32 frameDeltaTime,MainGUI * mainGUI){
	float moveFactor=frameDeltaTime;
	if( getWheelState()!=0 ){
		Game::getCameraManager()->moveActiveCamera(Vector(0,-moveFactor*getWheelState(),0));
		Game::getCameraManager()->rotateActiveCamera(Vector(-moveFactor*getWheelState(),0,0));
	}
	if( this->IsKeyDown( irr::KEY_PLUS ) ){
		Game::getCameraManager()->moveActiveCamera(Vector(0,moveFactor,0));
	}
	if( this->IsKeyDown( irr::KEY_MINUS ) ){
		Game::getCameraManager()->moveActiveCamera(Vector(0,-moveFactor,0));
	}

	if( this->IsKeyDown( irr::KEY_KEY_W ) || this->IsKeyDown( irr::KEY_UP ) ){
		vector3df rot=Game::getCameraManager()->getActiveCamera()->getCameraNode()->getRotation();
		float rad_Y=-((rot.Y-90)*3.14)/180.0f;
		Game::getCameraManager()->moveActiveCamera(Vector(moveFactor*cos(rad_Y),0,moveFactor*sin(rad_Y)));
	}

	if( this->IsKeyDown( irr::KEY_KEY_S ) || this->IsKeyDown( irr::KEY_DOWN)  )	{
		vector3df rot=Game::getCameraManager()->getActiveCamera()->getCameraNode()->getRotation(); 
		double rad_Y=-((rot.Y-90)*3.14)/180.0f;
		Game::getCameraManager()->moveActiveCamera(Vector(-moveFactor*cos(rad_Y),0,-moveFactor*sin(rad_Y)));
	}

	if( this->IsKeyDown( irr::KEY_KEY_A ) || this->IsKeyDown( irr::KEY_LEFT) ){
		vector3df rot=Game::getCameraManager()->getActiveCamera()->getCameraNode()->getRotation();
		float rad_Y=-(rot.Y*3.14f)/180.0f;
		Game::getCameraManager()->moveActiveCamera(Vector(-moveFactor*cos(rad_Y),0,-moveFactor*sin(rad_Y)));
	}

	if( this->IsKeyDown( irr::KEY_KEY_D ) || this->IsKeyDown( irr::KEY_RIGHT)  ){
		vector3df rot=Game::getCameraManager()->getActiveCamera()->getCameraNode()->getRotation();
		float rad_Y=-(rot.Y*3.14f)/180.0f;
		Game::getCameraManager()->moveActiveCamera(Vector(moveFactor*cos(rad_Y),0,moveFactor*sin(rad_Y)));
	}

	if( this->IsKeyDown( irr::KEY_KEY_Q ) ){
		Game::getCameraManager()->rotateActiveCamera(Vector(0,moveFactor,0));
	}


	if( this->IsKeyPressed( irr::KEY_SPACE ) ){
		Game::createUnit(Vector(std::rand()%20,20,std::rand()%20));
	}

	if( this->IsKeyPressed( irr::KEY_KEY_I) ){//item

	}else if( this->IsKeyPressed( irr::KEY_OEM_3 ) ){//console
		if(mainGUI->allowedType==5){mainGUI->allowedType=0;}
		else{mainGUI->allowedType=5;}
	}

	if( this->IsKeyPressed( irr::KEY_F11 ) ){
		Game::getCameraManager()->prevCamera();
	}
	else if( this->IsKeyPressed( irr::KEY_F12 ) ){
		Game::getCameraManager()->nextCamera();
	}


	if( this->IsMousePressed() )
	{

	}
	else if( this->IsKeyDown( irr::KEY_ESCAPE ) )
	{
		Game::device->drop();
		return -1;
	}
	this->cleanPressed();
}
