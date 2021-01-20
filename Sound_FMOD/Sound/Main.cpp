#include "MainUpdate.h"




int main(void)
{
    MainUpdate Main;
    Main.Initialize();

    DWORD dwTime = GetTickCount64();

    while (true)
    {
        if (dwTime < GetTickCount64())
        {
            dwTime = GetTickCount64();

            Main.Progress();
            Main.Render();
        }
    }

    return 0;
}



/***********************************************
*     **  FMOD  **
*  https://www.fmod.com/download
* 경로 접속후 [FMOD Windows 엔진] 다운로드.
*   이름 꼭!! 확인 할것! 다 비슷해서 다른거 다운받아서 설치하면 안됨.
* 
* 솔루션탐색기 -> 프로젝트 우클릭 -> 속성 -> VC++ -> 일반 -> 포함디렉토리 경로설정
* C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\inc
* 
* 솔루션탐색기 -> 프로젝트 우클릭 -> 속성 -> VC++ -> 일반 -> 라이브러리 디렉토리 경로설정
* C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\lib\x86
* 
* 솔루션탐색기 -> 프로젝트 우클릭 -> 속성 -> 링커 -> 입력 -> 추가종속석 -> 라이브러리파일 입력
* 파일명 : fmod_vc.lib
* 
* C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\lib\x86
* 다행 경로에 있는 파일 중 fmod.dll 파일을 프로젝트 도큐먼트폴더에 복사하기.
* 
***********************************************/