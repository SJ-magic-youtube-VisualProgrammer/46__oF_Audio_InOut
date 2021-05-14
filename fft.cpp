/************************************************************
************************************************************/
#include "fft.h"

/************************************************************
************************************************************/

/******************************
******************************/
FFT::FFT()
{
}

/******************************
******************************/
FFT::~FFT()
{
}

/******************************
******************************/
void FFT::threadedFunction()
{
	while(isThreadRunning()) {
		lock();
		
		unlock();
		
		sleep(THREAD_SLEEP_MS);
	}
}

/******************************
******************************/
void FFT::setup(int AUDIO_BUF_SIZE)
{
	/********************
	■std::vectorのresizeとassignの違い (C++)
		https://minus9d.hatenablog.com/entry/2021/02/07/175159
	********************/
	vol_l.assign(AUDIO_BUF_SIZE, 0.0);
	vol_r.assign(AUDIO_BUF_SIZE, 0.0);
}

/******************************
******************************/
void FFT::update()
{
}

/******************************
******************************/
void FFT::draw()
{
}

/******************************
******************************/
void FFT::SetVol(ofSoundBuffer & buffer)
{
	lock();
		
		if( (vol_l.size() < buffer.getNumFrames()) || (vol_r.size() < buffer.getNumFrames()) ){
			printf("size of vol vector not enough\n");
			fflush(stdout);
		}else{
			for (size_t i = 0; i < buffer.getNumFrames(); i++){
				vol_l[i] = buffer[i*2 + 0];
				vol_r[i] = buffer[i*2 + 1];
			}
		}
	
	unlock();
}

/******************************
******************************/
void FFT::GetVol(ofSoundBuffer & buffer, bool b_EnableAudioOut)
{
	lock();
	
		if( (vol_l.size() < buffer.getNumFrames()) || (vol_r.size() < buffer.getNumFrames()) ){
			printf("size of vol vector not enough\n");
			fflush(stdout);
		}else{
			for (size_t i = 0; i < buffer.getNumFrames(); i++){
				if(b_EnableAudioOut){
					buffer[i*2 + 0]	= vol_l[i];
					buffer[i*2 + 1]	= vol_r[i];
				}else{
					buffer[i*2 + 0]	= 0;
					buffer[i*2 + 1]	= 0;
				}
			}
		}
	
	unlock();

}
