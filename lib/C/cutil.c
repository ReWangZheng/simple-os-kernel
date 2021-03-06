#include "cutil.h"
#include "type.h"
//得到光标
Cursor GetCursor(){
    Cursor cursor;
    u16 cursors = getcursor();
    cursor.x = cursors % 80;
    cursor.y = cursors / 80;
    return cursor;
}
//连接两个字
u16 u8_and_u8(u8 high,u8 low){
    u16 res = ((u16)high<<8)|((u16)low);
    return res;
}
//连接两个16位字
u32 u16_and_u16(u16 high,u16 low){
    u32 res = ((u32)high<<16)|((u32)low);
    return res;
}

//数字转字符 10进制
char * itoc(char *str,int number){
    char numberchar[]={'0','1','2','3','4','5','6','7','8','9'};
    int i=0;
    int yushu =0;
    int len=0;
    int temp = number;
    do
    {
        temp /= 10; //10 1 0
        len++;
    } while (temp > 0);
    str[len]=0;
    do
    {
        yushu =number % 10;
        number /= 10;
        str[--len]=numberchar[yushu];
    } while (number > 0);
    return str;
}
//数字转字符 16进制
char * itoh(char *str,int number){
    char numberchar[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    int i=0;
    int yushu =0;
    int len=2;
    int temp = number;
    do
    {
        temp /= 16; //10 1 0
        len++;
    } while (temp > 0);
    str[len]=0;
    do
    {
        yushu =number % 16;
        number /= 16;
        str[--len]=numberchar[yushu];
    } while (number > 0);
    str[0] = '0';
    str[1] = 'x';
    return str;
}
//清屏，并且设置光标在0,0
void clean_screen(){
    clear();
    SetCursor(0,0);
}
// 打印字符串
void show_str_format(int x,int y,char *str,...){
    u32 * paragram = &str;
    u16 *display = 0xb8000;
    int i = 0;
    int cursor = 0;
    int state = 0;
    display = display + y*80 + x;
    char temp[30];
    while(str[i]!=0){
        if(str[i]=='%' && str[i+1] == 'd'){
            //itoa(*(++paragram),ttt,10);
            itoc(temp,*(++paragram));
            for(int j =0;j<30;j++){
                if(temp[j]==0){
                    break;
                }else
                {
                    *(display + cursor) = u8_and_u8(0x07,temp[j]); 
                    cursor++;        
                }
            }
            i+=2;
        }else if(str[i]=='%' && str[i+1] == 'x'){
            itoh(temp,*(++paragram));
            for(int j =0;j<30;j++){
                if(temp[j]==0){
                    break;
                }else
                {
                    *(display + cursor) = u8_and_u8(0x07,temp[j]); 
                    cursor++;        
                }
            }
            i+=2;
        }else if(str[i]=='%' && str[i+1] == 's'){
            paragram++;
            char * s = (*paragram);
            for(int j =0;j<30;j++){
                if(s[j]==0){
                    break;
                }else
                {
                    *(display + cursor) = u8_and_u8(0x07,s[j]); 
                    cursor++;        
                }
            }
            i+=2;

        }
        else
        {
            *(display + cursor) = u8_and_u8(0x07,str[i]); 
            i++;
            cursor++;
        }
    }     
}