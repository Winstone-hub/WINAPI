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
* ��� ������ [FMOD Windows ����] �ٿ�ε�.
*   �̸� ��!! Ȯ�� �Ұ�! �� ����ؼ� �ٸ��� �ٿ�޾Ƽ� ��ġ�ϸ� �ȵ�.
* 
* �ַ��Ž���� -> ������Ʈ ��Ŭ�� -> �Ӽ� -> VC++ -> �Ϲ� -> ���Ե��丮 ��μ���
* C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\inc
* 
* �ַ��Ž���� -> ������Ʈ ��Ŭ�� -> �Ӽ� -> VC++ -> �Ϲ� -> ���̺귯�� ���丮 ��μ���
* C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\lib\x86
* 
* �ַ��Ž���� -> ������Ʈ ��Ŭ�� -> �Ӽ� -> ��Ŀ -> �Է� -> �߰����Ӽ� -> ���̺귯������ �Է�
* ���ϸ� : fmod_vc.lib
* 
* C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\lib\x86
* ���� ��ο� �ִ� ���� �� fmod.dll ������ ������Ʈ ��ť��Ʈ������ �����ϱ�.
* 
***********************************************/