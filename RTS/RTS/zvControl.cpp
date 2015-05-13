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
	if (flagaKeyIsPressed==true){
		for( u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i ){
			KeyIsPressed[i] = false;
		}
		flagaKeyIsPressed=false;
	}
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

int Control::control(IrrlichtDevice * device,f32 frameDeltaTime,ListObject*allObiekt, 
					 MainGUI * mainGUI,CameraManager * cameraManager){
	float moveFactor=10*frameDeltaTime;
	if( getWheelState()!=0 ){
		cameraManager->moveActiveCamera(Vector(0,-moveFactor*getWheelState()*20,0));
	}

	if( this->IsKeyDown( irr::KEY_KEY_W ) || this->IsKeyDown( irr::KEY_UP ) )
	{
		cameraManager->moveActiveCamera(Vector(0,0,moveFactor));
	}
	if( this->IsKeyDown( irr::KEY_KEY_S ) || this->IsKeyDown( irr::KEY_DOWN)  )
	{
		cameraManager->moveActiveCamera(Vector(0,0,-moveFactor));
	}
	if( this->IsKeyDown( irr::KEY_KEY_A ) || this->IsKeyDown( irr::KEY_LEFT) )
	{
		cameraManager->moveActiveCamera(Vector(-moveFactor,0,0));
	}
	if( this->IsKeyDown( irr::KEY_KEY_D ) || this->IsKeyDown( irr::KEY_RIGHT)  )
	{
		cameraManager->moveActiveCamera(Vector(moveFactor,0,0));
	}
	if( this->IsKeyDown( irr::KEY_KEY_Q ) )
	{
		
	}
	if( this->IsKeyDown( irr::KEY_KEY_E ) )
	{

	}
	if( this->IsKeyDown( irr::KEY_KEY_C ) )
	{
		
	}
	if( this->IsKeyDown( irr::KEY_KEY_Z ) )
	{
	
	}
	if( this->IsKeyPressed( irr::KEY_SPACE ) )
	{
		Game::createUnit(Vector(std::rand()%50,2000,std::rand()%50));
	}
	if( this->IsKeyPressed( irr::KEY_KEY_I) )
	{//item
		
	}
	else if( this->IsKeyPressed( irr::KEY_KEY_L) )
	{//leksykon wiedzy

	}
	else if( this->IsKeyPressed( irr::KEY_KEY_M) )
	{//mapa
		
	}
	else if( this->IsKeyPressed( irr::KEY_KEY_U) )
	{//skills+staty
		
	}
	else if( this->IsKeyPressed( irr::KEY_OEM_3 ) )
	{//mapa
		//if(mainGUI->allowedType==5){mainGUI->allowedType=0;}
		//else{mainGUI->allowedType=5;}
	}
	if( this->IsKeyPressed( irr::KEY_F11 ) )
	{
		cameraManager->prevCamera();
	}
	else if( this->IsKeyPressed( irr::KEY_F12 ) ){
		cameraManager->nextCamera();
	}
	if( this->IsMousePressed() )
	{
		
	}
	else if( this->IsKeyDown( irr::KEY_ESCAPE ) )
	{
		device->drop();
		return -1;
	}
	this->cleanPressed();
}
