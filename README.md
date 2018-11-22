Базовый класс Thread и на его основе таймер

Пример использования:

class ActionTimer :public Timer {
public:
	ActionTimer() :Timer(16) {}; //16msec
	void TFunction(std::clock_t delta) {
		OnTimer(delta);
	};
};

void OnTimer(std::clock_t delta){
   ...
}

ActionTimer actiontimer;

void main(void){
    std::thread actionthread = actiontimer.Start();
    ...
    actiontimer.Stop();
	  actionthread.join();
}
